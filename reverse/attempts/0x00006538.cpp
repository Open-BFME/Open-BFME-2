// ?d_00006538@@YAXXZ
// partial score=0.9 date=2026-08-31
// ?d_00006538@@YAXXZ
// partial score=0.9 date=2026-08-31
// cl: /O1 /arch:SSE2
// Retail 0x00006538 is ??0RGBColor@@QAE@H@Z (exports.csv), and it is one
// forwarding call to ?setFromInt@RGBColor@@QAEXH@Z at 0x00004EDF, which is
// already matched out of color.cpp.
//
// The body cannot live in color.cpp. With setFromInt defined in the same
// translation unit MSVC 7.1 keeps `this` in ecx across the call and emits
//     push [esp+4]; call setFromInt; mov eax,ecx; ret 4          (13 bytes)
// while retail saves it:
//     push esi; push [esp+8]; mov esi,ecx; call setFromInt; mov eax,esi;
//     pop esi; ret 4                                             (18 bytes)
// which is what a caller that has only seen a DECLARATION of setFromInt emits.
// Retail's constructor is therefore a COMDAT from a translation unit that only
// declares setFromInt - consistent with 0x00006538 sitting immediately ahead of
// the ascii_string.cpp run at 0x0000654A rather than beside the rest of
// color.cpp. Landing it needs that second translation unit's real path, not a
// different body.
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
