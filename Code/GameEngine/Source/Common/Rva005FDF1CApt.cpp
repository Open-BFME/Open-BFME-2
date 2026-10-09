// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?SetPlayerNameString@StrategicHUD@@YAXHPAURva005FDF1COuter@@ABVUnicodeString@@@Z retail 0x005FDF1C 103B
// Evidence: format APT:_level%u.%s_PlayerName via 0x00038150; bfmeSetText via pin 0x00225301; releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C; callers 0x005FE1C8 0x005FE350 0x005FE6B2; precedent Rva005D2FD0Apt.cpp
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"
struct Rva005FDF1COuter;
class UnicodeString;
namespace StrategicHUD
{
	void __cdecl SetLocalPlayerNameString(int level, Rva005FDF1COuter *outer, const UnicodeString &text);
	void __cdecl SetPlayerNameString(int level, Rva005FDF1COuter *outer, const UnicodeString &text);
}

struct Rva005FDF1CInner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005FDF1COuter
{
	Rva005FDF1CInner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

void __cdecl StrategicHUD::SetPlayerNameString(int level, Rva005FDF1COuter *outer, const UnicodeString &text)
{
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_PlayerName", level, mid);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}

// ?SetLocalPlayerNameString@StrategicHUD@@YAXHPAURva005FDF1COuter@@ABVUnicodeString@@@Z retail 0x005FDF83 103B
// Evidence: format APT:_level%u.%s_LocalPlayerName via 0x00038150; same callees globals callers 0x005FE3AA 0x005FE7E1; sibling of 0x005FDF1C
void __cdecl StrategicHUD::SetLocalPlayerNameString(int level, Rva005FDF1COuter *outer, const UnicodeString &text)
{
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_LocalPlayerName", level, mid);
	g_bfmeAptWindowManager->bfmeSetText(key, text, true);
}
