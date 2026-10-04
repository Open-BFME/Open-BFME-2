// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$_M_allocate_and_copy@PAURva004F6986@@@?$vector@URva004F6986@@V?$allocator@URva004F6986@@@_STL@@@_STL@@IAEPAURva004F6986@@IPAU2@0@Z
// retail 0x004F6BD8, 45 bytes.
//
// Dedicated no-EH instantiation of vector<Rva004F6986>::_M_allocate_and_copy,
// the 8-byte-element body. Evidence: the matched reserve
// ?reserve@?$vector@URva004F6986@@ at 0x004F8B21 calls it, with `sar 3` in the
// caller confirming the 8-byte stride, and the allocator it calls is the
// address 0x00523D6C already pinned as the STLport 8-byte `allocate`.
// The copy worker it calls is pinned at 0x004F6A88 as the __uninitialized_copy
// instantiation over that same element type, so the emitted callee name is the
// stock stlport one rather than a hand-rolled shim's.
//
// Spelled with the stock stlport headers and an explicit instantiation of the
// whole class, as stlport_vector_e8_allocate_copy.cpp does, which is what makes
// the emitted __uninitialized_copy symbol resolve to retail's.

#include <vector>

struct Rva004F6986
{
	~Rva004F6986();
	char m_pad[8];
};

template class _STL::vector<Rva004F6986, _STL::allocator<Rva004F6986> >;