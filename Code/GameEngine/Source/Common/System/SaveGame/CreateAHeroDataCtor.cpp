// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0CreateAHeroData@@QAE@HHHABVUnicodeString@@HHH@Z, retail
// 0x00409C3D..0x00409D31 (244 bytes, EH, ret 0x1C): CreateAHeroData's value
// constructor (pinned; GameSlot's constructor and the hero managers call it).
// The 0x140-byte Snapshot-derived layout is the one CreateAHeroDataCopy.cpp
// recovers (table 0x00C38D88): the first argument at +4, the name at +8, the
// next two at +0x0C/+0x10, the last three at +0x2C..+0x34, 0x2FF at +0x38, the
// trees, string vector, bit vector and int-keyed vector map, and fifteen
// 12-byte elements through the EH vector constructor iterator over the rowed
// element ctor 0x005C39DE; the new hero then registers itself (pinned
// 0x0021D517). Container members are spelled with the instantiations whose
// rowed default constructors retail calls (the int-keyed tree ctor 0x0033C432
// serves all three trees; the vector map ctor is 0x00413727).
#include <vector>
#include <map>
#include "Common/Snapshot.h"
#include "ascii_string.h"
#include "unicode_string.h"
// bfme link decl-only begin
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$_Bvector_base@V?$allocator@_N@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Bvector_base<allocator<bool> >::~_Bvector_base(); }

struct Rva00501875Count
{
	int m_count;
};

// Use the verified provider in Rva00501875KeyPresence.cpp for EH cleanup.
namespace _STL {
template <> _Rb_tree<int, pair<const int, Rva00501875Count>,
    _Select1st<pair<const int, Rva00501875Count> >, less<int>,
    allocator<pair<const int, Rva00501875Count> > >::~_Rb_tree();
}

struct BfmeE8
{
	float x;
	float y;
};

#include "../../../../Include/Common/BfmeHeroElement005C39DE.h"

class CreateAHeroData;
void RegisterCreateAHeroAtRva0021D517(CreateAHeroData *);	// 0x0021D517

typedef _STL::map<int, Rva00501875Count> CreateAHeroTree;
typedef _STL::map<int, _STL::vector<_STL::vector<BfmeE8> > > CreateAHeroVectorMap;

// EH cleanup uses the existing STLport destructor providers.
namespace _STL {
template <> vector<bool, allocator<bool> >::~vector();
template <> vector<vector<BfmeE8>, allocator<vector<BfmeE8> > >::~vector();
template <> _Rb_tree<int, pair<const int, vector<vector<BfmeE8> > >,
    _Select1st<pair<const int, vector<vector<BfmeE8> > > >, less<int>,
    allocator<pair<const int, vector<vector<BfmeE8> > > > >::~_Rb_tree();
}

class CreateAHeroData : public Snapshot
{
public:
	CreateAHeroData(int word04, int word0C, int word10, const UnicodeString &text, int word2C, int word30, int word34);
	virtual ~CreateAHeroData();

public:
	// Declared like CreateAHeroDataCopy.cpp's view so every unit emits the same vtable copy.
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
protected:
	virtual void loadPostProcess();

private:
	unsigned int word04;
	UnicodeString text08;
	unsigned int word0C, word10;
	CreateAHeroTree map14, map20;
	unsigned int word2C, word30, word34, word38;
	_STL::vector<AsciiString> strings3C;
	unsigned char flag48;
	AsciiString text4C;
	CreateAHeroTree map50;
	_STL::vector<bool> bits5C;
	unsigned char flag70, flag71;
	CreateAHeroVectorMap map74;
	BfmeHeroElement005C39DE elements80[15];
	unsigned int word134, word138, word13C;
};

CreateAHeroData::CreateAHeroData(int a, int b, int c, const UnicodeString &text, int d, int e, int f)
	: word04(a), text08(text), word0C(b), word10(c),
	  word2C(d), word30(e), word34(f), word38(0x2FF),
	  flag48(0), flag70(0), flag71(0),
	  word134(0), word138(0), word13C(0)
{
	RegisterCreateAHeroAtRva0021D517(this);
}
