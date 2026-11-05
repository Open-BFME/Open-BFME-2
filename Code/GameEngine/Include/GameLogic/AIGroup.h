// Target facts (code addresses are RVAs; table addresses are VAs):
// AI::createGroup pushes 0x3C at 0x002FEC57 and calls AIGroup's constructor at 0x002FEC6F. Constructor 0x0036E4C7 stores 0x00C17D00 at +0 (0x0036E4E7), builds the list at +4 (0x0036E4ED -> 0x004EC36C) and the vector at +0x30 (0x0036E4F9 -> 0x00211E58). Destructor 0x0036E564 restores 0x00C17D00 at 0x0036E578, then Snapshot's 0x00BBB554 at 0x0036E5E0 after member teardown. These are derived and base lifetime tables; AIGroup has one Snapshot base at +0 and no separate MemoryPoolObject subobject.
// Table 0x00C17D00 has exactly four entries, followed by the "AIGroup" literal at 0x00C17D10: slot 0 is 0x0036E8EA (calls destructor 0x0036E564, conditionally calls global delete 0x0002FD60); slot 1 is the empty RET at 0x000B3FD0 (Snapshot::loadPostProcess); slot 2 is 0x0036E55E (returns 0x00C17D10, Snapshot::GetSnapshotName); slot 3 is xfer at 0x0036E3C6. Snapshot's table has its deleting destructor and three pure slots. The row named name() owns the slot-2 body; name() remains separately declared with its ledger spelling.
// Constructor stores 0x0036E4FE..0x0036E546 and getSpeed 0x0036E333 prove path +0x14, speed +8, dirty byte +0xC and ID +0x10. The ID comes from TheAI's incremented +0x1C counter. Constructor stores at 0x0036E50D..0x0036E526 and xfer 0x0036E3C6 prove two twelve-byte coordinate members at +0x18/+0x24; the second starts with 10.0f from 0x00BC2428 and two zeroes. Their storage remains opaque as field18/field24, without assigning unproved semantic names.
// Destructor 0x0036E581..0x0036E5B7 proves the +4 list sentinel and nodes with next/previous at +0/+4 and Object* at +8. getAllIDs 0x0036F710 passes +0x30 to vector<ObjectID>::erase/push_back and returns that address; the allocation extent bounds this vector to twelve bytes. The list and vector storage remain opaque, without a second container definition. Other method declarations below follow their exact reverse/functions.csv names and signatures; trailing comments give their retail RVAs. Zero Hour's GeneralsMD GameLogic/AI.h supplies the established speed, dirty, ID and path field names, but not BFME2's layout or extra members.
#pragma once
#ifndef CANONICAL_AIGROUP_H
#define CANONICAL_AIGROUP_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class AI;
class CommandButton;
class Coord2D;
struct Coord3D;
class Object;
class Path;
class Player;
class PolygonTrigger;
class Rva003427DD;
class Team;
class UpgradeTemplate;
class Waypoint;
struct Rva0036D7A6Outer;
struct Rva00372571Params;
template<class T> class StringBase;
namespace _STL {
template<class T> class allocator;
template<class T, class A> class vector;
}
enum AttitudeType;
enum CommandSourceType;
enum GUICommandType;
enum GuardMode;
enum ModelConditionFlagType;
enum ObjectID;
enum WeaponLockType;
enum WeaponSetType;
enum WeaponSlotType;

class AIGroup : public Snapshot
{
    friend class AI;
public:
    AIGroup(); // 0x0036E4C7
protected:
    virtual ~AIGroup(); // 0x0036E564
    // Snapshot slots, spelled the way the unit selected Snapshot.h's (as Team's);
    // AIGroup's rows are loadPostProcess, GetSnapshotName() const and xfer.
public:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess(); // slot 1, 0x000B3FD0
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const; // slot 2, 0x0036E55E
#endif
#else
    virtual void crc(Xfer *xfer);
#endif
protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &);
#else
    virtual void DoXfer(Xfer *);
#endif
#else
    virtual void xfer(Xfer *); // slot 3, 0x0036E3C6
#endif
public:
    const char *name() const; // 0x0036E55E
    void add(Object *); // 0x0036E5F1
    bool remove(Object *); // 0x0036CF07
    bool isMember(Object *); // 0x0036CED0
    bool containsAnyObjectsNotOwnedByPlayer(const Player *); // 0x0036CF73
    bool removeAnyObjectsNotOwnedByPlayer(const Player *); // 0x0036CFA4
    bool rva0036CFE5(const Player *); // 0x0036CFE5
    bool removeInvalidObjectsFromGroup(Rva0036D7A6Outer *); // 0x0036D7A6
    float getSpeed(); // 0x0036E333
    bool getCenter(Coord3D *); // 0x0036D035
    bool getMinMaxAndCenter(Coord2D *, Coord2D *, Coord3D *); // 0x0036D14F
    const _STL::vector<ObjectID, _STL::allocator<ObjectID> > &getAllIDs() const; // 0x0036F710
    bool isIdle() const; // 0x0036DF4D
    bool rva0036E071() const; // 0x0036E071
    bool rva0036E0B6() const; // 0x0036E0B6
    bool rva0036E0E3(); // 0x0036E0E3
    bool rva0036E357(); // 0x0036E357
    void rva0036E2E2(bool); // 0x0036E2E2
    void rva0036CE87(); // 0x0036CE87
    void setAttitude(AttitudeType); // 0x0036DD16
    void setMineClearingDetail(bool); // 0x0047A69C
    bool setWeaponLockForGroup(WeaponSlotType, WeaponLockType); // 0x0036DD45
    void releaseWeaponLockForGroup(WeaponLockType); // 0x0036DDF2
    void setWeaponSetFlag(WeaponSetType); // 0x0036DE17
    void queueUpgrade(const UpgradeTemplate *); // 0x0036DE89
    void rva0036DF14(const UpgradeTemplate *); // 0x0036DF14
    Object *getSpecialPowerSourceObject(unsigned int); // 0x0036E111
    Object *getCommandButtonSourceObject(GUICommandType); // 0x0036E158
    void cohereMoveSpeed(); // 0x0036DF92
    void cohereAttackState(); // 0x003705C2
    void groupChangeStance(int); // 0x0036E269
    void groupSetEmoticon(const StringBase<char> &, int); // 0x0036E1C3
    void groupDoCommandButton(const CommandButton *, CommandSourceType); // 0x0036DC8D
    void groupDoCommandButtonAtPosition(const CommandButton *, const Coord3D *, CommandSourceType); // 0x0036DCB8
    void groupDoCommandButtonAtObject(const CommandButton *, Object *, CommandSourceType); // 0x0036DCE7
    bool groupDoSpecialPower(unsigned int, unsigned int, int); // 0x0036D869
    bool groupDoSpecialPowerAtLocation(unsigned int, const Coord3D *, const Object *, unsigned int, int); // 0x0036DA02
    void groupDoSpecialPowerAtObject(unsigned int, Object *, unsigned int, CommandSourceType); // 0x0036E658
    void groupMoveToPosition(Rva00372571Params *, int); // 0x00372571
    void groupMoveToAndEvacuate(const Coord3D *, CommandSourceType); // 0x0036FA8C
    void groupMoveToAndEvacuateAndExit(const Coord3D *, CommandSourceType); // 0x0036FAC2
    void groupTightenToPosition(const Coord3D *, bool, CommandSourceType); // 0x0036F917
    // Inline forwarders: AITactic::teamAttackObject 0x004ED1A1 and doTeamAttackNamed 0x003C3B7D call
    // groupAttackObjectPrivate 0x0036FD64 directly with false; 0x00376CE4/0x00376CFA are their
    // out-of-line COMDAT copies (false/true forced flag). Zero Hour's AI.h has the same inline pair.
    void groupAttackObject(Object *victim, int maxShotsToFire, CommandSourceType cmdSource) // 0x00376CE4
    { groupAttackObjectPrivate(false, victim, maxShotsToFire, cmdSource); }
    void groupForceAttackObject(Object *victim, int maxShotsToFire, CommandSourceType cmdSource) // 0x00376CFA
    { groupAttackObjectPrivate(true, victim, maxShotsToFire, cmdSource); }
    void groupAttackTeam(const Team *, int, CommandSourceType); // 0x0036FF33
    void groupAttackPosition(const Coord3D *, int, CommandSourceType); // 0x0036FF74
    void groupAttackMoveToPosition(const Coord3D *, int, CommandSourceType); // 0x00372B09
    void groupAttackArea(PolygonTrigger *, CommandSourceType); // 0x00370517
    void groupIdle(CommandSourceType); // 0x0036FC23
    void groupHunt(CommandSourceType); // 0x0037008E
    void groupScatter(CommandSourceType); // 0x0036F757
    void groupOneRing(); // 0x00370680
    void groupRepair(Object *, CommandSourceType); // 0x003700C0
    void groupResumeConstruction(Object *, CommandSourceType); // 0x003700F6
    void groupGetHealed(Object *, CommandSourceType); // 0x0037012C
    void groupGetRepaired(Object *, CommandSourceType); // 0x00370162
    void groupEnter(Object *, CommandSourceType); // 0x00370198
    void groupDock(Object *, CommandSourceType); // 0x00370217
    void groupHarvest(const Coord3D *, CommandSourceType); // 0x0037024D
    void groupExit(Object *, CommandSourceType); // 0x00370283
    void groupEvacuate(CommandSourceType); // 0x003702B9
    void groupGuardPosition(const Coord3D *, GuardMode, CommandSourceType); // 0x003703CF
    void groupGuardObject(Object *, int, CommandSourceType); // 0x00370410
    void groupRotateFiringarc(const Coord3D *, CommandSourceType); // 0x003706C8
    bool computeGroundPath(const Coord3D *, CommandSourceType); // 0x0036D3A3
    bool moveInfantryToPos(const Coord3D *, CommandSourceType); // 0x00370795
    bool moveVehicleToPos(const Coord3D *, CommandSourceType); // 0x00371AE2
    void moveFormationToPos(const Coord3D *, CommandSourceType, int, bool, bool); // 0x00371166
    void createFormation(int, int); // 0x005494A0
    void groupSetPositionInFormation(const Coord3D *, const Coord3D *, int); // 0x0036D6F4
    static void rotateOffset(const Coord3D *, const Coord3D *, Coord2D *); // 0x0036CBF9
    static void computeIndividualDestination(Coord3D *, const Coord3D *, Object *, const Coord3D *, const float *, int); // 0x0036CC94
    void rva0036D805(int); // 0x0036D805
    void rva0036D837(int); // 0x0036D837
    void rva0036DBBA(int, int, unsigned int); // 0x0036DBBA
    void rva0036DC1D(ModelConditionFlagType, unsigned int); // 0x0036DC1D
    void rva0036DC6F(int, int); // 0x0036DC6F
    void rva0036DDCD(int); // 0x0036DDCD
    void rva0036F9FE(const Waypoint *, CommandSourceType, int); // 0x0036F9FE
    void rva0036FA56(const Waypoint *, CommandSourceType); // 0x0036FA56
    void rva0036FB57(const Waypoint *, CommandSourceType, int); // 0x0036FB57
    void rva0036FBC5(const Waypoint *, CommandSourceType); // 0x0036FBC5
    void rva00370399(const Rva003427DD *, CommandSourceType); // 0x00370399
    void rva00370451(const Team *, int, CommandSourceType); // 0x00370451
    void rva00370492(const PolygonTrigger *, int, CommandSourceType); // 0x00370492
    void rva003704D3(const PolygonTrigger *, int, CommandSourceType, const Coord3D *); // 0x003704D3
    void rva00370554(Object *, CommandSourceType); // 0x00370554
    void rva00372BB9(const void *, int); // 0x00372BB9
    void rva00372C05(); // 0x00372C05
private:
    void recompute(); // 0x0036D2C5
    void groupAttackObjectPrivate(bool, Object *, int, CommandSourceType); // 0x0036FD64
public:
    unsigned char m_unrecovered04[4]; // +0x04, list<Object *> storage
    float m_speed; // +0x08
    bool m_dirty; // +0x0C
    unsigned int m_id; // +0x10
    Path *m_groundPath; // +0x14
    unsigned char field18[12]; // +0x18
    unsigned char field24[12]; // +0x24
    unsigned char m_unrecovered30[12]; // +0x30, vector<ObjectID> storage
};

typedef char AIGroup_extent3C[(sizeof(AIGroup) == 0x3C) ? 1 : -1];
#endif
