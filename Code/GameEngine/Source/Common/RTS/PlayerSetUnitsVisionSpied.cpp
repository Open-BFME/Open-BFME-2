// cl: /O1 /DNDEBUG /MD
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

class Object
{
public:
	void makeDirty();
};

int callHandleShroud(Object *obj, void *userData)
{
	obj->makeDirty();
	return 1;
}

class Player
{
public:
	int iterateObjects(int (*func)(Object *, void *), void *userData) const;
	void setUnitsVisionSpied(bool setting, int byWhom);
private:
	char m_pad000[0x358];
	int m_visionSpiedBy[20];
	unsigned int m_visionSpiedMask;
};

void Player::setUnitsVisionSpied(bool setting, int byWhom)
{
	bool needRefresh = false;

	if (setting)
	{
		m_visionSpiedBy[byWhom] = m_visionSpiedBy[byWhom] + 1;
		if (m_visionSpiedBy[byWhom] == 1)
			needRefresh = true;
	}
	else
	{
		m_visionSpiedBy[byWhom] = m_visionSpiedBy[byWhom] - 1;
		if (m_visionSpiedBy[byWhom] == 0)
			needRefresh = true;
	}

	if (needRefresh)
	{
		unsigned int workingMask = 0;
		for (int i = 0; i < 20; ++i)
		{
			if (m_visionSpiedBy[i] > 0)
				workingMask |= (1 << i);
			else
				workingMask &= ~(1 << i);
		}

		m_visionSpiedMask = workingMask;

		iterateObjects(callHandleShroud, 0);
	}
}
