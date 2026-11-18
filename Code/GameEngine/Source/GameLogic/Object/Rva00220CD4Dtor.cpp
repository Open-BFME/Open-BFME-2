// cl: /O1 /MD /EHsc
// ??1Rva00220CD4@@UAE@XZ, retail 0x00220CD4 74B.
// Virtual dtor: vtable store, destroys +0x10 holder via rowed 0x00220C17,
// +0x0C via rowed 0x00360D26, then rowed base 0x001B4E74. Chain from holder.
// Caller 0x00220F71 deleting dtor. Layout base 0xC + 4 + 8 = 0x18.
class Rva00360D26Member
{
public:
    ~Rva00360D26Member();

private:
    unsigned m_unknown;
};

class Rva00220C17
{
public:
    ~Rva00220C17();

private:
    void *m_begin;
    void *m_end;
};

// SubsystemInterface with the 14 virtual slots of its retail vtable 0x00BD77A0.
// The canonical header keeps those slots behind BFME_SUBSYSTEM_SLOTS (the shim
// reference/shims/subsystem_bfme2/subsystem_interface.h defines it before the
// include), so define it here too; without it the class has no virtual base and
// the vtable below is four slots. Ctor 0x001B4E63 / dtor 0x001B4E74 are rowed as
// ??0/??1SubsystemInterface, so the derived vtable gets the retail 14-slot shape.
#define BFME_SUBSYSTEM_SLOTS
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva00220CD4 : public SubsystemInterface
{
public:
    virtual ~Rva00220CD4();
    // Retail vtable 0x007E6A84 slots 1/9/10 (init/reset/update) are the folded
    // empty body at 0x000B3FD0.
    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}

private:
    Rva00360D26Member m_member0C;
    Rva00220C17 m_holder10;
};

Rva00220CD4::~Rva00220CD4()
{
}

