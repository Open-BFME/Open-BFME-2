// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ZH AIUpdate.cpp::xfer; BFME1 donor 9cbfb551fe20dae985f91f2319d8997287b6a705.
// Identity: AIUpdateInterface slot 3 and SupplyTruckAIUpdate base call to 00267EDD.
// Fields, slots and added BFME2 transfers read from retail; names follow ZH
// where its transfer sequence agrees. Unidentified members retain offsets.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ascii_string.h"
#include "Common/Snapshot.h"
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

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};


class UpdateModule {
public:
 virtual void v00(); virtual void v01(); virtual void v02();
 void xfer(Xfer *);
 char m_base04[0x20-4];
};
class AIUpdateSnapshotMember : public Snapshot {
public:
 virtual void loadPostProcess(); virtual void crc(Xfer *); virtual void xfer(Xfer *);
};
class StateMachine : public Snapshot {
public:
 virtual void v4(); virtual void v5(); virtual void v6(); virtual void initDefaultState();
};
class Path {
public:
 Path(); void rva003661FC(Xfer *);
 char m_data[0x28];
};
class Locomotor;
class LocomotorSet {
public:
 void clear(); void xferSelfAndCurLocoPtr(Xfer *, Locomotor **);
 char m_data[0x24];
};
template<int N> class BitFlags {
public:
 void xfer(Xfer *);
 unsigned int m_bits[(N+31)/32];
};
class Rva0026AFDAMember { public: void doXfer(Xfer *); char m_data[0xC4]; };
struct Rva00336283Element;
class LuaScriptEngine { public: Rva00336283Element *rva00337DEF(const AsciiString &); };
extern LuaScriptEngine *TheLuaScriptEngine;
void XferCommandSourceType(Xfer *, int *);
Xfer *Rva00263569Xfer(Xfer *, int *);
void XferLocomotorSetType(Xfer *, int *);
void XferWhichTurretType(Xfer *, int *);
void XferAttitudeType(Xfer *, int *);
class PolygonTrigger { public: char m_pad[0x40]; AsciiString m_name; };
class AttackPriorityInfo { public: char m_pad[4]; AsciiString m_name; };
class Waypoint { public: char m_pad[4]; unsigned int m_id; };
class TerrainLogic { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual Waypoint *getWaypointByID(unsigned int);
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual PolygonTrigger *getTriggerAreaByName(const AsciiString &);
};
extern TerrainLogic *TheTerrainLogic;
class AIUpdateInterface : public UpdateModule {
public:
 virtual void xfer(Xfer *);
 virtual void gap4();
 virtual void gap5();
 virtual void gap6();
 virtual void gap7();
 virtual void gap8();
 virtual void gap9();
 virtual void gap10();
 virtual void gap11();
 virtual void gap12();
 virtual void gap13();
 virtual void gap14();
 virtual void gap15();
 virtual void gap16();
 virtual void gap17();
 virtual void gap18();
 virtual void gap19();
 virtual void gap20();
 virtual void gap21();
 virtual void gap22();
 virtual void gap23();
 virtual void gap24();
 virtual void gap25();
 virtual void gap26();
 virtual void gap27();
 virtual void gap28();
 virtual void gap29();
 virtual void gap30();
 virtual void gap31();
 virtual void gap32();
 virtual void gap33();
 virtual void gap34();
 virtual void gap35();
 virtual void gap36();
 virtual void gap37();
 virtual void gap38();
 virtual void gap39();
 virtual void gap40();
 virtual void gap41();
 virtual void gap42();
 virtual void gap43();
 virtual void gap44();
 virtual void gap45();
 virtual void gap46();
 virtual void gap47();
 virtual void gap48();
 virtual void gap49();
 virtual void gap50();
 virtual void gap51();
 virtual void gap52();
 virtual void gap53();
 virtual void gap54();
 virtual void gap55();
 virtual void gap56();
 virtual void gap57();
 virtual void gap58();
 virtual void gap59();
 virtual void gap60();
 virtual void gap61();
 virtual void gap62();
 virtual void gap63();
 virtual void gap64();
 virtual void gap65();
 virtual void gap66();
 virtual void gap67();
 virtual void gap68();
 virtual void gap69();
 virtual void gap70();
 virtual void gap71();
 virtual void gap72();
 virtual void gap73();
 virtual void gap74();
 virtual void gap75();
 virtual void gap76();
 virtual void gap77();
 virtual void gap78();
 virtual void gap79();
 virtual void gap80();
 virtual void gap81();
 virtual void gap82();
 virtual void gap83();
 virtual void gap84();
 virtual void gap85();
 virtual void gap86();
 virtual void gap87();
 virtual void gap88();
 virtual void gap89();
 virtual void gap90();
 virtual void gap91();
 virtual void gap92();
 virtual void gap93();
 virtual void gap94();
 virtual void gap95();
 virtual void gap96();
 virtual void gap97();
 virtual void gap98();
 virtual void gap99();
 virtual void gap100();
 virtual void gap101();
 virtual void gap102();
 virtual void gap103();
 virtual void gap104();
 virtual void gap105();
 virtual void gap106();
 virtual void gap107();
 virtual void gap108();
 virtual void gap109();
 virtual void gap110();
 virtual void gap111();
 virtual void gap112();
 virtual void gap113();
 virtual void gap114();
 virtual void gap115();
 virtual void gap116();
 virtual void gap117();
 virtual void gap118();
 virtual void gap119();
 virtual void gap120();
 virtual void gap121();
 virtual void gap122();
 virtual void gap123();
 virtual void gap124();
 virtual void gap125();
 virtual void gap126();
 virtual void gap127();
 virtual void gap128();
 virtual void gap129();
 virtual void gap130();
 virtual void gap131();
 virtual void gap132();
 virtual void gap133();
 virtual void gap134();
 virtual void gap135();
 virtual void gap136();
 virtual void gap137();
 virtual void gap138();
 virtual void gap139();
 virtual void gap140();
 virtual void gap141();
 virtual void gap142();
 virtual void gap143();
 virtual void gap144();
 virtual void gap145();
 virtual void gap146();
 virtual void gap147();
 virtual void gap148();
 virtual void gap149();
 virtual StateMachine *makeStateMachine();
 char m_unknown20[0x8];
 unsigned int m_priorWaypointID; // +0x28
 unsigned int m_currentWaypointID; // +0x2C
 StateMachine * m_stateMachine; // +0x30
 StateMachine * m_secondaryStateMachine; // +0x34
 StateMachine * m_tertiaryStateMachine; // +0x38
 unsigned int m_nextEnemyScanTime; // +0x3C
 ObjectID m_currentVictimID; // +0x40
 float m_desiredSpeed; // +0x44
 int m_lastCommandSource; // +0x48
 int m_guardMode; // +0x4C
 int m_guardTargetType[2]; // +0x50
 Coord3DBase m_locationToGuard; // +0x58
 ObjectID m_objectToGuard; // +0x64
 unsigned int m_extra68; // +0x68
 PolygonTrigger * m_areaToGuard; // +0x6C
 AttackPriorityInfo * m_attackInfo; // +0x70
 Coord3DBase m_waypointQueue[16]; // +0x74
 int m_waypointCount; // +0x134
 int m_waypointIndex; // +0x138
 Waypoint * m_completedWaypoint; // +0x13C
 Path * m_path; // +0x140
 ObjectID m_requestedVictimID; // +0x144
 Coord3DBase m_requestedDestination; // +0x148
 Coord3DBase m_requestedDestination2; // +0x154
 char m_unknown160[0x4];
 ObjectID m_ignoreObstacleID; // +0x164
 float m_pathExtraDistance; // +0x168
 char m_unknown16C[0x8];
 float m_extra174; // +0x174
 char m_unknown178[0x4];
 unsigned int m_queueForPathFrame; // +0x17C
 Coord3DBase m_finalPosition; // +0x180
 ObjectID m_repulsor1; // +0x18C
 ObjectID m_repulsor2; // +0x190
 char m_unknown194[0x4];
 ObjectID m_moveOutOfWay1; // +0x198
 ObjectID m_moveOutOfWay2; // +0x19C
 float m_pathFloat1A0; // +0x1A0
 char m_unknown1A4[0x28];
 LocomotorSet m_locomotorSet; // +0x1CC
 Locomotor * m_curLocomotor; // +0x1F0
 int m_curLocomotorSet; // +0x1F4
 float m_bfmeFloat1F8; // +0x1F8
 int m_locomotorGoalType; // +0x1FC
 Coord3DBase m_locomotorGoalData; // +0x200
 Snapshot * m_turretAI; // +0x20C
 int m_turretSyncFlag; // +0x210
 AsciiString m_attackInfoName; // +0x214
 int m_attitude; // +0x218
 unsigned int m_nextMoodCheckTime; // +0x21C
 Rva00336283Element * m_extra220; // +0x220
 AIUpdateSnapshotMember m_extra224; // +0x224
 char m_unknown228[0xC];
 unsigned int m_extra234; // +0x234
 ObjectID m_extra238; // +0x238
 char m_unknown23C[0x4];
 unsigned int m_extra240; // +0x240
 BitFlags<591> m_extra244; // +0x244
 BitFlags<591> m_extra290; // +0x290
 BitFlags<101> m_extra2DC; // +0x2DC
 Rva0026AFDAMember m_lastOutsideCommand; // +0x2EC
 bool m_doFinalPosition; // +0x3B0
 bool m_waitingForPath; // +0x3B1
 bool m_isAttackPath; // +0x3B2
 bool m_isFinalGoal; // +0x3B3
 bool m_isApproachPath; // +0x3B4
 bool m_isSafePath; // +0x3B5
 bool m_movementComplete; // +0x3B6
 bool m_extra3B7; // +0x3B7
 bool m_isBlocked; // +0x3B8
 bool m_upgradedLocomotors; // +0x3B9
 bool m_canPathThroughUnits; // +0x3BA
 bool m_extra3BB; // +0x3BB
 bool m_randomlyOffsetMoodCheck; // +0x3BC
 bool m_isAiDead; // +0x3BD
 bool m_isRecruitable; // +0x3BE
 bool m_executingWaypointQueue; // +0x3BF
 bool m_extra3C0; // +0x3C0
 bool m_extra3C1; // +0x3C1
 bool m_extra3C2; // +0x3C2
 char m_unknown3C3[0x1];
 bool m_extra3C4; // +0x3C4
 bool m_extra3C5; // +0x3C5
 bool m_extra3C6; // +0x3C6
 bool m_extra3C7; // +0x3C7
 bool m_extra3C8; // +0x3C8
 bool m_extra3C9; // +0x3C9
 bool m_extra3CA; // +0x3CA
 bool m_extra3CB; // +0x3CB
 bool m_extra3CC; // +0x3CC
 bool m_extra3CD; // +0x3CD
 bool m_extra3CE; // +0x3CE
 char m_unknown3CF[0xD];
 ObjectID m_extra3DC; // +0x3DC
};

void AIUpdateInterface::xfer(Xfer *xfer)
{
 Xfer::Version version(1, 5);
 *xfer == version;
 UpdateModule::xfer(xfer);
 *xfer == m_priorWaypointID;
 *xfer == m_currentWaypointID;
 *xfer == *reinterpret_cast<Snapshot *>(m_stateMachine);
 bool gotsecondary;
 if (xfer->IsStoring()) gotsecondary = m_secondaryStateMachine != 0;
 *xfer == gotsecondary;
 if (gotsecondary) {
  if (xfer->IsLoading()) { m_secondaryStateMachine = makeStateMachine(); m_secondaryStateMachine->initDefaultState(); }
  *xfer == *reinterpret_cast<Snapshot *>(m_secondaryStateMachine);
 }
 bool gottertiary;
 if (xfer->IsStoring()) gottertiary = m_tertiaryStateMachine != 0;
 *xfer == gottertiary;
 if (gottertiary) {
  if (xfer->IsLoading()) { m_tertiaryStateMachine = makeStateMachine(); m_tertiaryStateMachine->initDefaultState(); }
  *xfer == *reinterpret_cast<Snapshot *>(m_tertiaryStateMachine);
 }
 *xfer == m_isAiDead;
 *xfer == m_isRecruitable;
 *xfer == m_nextEnemyScanTime;
 XferObjectID(xfer, &m_currentVictimID);
 *xfer == m_desiredSpeed;
 XferCommandSourceType(xfer, &m_lastCommandSource);
 Rva00263569Xfer(xfer, m_guardTargetType);
 *xfer == m_locationToGuard;
 XferObjectID(xfer, &m_objectToGuard);
 *xfer == m_extra68;
 AsciiString triggerName;
 if (m_areaToGuard) triggerName = m_areaToGuard->m_name;
 *xfer == triggerName;
 if (xfer->IsLoading() && !triggerName.isEmpty()) m_areaToGuard = TheTerrainLogic->getTriggerAreaByName(triggerName);
 AsciiString attackName;
 if (m_attackInfo) attackName = m_attackInfo->m_name;
 *xfer == attackName;
 if (xfer->IsLoading()) m_attackInfoName = attackName;
 *xfer == m_waypointCount;
 if (m_waypointCount < 0 || m_waypointCount > 16) throw XferException(5, 0);
 for (int i=0; i<m_waypointCount; ++i) *xfer == m_waypointQueue[i];
 *xfer == m_waypointIndex;
 *xfer == m_executingWaypointQueue;
 unsigned int id = 0x7fffffff;
 if (m_completedWaypoint) id = m_completedWaypoint->m_id;
 *xfer == id;
 if (xfer->IsLoading()) m_completedWaypoint = TheTerrainLogic->getWaypointByID(id);
 *xfer == m_waitingForPath;
 if (version.m_minimum >= 3) XferObjectID(xfer, &m_extra3DC);
 bool gotPath = m_path != 0;
 *xfer == gotPath;
 if (xfer->IsLoading() && gotPath) m_path = new Path;
 if (gotPath) m_path->rva003661FC(xfer);
 XferObjectID(xfer, &m_requestedVictimID);
 *xfer == m_requestedDestination;
 *xfer == m_requestedDestination2;
 XferObjectID(xfer, &m_ignoreObstacleID);
 *xfer == m_pathExtraDistance;
 *xfer == m_queueForPathFrame;
 *xfer == m_finalPosition;
 *xfer == m_doFinalPosition;
 *xfer == m_isAttackPath;
 *xfer == m_isFinalGoal;
 *xfer == m_isApproachPath;
 *xfer == m_isSafePath;
 *xfer == m_movementComplete;
 *xfer == m_isSafePath;
 *xfer == m_upgradedLocomotors;
 *xfer == m_canPathThroughUnits;
 *xfer == m_randomlyOffsetMoodCheck;
 XferObjectID(xfer, &m_repulsor1);
 XferObjectID(xfer, &m_repulsor2);
 XferObjectID(xfer, &m_moveOutOfWay1);
 XferObjectID(xfer, &m_moveOutOfWay2);
 if (xfer->IsLoading()) { m_locomotorSet.clear(); m_curLocomotor = 0; }
 m_locomotorSet.xferSelfAndCurLocoPtr(xfer, &m_curLocomotor);
 XferLocomotorSetType(xfer, &m_curLocomotorSet);
 xfer->XferRawBytes(&m_locomotorGoalType, 4);
 *xfer == m_locomotorGoalData;
 if (m_turretAI) *xfer == *m_turretAI;
 XferWhichTurretType(xfer, &m_turretSyncFlag);
 XferAttitudeType(xfer, &m_attitude);
 *xfer == m_nextMoodCheckTime;
 AsciiString name220;
 if (m_extra220) name220 = *reinterpret_cast<AsciiString *>(m_extra220);
 *xfer == name220;
 if (xfer->IsLoading()) {
  if (!name220.isEmpty()) m_extra220 = TheLuaScriptEngine->rva00337DEF(name220);
  else m_extra220 = 0;
 }
 m_extra224.xfer(xfer);
 XferObjectID(xfer, &m_extra238);
 *xfer == m_extra3CA;
 m_extra244.xfer(xfer);
 m_extra290.xfer(xfer);
 *xfer == m_extra3CB;
 m_lastOutsideCommand.doXfer(xfer);
 *xfer == m_extra3CC;
 *xfer == m_pathFloat1A0;
 if (version.m_minimum < 5) {
  bool extra = false;
  *xfer == extra;
  if (!extra) m_pathFloat1A0 = 3.402823466e+38F;
 }
 *xfer == m_extra3C1;
 *xfer == m_extra3C8;
 *xfer == m_extra3C5;
 *xfer == m_extra3C6;
 *xfer == m_extra3BB;
 *xfer == m_isBlocked;
 *xfer == m_extra3C2;
 *xfer == m_extra3B7;
 *xfer == m_extra3C7;
 *xfer == m_extra3C9;
 *xfer == m_extra3C0;
 *xfer == m_extra3C4;
 *xfer == m_bfmeFloat1F8;
 xfer->XferRawBytes(&m_guardMode, 4);
 *xfer == m_extra174;
 *xfer == m_extra234;
 m_extra2DC.xfer(xfer);
 *xfer == m_extra3CD;
 *xfer == m_extra3CE;
 *xfer == m_extra240;
 if (version.m_minimum >= 2 && version.m_minimum < 4) {
  bool extra = false;
  *xfer == extra;
 }
}
