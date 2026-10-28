// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
#include <list>
class Rva004246BDObj;
// Declared only: retail's node allocation is the separately rowed 34-byte body
// at this name's pinned address; this TU's copy is not retail's.
template <> _STL::_List_node<Rva004246BDObj *> *_STL::list<Rva004246BDObj *>::_M_create_node(Rva004246BDObj *const &);
template void _STL::list<Rva004246BDObj *>::push_back(Rva004246BDObj *const &);
// The declared node allocation binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?_M_create_node@?$list@PAVRva004246BDObj@@V?$allocator@PAVRva004246BDObj@@@_STL@@@_STL@@IAEPAU?$_List_node@PAVRva004246BDObj@@@2@ABQAVRva004246BDObj@@@Z=?rva00423D0DCreate@@YGPAXH@Z")
