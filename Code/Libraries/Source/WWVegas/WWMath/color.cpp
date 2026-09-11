// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

class Debug
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual Debug &operator<<(const char *value);
    virtual Debug &operator<<(int value);
    virtual Debug &operator<<(unsigned int value);
    virtual Debug &operator<<(unsigned char value);
    virtual Debug &operator<<(short value);
    virtual Debug &operator<<(unsigned short value);
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual Debug &operator<<(float value);
};

struct RGBColor
{
    RGBColor &operator=(const RGBColor &that);
    int getAsInt() const;
    void setFromInt(int color);

    float red;
    float green;
    float blue;
};

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

int RGBColor::getAsInt() const
{
    return ((int)(red * 255.0) << 16) | ((int)(green * 255.0) << 8) | ((int)(blue * 255.0) << 0);
}

// The 12-byte block copy folded with the coordinate assignments at 0x0000353A.
RGBColor &RGBColor::operator=(const RGBColor &that)
{
    struct Raw
    {
        unsigned int red;
        unsigned int green;
        unsigned int blue;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

void RGBColor::setFromInt(int color)
{
    static const float scale = 1.0f / 255.0f;
    red = (float)((color >> 16) & 0xFF) * scale;
    green = (float)((color >> 8) & 0xFF) * scale;
    blue = (float)(color & 0xFF) * scale;
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

class GameClientRandomVariable
{
public:
    enum DistributionType
    {
        CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
    };

    void setRange(float low, float high, DistributionType type = UNIFORM);

public:
    DistributionType m_type;
    float m_low;
    float m_high;
};

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
