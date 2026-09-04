// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport

// Open-BFME5: STLport map<AsciiString, V>::operator[] -- six bodies of 169
// bytes that carried only a machine byte-dump row.
//
// The shape is STLport's own: lower_bound, then a comparison against the
// candidate to decide whether the key is already there, and on a miss a
// value_type built from the key and a value-initialised mapped type, handed to
// the hinted insert.  The SEH prologue and the call to StringBase<char>'s
// destructor on the way out are that temporary's.
//
// Neither tree needs guessing.  Each body calls a _M_lower_bound and a hinted
// insert_unique that are already converted elsewhere in the repo, and the
// insert_unique names the value_type outright -- pair<const AsciiString, V>
// with a four-byte V, which agrees with the mapped reference this body returns
// at node+0x14.  The mapped types keep the names those conversions gave them.
//
// The two callees were spelled by different hands: the insert_unique rows carry
// the map spelling used here, while the _M_lower_bound rows spell the same tree
// through a key-of-value functor.  Only one spelling can be in one file, so the
// insert_unique resolves by name and each _M_lower_bound gets a pin at the ILT
// thunk this body reaches.

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <map>

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};
}

enum IndexMapValueA { IndexMapValueAZero = 0 };

typedef _STL::map<AsciiString, IndexMapValueA, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, IndexMapValueA> > > IndexMapA;

// retail 0x00347820, over the tree whose _M_lower_bound is at 0x0033F2E0
template IndexMapValueA &IndexMapA::operator[]( const AsciiString & );
enum IndexMapValueB { IndexMapValueBZero = 0 };

typedef _STL::map<AsciiString, IndexMapValueB, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, IndexMapValueB> > > IndexMapB;

// retail 0x003BAEF0, over the tree whose _M_lower_bound is at 0x003B9A10
template IndexMapValueB &IndexMapB::operator[]( const AsciiString & );
enum IndexMapValueC { IndexMapValueCZero = 0 };

typedef _STL::map<AsciiString, IndexMapValueC, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, IndexMapValueC> > > IndexMapC;

// retail 0x0044A860, over the tree whose _M_lower_bound is at 0x00448AD0
template IndexMapValueC &IndexMapC::operator[]( const AsciiString & );
// This one's mapped type is a single byte -- retail stores the
// default-constructed value with `mov BYTE PTR [esp+0x10], al` where its five
// siblings store a dword -- so it is one byte wide and not a four-byte
// enumeration.  It is spelled char rather than bool only because the bool
// instantiation of this same operator is already a matched row at 0x00063960
// and one name may name one address; the bytes cannot tell the two apart.
typedef _STL::map<AsciiString, char, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, char> > > IndexMapD;

// retail 0x004545A0, over the tree whose _M_lower_bound is at 0x00452E60
template char &IndexMapD::operator[]( const AsciiString & );
enum IndexMapValueE { IndexMapValueEZero = 0 };

typedef _STL::map<AsciiString, IndexMapValueE, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, IndexMapValueE> > > IndexMapE;

// retail 0x00463D50, over the tree whose _M_lower_bound is at 0x00460F80
template IndexMapValueE &IndexMapE::operator[]( const AsciiString & );
enum IndexMapValueF { IndexMapValueFZero = 0 };

typedef _STL::map<AsciiString, IndexMapValueF, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, IndexMapValueF> > > IndexMapF;

// retail 0x00476F70, over the tree whose _M_lower_bound is at 0x00474CD0
template IndexMapValueF &IndexMapF::operator[]( const AsciiString & );
