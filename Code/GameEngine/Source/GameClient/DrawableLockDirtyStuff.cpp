// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Drawable::friend_lockDirtyStuffForIteration (retail 0x002717EB, 43B) and
// Drawable::friend_unlockDirtyStuffForIteration (0x00271816, 16B), the
// adjacent pair just before the Drawable constructor.
// Target evidence: the first, while the lock count (VA 0x00DFEB7C) is zero
// and TheGameClient (VA 0x00DFE77C) exists, walks the drawable list from
// TheGameClient's slot 17 (firstDrawable) through the +0x104 next link, then
// increments the count; the second decrements it only while positive.
// Donor: Zero Hour GameClient/Drawable.cpp (same two functions over
// Drawable::s_modelLockCount; the loop body's getDrawModules() call leaves no
// code in retail). The count has no other reader in the ledger, so it is
// defined here under the donor's static-member name.
typedef int Int;

#include "../../Include/GameClient/Drawable.h"

class GameClientView
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11)
	V(12) V(13) V(14) V(15) V(16)
#undef V
	virtual Drawable *firstDrawable();		// slot 17
};

class GameClient;
extern GameClient *TheGameClient;

Int Drawable::s_modelLockCount = 0;

void Drawable::friend_lockDirtyStuffForIteration()
{
	if (s_modelLockCount == 0)
	{
		if (TheGameClient)
		{
			for (Drawable *drawable = ((GameClientView *)TheGameClient)->firstDrawable(); drawable != 0; drawable = drawable->getNextDrawable())
			{
				drawable->getDrawModules();
			}
		}
	}
	++s_modelLockCount;
}

void Drawable::friend_unlockDirtyStuffForIteration()
{
	if (s_modelLockCount > 0)
		--s_modelLockCount;
}
