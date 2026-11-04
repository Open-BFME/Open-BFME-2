// cl: /DNDEBUG /MD
// ?attemptToPurchaseScience@Player@@QAE_NW4ScienceType@@@Z @0x002AD826 56B
// Player purchase path: capable check then ScienceStore cost then bank withdraw via slot 2 then private addScience. Evidence: calls rowed isCapable 0x002ABE86 plus getCost 0x001FF3DC plus pin addScience 0x002AD661, TheScienceStore global, virtual [edx+8] on +8 member, callers 0x003BC775 plus 0x004F32E9, neighbours Rva002AD5ED plus grantScience PlayerO1Shard.
typedef bool Bool;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

#include "../../../Include/Common/ScienceStore.h"
extern ScienceStore *TheScienceStore;

#include "../../../Include/Common/Player.h"

bool Player::attemptToPurchaseScience(ScienceType science)
{
	if (!isCapableOfPurchasingScience(science))
		return false;
	int cost = TheScienceStore->getSciencePurchaseCost(science);
	rslot02(-cost);
	addScience(science);
	return true;
}
