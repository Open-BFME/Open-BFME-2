// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport

// STLport _Rb_tree<AsciiString, V>::insert_unique(const value_type
// &) for the three trees whose comparator is case-insensitive -- 275 bytes each
// where the case-sensitive siblings in reference/open-bfme-1's 
// RvaTreeInsertUniquePlain.cpp are 310.
//
// The thirty-five byte difference is the comparison.  less<AsciiString> inlines
// AsciiString::compare -- two lengths as halfwords, repe cmpsb, the length
// difference as the tiebreak -- at both comparison sites.  This comparator does
// not: what these bodies call at both sites is
// StringBase<char>::compareNoCase, out of line, which is why the shim used here
// is stringbaseascii rather than the case-sensitive file's.
//
// The comparator has no name the bytes reach, so it is spelled for the function
// it calls, exactly as the _M_insert conversions in reference/open-bfme-1's 
// RvaTreeMInsertStringKey.cpp already spell it; the tree types come from those
// _M_insert bodies unchanged,
// which is why the mapped types are named for the _M_insert's address.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/AsciiString.h"

// The CRT import, not the static one: retail reaches _memicmp through the
// import table, so the comparison ends in `call dword ptr [__imp__memicmp]`
// rather than a direct call.
extern "C" __declspec(dllimport) int __cdecl _memicmp( const void *buf1, const void *buf2, unsigned int count );

// StringBase<char>::compareNoCase, spelled out where the sibling
// reference/open-bfme-1's RvaTreeInsertUniquePlain.cpp lets the shim spell compare.  It has to be a
// real function rather than a hand-inlined expression, because retail expands
// it at one of the two comparison sites in each of these bodies and calls the
// out-of-line copy at 0x00090570 at the other -- an inline budget spent inside
// the loop and refused afterwards.  Written this way MSVC is given the same
// choice and makes the same one.  The shape is compare's: the length as a
// halfword at +4 of the header, a null pointer standing in for the empty
// string, the length difference as the tiebreak.
template <>
inline int StringBase<char>::compareNoCase( const StringBase<char> &str ) const
{
	int thatLen = str.m_data ? str.m_data->length : 0;
	const char *thatData = str.m_data ? &str.m_data->data[ 0 ] : (const char *)"";
	int thisLen = m_data ? m_data->length : 0;
	const char *thisData = m_data ? &m_data->data[ 0 ] : (const char *)"";
	int n = thisLen < thatLen ? thisLen : thatLen;
	int c = _memicmp( thisData, thatData, n );
	if ( c != 0 )
		return c;
	return thisLen - thatLen;
}

// The comparator has no name the bytes reach; it is spelled for the function it
// calls, exactly as the _M_insert conversions in reference/open-bfme-1's 
// RvaTreeMInsertStringKey.cpp already spell it.
struct BfmeStringNoCaseLess
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const
	{
		return ( (const StringBase<char> *)&left )->compareNoCase( *(const StringBase<char> *)&right ) < 0;
	}
};

// Nothing in these bytes says what the mapped type actually is, so each is
// spelled as a plain N-byte payload; retail addresses are documented per tree
// below rather than baked into the identifier.
struct NoCaseTreeValue4
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCaseTreePair4;

typedef _STL::_Rb_tree<AsciiString, NoCaseTreePair4, _STL::_Select1st<NoCaseTreePair4>,
	BfmeStringNoCaseLess, _STL::allocator<NoCaseTreePair4> > NoCaseTree4;

// retail 0x00093760, inserting through the _M_insert at 0x00093670
template _STL::pair<NoCaseTree4::iterator, bool>
NoCaseTree4::insert_unique( const NoCaseTreePair4 & );

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	BfmeStringNoCaseLess, _STL::allocator<AsciiString> > NoCaseStringSet;

// retail 0x00197270, inserting through the _M_insert at 0x00195D30 -- a set of the key
template _STL::pair<NoCaseStringSet::iterator, bool>
NoCaseStringSet::insert_unique( const AsciiString & );

struct NoCaseTreeValue8
{
	char m_body[ 8 ];
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue8> NoCaseTreePair8;

typedef _STL::_Rb_tree<AsciiString, NoCaseTreePair8, _STL::_Select1st<NoCaseTreePair8>,
	BfmeStringNoCaseLess, _STL::allocator<NoCaseTreePair8> > NoCaseTree8;

// retail 0x003D4320, inserting through the _M_insert at 0x003D3F90
template _STL::pair<NoCaseTree8::iterator, bool>
NoCaseTree8::insert_unique( const NoCaseTreePair8 & );
