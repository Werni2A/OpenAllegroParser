#include <cmath>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include "General.hpp"
#include "Pad.hpp"


void Pad::setType(Type aType)
{
    mType = aType;
}


Type Pad::getType() const
{
    return mType;
}


void Pad::setLayer(Layer aLayer)
{
    mLayer = aLayer;
}


Layer Pad::getLayer() const
{
    return mLayer;
}


void Pad::setFigure(uint32_t aFigure)
{
    setFigure(ToFigure(aFigure));
}


void Pad::setFigure(Figure aFigure)
{
    // @todo check for validiy of Figure!
    mFigure = aFigure;
}


Figure Pad::getFigure() const
{
    return mFigure;
}


void Pad::setOffsetX(int32_t aOffset)
{
    mOffsetX = aOffset;
}


int32_t Pad::getOffsetX() const
{
    return mOffsetX;
}


double Pad::getOffsetXfp() const
{
    // @todo get real accuray and don't hardcode it
    double accuracy = 2;
    return mOffsetX / std::pow(10.0, accuracy);
}


void Pad::setOffsetY(int32_t aOffset)
{
    mOffsetY = aOffset;
}


int32_t Pad::getOffsetY() const
{
    return mOffsetY;
}


double Pad::getOffsetYfp() const
{
    // @todo get real accuray and don't hardcode it
    double accuracy = 2;
    return mOffsetY / std::pow(10.0, accuracy);
}


std::string Pad::getOffsetStr() const
{
    return "(" + std::to_string(getOffsetXfp()) + ";" + std::to_string(getOffsetYfp()) + ")";
}


void Pad::setWidth(int32_t aWidth)
{
    if(aWidth < 0)
    {
        throw std::invalid_argument("Width must be >= 0 but is " + std::to_string(aWidth));
    }

    // setHeight performs a check that `width` and `height` are equal for certain `figure`s.
    switch(mFigure)
    {
        case Figure::NONE:
            if(aWidth != 0)
            {
                throw std::invalid_argument("For `figure` " + to_string(mFigure)
                    + ", `width` must be 0 but is " + std::to_string(aWidth) + "!");
            }
            break;

        default:
            break;
    }

    mWidth = aWidth;
}


int32_t Pad::getWidth() const
{
    return mWidth;
}


double Pad::getWidthFp() const
{
    // @todo get real accuray and don't hardcode it
    double accuracy = 2;
    return mWidth / std::pow(10.0, accuracy);
}


void Pad::setHeight(int32_t aHeight)
{
    if(aHeight < 0)
    {
        throw std::invalid_argument("Height must be >= 0 but is " + std::to_string(aHeight));
    }

    switch(mFigure)
    {
        case Figure::CIRCLE:  [[fallthrough]];
        case Figure::SQUARE:  [[fallthrough]];
        case Figure::DONUT:   [[fallthrough]];
        case Figure::OCTAGON: [[fallthrough]];
        case Figure::NSIDED_POLYGON:
            // setHeight needs to be called after setWidth,
            // such that this check makes sense!
            if(mWidth != aHeight)
            {
                throw std::invalid_argument("For `figure` " + to_string(mFigure)
                    + ", `width` and `height` must be equal!");
            }
            break;

        case Figure::NONE:
            if(aHeight != 0)
            {
                throw std::invalid_argument("For `figure` " + to_string(mFigure)
                    + ", `height` must be 0 but is " + std::to_string(aHeight) + "!");
            }
            break;

        default:
            break;
    }

    mHeight = aHeight;
}


int32_t Pad::getHeight() const
{
    return mHeight;
}


double Pad::getHeightFp() const
{
    // @todo get real accuray and don't hardcode it
    double accuracy = 2;
    return mHeight / std::pow(10.0, accuracy);
}


void Pad::setSpecialCorners(uint16_t aSpecialCorners)
{
    // Special corners (rounded or chamfered) are only defined for
    // ROUNDED_RECTANGLE or CHAMFERED_RECTANGLE.
    if(mFigure == Figure::ROUNDED_RECTANGLE ||
       mFigure == Figure::CHAMFERED_RECTANGLE)
    {
        // Only lower 4 bits are allowed.
        if((aSpecialCorners & 0xFFF0u) > 0u)
        {
            throw std::invalid_argument("Only lower 4 bits for 4 corners are allowed"
                " but got 0x" + ToHex(aSpecialCorners, 2) + "!");
        }

        // Must have at least 1 special corner. Otherwise its
        // equivalent to a normal RECTANGLE.
        if(aSpecialCorners == 0u)
        {
            throw std::invalid_argument("Must have > 0 special corners but got "
                + std::to_string(aSpecialCorners) + ", otherwise its equal to `RECTANGLE`!");
        }
    }
    else
    {
        if(aSpecialCorners != 0u)
        {
            throw std::invalid_argument("Special corners are not defined for this `figure`."
                " It must be 0 but is " + std::to_string(aSpecialCorners) + "!");
        }
    }

    mSpecialCorners = aSpecialCorners;
}


void Pad::setNsides(uint32_t aNsides)
{
    if(mFigure == Figure::NSIDED_POLYGON)
    {
        const bool isEven = (aNsides % 2u) == 0u;

        // Only even values are allowed and only values >= 6.
        if(!isEven || (aNsides < 6u))
        {
            throw std::invalid_argument("`nsides` must be even and >= 6 but is "
                + std::to_string(aNsides) + "!");
        }
    }
    else
    {
        if(aNsides != 0u)
        {
            throw std::invalid_argument("`nsides` must be 0 as it's not defined for `figure` "
                + to_string(mFigure) + " but is " + std::to_string(aNsides) + "!");
        }
    }

    mNsides = aNsides;
}


uint32_t Pad::getNsides() const
{
    return mNsides;
}


void Pad::setCorner(int32_t aCorner)
{
    switch(mFigure)
    {
        case Figure::ROUNDED_RECTANGLE:
        [[fallthrough]];
        case Figure::CHAMFERED_RECTANGLE:
            {
                int32_t minCorner = std::min(mWidth, mHeight) / 2;
                if(aCorner > minCorner)
                {
                    throw std::invalid_argument("`corner` must be <= min(`width`, `height`) = "
                        + std::to_string(minCorner) + ", but is " + std::to_string(aCorner) + "!");
                }

                if(aCorner <= 0)
                {
                    throw std::invalid_argument("`corner` must be > 0 but is " + std::to_string(aCorner) + "!");
                }
            }
            break;

        case Figure::DONUT:
            // `width` = `height` represent the outer diameter.
            // `corner` represents the inner diameter.
            if(aCorner >= mWidth)
            {
                throw std::invalid_argument("`corner` (inner diameter) must be < `width`/`height` (outer diameter) = "
                    + std::to_string(mWidth) + " but is " + std::to_string(aCorner) + "!");
            }
            break;

        default:
            if(aCorner != 0)
            {
                throw std::invalid_argument("`corner` must be 0 as it's not defined for `figure` "
                    + to_string(mFigure) + " but is " + std::to_string(aCorner) + "!");
            }
            break;
    }

    mCorner = aCorner;
}


int32_t Pad::getCorner() const
{
    return mCorner;
}


double Pad::getCornerFp() const
{
    // @todo get real accuray and don't hardcode it
    double accuracy = 2;
    return mCorner / std::pow(10.0, accuracy);
}


bool Pad::isLowerLeftCornerSpecial() const
{
    return (mSpecialCorners & 0x1u) > 0u;
}


bool Pad::isLowerRightCornerSpecial() const
{
    return (mSpecialCorners & 0x2u) > 0u;
}


bool Pad::isUpperRightCornerSpecial() const
{
    return (mSpecialCorners & 0x4u) > 0u;
}


bool Pad::isUpperLeftCornerSpecial() const
{
    return (mSpecialCorners & 0x8u) > 0u;
}