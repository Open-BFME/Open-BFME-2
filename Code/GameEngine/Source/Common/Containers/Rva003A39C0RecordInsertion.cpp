// cl: /D_CRTIMP= /Ireference/shims/bfmealloc/stl -DNDEBUG -DWIN32 -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/Containers
// stlport

// Native BFME2 indexed wrapper313008/108B constructs the measured184B
// element via3118DF, copies12 raw bytes into+A4, inserts at index20+2 in
// the vector at owner+2C via312E04, then destroys the temporary via89851.
// Native constructor312C95 stores vtable7C7514; its slots4/5 identify this
// indexed operation and the begin-insert operation313074 below as one owner.
// This remains a partial layout/codegen view. Original owner/input names
// and the input words' semantic scalar types are not established.

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
	void insertAtBegin(const Rva003A39C0Words &src);

	unsigned char m_prefix[0x20];
	int m_index20;					// +0x20
	unsigned char m_gap24[0x2c - 0x20 - 4];
	_STL::vector<Rva003A35A0Element> m_records;	// +0x2c
};

// Native BFME2 RVA0x00313008.
void Rva003A39C0Owner::insertAfterIndex(const Rva003A39C0Words &src)
{
	Rva003A35A0Element temp;

	temp.position = src;

	m_records.insert(m_records.begin() + (m_index20 + 2), temp);
}


// Whole donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/Containers/Rva003A3A90.cpp. Its begin-insert
// semantics carry over; target313074/95B uses an aggregate12B copy at+A4
// where that donor spelled three scalar assignments. Native ctor/insert/
// dtor calls and the shared vtable establish the target relationships;
// donor names do not establish original application owner or input types.
void Rva003A39C0Owner::insertAtBegin(const Rva003A39C0Words &src)
{
    Rva003A35A0Element temp;
    temp.position=src;
    m_records.insert(m_records.begin(),temp);
}
