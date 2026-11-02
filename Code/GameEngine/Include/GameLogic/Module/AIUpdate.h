// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x0026E9BD calls UpdateModule (0x00253390), then installs
// 0x00BFA480/+0, 0x00BFA3C0/+0x0C, 0x00C53A98/+0x10,
// 0x00C47B88/+0x20 and 0x00C52F88/+0x24 at 0x0026EA00..0x0026EA1B.
// The earlier +0x20/+0x24 pure tables 0x00C1C780/0x00C40818 are base
// construction stores (0x0026E9E5/0x0026E9EE), not competing class tables.
// Protected destructor 0x0026E836 restores those five class tables at
// 0x0026E849..0x0026E864. Its deleting wrapper 0x0026ED95 calls it.
// UpdateModule's destructor 0x0024A797 restores BehaviorModule's primary
// 0x00BEEA7C and interface 0x00BEE9C0 during base destruction.
// Factory 0x0024BDB7 pushes 0x3E4 at 0x0024BDC2 and calls the constructor
// at 0x0024BDE1. The constructor writes its final byte at +0x3E0.
// Primary table 0x00BFA480 has 154 slots, followed by its name literal.
// Slots 0..12 extend UpdateModule's existing primary slots; slot 12 is
// getUpdatePhase (Zero Hour declaration), returning zero at 0x000D43D0.
// Interface tables have 47 slots at +0x0C, three at +0x10, one at +0x20
// and six at +0x24. Their first slots call aiDoCommand (0x002673F6) and onCollide
// (0x0026DF0D), whose bodies subtract 0x20/0x24 to recover the whole object.
// AICommandInterface's name and aiDoCommand slot are also declared in ZH AI.h;
// the other interface's class name is unknown, so AIUpdateInterface24 is neutral.
// Its pure table 0x00C40818 has six entries. In 0x00C52F88, slot 1 is
// 0x005CB9FF (false, ret 4), and slots 2..5 are 0x0047A699 (false, ret).
// The next stored table at 0x00C52FA0 bounds all six slots.
// Constructor stores establish scalar widths from +0x28..+0x70,
// +0x134..+0x1A4, +0x1C8, +0x1F0..+0x220, +0x234..+0x240 and +0x3DC;
// its +0x74 vector construction is 16 records of 12 bytes. Its byte stores
// establish +0x3B0..+0x3CF and +0x3E0. Member calls place opaque storage at
// +0x1CC (0x001E7087), +0x224 (0x0026E7C8), +0x244/+0x290 (0x00042526),
// +0x2DC (0x0024CA24), +0x2EC (0x0026AFDA) and +0x3D0 (0x00262436).
// destroyPath 0x00262A8A reads +0x140; requestSafePath 0x00263EA2 proves
// destination +0x148, timestamp +0x160, repulsors +0x18C/+0x190 and flags
// +0x3B1..+0x3B5. Private guard commands 0x00264BC2/0x00264D0E and
// 0x0026C1CE prove +0x48..+0x70. ZH AIUpdate.h supplies their field names.
// Named method declarations use the ledger's decorated signatures; primary
// slot comments give each retail target. Folded bodies with no class-specific
// name use neutral vslotNNN declarations; measured trivial defaults are inline.
// setCurrentVictim 0x00268D1F and getCurrentVictim 0x00268D71 place the
// victim ID at +0x40. Turret queries 0x002626B7 and destructor 0x0026E836
// bound m_turretAI to one pointer at +0x20C. Ground-movement predicate
// 0x0026731C reads the locomotor-set surface mask at +0x1DC.
// TurretAI::removeSelfAsTargeter calls primary slot 129 at 0x004D8290;
// AIAttackState::onEnter 0x0034B502 calls slot 144. Zero Hour AIUpdate.h
// names these addTargeter and notifyVictimIsDead, and supplies the inline
// getPath/isWaitingForPath/getCrateID accessors. AIGuardIdleState::update
// 0x00543E5D reads the crate ID at +0x238. The name getDozerAIInterface
// comes from Zero Hour; ControlBar::getCommandAvailability 0x0053BD66
// dispatches it through primary slot 93.
// AIAttackState::onEnter calls the protected Object overload of
// playAttackVoiceResponse at 0x0034B870, requiring access from that state.

#pragma once
#ifndef __BFME2_AIUPDATE_H_
#define __BFME2_AIUPDATE_H_

#include "UpdateModule.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class AIStateMachine;
class AttackPriorityInfo;
class BfmeFixedStorage0004543D;
class CommandButton;
class DamageInfo;
class DozerAIInterface;
class Locomotor;
class Path;
class PathfindServicesInterface;
class Player;
class PolygonTrigger;
class RadarObject;
class Rva00263404Source;
class Rva003427DD;
class Rva0035149F;
class Team;
class ThingTemplate;
class TurretAI;
class Waypoint;
namespace _STL {
template <class T> class allocator;
template <class T, class Allocator> class vector;
}
enum AttitudeType;
enum CommandSourceType;
enum GuardMode;
enum MoodMatrixAction;
enum ObjectID;
enum PathfindLayerEnum;
enum WeaponSlotType;
enum WhichTurretType;
struct AICommandParms;
struct Rva00264D81Arg;
struct Coord2D;
class AsciiString;

class AICommandInterface
{
public:
    virtual void aiDoCommand(const AICommandParms *) = 0;
    void aiForceAttackObject(Object *,int,CommandSourceType);
    void aiAttackPosition(Coord3D const *,int,CommandSourceType);
    void aiIdle(CommandSourceType);
    void aiBfmeObjectCommand3D(Object *,CommandSourceType);
    void aiFacePosition(Coord3D const *,int);
    void aiFaceObject(Object *,CommandSourceType);
    void aiWanderInPlace(CommandSourceType);
    void rva003C7653(Object *,CommandSourceType);
    void aiFollowWaypointPath(Waypoint const *,CommandSourceType);
    void aiAttackArea(PolygonTrigger const *,CommandSourceType);
    void aiAttackTeam(Team const *,int,CommandSourceType);
    void rva0036EBB8(Object *,CommandSourceType);
    void rva0036EC1D(Object *,CommandSourceType);
    void aiFollowWaypointPathExact(Waypoint const *,CommandSourceType);
    void aiFollowWaypointPathAsTeam(Waypoint const *,CommandSourceType);
    void aiBfmeCommand33(Waypoint const *,CommandSourceType);
    void rva0036EFF5(Object *,CommandSourceType);
    void aiEvacuate(bool,CommandSourceType);
    void aiHunt(CommandSourceType);
    void aiExit(Object *,CommandSourceType);
    void aiDock(Object *,CommandSourceType);
    void rva0026C486(Object *,CommandSourceType);
    void aiMoveAwayFromUnit(Object *,Coord3D const *,CommandSourceType);
    void rva0026C347(Object *,CommandSourceType);
    void rva0026C2D9(Object *,int,CommandSourceType);
    void aiGuardPosition(Coord3D const *,GuardMode,CommandSourceType);
    void rva0045003E(int,CommandSourceType);
    void aiTightenToPosition(Coord3D const *,CommandSourceType);
    void aiMoveToAndEvacuate(Coord3D const *,CommandSourceType);
    void aiMoveToAndEvacuateAndExit(Coord3D const *,CommandSourceType);
    void aiGoProne(Rva003427DD const *,CommandSourceType);
    void rva0036F19B(Object *,CommandSourceType);
    void aiResumeConstruction(Object *,CommandSourceType);
    void aiGetHealed(Object *,CommandSourceType);
    void aiGetRepaired(Object *,CommandSourceType);
    void rva0036F6A7(float,CommandSourceType);
    void aiGuardObject(Object *,int,CommandSourceType);
    void rva0036F54D(Team const *,int,CommandSourceType);
    void aiGuardArea(PolygonTrigger const *,int,CommandSourceType);
    void rva003C77EE(Waypoint const *,CommandSourceType);
    void rva003C76B8(int,CommandSourceType);
    void rva003C78AF(Waypoint const *,CommandSourceType);
    void aiMoveToObject(Object *,CommandSourceType);
    void rva0037379B(Object *,CommandSourceType);
    void rva0044FFD9(Object *,CommandSourceType);
    void rva0036EE16(Rva0035149F const *,Object *,CommandSourceType);
    void rva0036EE89(Rva0035149F const *,Object *,float,CommandSourceType);
    void rva0036EF09(Rva0035149F const *,Object *,float,CommandSourceType);
    void rva0047971C(Rva0035149F const &,Object *,CommandSourceType);
    void rva004C6D35(Object *,CommandSourceType);
    void aiFollowPathAppend(Coord3D const *,CommandSourceType);
    void aiMoveToPositionAndFaceDirection(Coord3D const *,CommandSourceType,float);
    void aiAttackMoveToPositionAndFaceDirection(Coord3D const *,int,CommandSourceType,float);
    void aiMoveToPositionSA(Coord3D const *,int);
    void aiHarvest(Coord3D const *,CommandSourceType);
    void aiGuardAreaFromPosition(PolygonTrigger const *,int,CommandSourceType,Coord3D const *);
    void aiAttackMoveToPositionAmphibious(Coord3D const *,CommandSourceType);
    void aiMoveToPositionAmphibious(Coord3D const *,CommandSourceType);
    void aiAttackLevelPosition(Coord3D const *,CommandSourceType);
    void aiMoveToPosition(Coord3D const *,CommandSourceType);
    void aiMoveToPositionEvenIfSleeping(Coord3D const *,CommandSourceType);
    void aiMoveToAndDelete(Coord3D const *,CommandSourceType);
    void aiMoveToAndDie(Coord3D const *,CommandSourceType);
};

class AIUpdateInterface24
{
public:
    virtual void onCollide(Object *, const Coord3D *, const Coord3D *) = 0;
    virtual bool vslot24_01(int) = 0;
    virtual bool vslot24_02() = 0;
    virtual bool vslot24_03() = 0;
    virtual bool vslot24_04() = 0;
    virtual bool vslot24_05() = 0;
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
    friend class AIAttackState;
public:
    AIUpdateInterface(Thing *, const ModuleData *);
    virtual NameKeyType getModuleNameKey() const;
    virtual void onObjectCreated();
    virtual void xfer(Xfer *);
    virtual AIUpdateInterface *getAIUpdateInterface();
    virtual UpdateSleepTime update();
    virtual DisabledMaskType getDisabledTypesToProcess() const;
    virtual void aiDoCommand(const AICommandParms *);
    virtual void onCollide(Object *, const Coord3D *, const Coord3D *);
    virtual bool vslot24_01(int) { return false; }
    virtual bool vslot24_02() { return false; }
    virtual bool vslot24_03() { return false; }
    virtual bool vslot24_04() { return false; }
    virtual bool vslot24_05() { return false; }

protected:
    virtual void privateMoveToPosition(Coord3D const *,float,CommandSourceType); // 13: RVA 0x0026B487
    virtual void privateAttackMoveToPositionAndOrientation(Coord3D const *,float,int,CommandSourceType); // 14: RVA 0x0026C04E
    virtual void bfmePrivateCommand01(Object *,CommandSourceType); // 15: RVA 0x0026B637
    virtual void privateMoveToPositionSA(Coord3D const *,CommandSourceType); // 16: RVA 0x00267CFA
    virtual void privateMoveToPositionAmphibious(Coord3D const *,int,CommandSourceType); // 17: RVA 0x0026B567
    virtual void bfmePrivateCommand48(Object *,CommandSourceType); // 18: RVA 0x00264558
    virtual void privateMoveToAndEvacuate(Coord3D const *,CommandSourceType); // 19: RVA 0x0026B6B2
    virtual void privateMoveToAndEvacuateAndExit(Coord3D const *,CommandSourceType); // 20: RVA 0x0026B720
    virtual void bfmePrivateCommand38(Coord3D const *,CommandSourceType); // 21: RVA 0x0026B78E
    virtual void bfmePrivateCommand41(Coord3D const *,CommandSourceType); // 22: RVA 0x0026B7FC
    virtual void bfmePrivateCommand42(Object *,CommandSourceType); // 23: RVA 0x0026D56C
    virtual void privateIdle(CommandSourceType); // 24: RVA 0x0026D5FB
    virtual void privateTightenToPosition(Coord3D const *,CommandSourceType); // 25: RVA 0x00267DAD
    virtual void privateFollowWaypointPath(Waypoint const *,CommandSourceType); // 26: RVA 0x0026B8E5
    virtual void privateFollowWaypointPathAsTeam(Waypoint const *,CommandSourceType); // 27: RVA 0x0026B9E2
    virtual void privateFollowWaypointPathExact(Waypoint const *,CommandSourceType); // 28: RVA 0x0026B987
    virtual void privateFollowWaypointPathAsTeamExact(Waypoint const *,CommandSourceType); // 29: RVA 0x0026BA33
    virtual void privateFollowPath(Rva0035149F const *,Object *,CommandSourceType,bool); // 30: RVA 0x0026BA84
    virtual void bfmePrivateCommand24(Rva0035149F const *,Object *,float,CommandSourceType); // 31: RVA 0x0026BB5A
    virtual void bfmePrivateCommand25(Rva0035149F const *,Object *,float,CommandSourceType); // 32: RVA 0x0026BC16
    virtual void privateFollowPathAppend(Coord3D const *,CommandSourceType); // 33: RVA 0x0026E074
    virtual void privateAttackObject(Object *,int,CommandSourceType); // 34: RVA 0x0026BCD2
    virtual void bfmePrivateCommand39(Object *,CommandSourceType); // 35: RVA 0x0026BE86
public:
    virtual void vslot036(void *, int); // 36: RVA 0x0050B238
    virtual void vslot037(void *, int); // 37: RVA 0x0050B238
protected:
    virtual void privateForceAttackObject(Object *,int,CommandSourceType); // 38: RVA 0x0026BEE6
    virtual void privateAttackTeam(Team const *,int,CommandSourceType); // 39: RVA 0x0026BFD9
    virtual void privateAttackPosition(Coord3D const *,int,CommandSourceType); // 40: RVA 0x0026DB1A
    virtual void bfmePrivateCommand49(Object *,CommandSourceType); // 41: RVA 0x0026C0D6
    virtual void privateAttackFollowWaypointPath(Waypoint const *,int,bool,CommandSourceType); // 42: RVA 0x0026C150
    virtual void privateHunt(CommandSourceType); // 43: RVA 0x002646E9
public:
    virtual void vslot044(Object *, CommandSourceType); // 44: RVA 0x0050B238
    virtual void vslot045(Object *, CommandSourceType); // 45: RVA 0x0050B238
protected:
    virtual void privateGetHealed(Object *,CommandSourceType); // 46: RVA 0x0026DD89
    virtual void privateGetRepaired(Object *,CommandSourceType); // 47: RVA 0x0026DDBB
    virtual void privateEnter(Object *,CommandSourceType); // 48: RVA 0x00264775
    virtual void bfmePrivateCommand3D(Object *,CommandSourceType); // 49: RVA 0x002647EF
    virtual void privateMoveToObject(Object *,CommandSourceType); // 50: RVA 0x0026472F
    virtual void privateDock(Object *,CommandSourceType); // 51: RVA 0x0026481B
    virtual void privateHarvest(Coord3D const *,CommandSourceType); // 52: RVA 0x00264853
    virtual void privateExitInstantly(Object *,CommandSourceType); // 53: RVA 0x0026488B
    virtual void bfmePrivateCommand4B(Object *,Coord3D const *,CommandSourceType); // 54: RVA 0x002648F1
    virtual void bfmePrivateCommand4D(Object *,Rva0035149F const *,CommandSourceType); // 55: RVA 0x0026492A
    virtual void bfmePrivateCommand3E(Object *,CommandSourceType); // 56: RVA 0x00264963
    virtual void bfmePrivateCommand4A(Object *,Coord3D const *,CommandSourceType); // 57: RVA 0x002649A3
    virtual void bfmePrivateCommand4C(Object *,Rva0035149F const *,CommandSourceType); // 58: RVA 0x002649DC
    virtual void bfmePrivateCommand54(Object *,Coord3D const *,CommandSourceType); // 59: RVA 0x00264A15
public:
    virtual void rva0026DDED(int,CommandSourceType); // 60: RVA 0x0026DDED
protected:
    virtual void privateGoProne(DamageInfo const *,CommandSourceType); // 61: RVA 0x00262F5E
    virtual void privateGuardTunnelNetwork(int,CommandSourceType); // 62: RVA 0x00264CBB
    virtual void privateGuardPosition(Coord3D const *,GuardMode,CommandSourceType); // 63: RVA 0x00264BC2
    virtual void privateGuardObject(Object *,GuardMode,CommandSourceType); // 64: RVA 0x00264D0E
    virtual void bfmePrivateCommand20(Rva00264D81Arg const *,GuardMode,CommandSourceType); // 65: RVA 0x00264D81
    virtual void privateGuardRetaliate(Object *,Coord3D const *,int,CommandSourceType); // 66: RVA 0x00267DF1
    virtual void privateGuardAreaFromPosition(PolygonTrigger const *,GuardMode,CommandSourceType,Coord3D const *); // 67: RVA 0x00264DF8
    virtual void privateAttackArea(PolygonTrigger const *,CommandSourceType); // 68: RVA 0x0026C1CE
    virtual void privateFaceObject(Object *,CommandSourceType); // 69: RVA 0x002645B9
    virtual void privateFacePosition(Coord3D const *,CommandSourceType); // 70: RVA 0x00267D65
public:
    virtual void rva00262EFF(void *,void *,void *); // 71: RVA 0x00262EFF
protected:
    virtual void privateCommandButton(CommandButton const *,CommandSourceType); // 72: RVA 0x0026DE77
    virtual void privateCommandButtonPosition(CommandButton const *,Coord3D const *,CommandSourceType); // 73: RVA 0x00267E8E
public:
    virtual void vslot074(void *, void *, void *); // 74: RVA 0x000D1407
    virtual void bfmeGoCSG(void *,void *); // 75: RVA 0x00264A4E
    virtual void bfmeGoCSA(void *); // 76: RVA 0x00264A86
protected:
    virtual void bfmePrivateCommand53(CommandSourceType); // 77: RVA 0x00264AB2
public:
    virtual void bfmeGoCSH(void *,void *); // 78: RVA 0x00264ADE
    virtual void bfmeGoCSD(void *,void *); // 79: RVA 0x00264B16
protected:
    virtual void bfmePrivateCommand31(int,CommandSourceType); // 80: RVA 0x00264B86
    virtual void privateMoveAwayFromUnit(Object *,Coord3D const *,CommandSourceType); // 81: RVA 0x0026D765
    virtual void bfmePrivateCommand3C(Object *,CommandSourceType); // 82: RVA 0x0026B86A
public:
    virtual void bfmeGoCSE(void *,void *); // 83: RVA 0x00264B4E
protected:
    virtual void rva002630FD(int); // 84: RVA 0x002630FD
public:
    virtual void bfmeGoCSF(void *,void *); // 85: RVA 0x00263133
protected:
    virtual void rva0026316B(void *,int); // 86: RVA 0x0026316B
    virtual void rva002631A6(float,int); // 87: RVA 0x002631A6
public:
    virtual void vslot088(); // 88: RVA 0x000B3FD0
    virtual void vslot089(); // 89: RVA 0x000B3FD0
    virtual bool vslot090() const { return false; } // 90: RVA 0x0047A699
    virtual bool isBusy()const; // 91: RVA 0x00262B39
    virtual void *vslot092(); // 92: RVA 0x000D43D0
    virtual DozerAIInterface *getDozerAIInterface(); // 93: RVA 0x000D43D0
    virtual void *vslot094() const; // 94: RVA 0x000D43D0
    virtual void *vslot095() const; // 95: RVA 0x000D43D0
    virtual void *vslot096(); // 96: RVA 0x000D43D0
    virtual void *vslot097() const; // 97: RVA 0x000D43D0
    virtual void *vslot098(); // 98: RVA 0x000D43D0
    virtual void *vslot099() const; // 99: RVA 0x000D43D0
    virtual void *vslot100(); // 100: RVA 0x000D43D0
    virtual void *vslot101() const; // 101: RVA 0x000D43D0
    virtual void *vslot102(); // 102: RVA 0x000D43D0
    virtual void joinTeam(); // 103: RVA 0x0026D478
    virtual int rva0026E988(); // 104: RVA 0x0026E988
    virtual int rva0026E999(); // 105: RVA 0x0026E999
    virtual int vslot106(const Object *) const; // 106: RVA 0x005DAA6C
    virtual bool vslot107() const; // 107: RVA 0x0050B5C6
    virtual bool vslot108() const; // 108: RVA 0x0050B5C6
    virtual ObjectID vslot109() const; // 109: RVA 0x000D43D0
    virtual bool isIdle() const; // 110: RVA 0x002645FF
    virtual bool rva00262D8F()const; // 111: RVA 0x00262D8F
    virtual bool isClearingMines()const; // 112: RVA 0x00264656
    virtual bool rva00262DA3()const; // 113: RVA 0x00262DA3
    virtual bool rva00262DAB()const; // 114: RVA 0x00262DAB
    virtual bool rva00262DBF()const; // 115: RVA 0x00262DBF
    virtual bool rva00262D7B()const; // 116: RVA 0x00262D7B
    virtual void doQuickExit(_STL::vector<Coord3D,_STL::allocator<Coord3D> > const *); // 117: RVA 0x00262F19
    virtual const Coord3D *vslot118() const; // 118: RVA 0x00042287
    virtual ObjectID vslot119() const; // 119: RVA 0x002004A1
    virtual const PolygonTrigger *vslot120() const; // 120: RVA 0x00367508
    virtual int vslot121() const; // 121: RVA 0x0036750C
    virtual void vslot122(int); // 122: RVA 0x0033F15D
    virtual int vslot123() const; // 123: RVA 0x0009AAA4
    virtual void clearGuardTargetType(); // 124: RVA 0x0026E9AA
    virtual int vslot125() const; // 125: RVA 0x002A98A7
    virtual Object * construct(ThingTemplate const *,Coord3D const *,float,Player *,bool,int); // 126: RVA 0x0026E9B8
    virtual Object * getEnterTarget(); // 127: RVA 0x00264EF2
    virtual bool vslot128(Coord3D *) const; // 128: RVA 0x005CB9FF
    virtual void addTargeter(int, bool); // 129: RVA 0x0050B238
    virtual bool vslot130() const; // 130: RVA 0x0047A699
    virtual void setLocomotorGoalPositionOnPath(); // 131: RVA 0x00262C13
    virtual void setLocomotorGoalPositionExplicit(Coord3D const &); // 132: RVA 0x00262C35
    virtual void setLocomotorGoalPositionExplicitSmart(Coord3D const &); // 133: RVA 0x00262C53
    virtual void appendPositionToLocomotorPath(Coord3D const &,int); // 134: RVA 0x00267266
    virtual void setLocomotorGoalOrientation(float); // 135: RVA 0x00262C9B
    virtual void setLocomotorGoalNone(); // 136: RVA 0x00262CB6
    virtual bool isDoingGroundMovement()const; // 137: RVA 0x0026731C
    virtual bool rva00262BA9(); // 138: RVA 0x00262BA9
    virtual void micropathToPosition(Coord3D const *); // 139: RVA 0x0026412B
    virtual void doPathfind(PathfindServicesInterface *); // 140: RVA 0x00269902
    virtual void rva00263404(Rva00263404Source *); // 141: RVA 0x00263404
    virtual bool chooseLocomotorSet(int); // 142: RVA 0x00268B20
    virtual CommandSourceType vslot143() const; // 143: RVA 0x005C4AFD
    virtual void notifyVictimIsDead(); // 144: RVA 0x000B3FD0
    virtual void rva00267E46(); // 145: RVA 0x00267E46
    virtual bool vslot146() const; // 146: RVA 0x0050B5C6
    virtual void vslot147(); // 147: RVA 0x000B3FD0
    virtual bool isAllowedToRespondToAiCommands(AICommandParms const *)const; // 148: RVA 0x0026734C
protected:
    virtual UpdateSleepTime doLocomotor(); // 149: RVA 0x0026A3A0
    virtual AIStateMachine * makeStateMachine(); // 150: RVA 0x00262513
public:
    virtual bool getTreatAsAircraftForLocoDistToGoal()const; // 151: RVA 0x00262CF2
    virtual bool rva002697FC(); // 152: RVA 0x002697FC
    virtual void vslot153(); // 153: RVA 0x002628B1

protected:
    virtual ~AIUpdateInterface();
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *);
#endif
    virtual SleepyUpdatePhase getUpdatePhase() const;

public:
protected:
    void setLastCommandSource(CommandSourceType);
public:
    bool isTurretEnabled(WhichTurretType)const;
    Object * getCurrentVictim()const;
    WhichTurretType getWhichTurretForWeaponSlot(WeaponSlotType,float *,float *)const;
    char const * name()const;
    void recenterTurret(WhichTurretType);
    void setTurretEnabled(WhichTurretType,bool);
    bool isTurretInNaturalPosition(WhichTurretType)const;
    WhichTurretType getWhichTurretForCurWeapon()const;
    bool isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType,Object const *)const;
    bool getTurretRotAndPitch(WhichTurretType,float *,float *)const;
    float getTurretTurnRate(WhichTurretType)const;
    Object * getTurretTargetObject(WhichTurretType);
    void setTurretTargetPosition(WhichTurretType,Coord3D const *);
    void setTurretTargetObject(WhichTurretType,Object *,bool);
    void destroyPath();
    static Module * friend_newModuleInstance(Thing *,ModuleData const *);
protected:
    void wakeUpNow();
public:
    void setQueueForPathTime(int);
    void rva00262804(unsigned char);
    void rva0026295E();
    void rva0026293E();
    void rva00262ACE();
    void rva00262AEA();
    void rva0026304D(int);
    void rva00263025();
    RadarObject * rva002630F5();
    int rva002632B3()const;
    int rva002632C7()const;
    void friend_setPath(Path *);
    bool rva0033F8D4()const;
    void setCurrentVictim(Object const *);
    void rva0026DE3B(int);
    int rva00260DED()const;
    int getCurrentStateID()const;
    void rva00262D2D();
    void rva00262FFF();
    void friend_setGoalObject(Object *);
    void rva002633B6();
    void rva0026331C();
    void setGoalPositionClipped(Coord3D const *,float,int);
    void rva00265667(Coord3D const *,int);
    void ignoreObstacle(Object const *);
    bool rva00262BEC();
    bool isAircraftThatAdjustsDestination()const;
    void rva00262D40(int);
    bool rva00262DD3(Object const *)const;
    void rva002632E1();
    Locomotor * getCurLocomotor();
    int rva00265143();
    void transferAttack(ObjectID,ObjectID);
    void rva00263298();
    void markAsDead();
    void rva00262989(unsigned int);
    void setCompletedWaypoint(Waypoint const *);
    unsigned int getMoodMatrixActionAdjustment(MoodMatrixAction)const;
    int rva0026417F(bool);
    void rva00489DE3();
    void rva00489E2E();
protected:
    void playVoiceEnterStateAttackMove(Coord3D const *);
public:
    void BeginDefectedStateMachine();
    void BeginTemporaryStateMachine();
    void setPathExtraDistance(float);
    bool isMoving()const;
    unsigned char rva002641BA();
    bool queueWaypoint(Coord3D const *);
    bool canComputeQuickPath();
    Object * checkForCrateToPickup();
    void chooseGoodLocomotorFromCurrentSet();
    bool chooseLocomotorSetExplicit(int);
    bool computeAttackPath(PathfindServicesInterface *,Object const *,Coord3D const *);
    bool computePath(PathfindServicesInterface *,Coord3D *);
    bool computeQuickPath(Coord3D const *);
    bool findNearestLabeledContactPointOnTarget(Object *,Coord3D *,Coord3D const *,bool);
    Coord3D const * friend_getGoalPathPosition(int)const;
    AttitudeType getAttitude()const;
    unsigned int getMoodMatrixValue()const;
    int handleEngagedFlag();
    bool isPathAvailable(Coord3D const *)const;
    bool isQuickPathAvailable(Coord3D const *)const;
    void moveThroughPortalWithMicropath(Coord3D const *,Coord3D const *,int,PathfindLayerEnum,Coord3D const *,Coord3D const *);
protected:
    void playAttackVoiceResponse(Object *);
    void playAttackVoiceResponse(Coord3D const *);
    void playMoveVoiceResponse(Coord3D const *);
public:
    void processSpies(int,void *,void *);
    void requestApproachPath(Coord3D *);
    void requestAttackPath(ObjectID,Coord3D const *);
    bool requestMeleeApproachPath(Coord3D const *,bool);
    void requestPath(Coord3D *,bool);
    void requestSafePath(ObjectID);
    void rva002657CE();
    void rva0026D3FB(Object *);
    void setFinalPosition(Coord3D const *);
    void setIgnoreCollisionTime(int);
    void setPathFromWaypoint(Waypoint const *,Coord2D const *);
    float getLocomotorDistanceToGoal();
    void rva0026717B();
    bool findMeACrashSite(float,Coord3D const *,Coord3D *,BfmeFixedStorage0004543D);
    Object * getNextMoodTarget(bool,bool);
    bool rva0026CF11(Object *);
    int rva00262552(Coord3D const *);
    Coord3D rva00262E24();
    UpdateSleepTime rva0026A05D();
    void NotifyPathHasInvalidPortals();
    UpdateSleepTime quickHordeUpdate();
    Path *getPath() { return m_path; }
    const Path *getPath() const { return m_path; }
    bool isWaitingForPath() const { return m_field3B1; }
    ObjectID getCrateID() const { return m_crateCreated; }
    unsigned int m_priorWaypointID;
    unsigned int m_currentWaypointID;
    AIStateMachine *m_stateMachine;
    unsigned int m_nextEnemyScanTime;
    unsigned int m_field038;
    unsigned int m_field03C;
    ObjectID m_currentVictimID;
    float m_desiredSpeed;
    CommandSourceType m_lastCommandSource;
    GuardMode m_guardMode;
    int m_guardTargetType[2];
    Coord3D m_locationToGuard;
    ObjectID m_objectToGuard;
    unsigned int m_field068;
    const PolygonTrigger *m_areaToGuard;
    const AttackPriorityInfo *m_attackInfo;
    Coord3D m_waypointQueue[16];
    int m_waypointCount;
    int m_waypointIndex;
    const Waypoint *m_completedWaypoint;
    Path *m_path;
    ObjectID m_requestedVictimID;
    Coord3D m_requestedDestination;
    Coord3D m_requestedDestination2;
    unsigned int m_pathTimestamp;
    ObjectID m_ignoreObstacleID;
    float m_pathExtraDistance;
    int m_blockedFrames;
    float m_field170;
    float m_bumpSpeedLimit;
    unsigned int m_ignoreCollisionsUntil;
    unsigned int m_field17C;
    Coord3D m_field180;
    ObjectID m_repulsorID;
    ObjectID m_prevRepulsorID;
    unsigned int m_field194;
    ObjectID m_moveOutOfWay1;
    ObjectID m_moveOutOfWay2;
    float m_field1A0;
    unsigned int m_field1A4;
    unsigned char m_storage1A8[0x20];
    unsigned int m_field1C8;
    unsigned char m_storage1CC[0x10];
    int m_field1DC;
    unsigned char m_storage1E0[0x10];
    Locomotor *m_curLocomotor;
    int m_curLocomotorSet;
    float m_field1F8;
    unsigned int m_field1FC;
    Coord3D m_field200;
    TurretAI *m_turretAI[1];
    unsigned int m_field210;
    unsigned char m_storage214[4];
    unsigned int m_field218;
    unsigned int m_field21C;
    void *m_field220;
    unsigned char m_storage224[0x10];
    unsigned int m_field234;
    ObjectID m_crateCreated;
    unsigned int m_field23C;
    unsigned int m_field240;
    unsigned char m_storage244[0x4C];
    unsigned char m_storage290[0x4C];
    unsigned char m_storage2DC[0x10];
    unsigned char m_storage2EC[0xC4];
    bool m_field3B0;
    bool m_field3B1;
    bool m_field3B2;
    bool m_field3B3;
    bool m_field3B4;
    bool m_field3B5;
    bool m_field3B6;
    bool m_field3B7;
    bool m_field3B8;
    bool m_field3B9;
    bool m_field3BA;
    bool m_field3BB;
    bool m_field3BC;
    bool m_field3BD;
    bool m_field3BE;
    bool m_field3BF;
    bool m_field3C0;
    bool m_field3C1;
    bool m_field3C2;
    bool m_field3C3;
    bool m_field3C4;
    bool m_field3C5;
    bool m_field3C6;
    bool m_field3C7;
    bool m_field3C8;
    bool m_field3C9;
    bool m_field3CA;
    bool m_field3CB;
    bool m_field3CC;
    bool m_field3CD;
    bool m_field3CE;
    bool m_field3CF;
    unsigned char m_storage3D0[0xC];
    unsigned int m_field3DC;
    bool m_field3E0;
};

#endif
