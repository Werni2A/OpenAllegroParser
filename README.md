
# OpenAllegroParser

Purpose of this project is to provide an C++ library for parsing [Cadence](https://en.wikipedia.org/wiki/Cadence_Design_Systems)'s Allegro binary file formats. This library can be linked to other software for reading/modifying?/writing? Allegro binary files.

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

Padstacks should be the smallest and simplest file format. I will start with this one and proceed to more complex ones. From a first glance at a padstack it does not look like it is somehow encrypted or compressed.

# How to Contribute?

There are different ways to help this project forward. Some are

- provide test files (manually created or automated via SKILL),
- help reverse engineering/documenting the file format, or
- implement some unit tests.

In case you don't have access to OrCAD PcbDesigner or Allegro you can get [Cadence Allegro Viewer](https://www.cadence.com/en_US/home/tools/pcb-design-and-analysis/allegro-downloads-start.html) free of charge.

# Cadence Terms and Conditions

[Terms and Conditions](https://www.cadence.com/content/dam/cadence-www/global/en_US/documents/terms-and-conditions/cadence-orcad.pdf)

[Terms of Use Agreement](https://www.cadence.com/en_US/home/terms-of-use-agreement.html)
