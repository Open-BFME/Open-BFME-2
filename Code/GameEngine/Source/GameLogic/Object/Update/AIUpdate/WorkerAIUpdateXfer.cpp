// cl: /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
//
// ?xfer@WorkerAIUpdate@@MAEXPAVXfer@@@Z, retail 0x004AA1DB, 453 bytes.
// WorkerAIUpdate vtable 0x00854100 slot: the pointer sits at 0x0085419C,
// immediately before the rowed pool-key body 0x004A9B06 and in the same
// table as dozer slot 23 (0x004A9E3E at 0x0085415C).
//
// Same shape as the rowed DozerAIUpdate::xfer (0x00489671): AIUpdateInterface
// base 0x00267EDD, IsLightCRC, Version(1, 2), task count 3, three
// ObjectID/frame pairs, a state-machine snapshot, a raw int, dock count 3,
// nine bool+Coord3D docks, then the worker tail. Layout is the rowed ctor
// in WorkerAIUpdateCtor.cpp (tasks at +0x3F0, docks at +0x40C, machines at
// +0x4C0/+0x4C4/+0x4C8, audio handle at +0x4CC).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../../Include/Common/BfmeXfer.h"

#include "../../../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../../../Libraries/Include/Lib/Coord3DBase.h"

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);

#include "../../../../../Include/Common/XferException.h"

struct BfmeAudioEventPrefix136;
class Xfer;
struct BfmeAudioEventPrefix136;
class Xfer;
struct BfmeAudioEventPrefix136;
class Xfer;
struct AbilityMiscAudio;
#include "../../../../../Include/Common/GameAudio.h"
extern AudioManager *TheAudio;

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"

class WorkerAIUpdate : public AIUpdateInterface
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_unrecovered3E4[0x3F0 - sizeof(AIUpdateInterface)];
	enum { DOZER_NUM_TASKS = 3, DOZER_NUM_DOCK_POINTS = 3 };

	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};
	struct DockPoint
	{
		Bool valid;
		Coord3DBase location;
	};

	DozerTaskInfo m_task[DOZER_NUM_TASKS];
	Int m_currentTask;
	DockPoint m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_DOCK_POINTS];
	Int m_buildSubTask;
	Int m_4A0;
	ObjectID m_4A4;
	Coord3DBase m_4A8;
	Bool m_4B4;
	UnsignedInt m_preferredDock;
	Bool m_forcePending;
	Bool m_isRebuild;
	Bool m_forcedBusyPending;
	Snapshot *m_workerMachine;
	Snapshot *m_dozerMachine;
	Snapshot *m_supplyTruckStateMachine;
	UnsignedInt m_4CC;
};

void WorkerAIUpdate::xfer(Xfer *xfer)
{
	AIUpdateInterface::xfer(xfer);
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	Int numTasks = DOZER_NUM_TASKS;
	*xfer == numTasks;
	if (numTasks != DOZER_NUM_TASKS)
		throw XferException(5, 0);

	Int i, j;
	for (i = 0; i < DOZER_NUM_TASKS; i++)
	{
		XferObjectID(xfer, &m_task[i].m_targetObjectID);
		*xfer == m_task[i].m_taskOrderFrame;
	}
	*xfer == *m_dozerMachine;
	xfer->XferRawBytes(&m_currentTask, sizeof(m_currentTask));

	Int dockPoints = DOZER_NUM_DOCK_POINTS;
	*xfer == dockPoints;
	if (dockPoints != DOZER_NUM_DOCK_POINTS)
		throw XferException(5, 0);

	for (i = 0; i < DOZER_NUM_TASKS; i++)
	{
		for (j = 0; j < DOZER_NUM_DOCK_POINTS; j++)
		{
			*xfer == m_dockPoint[i][j].valid;
			*xfer == m_dockPoint[i][j].location;
		}
	}
	xfer->XferRawBytes(&m_buildSubTask, sizeof(m_buildSubTask));
	*xfer == *m_supplyTruckStateMachine;
	XferObjectID(xfer, &m_4A4);
	*xfer == m_4A8;
	*xfer == m_4B4;
	*xfer == m_4A0;
	*xfer == m_forcePending;
	*xfer == m_forcedBusyPending;
	*xfer == m_isRebuild;
	*xfer == *m_workerMachine;
	if (TheAudio)
		TheAudio->xferAudioHandle(xfer, &m_4CC);
	*xfer == m_preferredDock;
}
