// ??0BfmePod264@@QAE@ABU0@@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0BfmePod264@@QAE@ABU0@@Z @0x00289CEB 143B
// Evidence: pin copy ctor; callers _Construct 0x00289E85 and 0x0028A4CF; callees Vector_base 0x00211E58 x4 and member ctors 0x00042526 0x00330E5D and assign 0x00289902; offsets 0x24 0x30 0x3c 0x4c 0x58 0xa4.
#include <vector>
#include "ascii_string.h"

extern const void *const g_00BFB840[];

struct PlayerAITypeEntry
{
	AsciiString name;
	char unknown[12];
};

class Rva0042526Member
{
public:
	Rva0042526Member();
	~Rva0042526Member();
	char _pad[76];
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();
	char _pad[100];
};

struct Rva00289FBCRecord
{
	Rva00289FBCRecord &operator=(const Rva00289FBCRecord &that);
};

struct BfmePod264 : public Rva00289FBCRecord
{
	const void *m_00;
	int m_04;
	unsigned char m_08;
	char _p09[3];
	int m_0c;
	int m_10;
	char _pad14[0x10];
	_STL::vector<PlayerAITypeEntry> m_24;
	_STL::vector<PlayerAITypeEntry> m_30;
	_STL::vector<PlayerAITypeEntry> m_3c;
	char _pad48[4];
	_STL::vector<PlayerAITypeEntry> m_4c;
	Rva0042526Member m_58;
	RadiusDecalTemplate m_a4;
	BfmePod264(const BfmePod264 &that);
};

BfmePod264::BfmePod264(const BfmePod264 &that)
	: m_00((const void *)g_00BFB840)
	, m_04(0)
	, m_08(0)
	, m_0c(-1)
	, m_10(0)
	, m_24()
	, m_30()
	, m_3c()
	, m_4c()
	, m_58()
	, m_a4()
{
	Rva00289FBCRecord::operator=((const Rva00289FBCRecord &)that);
}
