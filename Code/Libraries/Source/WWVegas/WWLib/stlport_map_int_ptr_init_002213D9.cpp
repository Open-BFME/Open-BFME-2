// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva002213D9Get@@YAPAV?$map@HPAXU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@XZ, retail 0x002213D9 69B.
// Function-local static initializer: guard test/or, map ctor at 0x0033C432,
// atexit registration of the static's cleanup _$E2 (0x007B7704). Byte-exact via
// MSVC static init with /EHs.
//
// Target facts: the static at 0x009FE4AC is a map<AsciiString, NoCaseTreeValue4>.
// Its one constructor caller 0x0022141E (Rva002214A6Dtor.cpp) inserts
// make_pair(AsciiString, NoCaseTreeValue4) through the matched
// map<AsciiString, NoCaseTreeValue4>::insert (0x002213C5), and the cleanup
// chain _$E2 0x007B7704 -> ~map 0x002213C0 -> ~_Rb_tree 0x002212F1 -> clear
// 0x00221234 -> _M_erase 0x0022115A destroys AsciiString keys (0x0048BA39).
// This unit instantiates that chain from the static's real type. The getter
// keeps its retail-unknown name and map<int,void*> return type; its callers
// cast the result.
#include <map>
#include "ascii_string.h"
#include "../../../../GameEngine/Include/Common/NoCaseTreeValue4.h"

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCaseValue;
typedef _STL::map<AsciiString, NoCaseTreeValue4, _STL::less<AsciiString>, _STL::allocator<NoCaseValue> > NoCaseMap;

_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *Rva002213D9Get()
{
    static NoCaseMap s_map;
    return (_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *)&s_map;
}
