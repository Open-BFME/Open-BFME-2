// cl: /DNDEBUG /MD /EHsc /Ob2 /O1 /arch:SSE /G7
// Native 0x005624DE..0x005625C5: the four established vtable destinations
// identify the existing Rva003AEF9B copy owner. Calls construct the 0x1C
// smart-handle head and RenderObjectUpdateModuleInfo, then copy twelve
// random ranges from input +0xC..0x90 and rotation from +0x9C.
// The rowed info default constructor independently establishes the range
// layout and rotation offset. Composition is an ABI construction view;
// the complete retail inheritance names remain unproven.

class RvaSmartPtr12;
class Rva0055F98A
{
public:
    Rva0055F98A(const RvaSmartPtr12 &, int);
    virtual ~Rva0055F98A();
private:
    char storage[0x18];
};

struct RandomRange624DE
{
    unsigned kind;
    float low, high;
};

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/RenderObjectUpdateModuleInfo.h"
#include <string.h>
#pragma intrinsic(memcpy)

struct RenderModuleInput624DE
{
    char unknown00[12];
    RandomRange624DE values[12];
    unsigned rotation;
};

extern "C" char Rva003AEF9B_v0b;
extern "C" char Rva003AEF9B_v14b;
extern "C" char Rva003AEF9B_v18b;
extern "C" char Rva003AEF9B_vsub;

class Rva003AEF9B
{
public:
    Rva003AEF9B(const RvaSmartPtr12 &, int);
private:
    Rva0055F98A base;
    FXParticleSystem::RenderObjectUpdateModuleInfo info;
};

Rva003AEF9B::Rva003AEF9B(const RvaSmartPtr12 &smart, int input)
    : base(smart, input), info()
{
    *(void **)((char *)this + 0x1C) = &Rva003AEF9B_vsub;
    *(void **)this = &Rva003AEF9B_v0b;
    *(void **)((char *)this + 0x14) = &Rva003AEF9B_v14b;
    *(void **)((char *)this + 0x18) = &Rva003AEF9B_v18b;
    memcpy(&info.m_var0, &((const RenderModuleInput624DE *)input)->values[0], sizeof(info.m_var0));
    memcpy(&info.m_var1, &((const RenderModuleInput624DE *)input)->values[1], sizeof(info.m_var1));
    memcpy(&info.m_var2, &((const RenderModuleInput624DE *)input)->values[2], sizeof(info.m_var2));
    memcpy(&info.m_var3, &((const RenderModuleInput624DE *)input)->values[3], sizeof(info.m_var3));
    memcpy(&info.m_var4, &((const RenderModuleInput624DE *)input)->values[4], sizeof(info.m_var4));
    memcpy(&info.m_var5, &((const RenderModuleInput624DE *)input)->values[5], sizeof(info.m_var5));
    memcpy(&info.m_var6, &((const RenderModuleInput624DE *)input)->values[6], sizeof(info.m_var6));
    memcpy(&info.m_var7, &((const RenderModuleInput624DE *)input)->values[7], sizeof(info.m_var7));
    memcpy(&info.m_var8, &((const RenderModuleInput624DE *)input)->values[8], sizeof(info.m_var8));
    memcpy(&info.m_var9, &((const RenderModuleInput624DE *)input)->values[9], sizeof(info.m_var9));
    memcpy(&info.m_var10, &((const RenderModuleInput624DE *)input)->values[10], sizeof(info.m_var10));
    memcpy(&info.m_var11, &((const RenderModuleInput624DE *)input)->values[11], sizeof(info.m_var11));
    info.m_mode = ((const RenderModuleInput624DE *)input)->rotation;
}
