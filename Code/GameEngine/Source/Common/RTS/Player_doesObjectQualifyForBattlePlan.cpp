// cl: /DNDEBUG /MD
//
// ?doesObjectQualifyForBattlePlan@Player@@QBE_NPAVObject@@@Z @0x002AA0DE 69B:
// Zero Hour's and BFME1's Player::doesObjectQualifyForBattlePlan (BFME1
// 0x000C9AB0, the same two isAnyKindOf calls; Drawable's battle-plan icon draw
// calls it after getNumBattlePlansActive as in Zero Hour). Player member that
// answers whether a thing matches the kind-of filter held by the object at
// +0xB8: true when the filter and the thing exist, the thing is any of the
// filter's required kinds (+0x14) and none of its forbidden kinds (+0x30),
// both through the rowed Thing::isAnyKindOf 0x0030ADC7.

#include "../../../Include/Common/BitFlagsTemplate.h"

#include "../Thing/thing.h"

#include "../../GameLogic/Object/object.h"

struct Rva002AA0DEKindFilter
{
	char m_pad00[0x14];
	BitFlags<69> m_mustBe;
	char m_pad20[0x30 - 0x20];
	BitFlags<69> m_mustNotBe;
};

class Player
{
public:
	bool doesObjectQualifyForBattlePlan(Object *obj) const;
private:
	char m_pad00[0xB8];
	Rva002AA0DEKindFilter *m_B8;
};

bool Player::doesObjectQualifyForBattlePlan(Object *obj) const
{
	if (m_B8 && obj && obj->isAnyKindOf(m_B8->m_mustBe) && !obj->isAnyKindOf(m_B8->m_mustNotBe))
		return true;
	return false;
}
