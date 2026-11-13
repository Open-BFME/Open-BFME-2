// cl: /DNDEBUG /MD
// ?setScienceAvailability@Player@@QAEXW4ScienceType@@W4ScienceAvailabilityType@@@Z @ 0x002AD8C9 113B: Player science availability move
// Evidence: caller 0x003BC785 pushes ScienceAvailabilityType (from rowed getScienceAvailabilityTypeFromString) and ScienceType (from rowed Rva001FF725Get) with this=Player; ZH Player.cpp setScienceAvailability donor removes from Disabled then Hidden then pushes by type; retail vectors at +0x2FC/+0x308 are Disabled/Hidden under +0x2F0 m_sciences layout.
enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum ScienceAvailabilityType
{
	SCIENCE_AVAILABILITY_INVALID = -1,
	SCIENCE_AVAILABLE,
	SCIENCE_DISABLED,
	SCIENCE_HIDDEN,
	SCIENCE_AVAILABILITY_COUNT
};

enum ObjectID
{
	INVALID_ID = 0
};

typedef int Bool;

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *pos);
	void push_back(const T &val);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// Player+8 is Player's base Rva00380200 (constructor 0x002B0F3C installs 0x00BFDF18 there); slot 2 of that
// table is the void(int) the purchase calls with the negated cost.
#include "../Rva00380200.h"

#include "../../../Include/Common/ScienceStore.h"

extern ScienceStore *TheScienceStore;

class Player
{
public:
	void setScienceAvailability(ScienceType science, ScienceAvailabilityType type);
	bool forcePurchaseScience(ScienceType science);
private:
	bool addScience(ScienceType science);
	char m_pad00[8];
	Rva00380200 m_sub08;
	char m_pad34[0x2F0 - 0x34];
	_STL::vector<ScienceType> m_sciences;
	_STL::vector<ScienceType> m_sciencesDisabled;
	_STL::vector<ScienceType> m_sciencesHidden;
};

void Player::setScienceAvailability(ScienceType science, ScienceAvailabilityType type)
{
	Bool found = false;

	for (ScienceType *it = m_sciencesDisabled.m_start; it != m_sciencesDisabled.m_finish; ++it)
	{
		if (*it == science)
		{
			((_STL::vector<ObjectID> *)&m_sciencesDisabled)->erase((ObjectID *)it);
			found = true;
			break;
		}
	}
	if (!found)
	{
		for (ScienceType *it = m_sciencesHidden.m_start; it != m_sciencesHidden.m_finish; ++it)
		{
			if (*it == science)
			{
				((_STL::vector<ObjectID> *)&m_sciencesHidden)->erase((ObjectID *)it);
				found = true;
				break;
			}
		}
	}

	if (type == SCIENCE_DISABLED)
	{
		m_sciencesDisabled.push_back(science);
	}
	else if (type == SCIENCE_HIDDEN)
	{
		m_sciencesHidden.push_back(science);
	}
}

// Retail 0x002AD883 70B: Player grant-and-charge between grantScience 0x2AD85E and setScienceAvailability 0x2AD8C9.
// Evidence: isScienceGrantable row 0x001FF432, addScience pin 0x002AD661, getSciencePurchaseCost row 0x001FF3DC,
// TheScienceStore ?TheScienceStore, Rva00380200 slot 2 (rslot02) at +8 with neg cost, caller 0x001EC70A.
bool Player::forcePurchaseScience(ScienceType science)
{
	if (TheScienceStore->isScienceGrantable(science))
	{
		if (addScience(science))
		{
			int cost = TheScienceStore->getSciencePurchaseCost(science);
			Rva00380200 &sub08 = m_sub08;
			sub08.rslot02(-cost);
			return true;
		}
	}
	return false;
}
