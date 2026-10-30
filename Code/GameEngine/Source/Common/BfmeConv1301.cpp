// cl: /DNDEBUG /MD /EHsc /Od /Ob1 /Gy /D_STLP_USE_STATIC_LIB
// stlport46
// Open-BFME5 conversions.
// ?bfmeTwoSUA@BfmeThingSUA@@QAEXD@Z, retail 0x0002A090 (27B). Ported from
// Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1301.cpp (BFME1 0x00830390).
// Its target is the rowed bfmeAssignV16 at 0x00029490 (same B1 body
// 0x0082FB10), spelled with its rowed BfmeStrV16 name; zero bytes differ
// either way.
//
// Retail 0x000274D0 (107B) and 0x00028BF0 (27B) are STLport 4.6
// basic_string<char>::find(char, size_type) const (_string.c:354) and its
// inline find(char) const forwarder (_string.h:1079), instantiated below.
#include <string>

// find(char, size_type)'s byte search is find_if<const char *, _Eq_char_bound>
// at 0x00026C60, whose body lives in BfmeTwoHundredFiftySeven_FindByte.cpp; do
// not instantiate a second /Od copy here.
extern template const char *_STL::find_if(const char *, const char *,
	_STL::_Eq_char_bound<_STL::char_traits<char> >);

// rfind(char, size_type) at 0x000275C0 is instantiated in BfmeConv1481.cpp.
extern template _STL::string::size_type _STL::string::rfind(char, _STL::string::size_type) const;

// Retail 0x00028CF0 (29B) is the inline find_last_of(char, size_type) const
// forwarder to rfind(char, size_type) (_string.h:1120).
namespace _STL {
template string::size_type string::find(char, string::size_type) const;
template string::size_type string::find(char) const;
template string::size_type string::find_last_of(char, string::size_type) const;
}

class BfmeThingSUA
{
public:
	void bfmeTwoSUA(char a);
};

class BfmeStrV16
{
public:
	BfmeStrV16 *bfmeAssignV16(unsigned int id, char tag);
};

// ?bfmeTwoSUA@BfmeThingSUA@@QAEXD@Z
void BfmeThingSUA::bfmeTwoSUA(char a)
{
	((BfmeStrV16 *)this)->bfmeAssignV16(1, a);
}
