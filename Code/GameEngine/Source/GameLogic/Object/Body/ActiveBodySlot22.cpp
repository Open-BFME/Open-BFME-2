// cl: /MD /GX
//
// ActiveBody's slot 22 (0x004BF9ED, vftable 0x0085B038 and ten more body
// vftables that inherit it): when the module data's +0x4C radius is positive,
// optionally draw it (TheGlobalData +0xE9C: TheTerrainLogic's ground height
// under the object, then TheTacticalView slot 12 with colour 0xFFFF8000), then
// hand every alive object other than this one passing the relationship-1
// filter within that radius to 0x0028EC68 (1, the object, 10).
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).
class Object;
class Player;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
#include "../../../../Include/GameLogic/Rva0026119DFilter.h"

// vftable 0x00BF91BC, allow 0x002611BF.
#include "../../../../Include/GameLogic/Rva002611BFFilter.h"

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};


#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../object.h"

#include "../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

class View
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void rvaSlot12(const Coord3D *pos, float radius, int color);
};
extern View *TheTacticalView;

#include "../../../../Include/Common/GlobalData.h"
extern class GlobalData *TheWritableGlobalData;

class ActiveBodyModuleData
{
public:
	char m_pad00[0x4C];
	float m_cheerRadius;		// +0x4C the radius
};

#include "../../../../Include/GameLogic/Module/ActiveBody.h"

void ActiveBody::rva004BF9ED()
{
	const ActiveBodyModuleData *data = getActiveBodyModuleData();
	if (data->m_cheerRadius <= 0.0f)
		return;
	{
		Object *obj = getObject();
		if (TheWritableGlobalData->field0E9C) {
			Coord3D pos;
			pos.x = obj->getPosition()->x;
			pos.y = obj->getPosition()->y;
			pos.z = obj->getPosition()->z;
			pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
			TheTacticalView->rvaSlot12(&pos, data->m_cheerRadius, 0xFFFF8000);
		}
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), data->m_cheerRadius, 0,
			Rva00260EB1Filter(obj, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))), 0);
		Object *other;
		while ((other = hits.next()) != 0)
			other->rva0028EC68(1, obj, 10);
	}
}
