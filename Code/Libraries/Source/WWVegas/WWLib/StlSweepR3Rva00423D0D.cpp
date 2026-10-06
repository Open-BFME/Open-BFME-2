// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <list>



struct Rva00423D0DRecord { Rva00423D0DRecord(); Rva00423D0DRecord(const Rva00423D0DRecord&); ~Rva00423D0DRecord(); Rva00423D0DRecord&operator=(const Rva00423D0DRecord&); char bytes[12]; bool operator==(const Rva00423D0DRecord&) const; bool operator<(const Rva00423D0DRecord&) const; };
namespace _STL {template<> void _Construct<Rva00423D0DRecord,Rva00423D0DRecord>(Rva00423D0DRecord*,const Rva00423D0DRecord&);}


// This caller's native REL32 already names the kept provider at 0x00423648.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??$_Construct@URva00423D0DRecord@@U1@@_STL@@YAXPAURva00423D0DRecord@@ABU1@@Z=??$_Construct@URva00423648Element@@U1@@_STL@@YAXPAURva00423648Element@@ABU1@@Z")

// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_List_node<Rva00423D0DRecord> * _STL::list<Rva00423D0DRecord, _STL::allocator<Rva00423D0DRecord> >::_M_create_node(Rva00423D0DRecord const &);
