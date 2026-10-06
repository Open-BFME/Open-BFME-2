// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00057151@Rva00057151@@QAEXHHH@Z @0x00057151 127B
// Unlock body: pops an owning 4-byte reference from a deque group into a slot.
// Evidence: calls rowed deque back alias 0x3B5603 and rowed OpaqueRefElement4
// assignment 0x239099 plus rowed deque pop_back 0x5555F; empty check and
// pop_back match StlportOwnedDeque TU; float/flag updates at +0x30/+0x44/+0x45
// and source int at this+0x10->[0x78] read directly from retail immediates.
#include <deque>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);

class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    void Add_Ref() { InterlockedIncrement(&refs); }
    void Release_Ref();
private:
    long refs;
};

struct OpaqueRefElement4 {
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};

struct FloatSource {
    char _pad[0x78];
    int m_value;
};

struct Referent {
    void *vfptr;
    long refs;
    char _pad8[0x30 - 8];
    float m_float30;
    char _pad34[0x44 - 0x34];
    unsigned char m_flag44;
    unsigned char m_flag45;
};

class Rva00057151 {
public:
    void rva00057151(int a1, int a2, int a3);
private:
    char _pad0[0x10];
    FloatSource *m_source;
    char _pad14[0xA4C - 0x14];
    _STL::deque<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> > m_deques[6];
    int m_counts[3];
    OpaqueRefElement4 m_slots[3];
};

void Rva00057151::rva00057151(int a1, int a2, int a3)
{
    _STL::deque<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> > &d = m_deques[a2 + a1 * 2];
    if (d.empty())
        return;
    OpaqueRefElement4 &slot = m_slots[a1];
    slot = d.back();
    if (a3 == 0) {
        if (((Referent *)slot.referent)->m_flag44)
            ((Referent *)slot.referent)->m_flag44 = 0;
        else
            ((Referent *)slot.referent)->m_float30 = (float)m_source->m_value;
        ((Referent *)slot.referent)->m_flag45 = 1;
    } else {
        ((Referent *)slot.referent)->m_flag44 = 0;
        ((Referent *)slot.referent)->m_flag45 = 0;
        ((Referent *)slot.referent)->m_float30 = 0.0f;
    }
    d.pop_back();
}
