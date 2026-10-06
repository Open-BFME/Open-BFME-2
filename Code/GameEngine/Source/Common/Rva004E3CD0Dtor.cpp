// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva004E3CD0@@UAE@XZ @ 0x004E3CD0 (72B). Virtual dtor: vtable 0x00862054,
// cleanup this->rva004E2199 (row Code/.../Rva003EF14ADtor.cpp), then vector
// at +0x14 (row 0x004E3C32) and RvaVec at +4 (pin 0x002B80CE). Callers
// 0x004E3E09 and derived tail-jmps 0x004E3D30/0x004E3D47 prove base. Layout
// mirrors Rva004E2E58Value (unknown04 = RvaVec, begin/end/storage = vector,
// flag20) which is why the cleanup call uses ecx=this.
#include <vector>

class RvaVec002B80CE
{
public:
    ~RvaVec002B80CE();
private:
    char m_pad[16];
};

class Rva004E2382
{
public:
    ~Rva004E2382();
private:
    char m_pad[32];
};

typedef _STL::vector<Rva004E2382, _STL::allocator<Rva004E2382> > Rva004E2382Vec;

class Rva004E2E58Value
{
public:
    void rva004E2199();
};

class Rva004E3CD0
{
public:
    virtual ~Rva004E3CD0();
private:
    RvaVec002B80CE m_04;
    Rva004E2382Vec m_14;
    bool m_flag20;
};

Rva004E3CD0::~Rva004E3CD0()
{
    ((Rva004E2E58Value *)this)->rva004E2199();
}
