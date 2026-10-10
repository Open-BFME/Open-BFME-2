// cl: /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00289ABD@@UAE@XZ, retail 0x00289D7A, 239 bytes.
// Dtor: vptr, delete m_rva20 Record, delete vector<void*> elements + erase, slot9 cleanup, delete hash tables, tree dtor, free vec storage, base dtor.
// Evidence: pin ??1Rva00289ABD; callee rows 0x00288BF9 0x0002FD60 0x0031BD55 0x00289180 0x002895BF 0x00288B51 0x00030830 0x001B4E74; caller 0x00289E99 deleting dtor; layout mirrors ctor Rva00289ABDCtor.cpp.
#include "ascii_string.h"
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

extern "C" void __cdecl free(void *block);

struct Rva00288BF9Record
{
    ~Rva00288BF9Record();
};

class Rva00289371HashTable
{
public:
    ~Rva00289371HashTable();
};

class Rva0028881C
{
public:
    ~Rva0028881C();
private:
    void *m_header;
    int m_flag;
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
    virtual ~SubsystemInterface();
private:
    char m_pad04[8];
};

class Rva00289ABD : public SubsystemInterface
{
public:
    ~Rva00289ABD();
    virtual void rva00289180();
    Rva00289371HashTable *m_hash0C;
    Rva00289371HashTable *m_hash10;
    _STL::vector<void *> m_vec14;
    Rva00288BF9Record *m_rva20;
    unsigned char m_b24;
    Rva0028881C m_map28;
};

Rva00289ABD::~Rva00289ABD()
{
    Rva00288BF9Record *p = m_rva20;
    if (p != 0) {
        p->~Rva00288BF9Record();
        ::operator delete(p);
    }
    m_rva20 = 0;
    _STL::vector<void *> &v = m_vec14;
    for (_STL::vector<void *>::size_type i = 0; i < m_vec14.size(); ++i) {
        void *q = v[i];
        if (q != 0) {
            ((Rva00288BF9Record *)q)->~Rva00288BF9Record();
            ::operator delete(q);
        }
    }
    v.erase(v.begin(), v.end());
    rva00289180();
    Rva00289371HashTable *h0 = m_hash0C;
    if (h0 != 0) {
        h0->~Rva00289371HashTable();
        ::operator delete(h0);
    }
    m_hash0C = 0;
    Rva00289371HashTable *h1 = m_hash10;
    if (h1 != 0) {
        h1->~Rva00289371HashTable();
        ::operator delete(h1);
    }
    m_hash10 = 0;
}
