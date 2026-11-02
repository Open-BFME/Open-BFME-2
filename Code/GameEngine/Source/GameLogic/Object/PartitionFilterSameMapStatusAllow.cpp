// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// ?allow@PartitionFilterSameMapStatus@@UAE_NPAVObject@@@Z RVA 0x002611BF 30B.
// Evidence: slot 1 of vtable 0x00BF91BC, the second filter Zero Hour's
// privateAttackPosition builds (BFME2 0x0026DB1A installs it beside
// PartitionFilterPossibleToAttack's 0x00BF91B0); the body compares bit 3 of
// the two objects' +0x438 bytes, which is Zero Hour's
// m_privateStatus OFF_MAP (0x08) tested by Object::isOffMap(). Bit 0 of the
// same byte is EFFECTIVELY_DEAD, the test BFME2's
// AIUpdateInterface::isAllowedToRespondToAiCommands makes first.
typedef bool Bool;
typedef int Int;

enum ObjectPrivateStatusBits
{
	EFFECTIVELY_DEAD = 0x01,
	OFF_MAP = 0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	__declspec(dllimport) __forceinline Bool isOffMap() const { return (m_privateStatus & OFF_MAP) != 0; }

private:
	unsigned char m_unmodelled_00[0x438];
	unsigned char m_privateStatus;				// +0x438
};

// BFME 2's partition filter base (ctor 0x000421C8): a vptr and the +0x04
// link to the next filter; slot 0 deleting dtor, slot 1 allow, slot 2 the
// shared getPlayerMask 0x0036CC7A.  The ZH source's private m_unmodelled_04
// is this base's m_next, so m_obj stays at +0x08.
#include "../../../Include/GameLogic/PartitionFilter.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterSameMapStatus : public Rva000421C8
{
public:
	virtual Bool allow(Object *objOther);
private:
	const Object *m_obj;						// +0x08
};

Bool PartitionFilterSameMapStatus::allow(Object *objOther)
{
	return m_obj->isOffMap() == objOther->isOffMap();
}

// The 30 matched filter users that build this filter inline name its class
// by its allow address (Rva002611BFFilter, vftable 0x00BF91BC); their
// slot-1 reference binds to this body.
#pragma comment(linker, "/alternatename:?allow@Rva002611BFFilter@@UAE_NPAVObject@@@Z=?allow@PartitionFilterSameMapStatus@@UAE_NPAVObject@@@Z")
