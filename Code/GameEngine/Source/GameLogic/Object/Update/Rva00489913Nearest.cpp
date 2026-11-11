// ?rva00489913@Rva00489913@@QAEPAVObject@@PAV2@0PAUCoord3D@@@Z @0x00489913 244B.
// Bridge endpoint scan. Bit 0x40 on the second object's info selects the
// four-slot search; otherwise the 0x00489039 helper runs once and the
// second object is returned. The nearest endpoint inside the squared
// 1e10 cap is copied to the out coord.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Common/GameLogicObjectLookupView.h"

class Rva00489913Info
{
public:
	char m_pad00[0x10a];
	unsigned char m_bits;
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

class Object
{
public:
	char m_pad00[4];
	Rva00489913Info *m_info;
	char m_pad08[0x38 - 8];
	Coord3D m_pos;
	char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_checker;
};


extern GameLogic *TheGameLogic;

class BridgeBehaviorInterface
{
public:
	virtual void gap0() = 0;
	virtual ObjectID endpoint(int index) = 0;
};

#include "../../../../Include/GameLogic/Module/BridgeBehaviorClass.h"

class Rva00489913
{
public:
	Object *rva00489913(Object *query, Object *bridgeObj, Coord3D *out);
	bool rva00489039(Object *query, Object *other, Coord3D *out);
};

// 0x00489039 is rowed as DozerAIUpdate::findGoodBuildOrRepairPosition
// (421B; ZH/BFME1 donor); the rowed 0x00489913 caller in DozerAIUpdateCtor
// is the same bridge scan calling it, so these resolve to the rowed body
// instead of the unrowed spelling (sole U on this unit).
class DozerAIUpdate
{
protected:
	bool findGoodBuildOrRepairPosition(const Object *query, const Object *other, Coord3D &out);
	friend class Rva00489913;
};

Object *Rva00489913::rva00489913(Object *query, Object *bridgeObj, Coord3D *out)
{
	Object *result = bridgeObj;
	if ((bridgeObj->m_info->m_bits & 0x40) != 0)
	{
		BridgeBehaviorInterface *bridge =
			BridgeBehavior::getBridgeBehaviorInterfaceFromObject(bridgeObj);
		if (bridge != 0)
		{
			AIUpdateInterface *checker = query->m_checker;
			float best = 10000000000.0f;
			result = 0;
			for (int index = 0; index < 4; ++index)
			{
				Object *found = TheGameLogic->findObjectByID(bridge->endpoint(index));
				if (found == 0)
					continue;
				Coord3D pos;
				if (!((DozerAIUpdate *)this)->findGoodBuildOrRepairPosition(query, found, pos))
					continue;
				if (!checker->isPathAvailable(&pos))
					continue;
				float dx = query->m_pos.x - pos.x;
				float dy = query->m_pos.y - pos.y;
				float dist = dx * dx + dy * dy;
				if (dist < best)
				{
					*out = pos;
					result = found;
					best = dist;
				}
			}
			return result;
		}
	}
	((DozerAIUpdate *)this)->findGoodBuildOrRepairPosition(query, bridgeObj, *out);
	return result;
}
