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

namespace FXParticleSystem
{
class RenderObjectUpdateModuleInfo
{
public:
    RenderObjectUpdateModuleInfo();
    virtual ~RenderObjectUpdateModuleInfo();
    RandomRange624DE values[12];
    unsigned rotation;
};
}

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
    info.values[0] = ((const RenderModuleInput624DE *)input)->values[0];
    info.values[1] = ((const RenderModuleInput624DE *)input)->values[1];
    info.values[2] = ((const RenderModuleInput624DE *)input)->values[2];
    info.values[3] = ((const RenderModuleInput624DE *)input)->values[3];
    info.values[4] = ((const RenderModuleInput624DE *)input)->values[4];
    info.values[5] = ((const RenderModuleInput624DE *)input)->values[5];
    info.values[6] = ((const RenderModuleInput624DE *)input)->values[6];
    info.values[7] = ((const RenderModuleInput624DE *)input)->values[7];
    info.values[8] = ((const RenderModuleInput624DE *)input)->values[8];
    info.values[9] = ((const RenderModuleInput624DE *)input)->values[9];
    info.values[10] = ((const RenderModuleInput624DE *)input)->values[10];
    info.values[11] = ((const RenderModuleInput624DE *)input)->values[11];
    info.rotation = ((const RenderModuleInput624DE *)input)->rotation;
}
