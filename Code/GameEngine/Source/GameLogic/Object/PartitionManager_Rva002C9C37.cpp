// cl: /O1 /DNDEBUG /MD /EHsc
// Weapon's object-to-object range and attack distance, retail 0x002C9BE4
// (20B) and 0x002C9C37 (75B).
//
// Target evidence: every caller passes a Weapon as the receiver (0x003543BF
// loads ECX from Object::getCurrentWeapon, WeaponSet::chooseBestWeaponForTarget
// 0x002C7D03 its candidate weapon, the pathfinder 0x002FB091/0x002FCB1C/
// 0x002FCBFB the attacking weapon), and both bodies keep that receiver for
// their callees: 0x002C9BC3 (source, position) takes the height difference
// to the position and hands it to 0x002C9B80, which runs Weapon::computeBonus
// on the receiver and asks the template at +4 for the height-adjusted range
// (BFME 1 donor: Weapon::getAttackRange(source, heightDifference)). The
// object form passes the victim's position (+0x38). The masked byte search
// that placed 0x002C9BE4 as Zero Hour's PartitionManager::getRelativeAngle2D
// matched only the forwarding shape; its callee chain is Weapon's range.
//
// 0x002C9C37 is Zero Hour's Weapon::getAttackDistance: with a victim object
// it adds both objects' bounding circle radii (+0xBC) to that range;
// otherwise it uses the position range, or the range at zero height
// difference when there is no position either.
//
// The two callees keep their ledger's address-derived owners until their
// own consumers are renamed; this unit keeps its earlier path so the link
// census can measure the change.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Accessed members only; plain fields so this unit emits no accessor COMDATs.
class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;					// +0x38
	unsigned char m_pad44[0xBC - 0x44];
	float m_boundingCircleRadius;		// +0xBC
};

class Rva002C9BC3Owner
{
public:
	float rva002C9BC3(void *source, void *pos);
};

class Rva002C9B80Owner
{
public:
	float rva002C9B80(void *source, float heightDifference);
};

#include "../../../Include/GameLogic/Weapon.h"

float Weapon::getAttackDistance(const Object *source, const Object *victimObj, const Coord3D *victimPos) const
{
	if (victimObj) {
		float range = getAttackRange(source, victimObj);
		range += source->m_boundingCircleRadius;
		range += victimObj->m_boundingCircleRadius;
		return range;
	} else if (victimPos) {
		return ((Rva002C9BC3Owner *)this)->rva002C9BC3((void *)source, (void *)victimPos);
	} else {
		return ((Rva002C9B80Owner *)this)->rva002C9B80((void *)source, 0.0f);
	}
}

float Weapon::getAttackRange(const Object *source, const Object *victim) const
{
	return ((Rva002C9BC3Owner *)this)->rva002C9BC3((void *)source, (void *)&victim->m_position);
}
