// cl: /D_CRTIMP= /Ireference/shims/bfmealloc/stl -DNDEBUG -DWIN32 -MD -EHsc -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/Containers
// stlport

#define _STLP_NO_EXCEPTIONS 1
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

struct Rva003A3B50Input
{
	int word00, word04, word08;
};

struct Rva003A35A0Element
{
	unsigned char m_prefix[0xA4];
	Rva003A3B50Input m_point;
	unsigned char m_tail[8];

	// Native call at 0x003130EE reaches the verified default ctor 0x003118DF.
	// The donor's different address does not identify a BFME2 body.
	Rva003A35A0Element();
	Rva003A35A0Element( const Rva003A35A0Element & );
	~Rva003A35A0Element();
	Rva003A35A0Element &operator=( const Rva003A35A0Element &other );
};

class Rva003A3B50Owner
{
public:
	void append( const Rva003A3B50Input *value );

private:
	char m_unreconstructed_00[ 0x2C ];
	_STL::vector<Rva003A35A0Element> m_elements;
};

// ?append@Rva003A3B50Owner@@QAEXPBURva003A3B50Input@@@Z
void Rva003A3B50Owner::append( const Rva003A3B50Input *value )
{
	Rva003A35A0Element element;
	element.m_point = *value;
	m_elements.push_back( element );
}
