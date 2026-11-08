// cl: /O1 /DNDEBUG /MD
//
// ?getPercentReady@SpecialPowerModule@@UBEMXZ @0x0049355E 194B: slot 2 of the interface, retail's table 0x00C5E080.
// Early outs return the global at VA 0x00BBAEAC, 1, or the float at +0x14.
// Otherwise 1 minus the unsigned ready delta over the unsigned at +4.

#include "../../Include/Common/Overridable.h"
#include "../../Include/Common/SpecialPower.h"
#include "../../Include/GameLogic/Module/SpecialPowerModule.h"

class Rva002AC6B1PlayerTimers
{
public:
	unsigned int getOrStart(const SpecialPowerTemplate *tmpl);
};

class Player;

#include "../GameLogic/Object/object.h"

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

struct Rva0049355EHolder
{
	char m_pad[8];
	const Overridable *m_ov;
};

class SpecialPowerModule : public SpecialPowerModuleInterface
{
public:
	virtual float getPercentReady() const;
	unsigned int m_reloadTime;
	unsigned int m_availableOnFrame;
	int m_c;
	char m_gap[4];
	float m_pausedPercent;
	unsigned char m_blocked;
};

float SpecialPowerModule::getPercentReady() const
{
	if (m_blocked != 0)
		return 0.0f;
	if (isReady())
		return 1.0f;
	if (m_c > 0)
		return m_pausedPercent;
	Rva0049355EHolder *holder = *(Rva0049355EHolder **)((char *)this - 0xC);
	if (holder->m_ov == 0)
		return 0.0f;
	Object *obj = *(Object **)((char *)this - 8);
	unsigned int value = m_availableOnFrame;
	if (obj != 0)
	{
		Player *player = obj->getControllingPlayer();
		if (player != 0 && ((const SpecialPowerTemplate *)holder->m_ov->friend_getFinalOverride())->m_sharedSyncedTimer != 0)
			value = ((Rva002AC6B1PlayerTimers *)player)->getOrStart(getSpecialPowerTemplate());
		value -= TheGameLogic->getFrame();
		return 1.0f - (float)value / (float)m_reloadTime;
	}
	return 0.0f;
}
