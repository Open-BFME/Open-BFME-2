// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?doXfer@Rva0026AFDAMember@@QAEXPAVXfer@@@Z retail 0x003533BF..0x00353667
// (680B) thiscall ret 4.
//
// Non-virtual transfer of the 0xC4 command-parameter member that the
// DeployStyle +0x3E4 owner and AIUpdate +0x2EC carry (callers 0x002684A5
// 0x0036ACAF 0x0048E81E). Donor: BFME 1 AICommandParmsStorageXfer.cpp
// (AICommandParmsStorage::doXfer; Zero Hour AIStates.cpp line for line) with
// the layout the member ctor 0x0026AFDA and dtor 0x0026B03D establish.
// BFME 2 read from retail: version block (1 2) through Xfer slot +0x28; the
// float at +0x3C is transferred only from version 2; the +0x40 member is
// transferred through its own first virtual (vtable 0x007F9200 slot 0 is
// 0x004D6F86); the polygon trigger name is at +0x40 and is looked up by
// reference through TerrainLogic slot +0x9C; waypoints by id through +0x8C;
// the command button name is at +0x10 and is resolved through
// ControlBar::findCommandButton 0x0031BE3C; the path is a 0x28-byte Path
// (ctor 0x00363DC8) transferred through 0x003661FC.
// Xfer slots: +0x04 isLoading +0x60 Coord3D +0x6C AsciiString +0x70 Real
// +0x78 UnsignedInt +0x7C Int +0x90 Bool (as AIUpdateXfer.cpp's model).
#include "ascii_string.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

// Version block (read-back version then the writer's version); retail's
// frame places it as a four-byte object (BFME 1 donor note).

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	unsigned char m_version;
	unsigned char m_currentVersion;
	unsigned short m_unmodelled02;
};

void XferAICommandType(Xfer *xfer, int *value);
void XferCommandSourceType(Xfer *xfer, int *value);
void XferObjectID(Xfer *xfer, ObjectID *value);

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
	int size() const { return m_finish - m_start; }
	T &operator[](int i) { return m_start[i]; }
private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

#include "../../../../../Include/GameLogic/Waypoint.h"

#include "../../../../../Include/GameLogic/PolygonTrigger.h"

#include "../../../../../Include/GameClient/CommandButton.h"

#include "../../../../../Include/GameLogic/PathfindPath.h"

#include "../../../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

#include "../../../../../Include/GameClient/ControlBar.h"

extern ControlBar *TheControlBar;

// The +0x40 member (vtable 0x007F9200): its only virtual transfers it.
class Rva003533BFDamageView
{
public:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad04[0x7C - 4];
};

#define INVALID_WAYPOINT_ID 0x7fffffff

class Rva0026AFDAMember
{
public:
	void doXfer(Xfer *xfer);

private:
	Int m_cmd;					// +0x00
	Int m_cmdSource;				// +0x04
	Coord3D m_pos;					// +0x08
	ObjectID m_obj;					// +0x14
	ObjectID m_otherObj;				// +0x18
	AsciiString m_teamName;				// +0x1C
	AsciiString m_teamOwner;			// +0x20
	_STL::vector<Coord3D> m_coords;			// +0x24
	Waypoint *m_waypoint;				// +0x30
	PolygonTrigger *m_polygon;			// +0x34
	Int m_intValue;					// +0x38
	Real m_real3C;					// +0x3C
	Rva003533BFDamageView m_damage;			// +0x40
	const CommandButton *m_commandButton;		// +0xBC
	Path *m_path;					// +0xC0
};

void Rva0026AFDAMember::doXfer(Xfer *xfer)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->operator==(version);

	XferAICommandType(xfer, &m_cmd);
	XferCommandSourceType(xfer, &m_cmdSource);
	xfer->operator==(reinterpret_cast<Coord3DBase &>(m_pos));
	XferObjectID(xfer, &m_obj);
	XferObjectID(xfer, &m_otherObj);
	xfer->operator==(m_teamName);
	xfer->operator==(m_teamOwner);
	Int numCoords = m_coords.size();
	xfer->operator==(numCoords);
	Int i;
	if (xfer->IsLoading())
	{
		for (i = 0; i < numCoords; i++)
		{
			Coord3D pos;
			xfer->operator==(reinterpret_cast<Coord3DBase &>(pos));
			m_coords.push_back(pos);
		}
	}
	else
	{
		for (i = 0; i < numCoords; i++)
		{
			Coord3D pos;
			pos.x = m_coords[i].x;
			pos.y = m_coords[i].y;
			pos.z = m_coords[i].z;
			xfer->operator==(reinterpret_cast<Coord3DBase &>(pos));
		}
	}

	UnsignedInt id = INVALID_WAYPOINT_ID;
	if (m_waypoint)
		id = m_waypoint->getID();
	xfer->operator==(id);
	Bool loading = xfer->IsLoading();
	if (loading && id != INVALID_WAYPOINT_ID)
		m_waypoint = TheTerrainLogic->getWaypointByID(id);

	AsciiString triggerName;
	if (m_polygon)
		triggerName = m_polygon->getTriggerName();
	xfer->operator==(triggerName);
	if (xfer->IsLoading())
	{
		if (!triggerName.isEmpty())
			m_polygon = TheTerrainLogic->getTriggerAreaByName(triggerName);
	}

	xfer->operator==(m_intValue);
	if (version.m_currentVersion >= 2)
		xfer->operator==(m_real3C);

	m_damage.xfer(xfer);

	AsciiString cmdName;
	if (m_commandButton)
		cmdName = m_commandButton->getName();
	xfer->operator==(cmdName);
	if (!cmdName.isEmpty() && m_commandButton == 0)
		m_commandButton = TheControlBar->findCommandButton(cmdName);

	Bool hasPath = m_path != 0;
	xfer->operator==(hasPath);
	if (hasPath && m_path == 0)
		m_path = new Path;
	if (hasPath)
		m_path->DoXfer(xfer);
}
