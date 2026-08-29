// cl: /O1 /ICode/GameEngine/Source/Common

struct RGBColor
{
    int getAsInt() const;

    float red;
    float green;
    float blue;
};

int RGBColor::getAsInt() const
{
    return ((int)(red * 255.0) << 16) | ((int)(green * 255.0) << 8) | ((int)(blue * 255.0) << 0);
}
