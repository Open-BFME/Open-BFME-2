// cl: /DNDEBUG /MD
//
// Donor: Generals Player::setUnitsVisionSpied(Bool, PlayerIndex) and its
// callHandleShroud callback (reference/open-bfme-1/reference/
// CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source/Common/RTS/Player.cpp).
// BFME2 keeps the two-argument Generals form (Zero Hour added a kind-of mask).
//
// ?setUnitsVisionSpied@Player@@QAEX_NH@Z @0x002ABA3D 94B: edge-triggered
// reference count in m_visionSpiedBy[20] (+0x358); on a 0<->1 edge it rebuilds
// m_visionSpiedMask (+0x3A8) and refreshes every object through the rowed
// int-callback Player::iterateObjects 0x002AB08B.
//
// ?callHandleShroud@@YAHPAVObject@@PAX@Z @0x002AA20F 13B: the BFME callback
// marks the object dirty (rowed Object::makeDirty 0x0028BB44) and continues.

#include "../../GameLogic/Object/object.h"

int callHandleShroud(Object *obj, void *userData)
{
	obj->makeDirty();
	return 1;
}

#include "../../../Include/Common/Player.h"

void Player::setUnitsVisionSpied(bool setting, int byWhom)
{
	bool needRefresh = false;

	if (setting)
	{
		m_358[byWhom] = m_358[byWhom] + 1;
		if (m_358[byWhom] == 1)
			needRefresh = true;
	}
	else
	{
		m_358[byWhom] = m_358[byWhom] - 1;
		if (m_358[byWhom] == 0)
			needRefresh = true;
	}

	if (needRefresh)
	{
		unsigned int workingMask = 0;
		for (int i = 0; i < 20; ++i)
		{
			if (m_358[i] > 0)
				workingMask |= (1 << i);
			else
				workingMask &= ~(1 << i);
		}

		m_3A8 = workingMask;

		iterateObjects(callHandleShroud, 0);
	}
}
