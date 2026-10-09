// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
//
// ?doEffectPosition@FireLogicNugget@@UAEXPBUFireLogicNuggetSource@@PBUCoord3D@@@Z
// retail 0x0050BE34..0x0050BF8F (347 bytes) thiscall RET 8.
//
// Identity: WorldBuilder twin 0x010AA320 is FireLogicNugget::doEffectPosition
// (FireLogicNugget.cpp asserts "!targetPosition" line 47 and "m_damageArc ==
// PI" lines 72/79); retail it is slot 6 of the FireLogicNugget vtable
// 0x008650B8 (absolute reference 0x008650D0), the slot the rowed
// FireLogicNugget::doEffectObject 0x0050BDD5 forwards to. By the +0x1A4 logic
// type it calls the rowed FireLogicSystem members on the 0x00DFEC68 system:
// burn rate in a forward arc (rowed Thing::getUnitDirectionVector2D 0x0030A2A2
// on the source looked up by its +8 id through GameLogic::findObjectByID,
// cosine of the +0x138 arc) or in a circle, negated, fuel with the +0x1A8..
// +0x1B0 parameters (ctor default 10000 at +0x1B0), and the two "true" forms.
// Field names other than m_damageArc are inferred; the source argument's type
// is a view (only its +8 object id is read).
#include <math.h>
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

class Thing
{
public:
	void getUnitDirectionVector2D(Coord3D &dir) const;
};

class Object : public Thing
{
};


extern GameLogic *TheGameLogic;

class FireLogicSystem
{
public:
	void ChangeBurnRateInArea(const Coord3D *pos, Real radius, Int amount, Bool flag);
	void ChangeBurnRateInArea(const Coord3D *pos, Real radius, const Coord3D *dir, Real cosArc, Int amount, Bool flag);
	void ChangeFuelInArea(Real *pos, Real radius, Int amount, Int a, Int b, Int c, Bool flag);
};

// The fire logic system at 0x00DFEC68 (the data ledger's name for the pointer).
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
inline FireLogicSystem *TheFireLogicSystem() { return (FireLogicSystem *)TheTriggerManager; }

struct FireLogicNuggetSource
{
	char m_pad00[0x08];
	ObjectID m_sourceID;				// +0x08
};

class Made002CC5E1
{
public:
	virtual ~Made002CC5E1();

protected:
	char m_pad004[0x128 - 0x004];
	Real m_amount;						// +0x128
	char m_pad12C[0x130 - 0x12C];
	Real m_radius;						// +0x130
	char m_pad134[0x138 - 0x134];
	Real m_damageArc;					// +0x138
	char m_pad13C[0x1A4 - 0x13C];
};

class FireLogicNugget : public Made002CC5E1
{
public:
	virtual void doEffectPosition(const FireLogicNuggetSource *source, const Coord3D *targetPosition);

private:
	Int m_logicType;					// +0x1A4
	Int m_fuelA;						// +0x1A8
	Int m_fuelB;						// +0x1AC
	Int m_fuelC;						// +0x1B0
};

void FireLogicNugget::doEffectPosition(const FireLogicNuggetSource *source, const Coord3D *targetPosition)
{
	if (!targetPosition)
		return;
	switch (m_logicType)
	{
	case 0:
		if (m_damageArc >= 0.0f && m_damageArc < 3.1415927f)
		{
			Object *obj = TheGameLogic->findObjectByID(source->m_sourceID);
			Coord3D dir;
			dir.x = 1.0f;
			dir.y = 0.0f;
			dir.z = 0.0f;
			Real cosArc = 1.0f;
			if (obj)
			{
				obj->getUnitDirectionVector2D(dir);
				cosArc = (Real)cos(m_damageArc);
			}
			TheFireLogicSystem()->ChangeBurnRateInArea(targetPosition, m_radius, &dir, cosArc, (Int)m_amount, false);
		}
		else
		{
			TheFireLogicSystem()->ChangeBurnRateInArea(targetPosition, m_radius, (Int)m_amount, false);
		}
		break;
	case 1:
		TheFireLogicSystem()->ChangeBurnRateInArea(targetPosition, m_radius, (Int)-m_amount, false);
		break;
	case 2:
		TheFireLogicSystem()->ChangeFuelInArea((Real *)targetPosition, m_radius, (Int)m_amount, m_fuelA, m_fuelB, m_fuelC, false);
		break;
	case 3:
		TheFireLogicSystem()->ChangeBurnRateInArea(targetPosition, m_radius, (Int)m_amount, true);
		break;
	case 4:
		TheFireLogicSystem()->ChangeFuelInArea((Real *)targetPosition, m_radius, (Int)m_amount, m_fuelA, m_fuelB, m_fuelC, true);
		break;
	}
}
