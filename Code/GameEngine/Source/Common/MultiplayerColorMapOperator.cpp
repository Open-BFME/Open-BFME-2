// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Ported from reference/open-bfme-1/Code/GameEngine/Source/Common/MultiplayerColorMapOperator.cpp.
// Retail 0x003812E6 (141B) is the color-list miss-path body: lower_bound over
// the map, default-constructed insertion value on miss, pair construction plus
// hinted insert, twin member-teardown cleanups. Served as lookup@PAH (the key
// travels by address, dereferenced inside); the expansion below is
// map<Int, MCD>::operator[] reached through the RetailColorList wrapper.
// BFME2 value model is 0x40 bytes (see MultiplayerColorPairConstructor.cpp),
// not the reference's 0x24-byte shape.

#include <map>

typedef int Int;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase() : m_data(0) {}

private:
	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other);
	~AsciiString();
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();
	MultiplayerColorDefinition(const MultiplayerColorDefinition &other);

private:
	AsciiString m_tooltipName; // +0x00
	RGBColor m_rgbValue; // +0x04
	int m_color; // +0x10
	RGBColor m_rgbValueNight; // +0x14
	int m_colorNight; // +0x20
	RGBColor m_rgbExtra1; // +0x24
	RGBColor m_rgbExtra2; // +0x30
	bool m_extraFlag; // +0x3C
};

typedef char MultiplayerColorMapValueMatchesRetail[(sizeof(MultiplayerColorDefinition) == 0x40) ? 1 : -1];

typedef std::map<Int, MultiplayerColorDefinition> MultiplayerColorList;

namespace _STL
{
	// Declared (never defined here) so the subscript calls out of line to the
	// landed pair body instead of inlining it.
	template <>
	__declspec(noinline) pair<const Int, MultiplayerColorDefinition>::pair(
		const Int &firstValue, const MultiplayerColorDefinition &secondValue);
}

// Retail shares one ret and one NULL store for all getColor paths; the list
// itself lives at settings+0x34 (node count at +0x34 per the rowed getColor).
struct RetailColorList
{
	MultiplayerColorList m_list;
	MultiplayerColorDefinition *lookup(int *which);
};

// Hand-expanded miss path (the header's operator[] lowers the insertion value
// through a __default_constructed helper retail never calls): fully nested
// temporaries so each construction feeds the next call straight out of eax,
// with twin member-teardown cleanups for the two temps.
MultiplayerColorDefinition *RetailColorList::lookup(int *which)
{
	MultiplayerColorList::iterator it = m_list.lower_bound(*which);
	if (it == m_list.end() || *which < it->first)
		it = m_list.insert(it, MultiplayerColorList::value_type(*which, MultiplayerColorDefinition()));
	return &it->second;
}
