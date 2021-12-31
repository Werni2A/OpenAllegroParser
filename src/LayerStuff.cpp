
#include "LayerStuff.hpp"


std::vector<padTypeLayer> layerLst = {
    // @todo figure out. This one is weird.
    //       Maybe its not a pad but some other info?
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index  0

    { Type::ANTIPAD_PAD, Layer::DEFAULT_INTERNAL       }, // Index  1
    { Type::THERMAL_PAD, Layer::DEFAULT_INTERNAL       }, // Index  2
    { Type::REGULAR_PAD, Layer::DEFAULT_INTERNAL       }, // Index  3
    { Type::KEEPOUT,     Layer::DEFAULT_INTERNAL       }, // Index  4

    // @todo Probably Begin layer
    //       Maybe it must also be swapped with the upper INTERNAL layers
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index  5
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index  6
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index  7
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index  8

    { Type::REGULAR_PAD, Layer::BACKDRILL_SOLDERMASK   }, // Index  9

    { Type::REGULAR_PAD, Layer::TOP_COVERLAY_PAD       }, // Index 10
    { Type::REGULAR_PAD, Layer::BOTTOM_COVERLAY_PAD    }, // Index 11

    // @todo figure out
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index 12
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index 13

    { Type::REGULAR_PAD, Layer::TOP_SOLDER_MASK_PAD    }, // Index 14
    { Type::REGULAR_PAD, Layer::BOTTOM_SOLDER_MASK_PAD }, // Index 15

    { Type::REGULAR_PAD, Layer::TOP_PASTE_MASK_PAD     }, // Index 16
    { Type::REGULAR_PAD, Layer::BOTTOM_PASTE_MASK_PAD  }, // Index 17

    { Type::REGULAR_PAD, Layer::TOP_FILM_MASK_PAD      }, // Index 18
    { Type::REGULAR_PAD, Layer::BOTTOM_FILM_MASK_PAD   }, // Index 19

    { Type::KEEPOUT,     Layer::ADJACENT_KEEPOUT       }, // Index 20

    { Type::ANTIPAD_PAD, Layer::END_LAYER              }, // Index 21
    { Type::THERMAL_PAD, Layer::END_LAYER              }, // Index 22
    { Type::REGULAR_PAD, Layer::END_LAYER              }, // Index 23
    { Type::KEEPOUT,     Layer::END_LAYER              }  // Index 24
};