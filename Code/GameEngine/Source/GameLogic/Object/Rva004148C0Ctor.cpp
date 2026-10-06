// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0Rva004147CF@@QAE@ABVAsciiString@@@Z, retail 0x004148C0, 114 bytes. Ctor
// of Snapshot subclass Rva004147CF (vtable at [this]): AsciiString at +4 via
// rowed StringBase copy 0x000365F0, ints at +8/-1 +C/0xA +10/g_Va00DBA4E4,
// member at +14 via rowed 0x003623E5, flags at +18/+19, vector<BfmeE16> at
// +1C via rowed Vector_base 0x00211E58, ints at +28/+2C zeroed. Evidence:
// leaf packet stores vtable and calls rowed bodies; layout mirrors sibling
// Rva00414932Dtor plus stlport_asciistring_record_bodies; caller at 0x00414FD6.
#include <vector>

#include "ascii_string.h"
#include "Common/Snapshot.h"

struct BfmeE16 { float x; float y; float z; float w; };

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
private:
	unsigned int m_record;
};

extern int g_Va00DBA4E4;

class Rva004147CF : public Snapshot
{
public:
	Rva004147CF(const AsciiString &name);
private:
	AsciiString m_str04;
	int m_unk08;
	int m_unk0C;
	int m_unk10;
	Rva003623E5Member m_member14;
	bool m_flag18;
	bool m_flag19;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec1C;
	int m_unk28;
	int m_unk2C;
};

Rva004147CF::Rva004147CF(const AsciiString &name)
	: m_str04(name)
	, m_unk08(-1)
	, m_unk0C(10)
	, m_unk10(g_Va00DBA4E4)
	, m_flag18(true)
	, m_flag19(true)
	, m_vec1C(_STL::allocator<BfmeE16>())
	, m_unk28(0)
	, m_unk2C(0)
{
}
