// cl: /MD /EHsc
// ??1WeaponSet@@UAE@XZ retail 0x002C7311 81B
// Zero Hour WeaponSet::~WeaponSet shape: delete each of the six weapon slots
// at +8 when set; then the inline Snapshot-style base dtor restores BBB554.
// Retail deletes through the slot-0 deleting dtor with flag 0 followed by the
// global ??3@YAXPAX@Z (a global-scope delete). Identity from the pin (slot 2
// of vtable 0x00C0089C returns "WeaponSet"); six slots at +8 as in the rowed
// WeaponSetRvaSlotSearch.cpp. Helper class names are local.

class WeaponSetSlot
{
public:
	virtual ~WeaponSetSlot();
};

// The base is the canonical Snapshot (vtable 0x00BBB554): retail unwind
// funclets destroy it through the folded Snapshot destructor 0x0049B47C.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0, WEAPONSLOT_COUNT = 6
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};
enum WeaponChoiceCriteria
{
 PREFER_MOST_DAMAGE=0, PREFER_LONGEST_RANGE=1, PREFER_SPECIAL=2,
 PREFER_SMALLEST_RANGE_ERROR=3, PREFER_RANDOM=4, PREFER_TEMPLATE_DEFAULT=5
};
#include "../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"




enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};
enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0,
	ATTACK_TUNNEL_NETWORK_GUARD = 4
};
class Object;
class Weapon;
struct EmitVtableTag;
struct Coord3D;
class WeaponTemplateSet;
#include "../../../Include/GameLogic/WeaponSetClass.h"

WeaponSet::~WeaponSet()
{
	for (int i = 0; i < 6; ++i)
		if (m_weapons[i])
			::delete (WeaponSetSlot *)m_weapons[i];
}
