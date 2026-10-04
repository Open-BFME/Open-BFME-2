// cl: /D_CRTIMP= /Ireference/shims/bfmealloc/stl -DNDEBUG -DWIN32 -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/Containers
// stlport

// retail RVA 0x003A39C0. A temporary Rva003A35A0Element (the same 184-byte
// STLport vector element already landed at 0x003A35F0,
// Rva003A35F0VectorInsert.cpp) is default-constructed through the pinned
// 0x22F0C ctor, its three words at +0xA4..+0xAC overwritten from the incoming
// pointer argument, and the result inserted at this->m_index20+2 into the
// vector at this+0x2C. No named caller, owner class or field identity is
// available, so the owner and fields are address-derived.

#include <cstddef>
#include "_alloc.h"
#include <vector>
// Match the existing retail 17-byte unsigned max COMDAT without changing
// the /O1 insert family or selecting a conflicting library definition.
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int& max<unsigned int>(const unsigned int& a, const unsigned int& b) { return a < b ? b : a; }
}
#pragma optimize("", on)

struct Rva003A39C0Words { int word00, word04, word08; };
struct Rva003A35A0Element
{
	int prefix[41];
	Rva003A39C0Words position;
	int tail[2];

	Rva003A35A0Element();
	Rva003A35A0Element(const Rva003A35A0Element &);
	~Rva003A35A0Element();
	Rva003A35A0Element &operator=(const Rva003A35A0Element &other);
};


struct Rva003A39C0Owner
{
	void insertAfterIndex(const Rva003A39C0Words &src);

	unsigned char m_prefix[0x20];
	int m_index20;					// +0x20
	unsigned char m_gap24[0x2c - 0x20 - 4];
	_STL::vector<Rva003A35A0Element> m_records;	// +0x2c
};

// retail RVA 0x003A39C0
void Rva003A39C0Owner::insertAfterIndex(const Rva003A39C0Words &src)
{
	Rva003A35A0Element temp;

	temp.position = src;

	m_records.insert(m_records.begin() + (m_index20 + 2), temp);
}
