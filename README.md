
# OpenAllegroParser

Purpose of this project is to provide a C++17 library for parsing [Cadence](https://en.wikipedia.org/wiki/Cadence_Design_Systems)'s Allegro binary file formats. This library can be linked to other software for reading/modifying?/writing? Allegro binary files and reading?/writing? XML files.

**See also the complementary project [OpenOrCadParser](https://github.com/Werni2A/OpenOrCadParser).**

The focus lies on

- `*.brd` board database,
- `*.mdd` module definition,
- `*.dra` drawing,
- `*.psm` package symbol,
- `*.ssm` shape symbol,
- `*.fsm` flash symbol,
- `*.osm` format symbol,
- `*.bsm` mechanical symbol, and
- `*.pad` padstack.

See [OrCAD Allegro Files Extension and their Contents](https://vjguptapcb.blogspot.com/2020/08/orcad-allegro-files-extension-and-their.html) or [Cadence Allegro file Extensions and what they contain](https://kumargs-pcb-design.blogspot.com/2009/01/cadence-allegro-file-extensions-and.html) for more information on the file purpose.

---

# Documentation

1. `*.brd` Board Database
2. `*.mdd` Module Definition
3. `*.dra` Drawing
4. `*.psm` Package Symbol
5. `*.ssm` Shape Symbol
6. `*.fsm` Flash Symbol
7. `*.osm` Format Symbol
8. `*.bsm` Mechanical Symbol
9. [`*.pad` Padstack](doc/pad.md)

---

# Current State &mdash; March 2022

- Working on padstack parser.
- Setting up padstack unit tests.

---

# Build

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Dependencies

- Compiler with C++17 Support
- [CMake](https://cmake.org/) >= 3.5
- [Boost](https://www.boost.org/) - Program Options
- [fmt](https://github.com/fmtlib/fmt)
- [libzippp](https://github.com/ctabin/libzippp)
- [Magic Enum](https://github.com/Neargye/magic_enum)
- [Nameof](https://github.com/Neargye/magic_enum)
- [TinyXML2](https://github.com/leethomason/tinyxml2)
- [vcpkg](https://vcpkg.io/en/index.html)

---

# Usage

**I tested with some pads created with version `17.4-2019 S019 (3959056) [7/8/2021]` which works mostly fine. In case you find pads that do not work - with the specified version - please create an issue and append your `*.pad` as well as `*.pxml` files.**

**Note:**

Pad files have some structures with dynamic size where I haven't found a way to calculate those sizes. A workaround to this issue is to brute force all combinations and see when the parser runs without errors. Brute force sounds like a tedious job to do. However, it's quite fast because the amount of possible combinations is relatively low.

Therefore, modify the path to your pad in `findUnknownParameterSet.py` and run it with `python3 findUnknownParameterSet.py`. Hopefully there is a parameter set found that works for your file, and you will see an output similar to the following.

```text
---------------------------------------------
------- Found valid Parameter Set -----------
---------------------------------------------

./build/OpenAllegroParser -i simple_example.pad --numUserLayers 5 --unknownFlag
```

Add the flag `-p` to the command from above and run it as `./build/OpenAllegroParser -i simple_example.pad --numUserLayers 5 --unknownFlag -p` and you will see a similar output with all the pad's information like the one below. At the beginning a lot of debug output is shown that might be not as interesting for you, as for me. Just scroll down to the more important pad information.

<details>
<summary>Click to expand</summary>

```text

./build/OpenAllegroParser -i simple_example.pad --numUserLayers 5 --unknownFlag -p

Opening file: "simple_example.pad"
File contains 5020 byte.
File found at 0x00000ed8: simple_example.zip

...

-----------------------------------------------
--------------- File Content ------------------
-----------------------------------------------
PadFile:
  swVersion = pad395907/8/2
  accuracy  = 1
  unit      = mils
  strIdxPadName       = 30 (SIMPLE_EXAMPLE)
  idxUnknown          = 31
  strIdxDrillToolSize = 32 (SIZE_XYZ)
  drillmethod     = ETCH
  holeType        = CIRCLE
  staggeredDrills = 0
  plated          = 1
  not_suppress_nc_internal_pads = 1
  isPolyVia       = 0
  padstackusage   = THRU_PIN
  drill_rows      = 1
  drill_columns   = 1
  lock_layer_span = 1
  offsetX         = 0
  offsetY         = 0
  clearance_columns = 1
  clearance_rows    = 2
  finished_size     = 4
  positivetolerance = 2
  negativetolerance = 1
  width             = 10
  height            = 20
  figure            = CROSS
  characters        = X
  back_drill_figure_width  = 0
  back_drill_figure_height = 0
  back_drill_figure        = NONE
  back_drill_characters    =
  counter_drill_diameter          = 0
  counter_drill_positivetolerance = 0
  counter_drill_negativetolerance = 0
  counterangle         = 0
  genericLayers:
    0: Pad:
      type   = 0
      layer  = 0
      figure = RECTANGLE
      offset = (0.020000;0.030000)
      width  = 0.100000
      height = 0.100000
    1: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    2: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    3: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    4: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    5: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    6: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    7: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    8: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    9: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    10: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    11: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    12: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    13: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    14: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    15: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    16: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    17: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    18: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    19: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    20: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    21: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    22: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
    23: Pad:
      type   = 0
      layer  = 0
      figure = CIRCLE
      offset = (0.020000;0.030000)
      width  = 0.100000
      height = 0.100000
    24: Pad:
      type   = 0
      layer  = 0
      figure = NONE
      offset = (0.000000;0.000000)
      width  = 0.000000
      height = 0.000000
  dateTime1         = Thu Dec 30 20:57:49 2021

  username          = domin
  dateTime2         = Thu Dec 30 20:57:49 2021

  dateTime3         = Thu Dec 30 20:57:49 2021

  dateTime4         = Thu Dec 30 20:57:49 2021

  dateTime5         = Thu Dec 30 20:57:49 2021

  dateTime6         = Thu Dec 30 20:57:49 2021


Closing file: "simple_example.pad"
```
</details>

</br>

```bash
./OpenAllegroParser --help
Allowed options:
  -h [ --help ]         produce help message
  -p [ --print ]        print file content to terminal
  -e [ --extract ]      extract files from within the binary
  -i [ --input ] arg    input file to parse
  -o [ --output ] arg   output path (required iff extract is set)
  --unknownFlag         activate some dynamic feature in the file
  --numUserLayers arg   number of user layers
  --additionalStr2 arg  number of additional strings in list

./OpenAllegroParser --input file.pad --extract --output out/
Opening file: file.pad
File contains 4960 byte.
File found at 0x00000abc: file.zip
Extract ZIP file: file.pad/file.zip
Extract from ZIP, 4200 Byte file: out/file.pad/Users/%USERNAME%/AppData/Local/Temp/#Taaaaaa00765.tmp
Closing file: file.pad
```

---

# Related Projects

[kicad-allegro](https://github.com/system76/kicad-allegro) (Rust based Allegro Extract (ASCII) to KiCad Converter and Viewer)

---

# How to Contribute?

There are different ways to help this project forward. Some are

- provide test files (manually created or automated via SKILL),
- help reverse engineering/documenting the file format, or
- implement some unit tests.

In case you don't have access to OrCAD PcbDesigner or Allegro you can get [Cadence Allegro Viewer](https://www.cadence.com/en_US/home/tools/pcb-design-and-analysis/allegro-downloads-start.html) free of charge.

---

# Cadence Terms and Conditions

[Terms and Conditions](https://www.cadence.com/content/dam/cadence-www/global/en_US/documents/terms-and-conditions/cadence-orcad.pdf)

[Terms of Use Agreement](https://www.cadence.com/en_US/home/terms-of-use-agreement.html)
