// cl: /Ireference/shims/bfme2_ascii /MD
//
// Retail 0x001EF291 58B:
// ?getCursorIndex@Mouse@@QAEHABVAsciiString@@@Z
// Empty check via rowed isEmpty 0x00001E2F returns -1. Loop 0x38 over
// retail pointer table at 0x00DB9058 via rowed compareNoCase 0x00037980
// returns index or -1. Callers at 0x002A344F 0x004023A6 0x0042AB2B.
//

#include "ascii_string.h"


// g_00DB9058: VA 0x00DB9058 (.data); retail's 56 string pointers are bounded
// by the lookup's 0..0x37 loop. compareNoCase observes text, not literal addresses.
const char *g_00DB9058[] = {
	"None",
	"Normal",
	"Arrow",
	"Scroll",
	"Target",
	"Move",
	"AttackMove",
	"AttackObj",
	"ForceAttackObj",
	"ForceAttackGround",
	"Build",
	"InvalidBuild",
	"GenericInvalid",
	"Select",
	"EnterFriendly",
	"EnterAggressive",
	"SetRallyPoint",
	"GetRepaired",
	"GetHealed",
	"DoRepair",
	"ResumeConstruction",
	"CaptureBuilding",
	"SnipeVehicle",
	"LaserGuidedMissiles",
	"TankHunterTNTAttack",
	"StabAttack",
	"PlaceRemoteCharge",
	"PlaceTimedCharge",
	"Defector",
	"Dock",
	"FireFlame",
	"FireBomb",
	"PlaceBeacon",
	"DisguiseAsVehicle",
	"Waypoint",
	"OutRange",
	"StabAttackInvalid",
	"PlaceChargeInvalid",
	"Hack",
	"ParticleUplinkCannon",
	"LivingWorldZoom",
	"JoinHorde",
	"WeaponUpgrade",
	"ArmorUpgrade",
	"Beam",
	"Bombard",
	"Axe",
	"EvilAbilityObj",
	"PickUp",
	"WallInsufficientFunds",
	"WallInvalidTerrain",
	"WallExceedsDistance",
	"WallBlockedByObstacle",
	"SendToDeath",
	"DeliverRing",
	"Patrol"
};

class Mouse
{
public:
	int getCursorIndex(const AsciiString &s);
};

int Mouse::getCursorIndex(const AsciiString &s)
{
	if (s.isEmpty())
		return -1;
	for (int i = 0; i < 0x38; ++i) {
		if (s.compareNoCase(g_00DB9058[i]) == 0)
			return i;
	}
	return -1;
}
