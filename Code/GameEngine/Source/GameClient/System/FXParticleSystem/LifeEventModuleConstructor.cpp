// cl: /DNDEBUG /MD /EHsc /Ob2 /O1 /arch:SSE /G7
// Native 0x0056413D..0x005641BB uses all three established vtable globals
// of Rva003AE0D5's copy constructor. Its rowed unsigned head constructor
// and the existing Rva003AE11B subobject vtable independently fix the
// two construction stages and offsets. The input's event-info fields
// follow the rowed sampler and LifeEventModuleInfo::getEventFX calls.
// Composition is an ABI view; complete inheritance names are unproven.

class FXList;
class GameClientRandomVariable
{
public:
    float getValue() const;
    unsigned kind;
    float low, high;
};

namespace FXParticleSystem
{
class LifeEventModuleInfo
{
public:
    const FXList *getEventFX();
    void *vtable;
    void *eventName;
    GameClientRandomVariable time;
    const FXList *cache;
};
}

struct LifeInput413D
{
    char pad00[0x1D];
    bool flag;
    char pad1E[2];
    FXParticleSystem::LifeEventModuleInfo info;
};

class Rva003ADEBF
{
public:
    Rva003ADEBF(unsigned);
    virtual ~Rva003ADEBF();
    char pad04[8];
    bool flag;
};

class Rva003AE11B
{
public:
    Rva003AE11B() : time(0), fx(0) {}
    virtual ~Rva003AE11B();
    unsigned time;
    const FXList *fx;
};

extern "C" char Rva003AE0D5_v0;
extern "C" char Rva003AE0D5_v8;
extern "C" char Rva003AE0D5_v10;

class Rva003AE0D5
{
public:
    Rva003AE0D5(unsigned, LifeInput413D &);
private:
    Rva003ADEBF base;
    Rva003AE11B sub;
    bool active;
};

Rva003AE0D5::Rva003AE0D5(unsigned a, LifeInput413D &input)
    : base(a), sub()
{
    *(void **)this = &Rva003AE0D5_v0;
    *(void **)((char *)this + 8) = &Rva003AE0D5_v8;
    *(void **)((char *)this + 0x10) = &Rva003AE0D5_v10;
    sub.time = (unsigned)input.info.time.getValue();
    sub.fx = input.info.getEventFX();
    base.flag = input.flag;
    active = true;
}
