// cl: /ICode/GameEngine/Source/Common
// ?Rva0055CCEFIsZero@@YAHABURGBColor@@@Z at 0x0055CCEF size 55
// Evidence: unlock lane; three float !=0 checks over +0/+4/+8 returning 1 when all zero;
// callers are writeINI bodies; RGBColor layout per WWMath/color.cpp.

struct RGBColor
{
    float red;
    float green;
    float blue;
};

int Rva0055CCEFIsZero(const RGBColor &color)
{
    return color.red == 0.0f && color.green == 0.0f && color.blue == 0.0f;
}
