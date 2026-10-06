// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?xfer@Team@@MAEXPAVXfer@@@Z, retail 0x003A2072 (711 bytes).
// Identity (target): WorldBuilder's debug Team.cpp Team::DoXfer sits in the
// Team vtable slot 0x0081AF08 (after ??_GTeam and Team::LoadPostProcess)
// and its callees agree with retail's order: Team::iterate_TeamMemberList
// and the DLINK advance twice (count, then save), XferObjectID per member,
// the member-ID list push_back on load, XferObjectID for the common
// target and the set<int> transfer 0x002F1CDD.
// Donor (Zero Hour Team::xfer): the id check, the member count and IDs
// (loaded IDs queued in m_xferMemberIDList +0x12C for loadPostProcess), the
// state string and flags, two ints, the current waypoint by id
// (TheTerrainLogic slot 0x8C on load), the 32 generic-script flags behind a
// count check, the recruitability flags, the common attack target and the
// two relation maps' snapshots. Both checks throw XferException(5, 0).
// BFME 2 deltas (target): a light-CRC early out and Version(1, 1); eight
// flags at +0x5C; each generic-script slot also moves an unsigned int
// (+0x90); four flags at +0x110; then a real (+0x120), an unsigned int
// (+0x124), the set<int> at +0x130 and a flag (+0x128).
// Shape (inference): the count loop sits in its own block so its iterator
// shares the save loop's stack slot (cl 7.1 for-scope rules).
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include <list>
#include <set>

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



class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);
Xfer *Rva002F1CDDXfer(Xfer *xfer, _STL::set<int, _STL::less<int>, _STL::allocator<int> > *data);

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Waypoint
{
public:
	unsigned int getID() const { return m_id; }

private:
	unsigned char m_pad00[0x04];
	unsigned int m_id; // +0x04
};

class TerrainLogic
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
	virtual void v32(); virtual void v33(); virtual void v34();
	virtual Waypoint *getWaypointByID(unsigned int id); // slot 0x8C
};

extern TerrainLogic *TheTerrainLogic;

// The two relation maps are moved through Xfer's Snapshot overload.
class TeamRelationMap : public Snapshot
{
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

class TeamLinkedBase
{
public:
	virtual void v0();
};

enum { MAX_GENERIC_SCRIPTS = 32 };

class Team : public Snapshot, public TeamLinkedBase
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	unsigned char m_pad08[0x34 - 0x08];
	unsigned int m_id; // +0x34
	unsigned char m_pad38[0x44 - 0x38];
	AsciiString m_state; // +0x44
	unsigned char m_pad48[0x5C - 0x48];
	bool m_enteredOrExited; // +0x5C
	bool m_active; // +0x5D
	bool m_created; // +0x5E
	bool m_checkEnemySighted; // +0x5F
	bool m_seeEnemy; // +0x60
	bool m_prevSeeEnemy; // +0x61
	bool m_wasIdle; // +0x62
	bool m_flag63; // +0x63
	int m_destroyThreshold; // +0x64
	int m_curUnits; // +0x68
	Waypoint *m_currentWaypoint; // +0x6C
	bool m_shouldAttemptGenericScript[MAX_GENERIC_SCRIPTS]; // +0x70
	unsigned int m_genericScriptValue[MAX_GENERIC_SCRIPTS]; // +0x90
	bool m_isRecruitablitySet; // +0x110
	bool m_isRecruitable; // +0x111
	bool m_flag112; // +0x112
	bool m_flag113; // +0x113
	ObjectID m_commonAttackTarget; // +0x114
	TeamRelationMap *m_teamRelations; // +0x118
	TeamRelationMap *m_playerRelations; // +0x11C
	float m_real120; // +0x120
	unsigned int m_value124; // +0x124
	bool m_flag128; // +0x128
	_STL::list<int, _STL::allocator<int> > m_xferMemberIDList; // +0x12C
	_STL::set<int, _STL::less<int>, _STL::allocator<int> > m_set130; // +0x130
};

void Team::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	unsigned int teamID = m_id;
	*xfer == teamID;
	if (teamID != m_id)
		throw XferException(5, 0);

	unsigned short memberCount = 0;
	{
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
			memberCount++;
	}
	*xfer == memberCount;

	int memberID;
	if (xfer->IsStoring())
	{
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			memberID = iter.cur()->getID();
			XferObjectID(xfer, (ObjectID *)&memberID);
		}
	}
	else
	{
		for (unsigned short i = 0; i < memberCount; ++i)
		{
			XferObjectID(xfer, (ObjectID *)&memberID);
			m_xferMemberIDList.push_back(memberID);
		}
	}

	*xfer == m_state;
	*xfer == m_enteredOrExited;
	*xfer == m_active;
	*xfer == m_created;
	*xfer == m_checkEnemySighted;
	*xfer == m_seeEnemy;
	*xfer == m_prevSeeEnemy;
	*xfer == m_wasIdle;
	*xfer == m_flag63;
	*xfer == m_destroyThreshold;
	*xfer == m_curUnits;

	unsigned int currentWaypointID = m_currentWaypoint ? m_currentWaypoint->getID() : 0;
	*xfer == currentWaypointID;
	if (xfer->IsLoading())
		m_currentWaypoint = TheTerrainLogic->getWaypointByID(currentWaypointID);

	unsigned short shouldAttemptGenericScriptCount = MAX_GENERIC_SCRIPTS;
	*xfer == shouldAttemptGenericScriptCount;
	if (shouldAttemptGenericScriptCount != MAX_GENERIC_SCRIPTS)
		throw XferException(5, 0);
	for (int i = 0; i < shouldAttemptGenericScriptCount; ++i)
	{
		*xfer == m_shouldAttemptGenericScript[i];
		*xfer == m_genericScriptValue[i];
	}

	*xfer == m_isRecruitablitySet;
	*xfer == m_isRecruitable;
	*xfer == m_flag112;
	*xfer == m_flag113;
	XferObjectID(xfer, &m_commonAttackTarget);
	*xfer == *m_teamRelations;
	*xfer == *m_playerRelations;
	*xfer == m_real120;
	*xfer == m_value124;
	Rva002F1CDDXfer(xfer, &m_set130);
	*xfer == m_flag128;
}
