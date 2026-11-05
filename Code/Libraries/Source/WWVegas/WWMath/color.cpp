// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

#include "../../../../GameEngine/Source/Common/debug.h"

#define RGBCOLOR_VIEW_DEFAULT_CTOR
#define RGBCOLOR_VIEW_FLOAT_CTOR
#include "../../../Include/Lib/RGBColor.h"

struct RGBAColorReal
{
    RGBAColorReal &operator=(const RGBAColorReal &that);

    float red;
    float green;
    float blue;
    float alpha;
};

struct RGBAColorInt
{
    RGBAColorInt &operator=(const RGBAColorInt &that);

    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;
};

inline int RGBColor::getAsInt() const throw()
{
    return ((int)(red * 255.0) << 16) | ((int)(green * 255.0) << 8) | ((int)(blue * 255.0) << 0);
}

inline void RGBColor::setFromInt(int color) throw()
{
    red = (float)((color >> 16) & 0xFF) * (1.0f / 255.0f);
    green = (float)((color >> 8) & 0xFF) * (1.0f / 255.0f);
    blue = (float)(color & 0xFF) * (1.0f / 255.0f);
}

// Exported (retail export 315); identical code folding puts it on the shared
// "return this" body at 0x0047A6A9.
RGBColor::RGBColor()
{
}

// Exported (retail export 314); identical code folding puts it on Coord3D's
// three-float store at 0x000423A0.
RGBColor::RGBColor(float r, float g, float b)
{
    red = r;
    green = g;
    blue = b;
}

bool operator==(const RGBColor &left, const RGBColor &right)
{
    return left.red == right.red &&
        left.green == right.green &&
        left.blue == right.blue;
}

bool operator!=(const RGBColor &left, const RGBColor &right)
{
    return !(left == right);
}

// The 16-byte block copy folded with the integer-region assignment at 0x002E7FDA.
RGBAColorInt &RGBAColorInt::operator=(const RGBAColorInt &that)
{
    struct Raw
    {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int alpha;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

// The 16-byte block copy folded with the integer-region assignment at 0x002E7FDA.
RGBAColorReal &RGBAColorReal::operator=(const RGBAColorReal &that)
{
    struct Raw
    {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int alpha;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

Debug &operator<<(Debug &debug, const RGBColor &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ")";
    return debug;
}

Debug &operator<<(Debug &debug, const RGBAColorReal &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ", " << color.alpha << ")";
    return debug;
}

Debug &operator<<(Debug &debug, const RGBAColorInt &color)
{
    debug << "(" << color.red << ", " << color.green << ", " << color.blue << ", " << color.alpha << ")";
    return debug;
}

#include "../../../../GameEngine/Include/GameClient/GameClientRandomVariable.h"
#include "../../../../GameEngine/Include/GameClient/GameClientRandomVariableInlines.h"

namespace FXParticleSystem {

struct RGBColorKeyframe
{
    RGBColorKeyframe();
    RGBColorKeyframe &operator=(const RGBColorKeyframe &that);

    RGBColor color;
    unsigned int frame;
};

RGBColorKeyframe::RGBColorKeyframe()
{
    color.red = color.green = color.blue = 0.0f;
    frame = 0;
}

// The 16-byte block copy folded with the integer-region assignment at 0x002E7FDA.
RGBColorKeyframe &RGBColorKeyframe::operator=(const RGBColorKeyframe &that)
{
    struct Raw
    {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        unsigned int frame;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

struct RandomAlphaKeyframe
{
    RandomAlphaKeyframe();
    RandomAlphaKeyframe &operator=(const RandomAlphaKeyframe &that);

    GameClientRandomVariable alpha;
    unsigned int frame;
};

RandomAlphaKeyframe::RandomAlphaKeyframe()
{
    alpha.m_type = GameClientRandomVariable::CONSTANT;
    alpha.m_low = 0.0f;
    alpha.m_high = 0.0f;
    alpha.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    frame = 0;
}

// The 16-byte block copy folded with the integer-region assignment at 0x002E7FDA.
RandomAlphaKeyframe &RandomAlphaKeyframe::operator=(const RandomAlphaKeyframe &that)
{
    struct KeyBlock
    {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
        unsigned int value3;
    };

    *(KeyBlock *)this = *(const KeyBlock *)&that;
    return *this;
}

}

#pragma inline_depth(0)
// ?bfmeEmitcolor@@YAXPAURGBColor@@@Z present-unmatched
void bfmeEmitcolor(RGBColor *rGBColor)
{
    // Emit the implicit assignment folded at 0x0000353A without changing
    // the canonical header's inline copies in other translation units.
    typedef RGBColor &(RGBColor::*RGBColorAssign)(const RGBColor &);
    RGBColorAssign assignment = &RGBColor::operator=;
    (rGBColor->*assignment)(*rGBColor);
    rGBColor->getAsInt();
    rGBColor->setFromInt(0);
}
#pragma inline_depth()
