// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?SetSlotString@Impl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEXHPBDABVUnicodeString@@@Z retail 0x005FD788 116B
// Evidence: format APT:_level%u.%s_%s%s via 0x00038150; bfmeSetText via pin 0x00225301; releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C 0x0087A290; callers 0x005FD92E 0x005FD9A6 0x005FD9E9; sibling APT precedent Rva005FDF1C
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

struct Rva005FD788Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005FD788Outer
{
	Rva005FD788Inner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_Va0087A290[];

namespace StrategicHUD {
class ArmyUnitSwapperMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::ArmyUnitSwapperMovieClip::Impl
{
public:
	char m_pad0[4];
	int m_level4;
	Rva005FD788Inner *m_inner8;
	void SetSlotString(int index, const char *suffix, const UnicodeString &text);
};

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::SetSlotString(int index, const char *suffix, const UnicodeString &text)
{
	const char *table = g_Va0087A290[index];
	AsciiString key;
	const char *mid = m_inner8 ? m_inner8->m_name : "";
	key.format("APT:_level%u.%s_%s%s", m_level4, mid, table, suffix);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}
