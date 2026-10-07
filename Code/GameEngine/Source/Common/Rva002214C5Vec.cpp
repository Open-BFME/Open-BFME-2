// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva002214C5Get@@YAXPAV?$vector@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@@Z @0x002214C5 182B
// Builds FieldParse table (as vector<BfmeE16> 16B pods) from static map<AsciiString,NoCaseTreeValue4> via rowed getter 0x002213D9 plus Vector_base 0x00211E58 plus reserve 0x0022118F plus push_back 0x0059D2A3 plus _M_increment 0x00024250 plus SlaveAttackFieldTable plus swap 0x00567ECD plus _free 0x00030830. Evidence: retail bytes plus caller 0x0022157B plus rowed callees.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
#include "ascii_string.h"

extern "C" char s_slot3E4first;

struct NoCaseTreeValue4 { unsigned char m_data[4]; };
struct BfmeE16 { const char *a; void *b; void *c; int d; };
struct BfmeE12 { char m_d[12]; };
struct FieldParse { const char *token; void *parse; const void *userdata; int offset; };
class FXList;

extern const struct FieldParse SlaveAttackFieldTable;
extern const char g_Rva0107301CEmptyString[];
class INI;

// The table entries' parse target: the map value is an object whose first
// virtual parses from the INI.
class Rva0022104EParser
{
public:
	virtual void parse(INI *ini) = 0;
};

// FieldParse parse function 0x0022104E (13B) stored in every entry built
// below: forward the INI to the entry's userdata object.
void __cdecl Rva0022104EParse(INI *ini, void *instance, void *store, const void *userData)
{
	((Rva0022104EParser *)userData)->parse(ini);
}

extern _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *Rva002213D9Get();
void __cdecl free(void *);

void Rva002214C5Get(_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > *out)
{
    typedef _STL::map<AsciiString, NoCaseTreeValue4, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > MapNoCase;
    MapNoCase *map = (MapNoCase *)Rva002213D9Get();
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > tmp;
    tmp.reserve(map->size() + 1);
    MapNoCase::iterator it = map->begin();
    MapNoCase::iterator last = map->end();
    for (; it != last; ++it) {
        BfmeE16 e;
        e.a = it->first.str();
        e.b = (void *)&Rva0022104EParse;
        e.c = *(void **)&it->second;
        e.d = 0;
        tmp.push_back(e);
    }
    tmp.push_back(*(const BfmeE16 *)&SlaveAttackFieldTable);
    (( _STL::vector<struct BfmeE12, _STL::allocator<struct BfmeE12> > *)out)->swap(*( _STL::vector<struct BfmeE12, _STL::allocator<struct BfmeE12> > *)&tmp);
}
