// cl: /O1 /DNDEBUG /MD /GX
//
// Bodies ported from Open-BFME-1's
// Libraries/Source/WWVegas/WWLib/RvaStringAccessor.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva001A6F90Host::copyStringAt54 0x0027F5C1 (27B),
// Rva001A6FC0Host::copyStringAt58 0x0027F5DC (27B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

// Open-BFME5: 31 by-value string accessors, 32 or 35 bytes each.  Every one
// carried only a machine byte-dump row; over a hundred bodies of exactly this
// shape are already converted, in native_network.cpp and lanapi.cpp among
// others.
//
// The whole body is one return: copy-construct the caller's return slot from a
// string that lives at a fixed offset inside the object.  `add ecx, N` is that
// offset and it is the only thing that varies between them -- 35 bytes rather
// than 32 wherever N needs a dword instead of a byte.
//
// The copy constructor names the string.  Twenty-one reach 0x00887B60, which is
// the four-byte narrow string's; two reach 0x00888400 and one 0x004FB220, both
// wide.  Seven reach copy constructors that are themselves still dumps, so
// those get a string class of their own with the constructor pinned to the
// address the body calls -- four bytes wide and copied out of line, which is
// all the call proves.
//
// The HOSTS are not recovered at all.  Nothing in 32 bytes says what object
// holds the string, only that it holds one at that offset, so each host is a
// class named for the address of its accessor.

namespace _STL
{

template <class Character>
class char_traits
{
};

template <class Character>
class allocator
{
};

// The destructor is what makes these bodies 32 bytes rather than 24: with
// exceptions on, a by-value return of a type that has one needs an unwind state
// slot, which is the `push ecx` and the zero stored into it.
template <class Character, class Traits, class Alloc>
class basic_string
{
public:
	basic_string( const basic_string &other );
	~basic_string();
};

}

template <class Character>
class StringBase
{
public:
	StringBase( const StringBase &other );
	~StringBase();
};

// One of the public names the 0x00887B60 fold already carries in the ledger.
template <class Character>
class BFMERetailStringBase
{
public:
	BFMERetailStringBase( const BFMERetailStringBase &other );
	~BFMERetailStringBase();
};

// 0x00887B60 and 0x004FB1B0 are BOTH four-byte-string copy constructors and
// they are NOT the same function -- 121 bytes against 86.  The first is the
// identical-code-folding group the ledger already knows as StringBase<char>'s,
// reached under half a dozen public names; the second is _STL::basic_string's.
// Twenty-one of these accessors call the first and five the second, so they
// return different string classes and are spelled that way.
typedef BFMERetailStringBase<char> BfmeRetailNarrowString;
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	BfmeNarrowString;
typedef _STL::basic_string<unsigned short, _STL::char_traits<unsigned short>,
	_STL::allocator<unsigned short> > BfmeWideString;
typedef StringBase<unsigned short> BfmeWideStringBase;

class Rva00083DA0Host
{
public:
	BfmeWideStringBase copyStringAt1280( void );
};


class Rva0009F820String
{
public:
	Rva0009F820String( const Rva0009F820String &other );
	~Rva0009F820String();
};

class Rva0009F820Host
{
public:
	Rva0009F820String copyStringAt14( void );
};


class Rva00193D20Host
{
public:
	BfmeRetailNarrowString copyStringAt30( void );
};


class Rva001A6F90Host
{
public:
	BfmeRetailNarrowString copyStringAt54( void );
};

// retail 0x001A6F90, the string at +0x54
BfmeRetailNarrowString Rva001A6F90Host::copyStringAt54( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x54 );
}

class Rva001A6FC0Host
{
public:
	BfmeRetailNarrowString copyStringAt58( void );
};

// retail 0x001A6FC0, the string at +0x58
BfmeRetailNarrowString Rva001A6FC0Host::copyStringAt58( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x58 );
}

class Rva001C42B0Host
{
public:
	BfmeRetailNarrowString copyStringAt270( void );
};


class Rva00235D20Host
{
public:
	BfmeRetailNarrowString copyStringAt240( void );
};


class Rva00338EF0Host
{
public:
	BfmeRetailNarrowString copyStringAt30( void );
};


class Rva0037B100Host
{
public:
	BfmeRetailNarrowString copyStringAtF4( void );
};


class Rva00385F20Host
{
public:
	BfmeWideStringBase copyStringAt418( void );
};


class Rva00415BF0Host
{
public:
	BfmeRetailNarrowString copyStringAt7C4( void );
};


class Rva00465550Host
{
public:
	BfmeRetailNarrowString copyStringAt254( void );
};


class Rva004A3C00Host
{
public:
	BfmeRetailNarrowString copyStringAt184( void );
};


class Rva004D7AC0Host
{
public:
	BfmeRetailNarrowString copyStringAt444( void );
};


class Rva00537630String
{
public:
	Rva00537630String( const Rva00537630String &other );
	~Rva00537630String();
};

class Rva00537630Host
{
public:
	Rva00537630String copyStringAt20( void );
};


class Rva00629ED0Host
{
public:
	BfmeRetailNarrowString copyStringAt8C( void );
};


class Rva0062C8B0Host
{
public:
	BfmeRetailNarrowString copyStringAt448( void );
};


class Rva006372A0Host
{
public:
	BfmeRetailNarrowString copyStringAt6C( void );
};


class Rva00637360Host
{
public:
	BfmeRetailNarrowString copyStringAt74( void );
};


class Rva00637450Host
{
public:
	BfmeRetailNarrowString copyStringAt7C( void );
};


class Rva006380C0Host
{
public:
	BfmeRetailNarrowString copyStringAt74( void );
};


class Rva00647720Host
{
public:
	BfmeNarrowString copyStringAtB0( void );
};


class Rva00647750Host
{
public:
	BfmeNarrowString copyStringAtC0( void );
};


class Rva00647780Host
{
public:
	BfmeWideString copyStringAt218( void );
};


class Rva006477B0Host
{
public:
	BfmeNarrowString copyStringAt14C( void );
};


class Rva006477E0Host
{
public:
	BfmeNarrowString copyStringAt140( void );
};


class Rva00647920Host
{
public:
	BfmeNarrowString copyStringAt3CC( void );
};


class Rva0068AEC0Host
{
public:
	BfmeRetailNarrowString copyStringAt60( void );
};


class Rva00751390Host
{
public:
	BfmeRetailNarrowString copyStringAt5C( void );
};


class Rva00759500Host
{
public:
	// retail returns with `ret 8`, so this one takes an argument it never reads
	BfmeRetailNarrowString copyStringAt8( int unused );
};


