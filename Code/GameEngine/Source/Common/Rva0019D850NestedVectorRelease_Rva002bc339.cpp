// cl: -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// ??0?$vector@V?$vector@URva002BC339Value@@V?$allocator@URva002BC339Value@@@_STL@@@_STL@@V?$allocator@V?$vector@URva002BC339Value@@V?$allocator@URva002BC339Value@@@_STL@@@_STL@@@2@@_STL@@QAE@I@Z
// retail 0x002BC339, 100 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva0019D850NestedVectorRelease.cpp: the donor
// preamble and this one vector<vector<Rva002BC339Value>> fill constructor, the
// donor's other definitions omitted. Rva002BC339Value is a per-RVA opaque
// twelve-byte payload stand-in (the donor's own convention, so every decorated
// name in the instantiation is unique and no symbol is given a second address);
// only the buffer and its zeroing reach the bytes.
#include <vector>

struct Rva002BC339Value
{
	int m_words[3];
};

template _STL::vector<_STL::vector<Rva002BC339Value> >::vector(unsigned int);
