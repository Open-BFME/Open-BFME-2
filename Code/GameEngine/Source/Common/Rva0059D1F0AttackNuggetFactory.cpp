// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Near-twin of Rva0059EE10AttackNuggetFactory.cpp (retail 0x0059EE10, 135B)
// and sibling of Rva005A01F0AttackNuggetFactory.cpp (retail 0x005A01F0,
// 152B): same S4_PARSE_WITH_FIELDS shape, same base constructor pinned as
// ??0BfmeAttackNuggetBase@@QAE@XZ at 0x0001B522, but this instance carries a
// wider tail -- two words (m_10, m_14) plus two bytes (m_18, m_19) -- and
// re-installs +0 with its own address before the post-parse m_04=m_14
// resync. Class re-declared locally per file policy; identity of the
// derived struct is unresolved; its field table is owned below from retail.

class INI;
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

// Retail VA 0x00C164B0: three 16-byte records followed by the null record.
// The native table supplies the callback identities and target field offsets;
// the derived class's original name remains unresolved.
extern const FieldParse s4TableRva0059D1F0[] = {
	{ "StartFrame", &INI::parseInt, 0, 0x10 },
	{ "EndFrame", &INI::parseInt, 0, 0x14 },
	{ "FadeInUnfrozenSounds", &INI::parseBool, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

#include "../../Include/Common/Gen_00489270.h"

class Rva001DBAA4 { public: Rva001DBAA4(); };
class Rva00489210
{
public:
	// Construction is the rowed ??0Rva001DBAA4, reached by a qualified call.
	__declspec(dllimport) __forceinline Rva00489210() { ((Rva001DBAA4 *)this)->Rva001DBAA4::Rva001DBAA4(); }
	int *m_00;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};

// Rva001DBAC3Derived.cpp emits the vtable installed at +0.
extern "C" int __identifier("??_7Rva0035D352@@6B@");

struct FreezePostLoadSoundsTransition : public Rva00489210
{
	int m_startFrame, m_endFrame;
	char m_fadeInUnfrozenSounds, m_19;

	FreezePostLoadSoundsTransition()
	{
		m_00 = &__identifier("??_7Rva0035D352@@6B@");
		m_startFrame = 0;
		m_endFrame = 0x1e;
		m_fadeInUnfrozenSounds = 1;
		m_19 = 0;
		m_04 = 0x1e;
	}
};

void parseFreezePostLoadSoundsTransition(INI *ini, Gen_00489270 *sink)
{
	FreezePostLoadSoundsTransition *transition = new FreezePostLoadSoundsTransition;

	ini->initFromINI(transition, s4TableRva0059D1F0);
	transition->m_04 = transition->m_endFrame;

	sink->m((int)transition);
}
