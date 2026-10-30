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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

struct BfmeAudioEventPrefix136;
class Xfer;
struct BfmeAudioEventPrefix136;
class Xfer;
struct BfmeAudioEventPrefix136;
class Xfer;
struct AbilityMiscAudio;
class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	// vslot 25 (+0x64)
	virtual int addAudioEvent(BfmeAudioEventPrefix136 *event) = 0;
	virtual void _pad26() = 0;
	// vslot 27 (+0x6C)
	virtual void removeAudioEvent(unsigned int handle) = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	// vslot 52 (+0xD0)
	virtual bool isCurrentlyPlaying(int handle) = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual void _pad77() = 0;
	// vslot 78 (+0x138)
	virtual AbilityMiscAudio * getMiscAudio() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	// vslot 88 (+0x160)
	virtual void xferAudioHandle(Xfer *xfer, unsigned int *handle) = 0;
};
extern AudioManager *TheAudio;

class AIUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
private:
	char m_pad[0x3F0 - 4];
};

class WorkerAIUpdate : public AIUpdateInterface
{
protected:
	virtual void xfer(Xfer *xfer);
private:
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
