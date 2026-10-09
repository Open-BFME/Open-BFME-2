// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00055951@Rva00055951@@QAE?AU?$_Ht_iterator@U?$pair@$$CBHURva00054EBEElement@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00054EBEElement@@@_STL@@@2@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHURva00054EBEElement@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHURva00054EBEElement@@@_STL@@@2@@_STL@@I@Z
// Retail 0x00055951 59 bytes. MilesAudioManager's request set (+0x9C)
// lookup by playing handle: builds a 0x18-byte request on the stack
// through the rowed ctor 0x000A8684 stores the handle at +8 and finds the
// request's address through the rowed hashtable find 0x00054EBE (hidden
// return slot passed straight through) then destroys the request through
// the rowed dtor 0x000A86CE. No EH frame. Callers (all MilesAudioManager
// with ecx = this+0x9C): 0x00055FCA 0x0005B256 0x0005FA3C 0x000613A9.
#include <hash_map>

struct Rva00054EBEElement { char bytes[1]; bool operator<(const Rva00054EBEElement&)const; bool operator==(const Rva00054EBEElement&)const; };
namespace _STL {template<> struct hash<Rva00054EBEElement> { unsigned operator()(const Rva00054EBEElement&) const; };}

typedef _STL::hashtable<_STL::pair<int const, Rva00054EBEElement>, int, _STL::hash<int>,
    _STL::_Select1st<_STL::pair<int const, Rva00054EBEElement> >, _STL::equal_to<int>,
    _STL::allocator<_STL::pair<int const, Rva00054EBEElement> > > Rva00054EBETable;

class __declspec(novtable) Rva00A86CE
{
public:
    virtual ~Rva00A86CE();
    int m_04;
    unsigned int m_08;
    int m_0C;
    int m_10;
    int m_14;
};

class __declspec(novtable) Rva000A8684 : public Rva00A86CE
{
public:
    Rva000A8684();
};

class Rva00055951
{
public:
    Rva00054EBETable::iterator rva00055951(unsigned int handle);
};

Rva00054EBETable::iterator Rva00055951::rva00055951(unsigned int handle)
{
    Rva000A8684 request;
    request.m_08 = handle;
    return reinterpret_cast<Rva00054EBETable *>(this)->find(reinterpret_cast<int>(&request));
}
