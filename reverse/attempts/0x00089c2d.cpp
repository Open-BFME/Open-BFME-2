// ?rva00089C2D@W3DView@@AAEXHHMM@Z
// partial score=0.9 date=2026-10-09
// cl: /ICode/Libraries/Include/Lib /O1 /G5 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /MD /EHsc /Oy-
// ?rva00089C2D@W3DView@@AAEXHHMM@Z
// Native 0x00089C2D..0x00089E2A (507 bytes, ret 0x10). BFME2 form of Zero Hour's
// W3DView::setupWaypointPath: the leading segment-length loop, the half-angle
// smoothing of the camera angles and the final ground-height sampling follow
// GeneralsMD W3DView.cpp; BFME2 moves the waypoint list and the orient pass into
// the path object at +0x280 (rowed ctor 0x0008990C/dtor 0x00089971), whose vtable
// slot 2 loads the path (WB's CameraMoveAlongWaypointPathInfo names 0x00086A94
// padCameraAngle), and keeps one start and one end ground height instead of a
// per-waypoint table. Layout, call order and the end-height override through the
// object at +0x2458 (flag +0x2474) are read from retail; the argument meanings
// are not recovered (second word forwarded to the orient pass, two floats to
// the path loader).

#include "vector2.h"
#include "wwmath.h"

typedef float Real;
typedef int Int;

struct Coord3D { Real x, y, z; };

class TerrainLogic
{
public:
	virtual void terrainSlot00() = 0;
	virtual void terrainSlot04() = 0;
	virtual void terrainSlot08() = 0;
	virtual void terrainSlot0C() = 0;
	virtual void terrainSlot10() = 0;
	virtual void terrainSlot14() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;
};

class CameraMoveAlongWaypointPathInfo
{
public:
	virtual void pathSlot00();
	virtual void pathSlot04();
	virtual void loadPath(Int a, Int b, Real c, Real d, Int e, bool f);
	void rva00089510(Int orient, Real defaultAngle, Int flag);
	void padCameraAngle(Int a, Int b, Real angle);
};

class Rva0030E67CHeightSource
{
public:
	Real rva0030E67C(Real x, Real y);
};

struct WaypointRecord
{
	Coord3D pos;
	Real pad[2];
};

class W3DView
{
public:
	virtual void viewSlot00() = 0;
	virtual void viewSlot04() = 0;
	virtual void viewSlot08() = 0;
	virtual void viewSlot0C() = 0;
	virtual void viewSlot10() = 0;
	virtual void viewSlot14() = 0;
	virtual void viewSlot18() = 0;
	virtual void viewSlot1C() = 0;
	virtual void viewSlot20() = 0;
	virtual void viewSlot24() = 0;
	virtual void viewSlot28() = 0;
	virtual void viewSlot2C() = 0;
	virtual void viewSlot30() = 0;
	virtual void viewSlot34() = 0;
	virtual void viewSlot38() = 0;
	virtual void viewSlot3C() = 0;
	virtual void viewSlot40() = 0;
	virtual void viewSlot44() = 0;
	virtual void viewSlot48() = 0;
	virtual void viewSlot4C() = 0;
	virtual void viewSlot50() = 0;
	virtual void viewSlot54() = 0;
	virtual void viewSlot58() = 0;
	virtual void viewSlot5C() = 0;
	virtual void viewSlot60() = 0;
	virtual void viewSlot64() = 0;
	virtual void viewSlot68() = 0;
	virtual void viewSlot6C() = 0;
	virtual void setCameraLock(unsigned id) = 0;
	virtual void viewSlot74() = 0;
	virtual void viewSlot78() = 0;
	virtual void viewSlot7C() = 0;
	virtual void viewSlot80() = 0;
	virtual void viewSlot84() = 0;
	virtual void viewSlot88() = 0;
	virtual void viewSlot8C() = 0;
	virtual void viewSlot90() = 0;
	virtual void viewSlot94() = 0;
	virtual void viewSlot98() = 0;
	virtual void viewSlot9C() = 0;
	virtual void viewSlotA0() = 0;
	virtual void viewSlotA4() = 0;
	virtual void viewSlotA8() = 0;
	virtual void viewSlotAC() = 0;
	virtual void viewSlotB0() = 0;
	virtual void viewSlotB4() = 0;
	virtual void viewSlotB8() = 0;
	virtual void viewSlotBC() = 0;
	virtual void viewSlotC0() = 0;
	virtual void viewSlotC4() = 0;
	virtual void viewSlotC8() = 0;
	virtual void viewSlotCC() = 0;
	virtual void viewSlotD0() = 0;
	virtual void viewSlotD4() = 0;
	virtual void viewSlotD8() = 0;
	virtual void viewSlotDC() = 0;
	virtual void viewSlotE0() = 0;
	virtual void viewSlotE4() = 0;
	virtual void viewSlotE8() = 0;
	virtual void viewSlotEC() = 0;
	virtual void viewSlotF0() = 0;
	virtual void viewSlotF4() = 0;
	virtual void viewSlotF8() = 0;
	virtual void viewSlotFC() = 0;
	virtual Real getAngle() = 0;

private:
	void rva00089C2D(Int first, Int orient, Real easeIn, Real easeOut);

	unsigned char m_padding0004[0x1dc - 4];
	unsigned char m_cameraMoving;
	unsigned char m_padding01dd[0x280 - 0x1dd];
	unsigned char m_path[0x2ac - 0x280];
	WaypointRecord m_waypoints[100];
	unsigned char m_padding0a7c[0x16e8 - 0x2ac - sizeof(WaypointRecord) * 100];
	Real m_cameraAngle[100];
	unsigned char m_padding1878[0x1ae4 - 0x16e8 - sizeof(Real) * 100];
	Real m_segLength[100];
	unsigned char m_padding1c74[0x1ee8 - 0x1ae4 - sizeof(Real) * 100];
	Real m_totalDistance;
	Real m_startGround;
	Real m_endGround;
	unsigned char m_padding1ef4[0x22f0 - 0x1ef4];
	Int m_numWaypoints;
	unsigned char m_padding22f4[0x2354 - 0x22f4];
	Int m_waypointMode;
	unsigned char m_padding2358[0x23d4 - 0x2358];
	Int m_shutter;
	unsigned char m_padding23d8[0x2408 - 0x23d8];
	Real m_groundLevel;
	unsigned char m_padding240c[0x2458 - 0x240c];
	unsigned char m_heightSource[0x2474 - 0x2458];
	unsigned char m_useHeightSource;
};

extern TerrainLogic *TheTerrainLogic;

void W3DView::rva00089C2D(Int first, Int orient, Real easeIn, Real easeOut)
{
	CameraMoveAlongWaypointPathInfo *path = (CameraMoveAlongWaypointPathInfo *)m_path;
	path->loadPath(m_shutter, first, easeIn, easeOut, 0, true);

	Int i;
	m_totalDistance = 0.0f;
	for (i = 1; i < m_numWaypoints; i++)
	{
		Vector2 dir(m_waypoints[i + 1].pos.x - m_waypoints[i].pos.x, m_waypoints[i + 1].pos.y - m_waypoints[i].pos.y);
		m_segLength[i] = dir.Length();
		m_totalDistance += m_segLength[i];
	}
	m_segLength[0] = 0.0f;
	m_segLength[m_numWaypoints] = 0.0f;
	m_segLength[m_numWaypoints + 1] = 0.0f;

	path->rva00089510(orient, getAngle(), -1);
	path->padCameraAngle(0, 0, getAngle());

	m_cameraAngle[m_numWaypoints] = m_cameraAngle[m_numWaypoints - 1];
	m_cameraAngle[m_numWaypoints + 1] = m_cameraAngle[m_numWaypoints];
	for (i = m_numWaypoints - 1; i > 1; i--)
		m_cameraAngle[i] = (m_cameraAngle[i] + m_cameraAngle[i - 1]) * 0.5f;

	Coord3D finalPos = m_waypoints[m_numWaypoints].pos;
	m_startGround = m_groundLevel;
	m_endGround = TheTerrainLogic->getGroundHeight(finalPos.x, finalPos.y, 0);
	if (m_useHeightSource)
		m_endGround = ((Rva0030E67CHeightSource *)m_heightSource)->rva0030E67C(finalPos.x, finalPos.y);

	m_waypointMode = m_numWaypoints > 1;
	setCameraLock(0);
	m_cameraMoving = 0;
}
