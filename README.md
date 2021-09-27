
# OpenAllegroParser

Purpose of this project is to provide an C++ library for parsing [Cadence](https://en.wikipedia.org/wiki/Cadence_Design_Systems)'s Allegro binary file formats. This library can be linked to other software for reading/modifying?/writing? Allegro binary files.

The focus lies on
- `*.brd` layout,
- `*.dra` symbol drawing,
- `*.mdd` module definition and
- `*.pad` padstacks.

Padstacks should be the smallest and simplest file format. I will start with this one and proceed to more complex ones. From a first glance at a padstack it does not look like it is somehow encrypted or compressed.
