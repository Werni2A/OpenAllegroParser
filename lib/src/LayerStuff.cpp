
#include "../include/LayerStuff.hpp"


// @todo there is some weird dynamic behavior when, BEGIN_LAYER is used
//       or maybe it is because all other layers are already used and there
//       is not enough space in the data structure that BEGIN_LAYER can also
//       be stored. Therefore some new structure is appended?

const std::vector<PadTypeLayer> layerLst1 = {
    // @todo figure out. This one is weird.
    //       Maybe its not a pad but some other info?
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index  0

    { Type::ANTIPAD_PAD, Layer::DEFAULT_INTERNAL       }, // Index  1
    { Type::THERMAL_PAD, Layer::DEFAULT_INTERNAL       }, // Index  2
    { Type::REGULAR_PAD, Layer::DEFAULT_INTERNAL       }, // Index  3
    { Type::KEEPOUT,     Layer::DEFAULT_INTERNAL       }, // Index  4

    { Type::REGULAR_PAD, Layer::BACKDRILL_START        }, // Index  5
    { Type::ANTIPAD_PAD, Layer::BACKDRILL_START        }, // Index  6
    { Type::KEEPOUT,     Layer::BACKDRILL_CLEARANCE    }, // Index  7
    { Type::ANTIPAD_PAD, Layer::BACKDRILL_CLEARANCE    }, // Index  8

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



const std::vector<PadTypeLayer> layerLst2 = {
    // @todo figure out. This one is weird.
    //       Maybe its not a pad but some other info?
    { Type::UNKNOWN,     Layer::UNKNOWN                }, // Index  0

    { Type::ANTIPAD_PAD, Layer::DEFAULT_INTERNAL       }, // Index  1
    { Type::THERMAL_PAD, Layer::DEFAULT_INTERNAL       }, // Index  2
    { Type::REGULAR_PAD, Layer::DEFAULT_INTERNAL       }, // Index  3
    { Type::KEEPOUT,     Layer::DEFAULT_INTERNAL       }, // Index  4

    { Type::REGULAR_PAD, Layer::BACKDRILL_START        }, // Index  5
    { Type::ANTIPAD_PAD, Layer::BACKDRILL_START        }, // Index  6
    { Type::KEEPOUT,     Layer::BACKDRILL_CLEARANCE    }, // Index  7
    { Type::ANTIPAD_PAD, Layer::BACKDRILL_CLEARANCE    }, // Index  8

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

    { Type::ANTIPAD_PAD, Layer::BEGIN_LAYER            }, // Index 21
    { Type::THERMAL_PAD, Layer::BEGIN_LAYER            }, // Index 22
    { Type::REGULAR_PAD, Layer::BEGIN_LAYER            }, // Index 23
    { Type::KEEPOUT,     Layer::BEGIN_LAYER            }, // Index 24

    { Type::ANTIPAD_PAD, Layer::END_LAYER              }, // Index 25
    { Type::THERMAL_PAD, Layer::END_LAYER              }, // Index 26
    { Type::REGULAR_PAD, Layer::END_LAYER              }, // Index 27
    { Type::KEEPOUT,     Layer::END_LAYER              }  // Index 28
};