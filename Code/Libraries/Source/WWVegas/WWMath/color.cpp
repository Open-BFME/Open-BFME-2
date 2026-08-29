// cl: /O1 /arch:SSE2 /ICode/GameEngine/Source/Common

struct RGBColor
{
    int getAsInt() const;
    void setFromInt(int color);

    float red;
    float green;
    float blue;
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
