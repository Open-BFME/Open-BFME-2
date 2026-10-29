// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
//
// ??0Rva00500500@@QAE@ABV0@@Z @ 0x00500500 (29B).
// ??0Rva00500500@@QAE@AAPAXABVSpawnArmy@@@Z @ 0x00500770 (29B).
// ??$_Construct@VRva00500500@@V1@@_STL@@YAXPAVRva00500500@@ABV1@@Z @ 0x0050097D (45B).
// ?Rva00500BA6Create@@YGPAU?$_Rb_tree_node@VRva00500500@@@_STL@@ABVRva00500500@@@Z @ 0x00500BA6 (34B).
// Copy and pointer-plus-Rva ctors of the 92-byte wrapper holding a pointer
// at +0 and the ModuleData SpawnArmy at +4 via its rowed copy at
// 0x004E2F9F. Caller 0x00503355 builds a temp with the two-arg ctor then
// copies it with the copy ctor. Frameless: the pointer is trivial and the
// Rva is last so no EH unwind is needed.
// The 34B body is the tree _M_create_node for these wrappers: it allocates
// the 108-byte node through the rowed byte allocator 0x000307F0 and placement
// copies the wrapper at node+16 through the rowed _Construct 0x0050097D.
// It ignores its tree this-pointer so a __stdcall free function emits the
// same bytes; a future _M_insert at 0x00500BF5 can call it directly.
#include <memory>
#include <vector>
#include <set>

#include "ascii_string.h"

// SpawnArmy derives from the canonical Snapshot (vtable 0x00BBB554); its
// inline destructor restores that table, as the address-named view did.
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class SpawnArmy : public Snapshot {
public:
    virtual ~SpawnArmy();
    SpawnArmy(const SpawnArmy &other);
protected:
    virtual void loadPostProcess();
    virtual void crc(Xfer *xfer);
    virtual void xfer(Xfer *xfer);
public:
private:
    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0c;
    AsciiString m_10;
    AsciiString m_14;
    AsciiString m_18;
    AsciiString m_1c;
    unsigned int m_20;
    unsigned int m_24;
    AsciiString m_28;
    AsciiString m_2c;
    AsciiString m_30;
    AsciiString m_34;
    _STL::vector<AsciiString> m_vec38;
    unsigned int m_44;
    unsigned int m_48;
    unsigned int m_4c;
    AsciiString m_50;
    unsigned char m_54;
    unsigned char m_55;
};

class Rva00500500 {
public:
    Rva00500500(const Rva00500500 &other);
    Rva00500500(void *&p, const SpawnArmy &r);
private:
    void *m_ptr;
    SpawnArmy m_rva;
};

Rva00500500::Rva00500500(const Rva00500500 &other)
    : m_ptr(other.m_ptr), m_rva(other.m_rva)
{
}

Rva00500500::Rva00500500(void *&p, const SpawnArmy &spawnArmy)
    : m_ptr(p), m_rva(spawnArmy)
{
}

template void _STL::_Construct<Rva00500500, Rva00500500>(Rva00500500 *, const Rva00500500 &);

_STL::_Rb_tree_node<Rva00500500> *__stdcall Rva00500BA6Create(const Rva00500500 &value)
{
    _STL::_Rb_tree_node<Rva00500500> *node = (_STL::_Rb_tree_node<Rva00500500> *)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<Rva00500500>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
