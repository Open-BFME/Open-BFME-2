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

// SubsystemInterface with the 14 virtual slots of its retail vtable 0x00BD77A0,
// spelled as reference/shims/subsystem_bfme2/subsystem_interface.h does (ctor
// 0x001B4E63 / dtor 0x001B4E74 rowed as ??0/??1SubsystemInterface), so the
// derived vtable below gets the retail 14-slot shape.
class SubsystemInterface
{
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
    virtual void init() = 0;
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad() {}
    virtual bool vslot04(int) { return false; }
    virtual bool vslot05() { return false; }
    virtual int vslot06() { return 0; }
    virtual void vslot07(int) {}
    virtual void vslot08() {}
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual bool vslot11(int) { return false; }
    virtual void vslot12() {}
    virtual void vslot13(int) {}

private:
    char m_pad04[4];
    void *m_member08;
};

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

inline Rva00220CD4::~Rva00220CD4()
{
}

#pragma inline_depth(0)
// ?bfmeEmitRva00220CD4Dtor@@YAXPAVRva00220CD4@@@Z present-unmatched
void bfmeEmitRva00220CD4Dtor(Rva00220CD4 *p)
{
	p->Rva00220CD4::~Rva00220CD4();
}
#pragma inline_depth()
