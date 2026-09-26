// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva00464FC7@SlaughterHordeContain@@UAE_NPAXH@Z, retail 0x00464FC7, 74 bytes.
// Virtual slot 55 (offset 0xDC) of vtable 0x00848AA0 (class of
// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// SlaughterHordeContainCtor.cpp). Map<int int> at this+0x3C keyed by int at arg1+0x74:
// when second arg is 2 erases the key via rowed _Rb_tree find 0x388F63 (int-int)
// and erase 0x5530A8 (int-ptr; binary-identical node unlink for trivial values,
// called via reinterpret_cast to reproduce retail's exact mixed manglings),
// otherwise stores second arg via rowed map operator[] 0x28932C (int-int).
// Always returns true, null first arg included. Ghidra size 74 matches.
// Evidence: vtable slot plus OpenContain map<int void*> at +0x3C precedent;
// no direct caller; honest address name since method identity is unproven.
#include <map>

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

struct KeyHolder {
    char pad[0x74];
    int key;
};

class SlaughterHordeContain
{
public:
    SLOT16(s0) SLOT16(s1)
    virtual void s20(int); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual bool rva00464FC7(void *a, int b);
    char m_pad04[0x38];
    _STL::map<int, int> m_map3C;
    char m_pad48[0x9C - 0x48];
};

bool SlaughterHordeContain::rva00464FC7(void *a, int b)
{
    if (!a)
        return true;
    int key = reinterpret_cast<KeyHolder*>(a)->key;
    if (b == 2) {
        _STL::map<int, int>::iterator it = m_map3C.find(key);
        if (it == m_map3C.end())
            return true;
        reinterpret_cast<_STL::map<int, void*>*>(&m_map3C)->erase(reinterpret_cast<_STL::map<int, void*>::iterator&>(it));
    } else {
        m_map3C[key] = b;
    }
    return true;
}
