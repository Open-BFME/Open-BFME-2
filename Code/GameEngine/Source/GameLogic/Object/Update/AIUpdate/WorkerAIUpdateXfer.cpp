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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

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

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void slot88(Xfer *xfer, void *value);
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
		TheAudio->slot88(xfer, &m_4CC);
	*xfer == m_preferredDock;
}
