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
    int getAsInt() const;
    void setFromInt(int color);

    float red;
    float green;
    float blue;
};

struct RGBAColorReal
{
    float red;
    float green;
    float blue;
    float alpha;
};

struct RGBAColorInt
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;
};

int RGBColor::getAsInt() const
{
    return ((int)(red * 255.0) << 16) | ((int)(green * 255.0) << 8) | ((int)(blue * 255.0) << 0);
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
