// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ??0Rva005FE7FA@@QAE@HABVAsciiString@@@Z, retail 0x005FE7A7..0x005FE7FA
// (83 bytes, EH, ret 8). The local-player variant of the battle prompt
// player tab strip (vtable 0x0087A408 over the Rva005FE750 base of
// AptBattlePromptTabsConstructor.cpp): the base is built from the level and
// the player prefix, an empty wide string is kept at +0x38 and the local
// player name display is cleared (rowed SetLocalPlayerNameString with the
// empty string). Class name address-derived from the vtable's owner.
#include "ascii_string.h"
#include "unicode_string.h"

struct Rva005FDF1COuter;
namespace StrategicHUD
{
	void __cdecl SetLocalPlayerNameString(int level, Rva005FDF1COuter *outer, const UnicodeString &text);
}

class Rva005FE750
{
public:
	Rva005FE750(int level, const AsciiString &name);
	virtual ~Rva005FE750();
protected:
	int m_level04;
	AsciiString m_08;
private:
	char m_pad0C[0x38 - 0x0C];
};

class Rva005FE7FA : public Rva005FE750
{
public:
	Rva005FE7FA(int level, const AsciiString &name);
	virtual ~Rva005FE7FA();
private:
	UnicodeString m_38;
};

Rva005FE7FA::Rva005FE7FA(int level, const AsciiString &name)
	: Rva005FE750(level, name)
{
	StrategicHUD::SetLocalPlayerNameString(m_level04, (Rva005FDF1COuter *)&m_08, UnicodeString::TheEmptyString);
}
