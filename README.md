
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

# Current State &mdash; October 2021

- Working on padstack parser.

---

# Build

```bash
mkdir build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Dependencies

- Compiler with C++17 Support
- [CMake](https://cmake.org/) >= 2.8.12
- [vcpkg](https://vcpkg.io/en/index.html)
- [Boost](https://www.boost.org/) - Program Options
- [libzippp](https://github.com/ctabin/libzippp)

---

# Usage

```bash
./OpenAllegroParser --help
Allowed options:
  -h [ --help ]         produce help message
  -e [ --extract ]      extract files from within the binary
  -i [ --input ] arg    input file to parse
  -o [ --output ] arg   output path (required iff extract is set)

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
