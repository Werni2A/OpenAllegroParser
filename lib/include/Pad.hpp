#ifndef PAD_HPP
#define PAD_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include "Figure.hpp"
#include "General.hpp"
#include "LayerStuff.hpp"


class Pad
{
public:

    Pad(Type aType, Layer aLayer) :
        mType{aType}, mLayer{aLayer}, mFigure{Figure::NONE},
        mOffsetX{0}, mOffsetY(0), mWidth{0}, mHeight{0},
        mNsides{0u}, mCorner{0}, mSpecialCorners{0}
    { }

    void setType(Type aType);

    Type getType() const;


    void setLayer(Layer aLayer);

    Layer getLayer() const;


    void setFigure(uint32_t aFigure);

    void setFigure(Figure aFigure);

    Figure getFigure() const;


    void setOffsetX(int32_t aOffset);

    int32_t getOffsetX() const;

    double getOffsetXfp() const;


    void setOffsetY(int32_t aOffset);

    int32_t getOffsetY() const;

    double getOffsetYfp() const;


    std::string getOffsetStr() const;


    void setWidth(int32_t aWidth);

    int32_t getWidth() const;

    double getWidthFp() const;


    /**
     * @brief Set the Height object
     *
     * @param aHeight
     *
     * @warning setWidth needs to be called first!
     */
    void setHeight(int32_t aHeight);

    int32_t getHeight() const;

    double getHeightFp() const;


    void setNsides(uint32_t aNsides);

    uint32_t getNsides() const;


    void setCorner(int32_t aCorner);

    int32_t getCorner() const;

    double getCornerFp() const;


    void setSpecialCorners(uint16_t aSpecialCorners);

    bool isLowerLeftCornerSpecial() const;

    bool isLowerRightCornerSpecial() const;

    bool isUpperRightCornerSpecial() const;

    bool isUpperLeftCornerSpecial() const;

    std::string getShapeSymbolName() const;

private:

    Type  mType;
    Layer mLayer;

// @todo fix
public:
    std::string mUsrStr; // Name of layer, when it's user specific
private:

    Figure   mFigure;

    // The XML combines both of them in a
    // string with format "(mOffsetX;mOffsetY)",
    // where both offsets are represented as
    // floating point values with precision `accuracy`.
    int32_t mOffsetX;
    int32_t mOffsetY;

    // Depends on `figure`.
    // Some symmetrical figures like
    // `SQUARE`, `CIRCLE`, ...
    // have only one width or diameter specified,
    // then both values are equal.
    // For `DONUT` it's the outer diameter.
    int32_t mWidth;
    int32_t mHeight;

    // Depends on `figure`.
    // For `NSIDED_POLYGON` it's number of sides.
    // Otherwise it's 0.
    uint32_t mNsides;

    // Depends on `figure`.
    // For `ROUNDED_RECTANGLE` it's corner radius.
    // For `CHAMFERED_RECTANGLE` it's chamfered corner.
    // For `DONUT` it's the inner diameter.
    // Otherwise it's 0.
    int32_t mCorner;

    // Depends on `figure`.
    // For `ROUNDED_RECTANGLE` it specifies the rounded corners.
    // For `CHAMFERED_RECTANGLE` it specifies the chamfered corners.
    // Otherwise it's 0
    // It's a bit field for XML tags:
    // `ul` = upper left corner
    // `ur` = upper right corner
    // `ll` = Lower left corner
    // `lr` = lower right corner
    // Bit field specification:
    //  MSB 15 14 13 12 11 10  9  8 | 7  6  5  4  3  2  1  0 LSB
    //       0  0  0  0  0  0  0  0 | 0  0  0  0 ul ur lr ll
    uint16_t mSpecialCorners;

public: // @todo fix
    // Only set for Figure == SHAPE_SYMBOL
    uint32_t    mIdxShapeSymolNameStr;
    std::string mShapeSymbolNameStr; // @todo Retrieve this directly from mIdxShapeSymolNameStr
};


#include "General.hpp"


[[maybe_unused]]
static std::string to_string(const Pad& pad)
{
    std::string str;

    str += "Pad:" + newLine();
    str += indent(1) + "type   = " + to_string(pad.getType())  + newLine(); // @todo use shift operator

    if(pad.getType() == Type::USER_MASK)
    {
        str += indent(1) + "layer  = " + pad.mUsrStr+ newLine();
    }
    else
    {
        str += indent(1) + "layer  = " + to_string(pad.getLayer()) + newLine(); // @todo use shift operator
    }

    str += indent(1) + "figure = " + to_string(pad.getFigure())     + newLine();
    str += indent(1) + "offset = " + pad.getOffsetStr() + newLine();
    str += indent(1) + "width  = " + std::to_string(pad.getWidthFp())  + newLine();
    str += indent(1) + "height = " + std::to_string(pad.getHeightFp()) + newLine();

    if(pad.getFigure() == Figure::NSIDED_POLYGON)
    {
        str += indent(1) + "nsides = " + std::to_string(pad.getNsides()) + newLine();
    }

    if(pad.getFigure() == Figure::ROUNDED_RECTANGLE   ||
       pad.getFigure() == Figure::CHAMFERED_RECTANGLE ||
       pad.getFigure() == Figure::DONUT)
    {
        str += indent(1) + "corner = " + std::to_string(pad.getCornerFp()) + newLine();
    }

    if(pad.getFigure() == Figure::ROUNDED_RECTANGLE ||
       pad.getFigure() == Figure::CHAMFERED_RECTANGLE)
    {
        str += indent(1) + "ul   = " + std::to_string(pad.isUpperLeftCornerSpecial())  + newLine();
        str += indent(1) + "ur   = " + std::to_string(pad.isUpperRightCornerSpecial()) + newLine();
        str += indent(1) + "ll   = " + std::to_string(pad.isLowerLeftCornerSpecial())  + newLine();
        str += indent(1) + "lr   = " + std::to_string(pad.isLowerRightCornerSpecial()) + newLine();
    }

    if(pad.getFigure() == Figure::SHAPE_SYMBOL)
    {
        str += indent(1) + "mIdxShapeSymolNameStr = " + std::to_string(pad.mIdxShapeSymolNameStr) + " (" + pad.getShapeSymbolName() + ")" + newLine();
    }

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& os, const Pad& pad)
{
    os << to_string(pad);

    return os;
}


#endif // PAD_HPP