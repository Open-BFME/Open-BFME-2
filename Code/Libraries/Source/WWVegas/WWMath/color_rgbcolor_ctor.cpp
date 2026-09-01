// cl: /O1 /arch:SSE2
// ??0RGBColor@@QAE@H@Z at 0x00006538, the header-inline constructor that
// forwards to setFromInt.
//
// It cannot live in color.cpp. With setFromInt DEFINED in the same translation
// unit MSVC 7.1 keeps `this` in ecx across the call and emits thirteen bytes
// with no register save; retail's eighteen are what a unit that has only seen
// the declaration emits, because the call is opaque and `this` has to survive
// it in a callee-saved register. Retail's COMDAT also sits immediately ahead of
// the ascii_string.cpp run at 0x0000654A rather than beside the rest of
// color.cpp, so it came from another unit that merely included the header.

struct RGBColor
{
    RGBColor(int color);

    void setFromInt(int color);

    float red;
    float green;
    float blue;
};

RGBColor::RGBColor(int color)
{
    setFromInt(color);
}
