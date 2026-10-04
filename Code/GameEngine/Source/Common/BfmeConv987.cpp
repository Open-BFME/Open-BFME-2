// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common /Os
// stlport
// Open-BFME5 conversions.

// The lookup below is GameLogic::findObjectByID; GameLogicObjectLookup.h holds
// the declaration (its body stays in Thing/GameLogicFindObjectByID.cpp).
#include "Thing/GameLogicObjectLookup.h"

struct BfmeX987
{
	char m_bfmePad[0x74];
	int m_bfmeId;
};
extern GameLogic *TheGameLogic;

class BfmeA987
{
public:
	void bfmeGo987A();
	void bfmeGo987B();
	void bfmeBase987();

	char m_bfmePad[0x20];
	int m_bfmeId;
};
// The donor's BfmeDrop987 is a private placeholder view. Retail 0x00499C46
// calls the found Object's own kill (its REL32 at +27 lands on
// ?kill@Object@@QAEXW4DamageType@@W4DeathType@@@Z, matched at 0x002984D4), so
// this is Object itself: its clear is kill, and no new pin is warranted.
// GameLogicObjectLookup.h forward-declares Object; declare the one member this
// body calls rather than pulling in GameLogic/Object.h, whose sweep shim is
// not this TU's shape. Only the two enumerators the body pushes are named;
// GameLogic/Damage.h is not on this donor's include path.
enum DamageType { DAMAGE_SNIPER = 8 };
enum DeathType { DEATH_NORMAL = 0 };
class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
};
typedef Object BfmeDrop987;
class BfmeC987
{
public:
	void bfmeGo987C();

	char m_bfmePad[0x24];
	int m_bfmeId;
};
void BfmeC987::bfmeGo987C()
{
	BfmeDrop987 *x = reinterpret_cast<BfmeDrop987 *>(
		TheGameLogic->findObjectByID(m_bfmeId));

	if (x) {
		// Retail pushes 8 then 0 (see 0x00499C5B/0x00499C5D): DamageType 8 is
		// DAMAGE_SNIPER and DeathType 0 is DEATH_NORMAL.
		x->kill(DAMAGE_SNIPER, DEATH_NORMAL);
		m_bfmeId = 0;
	}
}
class BfmeD987
{
public:
	void bfmeGo987D(int unused);

	char m_bfmePad[4];
	int m_bfmeId;
};
