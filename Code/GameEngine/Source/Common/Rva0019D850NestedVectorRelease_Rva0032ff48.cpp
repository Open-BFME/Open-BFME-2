// cl: -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// ?resize@?$vector@V?$vector@URva0019D850Value@@V?$allocator@URva0019D850Value@@@_STL@@@_STL@@V?$allocator@V?$vector@URva0019D850Value@@V?$allocator@URva0019D850Value@@@_STL@@@_STL@@@2@@_STL@@QAEXI@Z
// retail 0x0032FF48, 73 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva0019D850NestedVectorRelease.cpp: the donor
// preamble and this one vector<vector<Rva0019D850Value> > member, the donor's
// other definitions omitted. Rva0019D850Value is an opaque twelve-byte payload
// stand-in; the outer resize body only constructs, resizes and destroys a
// temporary element, so no element identity reaches the bytes.
#include <vector>

struct Rva0019D850Value
{
	int m_words[3];
};

template void _STL::vector<_STL::vector<Rva0019D850Value> >::resize(unsigned int);
