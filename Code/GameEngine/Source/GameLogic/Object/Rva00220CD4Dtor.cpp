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

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
    virtual ~SubsystemInterface();

private:
    char m_pad04[4];
    void *m_member08;
};

class Rva00220CD4 : public SubsystemInterface
{
public:
    virtual ~Rva00220CD4();

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
