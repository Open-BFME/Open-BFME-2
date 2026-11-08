// cl: /MD
// ?xfer@Rva0034103B@@MAEXPAVXfer@@@Z @0x0034103B 217B: Rva0034103B xfer slot 3.
// Version1 via rowed 0x000053EE then base AIInternalMoveToState xfer via rowed 0x0033FF76 then IsLightCRC early-out via Xfer slot 0x10 then Coord2D at +0x4C via slot 0x50 plus float at +0x54 via slot 0x70 plus int at +0x58 via slot 0x7C plus two TerrainLogic ID refs at +0x5C/+0x60 via slot 0x78 plus IsLoading plus slot 0x8C plus bool at +0x64 via slot 0x90.
// Precedent Rva00458AAE xfer (Version1 base float int) plus DockUpdate 0x7fffffff ID shape plus Rva00573A00 TheTerrainLogic at 0x00DFEC50.
// Unblocks 0x0034117C and 0x00341205.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
#include "../../../Libraries/Include/Lib/Coord2D.h"
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
#include "../../Include/Common/BfmeXfer.h"
#include "../../Include/GameLogic/AIInternalMoveToState.h"
struct TerrainObj
{
	int m_00;
	int m_id;
};
#include "../../Include/GameLogic/TerrainLogic.h"
class Rva0034103B : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Coord2D m_4C;
	float m_54;
	int m_58;
	TerrainObj *m_5C;
	TerrainObj *m_60;
	bool m_64;
};
void Rva0034103B::xfer(Xfer *xfer)
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_4C;
	*xfer == m_54;
	*xfer == m_58;
	unsigned int id;
	id = 0x7fffffff;
	if (m_5C)
		id = m_5C->m_id;
	*xfer == id;
	if (xfer->IsLoading())
		m_5C = (TerrainObj *)TheTerrainLogic->getWaypointByID(id);
	id = 0x7fffffff;
	if (m_60)
		id = m_60->m_id;
	*xfer == id;
	if (xfer->IsLoading())
		m_60 = (TerrainObj *)TheTerrainLogic->getWaypointByID(id);
	*xfer == m_64;
}
