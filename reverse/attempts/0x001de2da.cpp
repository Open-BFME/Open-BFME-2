// ?reportEvaEvent@Eva@@QAE_NW4EvaEventID@@PBUCoord3D@@1@Z
// partial score=0.99 date=2026-10-08
// Whole-file Eva.cpp candidate; restore under Code/GameEngine/Source/GameClient.
// Native STLport delayed-report tree; the helper below owns 0x001DD468.
// cl: /O1 /G7 /EHsc /DNDEBUG /MD /arch:SSE
// Eva.cpp -- Eva event-status queries recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv). WB's debug Eva.cpp names each member and its
// diagnostics (Eva.cpp:1408..1447): an invalid EvaEventID, and a status array
// whose size differs from the info array's; retail keeps the checks and
// drops the messages. Layout (target): m_allEventInfos, 0x30-byte records at
// +0x1C; the parallel status array, 0x34-byte records at +0x5C. The status
// record's members are rowed under placeholder names (0x001DCDAF,
// 0x001DD240); field names past WB's are not recovered.

#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum EvaEventID
{
	EVA_INVALID = -1
};

// STLport vector view: inline size() divides the pointer difference.
template <class T> class EvaVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T &operator[](UnsignedInt i) { return m_start[i]; }
	const T &operator[](UnsignedInt i) const { return m_start[i]; }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

struct Vec001DCDAF
{
	Real x;
	Real y;
	Real z;
};

// A returned position. The memberwise copy constructor is what gives the
// retail return copies their fld/fstp-then-mov shape; the float constructor
// builds a result in place.
struct EvaCoord
{
	EvaCoord() {}
	EvaCoord(const EvaCoord &p) : x(p.x), y(p.y), z(p.z) {}
	EvaCoord(Real ax, Real ay, Real az) : x(ax), y(ay), z(az) {}
	Real x;
	Real y;
	Real z;
};

// One event's info record (0x30 bytes), seen by the status updates as their
// argument.
struct Arg001DCDAF
{
	unsigned char m_data[0x0c];
	UnsignedInt m_delayFrames;				// +0x0C, observed retail unsigned test
	unsigned char m_pad10[0x20 - 0x10];
	EvaEventID *m_eventIDsStart;			// +0x20, observed retail pointer read
	EvaEventID *m_eventIDsFinish;			// +0x24, observed retail pointer read
	unsigned char m_pad28[0x2c - 0x28];
	Bool m_2c;						// +0x2C, observed retail byte test
	unsigned char m_pad2d[0x30 - 0x2d];
};

class Player
{
public:
	int rva002ABCF0(unsigned char flag, int *out);		// 0x002ABCF0, the player's best object
};

// The object view: its position at +0x38.
struct EvaObjectView
{
	unsigned char m_pad00[0x38];
	EvaCoord m_position;					// +0x38
};

// The living-world player: its region name at +0x2C, its side at +0x14.
struct EvaWorldMapPlayer
{
	unsigned char m_pad00[0x14];
	int m_14;						// +0x14
	unsigned char m_pad18[0x2c - 0x18];
	unsigned char m_regionName[4];				// +0x2C
};

// One event's status record (0x34 bytes).
class Rva001DCDAF
{
public:
	Bool rva001DCDAF(const Arg001DCDAF *info, const Vec001DCDAF *pos, const Vec001DCDAF *pos2);	// 0x001DCDAF
	void rva001DD7C1(Arg001DCDAF *info, const Vec001DCDAF *position);
	EvaCoord getPlayPositionForEvent(const Arg001DCDAF *info, Player *localPlayerRTS, EvaWorldMapPlayer *localPlayerWorldMap) const;

	Real m_blockedTime;					// +0x00, > 0 blocks the event
	Real m_aboutToPlayTime;					// +0x04, >= 0 when about to play
	EvaCoord m_position;					// +0x08
	unsigned char m_pad14[0x20 - 0x14];
	Bool m_hasPosition;					// +0x20
	unsigned char m_pad21;
	Bool m_hasPlayed;					// +0x22
	unsigned char m_pad23[0x30 - 0x23];
	UnsignedInt m_lastReallyPlayedFrame;			// +0x30
};

class GameLogic
{
public:
	Bool rva001DCD1C();					// 0x001DCD1C

	unsigned char m_pad00[0x40];
	UnsignedInt m_frame;				// +0x40, observed retail load
};

class Eva;
extern GameLogic *TheGameLogic;
extern Eva *TheEva;

// The status record's played counter (0x001DD240), placeholder-rowed under
// another class name.
class Rva001DD240
{
public:
	void rva001DD240(UnsignedInt *info);			// 0x001DD240
};

// The report internalReportEvaEvent takes (WB's report record; rowed under
// the placeholder Rva001DD063, default constructor 0x001DD1D0): the event,
// then two optional positions, each behind a presence flag.
struct Rva001DD063
{
	Rva001DD063();						// 0x001DD1D0

	EvaEventID m_eventID;					// +0x00
	Bool m_hasPosition;					// +0x04
	Bool m_hasSecondPosition;				// +0x05
	unsigned char m_pad06[2];
	Coord3D m_position;					// +0x08
	Coord3D m_secondPosition;				// +0x14
};

// A delayed report keyed by the frame it is due (0x001DD2BF), held in Eva's
// multiset.
struct Rva001DD1B3
{
	Rva001DD1B3(const Int &frame, const Rva001DD063 &report);

	Int m_frame;						// +0x00
	Rva001DD063 m_report;					// +0x04
};

// stlport
#include <set>
typedef _STL::_Rb_tree<Rva001DD1B3, Rva001DD1B3, _STL::_Identity<Rva001DD1B3>, _STL::less<Rva001DD1B3>, _STL::allocator<Rva001DD1B3> > EvaDelayedTree;
namespace _STL {
template<> EvaDelayedTree::iterator EvaDelayedTree::insert_equal(const Rva001DD1B3 &);
}
typedef char EvaDelayedSetWidth[(sizeof(_STL::multiset<Rva001DD1B3, _STL::less<Rva001DD1B3>, _STL::allocator<Rva001DD1B3> >)==12)?1:-1];

struct EvaEventReport
{
	EvaEventID m_eventID;					// +0x00
	Bool m_hasPosition;					// +0x04
	Bool m_hasSecondPosition;				// +0x05
	unsigned char m_pad06[2];
	Vec001DCDAF m_position;					// +0x08
	Vec001DCDAF m_secondPosition;				// +0x14
};

class Eva
{
public:
	Bool reportEvaEvent(EvaEventID eventID, const Coord3D *position, const Coord3D *secondPosition);
	Bool internalReportEvaEvent(const EvaEventReport *report);	// 0x001DD468, unrowed
	void countEvaEventAsPlayed(EvaEventID eventID);
	Bool isEventBlockedByTimeout(EvaEventID eventID) const;
	Bool isEventAboutToPlay(EvaEventID eventID) const;
	Bool getLastReallyPlayedFrameForEvaEvent(EvaEventID eventID, UnsignedInt *frame) const;

private:
	unsigned char m_pad00[0x10];
	EvaDelayedTree m_delayedEvents;	// +0x10
	EvaVectorView<Arg001DCDAF> m_allEventInfos;		// +0x1C (WB name)
	unsigned char m_pad28[0x5c - 0x28];
	EvaVectorView<Rva001DCDAF> m_eventStatus;		// +0x5C
};

// Eva::countEvaEventAsPlayed, retail 0x001DD4E3 (90 bytes).
void Eva::countEvaEventAsPlayed(EvaEventID eventID)
{
	if (eventID == EVA_INVALID)
		return;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return;
	((Rva001DD240 *)&m_eventStatus[eventID])->rva001DD240((UnsignedInt *)&m_allEventInfos[eventID]);
}

// Eva::isEventBlockedByTimeout, retail 0x001DD53D (99 bytes): an invalid
// event counts as blocked.
Bool Eva::isEventBlockedByTimeout(EvaEventID eventID) const
{
	if (eventID == EVA_INVALID)
		return true;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return true;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return true;
	return m_eventStatus[eventID].m_blockedTime > 0.0f;
}

// Eva::isEventAboutToPlay, retail 0x001DD5A0 (100 bytes).
Bool Eva::isEventAboutToPlay(EvaEventID eventID) const
{
	if (eventID == EVA_INVALID)
		return false;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	return m_eventStatus[eventID].m_aboutToPlayTime >= 0.0f;
}

// Eva::getLastReallyPlayedFrameForEvaEvent, retail 0x001DD604 (108 bytes):
// the frame is cleared first and set only for an event that has played.
Bool Eva::getLastReallyPlayedFrameForEvaEvent(EvaEventID eventID, UnsignedInt *frame) const
{
	*frame = 0;
	if (eventID == EVA_INVALID)
		return false;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	if (!m_eventStatus[eventID].m_hasPlayed)
		return false;
	*frame = m_eventStatus[eventID].m_lastReallyPlayedFrame;
	return true;
}

// Eva::reportEvaEvent, retail 0x001DE2DA (247 bytes; WorldBuilder's Eva.cpp
// 0x00ACC880, asserts at lines 1230..1270): a report for an event whose info
// carries a delay is queued until the frame it is due, unless the logic's
// 0x001DCD1C state holds; otherwise it is reported now.
Bool Eva::reportEvaEvent(EvaEventID eventID, const Coord3D *position, const Coord3D *secondPosition)
{
	if (eventID == EVA_INVALID)
		return false;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	Rva001DD063 report;
	report.m_eventID = eventID;
	if (position)
	{
		report.m_position = *position;
		report.m_hasPosition = true;
	}
	else
		report.m_hasPosition = false;
	if (secondPosition)
	{
		report.m_secondPosition = *secondPosition;
		report.m_hasSecondPosition = true;
	}
	else
		report.m_hasSecondPosition = false;
	const UnsignedInt &delay = m_allEventInfos[eventID].m_delayFrames;
	if (delay > 0)
	{
		GameLogic *logic = TheGameLogic;
		if (!logic->rva001DCD1C())
		{
			m_delayedEvents.insert_equal(Rva001DD1B3(logic->m_frame + delay, report));
			return true;
		}
	}
	return internalReportEvaEvent(reinterpret_cast<const EvaEventReport *>(&report));
}

// ?rva001DD7C1@Rva001DCDAF@@QAEXPAUArg001DCDAF@@PBUVec001DCDAF@@@Z 74B @0x001DD7C1.
// Class identity follows the existing 0x34-byte Rva001DCDAF status record;
// retail writes its +0x22 flag, +0x24 position and +0x30 frame. The argument
// pointer fields and GameLogic frame offset are direct retail observations;
// the semantic member names remain structural inferences.
void Rva001DCDAF::rva001DD7C1(Arg001DCDAF *info, const Vec001DCDAF *position)
{
	((Rva001DD240 *)this)->rva001DD240((UnsignedInt *)info);
	EvaEventID *eventID = info->m_eventIDsStart;
	EvaEventID *eventIDsFinish = info->m_eventIDsFinish;
	while (eventID != eventIDsFinish)
	{
		TheEva->countEvaEventAsPlayed(*eventID);
		++eventID;
	}
	m_hasPlayed = true;
	m_lastReallyPlayedFrame = TheGameLogic->m_frame;
	*(Vec001DCDAF *)((unsigned char *)this + 0x24) = *position;
}

// The living-world region manager's lookups (TheLivingWorldLogic +0xB0):
// 0x002104B6 finds a region by name, 0x0020EA58 its centre point; the region
// keeps its owner at +0x13C.
class Rva002104B6
{
public:
	void *rva002104B6(void *name);
};

class Rva002B2702B0
{
public:
	bool rva0020EA58(void *region, float *center);
};

struct EvaRegionView
{
	unsigned char m_pad00[0x13c];
	int m_13c;						// +0x13C
};

class LivingWorldLogic
{
public:
	void *getRegionManager() const { return m_regionManager; }

	unsigned char m_pad00[0xb0];
	void *m_regionManager;					// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

// 0x002BF5B0 maps a world-map point to a 3D position.
class Rva002D3627Host
{
public:
	bool rva002BF5B0(const Coord2D *in, Coord3D *out);
};
extern Rva002D3627Host *g_00DFEF18;

// EvaEventStatus::getPlayPositionForEvent, retail 0x001DCE6B (279 bytes;
// WorldBuilder's Eva.cpp 0x00AC8E80, whose assert names both player
// parameters): the event's own position unless the info record's +0x2C byte
// is set, else the RTS player's best object, else the world-map player's
// region centre, else (-100, -100, 0).
EvaCoord Rva001DCDAF::getPlayPositionForEvent(const Arg001DCDAF *info, Player *localPlayerRTS, EvaWorldMapPlayer *localPlayerWorldMap) const
{
	if (m_hasPosition && !info->m_2c)
		return m_position;
	if (localPlayerRTS)
	{
		EvaObjectView *obj = (EvaObjectView *)localPlayerRTS->rva002ABCF0(1, 0);
		if (obj)
			return obj->m_position;
	}
	else if (localPlayerWorldMap)
	{
		EvaRegionView *region = (EvaRegionView *)((Rva002104B6 *)TheLivingWorldLogic->getRegionManager())->rva002104B6(localPlayerWorldMap->m_regionName);
		if (region && region->m_13c == localPlayerWorldMap->m_14)
		{
			Coord2D center;
			if (((Rva002B2702B0 *)TheLivingWorldLogic->getRegionManager())->rva0020EA58(region, &center.x))
			{
				Coord3D pos;
				pos.x = center.x;
				pos.y = center.y;
				pos.z = 0.0f;
				g_00DFEF18->rva002BF5B0(&center, &pos);
				return EvaCoord(pos.x, pos.y, pos.z);
			}
		}
	}
	return EvaCoord(-100.0f, -100.0f, 0.0f);
}

// Eva::internalReportEvaEvent, retail 0x001DD468 (123 bytes). WorldBuilder's
// Eva.cpp names this member; its report flags select the two optional positions.
// Array extents and strides are retail observations (0x30 info, 0x34 status).
// Keep the negated equality and member call: MSVC 7.1 emits the retail count
// evaluation order and preloads both array bases before pushing the positions.
Bool Eva::internalReportEvaEvent(const EvaEventReport *report)
{
	EvaEventID eventID = report->m_eventID;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (!(m_eventStatus.size() == m_allEventInfos.size()))
		return false;
	Arg001DCDAF *info = &m_allEventInfos[0];
	Rva001DCDAF *status = &m_eventStatus[0];
	Bool (Rva001DCDAF::*set)(const Arg001DCDAF *, const Vec001DCDAF *, const Vec001DCDAF *) = &Rva001DCDAF::rva001DCDAF;
	return (status[eventID].*set)(&info[eventID],
		report->m_hasPosition ? &report->m_position : 0,
		report->m_hasSecondPosition ? &report->m_secondPosition : 0);
}
