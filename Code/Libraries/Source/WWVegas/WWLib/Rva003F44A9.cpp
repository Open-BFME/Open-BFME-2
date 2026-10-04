// ?rva003F44A9@Rva003F44A9@@QAEPAXXZ
// partial score=0.98 date=2026-09-29
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003F44A9@Rva003F44A9@@QAEPAXXZ retail 0x003F44A9 68 bytes.
// First-empty finder over vector<Element*> at +4 where Element has
// StringBase<char> at +0x18 (isEmpty row 0x00001E2F). Returns first
// element whose string is empty else 0. Callers 0x003F4ABB 0x003F4FBD.
// Barrier between base/cur and loop fixes first size calc to reload
// (sub eax [esi+4]) for 68B/32insns exact size; remains early push edi
// plus mov ebp edi ordering and add ebp 4 position (1 reg wall).
#include <vector>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
template <class CHAR> class StringBase { void *m_data; public: bool isEmpty() const; };
struct Rva003F44A9Element { char m_pad[24]; StringBase<char> m_str; };
class Rva003F44A9 {
    char m_pad0[4];
    _STL::vector<Rva003F44A9Element *> m_list;
public:
    void *rva003F44A9();
    bool rva003F44ED();
};
void *Rva003F44A9::rva003F44A9()
{
    unsigned i = 0;
    if (i < m_list.size()) {
        Rva003F44A9Element **base = m_list.begin();
        Rva003F44A9Element **cur = base;
        _ReadWriteBarrier();
        do {
            if ((*cur)->m_str.isEmpty())
                return base[i];
            ++i;
            ++cur;
        } while (i < m_list.size());
    }
    return 0;
}

bool Rva003F44A9::rva003F44ED()
{
    unsigned i = 0;
    if (i < m_list.size()) {
        Rva003F44A9Element **cur = m_list.begin();
        _ReadWriteBarrier();
        do {
            if (!(*cur)->m_str.isEmpty())
                return true;
            ++i;
            ++cur;
        } while (i < m_list.size());
    }
    return false;
}
