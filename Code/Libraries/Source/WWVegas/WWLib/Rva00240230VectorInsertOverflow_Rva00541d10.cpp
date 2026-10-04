// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS /Os -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ?insert@?$vector@URva00244A80Element@@V?$allocator@URva00244A80Element@@@_STL@@@_STL@@QAEPAURva00244A80Element@@PAU3@ABU3@@Z
// retail 0x00541D10, 152 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/Libraries/Source/WWVegas/WWLib/Rva00240230VectorInsertOverflow.cpp: the
// donor preamble and this one vector<Rva00244A80Element> member, the donor's
// other instantiations omitted. The 28-byte element payload is not recovered;
// its width and nontrivial copy operations are fixed by the retail body.
#include <vector>

struct Rva00244A80Element
{
	char m_body[28];
	Rva00244A80Element();
	Rva00244A80Element(const Rva00244A80Element &other);
	Rva00244A80Element &operator=(const Rva00244A80Element &other);
};

template Rva00244A80Element * _STL::vector<Rva00244A80Element>::insert(
	Rva00244A80Element *, const Rva00244A80Element &);
