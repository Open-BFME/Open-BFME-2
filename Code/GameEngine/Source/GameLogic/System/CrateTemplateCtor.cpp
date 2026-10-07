// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0CrateTemplate@@QAE@XZ, retail 0x0035CC36 (148B).
// CrateTemplate::CrateTemplate (Zero Hour CrateSystem.cpp). Identity: the
// rowed CrateSystem::newCrateTemplate 0x0035CF2C and newCrateTemplateOverride
// 0x0035CEA6 new 0x44 bytes and call this ctor, then CrateTemplate's
// operator= 0x0035CE52; the class's vtable is 0x00C16394 and its dtor
// 0x0035CCCA (CrateTemplateDtor.cpp). Zero Hour's members in order: name
// +0x10, creationChance +0x14, veterancyLevel +0x18, killedByType mask +0x1C,
// killerScience +0x38, possibleCrates list +0x3C, isOwnedByMaker +0x40. The
// views below keep the spellings the bytes were matched with.
// Base (Overridable, here the opaque Rva001E3624) trivial (4/8/0C), string +0x10 zeroed then set to empty,
// float +0x14 0.0, int +0x18 5, member +0x1C via rowed Rva0024C7B3Member
// ctor then memset 0x1C (double zero is retail), int +0x38 -1 (or),
// list +0x3C via rowed BfmePod8 ctor then AsciiString clear (same storage,
// union; Bfme spelling required for 0x35C9A6 bytes though object is the
// AsciiString list the dtor clears), byte +0x40 0 via direct store
// (overlaps list prev low byte in retail).

#include "ascii_string.h"
#include <list>

#pragma function(memset)

extern "C" void *memset(void *dst, int value, unsigned int size);

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	unsigned char m_data[0x1C];
};

struct BfmePod8 { int a[2]; };

class Rva001E3624
{
public:
	Rva001E3624() : m_unk04(0), m_unk08(0), m_unk0C(-1) {}
	virtual ~Rva001E3624();
	void *m_unk04;
	unsigned char m_unk08;
	int m_unk0C;
};

class CrateTemplate : public Rva001E3624
{
public:
	CrateTemplate();
protected:
	virtual ~CrateTemplate();	// CrateTemplateDtor.cpp (pool glue keeps it protected)
public:
	AsciiString m_str10;
	float m_flt14;
	int m_int18;
	Rva0024C7B3Member m_mem1C;
	int m_neg38;
	_STL::list<BfmePod8> m_list3C;
};

CrateTemplate::CrateTemplate()
{
	m_str10.set("");
	m_flt14 = 0.0f;
	memset(&m_mem1C, 0, 0x1C);
	m_neg38 = -1;
	m_int18 = 5;
	((_STL::list<AsciiString> *)&m_list3C)->clear();
	*(unsigned char *)((char *)this + 0x40) = 0;
}
