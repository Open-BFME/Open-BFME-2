// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0050B16F@Made002CCA37@@QAE_NPAXPAVObject@@PBUCoord3D@@@Z, retail
// 0x0050B16F (141 bytes, RET 0x0C): slot 14 of the vtable 0x00864C38 that
// the rowed Made002CCA37 constructor installs (it inherits DamageNugget's
// damage nugget, whose slot-14 apply 0x005084FC it ends with). When the game
// has a damage-over-time manager (GameLogic +0x174) and there is a target,
// the nugget's damage (pinned helper 0x00508120) is recorded for the target's
// ID (rowed DOTManager 0x0043B8C0) as an 0x88-byte record: the DamageInfo
// (initialised through the rowed wrapper 0x0043B208) plus the nugget's
// interval (+0x1A4) and the two frames (+0x1A4 and +0x1A8 from now). Then
// the ordinary damage applies.
#include "../../Common/GameLogicObjectLookupView.h"

struct Coord3D;
class DamageInfo;

class Rva0043B163
{
public:
	unsigned char m_damageInfo[0x7C];
	int m_7C;
	int m_80;
	int m_84;
};

class Rva0043B208
{
public:
	Rva0043B208 *rva0043B208();
};

#include "../../../Include/GameLogic/DOTManager.h"

#include "object.h"

extern GameLogic *TheGameLogic;

#include "../../../Include/GameLogic/Module/Rva00507823.h"

class Made002CCA37;
class DamageNugget : public Rva00507823
{
	friend class Made002CCA37;
public:
	bool rva005084FC(void *weapon, Object *target, const Coord3D *position);
private:
	unsigned char m_pad128[0x1A4 - 0x128];
	bool generateDamageInfo(void *weapon, Object *target, DamageInfo *info, bool flag, const Coord3D *position);
};

class Made002CCA37 : public DamageNugget
{
public:
	Made002CCA37();
	bool rva0050B16F(void *weapon, Object *target, const Coord3D *position);
private:
	int m_1A4; // +0x1A4
	int m_1A8; // +0x1A8
};

bool Made002CCA37::rva0050B16F(void *weapon, Object *target, const Coord3D *position)
{
	DOTManager *dots = *(DOTManager **)((char *)TheGameLogic + 0x174);
	if (dots && target)
	{
		Rva0043B163 dot;
		((Rva0043B208 *)&dot)->rva0043B208();
		if (generateDamageInfo(weapon, target, (DamageInfo *)&dot, false, position) == true)
		{
			unsigned int frame = TheGameLogic->getFrame();
			dot.m_7C = m_1A4;
			dot.m_80 = m_1A8 + frame;
			dot.m_84 = m_1A4 + frame;
			dots->rva0043B8C0(target->m_id, &dot);
		}
	}
	return rva005084FC(weapon, target, position);
}
