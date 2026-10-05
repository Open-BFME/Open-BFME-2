// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$_M_allocate_and_copy@PAURva005C8624Element@@@?$vector@URva005C8624Element@@V?$allocator@URva005C8624Element@@@_STL@@@_STL@@IAEPAURva005C8624Element@@IPAU2@0@Z
// Retail 0x005C8445, 45 bytes. STLport vector<Rva005C8624Element>
// _M_allocate_and_copy (stride 0x48). Calls allocator<Rva005C8624Element>
// allocate (ICF twin of BfmePod72 allocate at 0x000B4106) and the landed
// __uninitialized_copy at 0x005C83FA. Same ebp+tag shape as vector<BfmeE8>
// _M_allocate_and_copy at 0x001D9AD9 which calls the PAU/PAU __false_type
// overload. Dedicated no-EH TU like stlport_vector_e8_allocate_copy.cpp.

#include <vector>
struct Rva005C8624Element
{
	int a[18];
};
template class _STL::vector<Rva005C8624Element, _STL::allocator<Rva005C8624Element> >;
