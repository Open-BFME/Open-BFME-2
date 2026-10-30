#pragma once
// Team: canonical BFME2 header (hand-written; header_adopt_lane's generator
// emits no virtuals, and this class is polymorphic).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
// Named TeamBFME2.h, like ScriptActionsBFME2.h: Zero Hour's Common/Player.h
// includes "Common/Team.h", so a Code/GameEngine/Include/Common/Team.h would
// shadow the Zero Hour header for every unit with that directory on its path.
//
// Target facts, read off game.dat:
//  - The ctor 0x003A39A7 stores the Snapshot base table 0x00BBB554 at +0,
//    constructs Rva0055B0CC (ctor 0x0055B048) at +4, then stores Team's own
//    tables 0x00C1AEFC at +0 and 0x00C1AEB8 at +4. So Team : Snapshot,
//    Rva0055B0CC (BFME2 drops Zero Hour's MemoryPoolObject base), and its own
//    members start at +0x30.
//  - 0x00C1AEFC has Snapshot's four slots: ??_G 0x003A38CD, loadPostProcess
//    0x003A2339, GetSnapshotName 0x003A3709, xfer 0x003A2072 (rows name all
//    four protected, M). 0x00C1AEB8 has Rva0055B0CC's seventeen: the ??_E
//    thunk 0x003A370F (sub ecx,4), slot 2 0x0039D840, slot 13 getLocation
//    0x0039D7DB, slots 14..16 0x0047A699 / 0x005CB9FA / 0x005DAA6C; the rest
//    are the base's.
//  - TeamFactory allocates 0x13C bytes before each ctor call (0x003A3C1E,
//    0x003A3D65, 0x003A3DE6): sizeof 0x13C.
//  - Member offsets from the ctor's stores (TeamCtor.cpp states each one).
//
// Members: every Team row of reverse/functions.csv with the access, constness
// and parameter types its decorated name states, minus two whose parameter
// types are templates units spell differently (countObjects' and
// transferKindOfUnitsTo's BitFlags; some units define a non-template BitFlags),
// plus the Zero Hour inline accessors the views inline.
// Data: the Zero Hour names for scalar members; the AsciiString, hash table,
// list and set members stay opaque until their types have shared headers.
// Data access is not modeled (all public); it has no codegen effect.
#ifndef CANONICAL_TEAM_H
#define CANONICAL_TEAM_H

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../Source/Common/Rva0055B0CC.h"

class AIGroup;
class AsciiString;
class BfmeFixedStorage0004543D;
class BfmeTab1026;
struct Coord3D;
class Object;
class ObjectTypes;
class Player;
class PlayerRelationMap;
class PolygonTrigger;
class Rva00376A62;
class Team;
class TeamPrototype;
class TeamRelationMap;
class ThingTemplate;
class Waypoint;
class Xfer;
enum Relationship;
// Units define the iterator template themselves (86 views declare the
// out-of-line iterate_TeamMemberList below against their own definition).
template <class OBJECT> class DLINK_ITERATOR;

class Team : public Snapshot, public Rva0055B0CC
{
public:
	Team(TeamPrototype *proto, int id);				// 0x003A39A7

	// Zero Hour inline accessors.
	TeamPrototype *getPrototype() const { return m_proto; }
	unsigned int getID() const { return m_id; }
	void setActive() { if (!m_active) { m_created = true; m_active = true; } }
	bool isActive() const { return m_active; }
	bool isCreated() const { return m_created; }
	bool didEnterOrExit() const { return m_enteredOrExited; }
	const Waypoint *getCurrentWaypoint() { return m_currentWaypoint; }
	void setCurrentWaypoint(const Waypoint *way) { m_currentWaypoint = way; }
	Object *getFirstItemIn_TeamMemberList() const { return m_dlinkhead_TeamMemberList; }

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
	bool isInList_TeamMemberList(Object *) const;	// 0x0028A74F
	void prependTo_TeamMemberList(Object *);		// 0x0028A75F
	void removeFrom_TeamMemberList(Object *);		// 0x0028A77F
	bool dlink_isInList_TeamInstanceList(Team *const *pListHead) const;	// 0x0039D40F
	void dlink_prependTo_TeamInstanceList(Team **pListHead);	// 0x0039D429
	void dlink_removeFrom_TeamInstanceList(Team **pListHead);	// 0x0039D440
	Player *getControllingPlayer() const;			// 0x0039D7CF
	virtual Coord3D getLocation() const;			// 0x0039D7DB, Rva0055B0CC slot 13
	void setTeamTargetObject(Object *);				// 0x0039D84A
	void rva0039D889(bool);							// 0x0039D889
	void rva0039D8BA(Object *);						// 0x0039D8BA
	void rva0039D8D3(unsigned int);					// 0x0039D8D3
	void setControllingPlayer(Player *newController);	// 0x0039D97E
	int getTargetableCount() const;					// 0x0039D9E3
	Coord3D *rva0039DA2A(Coord3D *) const;			// 0x0039DA2A
	bool rva0039DAF4() const;						// 0x0039DAF4
	void rva0039DB31(const void *);					// 0x0039DB31
	void countObjectsByThingTemplate(int numThings, const ThingTemplate *const *things, bool ignoreDead, int *counts, bool ignoreUnderConstruction) const;	// 0x0039DB89
	int rva0039DC05(int, bool, bool) const;			// 0x0039DC05
	int countBuildings() const;						// 0x0039DC63
	void healAllObjects();							// 0x0039DCE9
	int rva0039DD12(int (*func)(Object *, void *), void *userData) const;	// 0x0039DD12
	bool rva0039DD4B(bool);							// 0x0039DD4B
	bool rva0039DDC2(BfmeFixedStorage0004543D, bool);	// 0x0039DDC2
	bool rva0039DE46(BfmeTab1026 *, bool);			// 0x0039DE46
	bool hasAnyUnits();								// 0x0039DEC4
	bool hasAnyBuildings(BfmeFixedStorage0004543D, BfmeFixedStorage0004543D);	// 0x0039DF1C
	bool rva0039DF87(BfmeTab1026 *);				// 0x0039DF87
	bool isIdle() const;							// 0x0039DFF8
	bool hasAnyObjects(bool);						// 0x0039E042
	bool rva0039E0D0();								// 0x0039E0D0
	bool didAllEnter(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E15D
	bool didPartialEnter(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E20D
	bool didPartialExit(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E288
	bool didAllExit(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E303
	bool allInside(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E3C8
	bool noneInside(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E474
	bool someInsideSomeOutside(PolygonTrigger *pTrigger, unsigned int whichToConsider);	// 0x0039E50D
	void rva0039E5B9(Coord3D *);					// 0x0039E5B9
	void transferUnitsTo(Team *newTeam);			// 0x0039E660
	bool damageTeamMembers(float amount);			// 0x0039E76C
	void moveTeamTo(Coord3D destination);			// 0x0039E7F2
	bool hasAnyBuildFacility();						// 0x0039E815
	float rva0039E84B(Object *);					// 0x0039E84B
	Object *rva0039E8EB();							// 0x0039E8EB
	bool rva0039E8FF(int);							// 0x0039E8FF
	Object *rva0039E968(int);						// 0x0039E968
	Coord3D *rva0039E9A1(Coord3D *) const;			// 0x0039E9A1
	void disband();									// 0x0039E9E0
	void setAttackPriorityName(AsciiString name);	// 0x0039F094
	bool rva0039F0D2();								// 0x0039F0D2
	void updateState();								// 0x0039F0E3
	bool rva0039F824();								// 0x0039F824
	void notifyTeamOfObjectDeath(Object *goneObj);	// 0x0039F835
	void updateGenericScripts();					// 0x0039F8F7
	void getTeamAsAIGroup(AIGroup *pAIGroup);		// 0x003A0F62
	Relationship getRelationship(const Team *that) const;	// 0x003A0FD2
	Object *getTeamTargetObject();					// 0x003A105B
	bool rva003A10C0(int) const;					// 0x003A10C0
	bool rva003A10DF(int) const;					// 0x003A10DF
	void deleteTeam(bool ignoreDead);				// 0x003A10FE
	bool recruitUnit(Object **, float *, Object *, const ThingTemplate *, const Coord3D *);	// 0x003A123C
	Object *tryToRecruit(const ThingTemplate *, const Coord3D *, float, int, int, int);	// 0x003A135B
	bool rva003A1542(const ThingTemplate *, int);	// 0x003A1542
	int rva003A1626(const ThingTemplate *, Rva00376A62 *, int, Team *);	// 0x003A1626
	int rva003A178D(ObjectTypes *, int, Team *);	// 0x003A178D
	int rva003A1AA3(const ThingTemplate *, ObjectTypes *, int, float);	// 0x003A1AA3
	void evacuateTeam(bool);						// 0x003A1C3A
	void killTeam();								// 0x003A1D1A
	bool enableGenericScript(const AsciiString &, const AsciiString &, bool);	// 0x003A1F65
	void rva003A23A5(int id, bool add);				// 0x003A23A5
	void rva003A2CEB(int, Object *);				// 0x003A2CEB
	void rva003A2D53(int, Object *);				// 0x003A2D53
	void rva003A2DBB(float);						// 0x003A2DBB
	bool rva003A3717(const AsciiString &);			// 0x003A3717
	float rva003A3736(float);						// 0x003A3736
	void rva003A38E9(const AsciiString &, unsigned char);	// 0x003A38E9
	void setRecruitable(bool recruitable);			// 0x003BA5F9
	Team *dlink_next_TeamInstanceList() const;		// 0x005C4AF5

	// Rva0055B0CC slots Team fills with ICF-shared bodies.
	virtual float vslot02() const;					// slot 2, 0x0039D840
	virtual bool vslot14() const;					// slot 14, 0x0047A699
	virtual bool vslot15(int);						// slot 15, 0x005CB9FA
	virtual int vslot16(void *);					// slot 16, 0x005DAA6C

protected:
	virtual ~Team();								// 0x003A354F (??_G 0x003A38CD, ??_E 0x003A370F)

	// Snapshot slots, spelled the way the unit selected Snapshot.h's; Team's
	// rows are loadPostProcess, GetSnapshotName() const and xfer.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();
#else
	virtual void loadPostProcess();					// 0x003A2339
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;	// 0x003A3709
#endif
#else
	virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);
#else
	virtual void DoXfer(Xfer *xfer);
#endif
#else
	virtual void xfer(Xfer *xfer);					// 0x003A2072
#endif

public:
	TeamPrototype *m_proto;							// +0x30
	unsigned int m_id;								// +0x34
	Object *m_dlinkhead_TeamMemberList;				// +0x38
	Team *m_dlink_TeamInstanceList_prev;			// +0x3C
	Team *m_dlink_TeamInstanceList_next;			// +0x40
	unsigned char m_opaque44[4];					// +0x44 AsciiString m_state
	unsigned char m_opaque48[0x14];					// +0x48 hash table (ctor 0x003A393A)
	bool m_enteredOrExited;							// +0x5C
	bool m_active;									// +0x5D
	bool m_created;									// +0x5E
	bool m_5F;										// +0x5F
	bool m_checkEnemySighted;						// +0x60
	bool m_seeEnemy;								// +0x61
	bool m_prevSeeEnemy;							// +0x62
	bool m_wasIdle;									// +0x63
	int m_destroyThreshold;							// +0x64
	int m_curUnits;									// +0x68
	const Waypoint *m_currentWaypoint;				// +0x6C
	bool m_shouldAttemptGenericScript[32];			// +0x70
	int m_90[32];									// +0x90
	bool m_isRecruitablitySet;						// +0x110
	bool m_isRecruitable;							// +0x111
	bool m_112;										// +0x112
	bool m_113;										// +0x113
	int m_commonAttackTarget;						// +0x114
	TeamRelationMap *m_teamRelations;				// +0x118
	PlayerRelationMap *m_playerRelations;			// +0x11C
	float m_120;									// +0x120
	int m_124;										// +0x124
	bool m_128;										// +0x128
	unsigned char m_pad129[3];						// +0x129
	unsigned char m_opaque12C[4];					// +0x12C list<int>
	unsigned char m_opaque130[0xC];					// +0x130 set<AsciiString>
};													// sizeof 0x13C
typedef char CanonicalTeamSizeCheck[sizeof(Team) == 0x13C ? 1 : -1];

#endif // CANONICAL_TEAM_H
