/* Target facts (addresses are RVAs unless marked VA):
Pathfinder's constructor 0x002F6E22 stores VA 0x00C05408 at +0 (0x002F6E58) and VA 0x00C053F8 at +4 (0x002F6E5E). The destructor 0x002F213F restores the same pair at 0x002F2150/0x002F2156; its last +4 store at 0x002F21DA is VA 0x00BBB554, Snapshot's base table during teardown, also stored before construction at 0x002F6E3A. These are different subobjects and lifetime phases, not competing Pathfinder tables.
The primary table at RVA 0x00805408 has seven entries: 0x002FD344, 0x002FA3F1, 0x002FAD13, 0x002FC9B1, 0x002FB558, 0x002FB997, 0x002F64DD. The next word at 0x00805424 is the text "Pathfinder". The first six targets currently have nonvirtual ledger spellings; neutral interface slots preserve their positions without inventing virtual symbol owners. Slot 6 has the rowed virtual FindCollisionFreeQuickPath signature. PathfindServicesInterface is the Zero Hour base identity; its seven-slot BFME2 shape comes from these target words.
Snapshot is the four-byte secondary base at +4. Its table at RVA 0x008053F8 contains 0x002F21F1 (subtract four then delete), 0x000B3FD0 (empty postprocess), 0x002F21EB (returns "Pathfinder"), 0x002F21F9 (xfer). Snapshot's own RVA 0x007BB554 table has a deleting destructor and three pure slots. Snapshot's registered header supplies its declaration; inherited slot spellings follow that header.
AI's constructor 0x002FEA85 pushes 0x1D200 at 0x002FEAF2, calls the allocator at 0x002FEAFE, then calls Pathfinder's constructor at 0x002FEB11: sizeof(Pathfinder) is 0x1D200.
getCell at 0x002E6D62 reads the four extent coordinates at +0x14/+0x18/+0x1C/+0x20 and the map pointer at +0x10. Its layer address at 0x002E6D96 is this+0x60+layer*0x40; the ground cell stride at 0x002E6DA8 is 0x10. The extent and map names are corroborated by Zero Hour AIPathfind.h. Constructor stores prove four-byte fields at +0x0C/+0x10/+0x34/+0x58/+0x5C. SetDebugPathPosition at 0x002E74B5 copies twelve bytes to +0x4C. rva003E3BFB at 0x003E3BFB stores its ObjectID argument at +0x48, and computeAttackPath 0x00266AA2 and doPathfind call it where Zero Hour calls setIgnoreObstacleID, whose field is m_ignoreObstacleID. SetDebugPath at 0x002EDEAB deletes the Path at +0x58 and stores a new Path there. IsPointOnRamp at 0x002E757D walks a Bridge list from +0x5C through Bridge::isPointOnBridge 0x0027EEAD. rva002EE49B at 0x002EE49B returns early on a zero byte at +0x08, as Zero Hour's methods do on !m_isMapReady, and IsValidObjectMovement at 0x002EE64A saves, replaces and restores the +0x48 ID as Zero Hour does with m_ignoreObstacleID. Other storage is opaque.
Constructor/destructor array calls at 0x002F6E74/0x002F21D2 prove sixteen 0x40-byte layers at +0x60; calls at 0x002F6E83/0x002F21BC place the zone manager at +0x460; calls at 0x002F6EA1/0x002F21AD prove 64 four-byte strings at +0x1BFBC. Calls at 0x002F6EB0/0x002F2194 place the tree at +0x1C1C0, and the destructor frees allocations read at +0x1C1CC/+0x1D1F0. The registered PathfindZoneManager header is 0x1BA54 bytes, so it ends at +0x1BEB4, below the height table that retail 0x0052E7B3/0x0052E7BC reads at this+0x1BE78+4*layer for layers 17 and up; Zero Hour names the member m_zoneManager. The layer storage and everything from +0x1BEB4 on stay opaque.
The out-of-line declarations below reproduce the verified ledger signatures at these RVAs: 0x006D5CB0, 0x002F21EB, 0x002F3B6B, 0x005AD929, 0x002F3B9C, 0x002F1C25, 0x002E6D62, 0x002E8045, 0x002E8348, 0x002E8448, 0x002E8A47, 0x002EB6B4, 0x002EEF16, 0x002EF016, 0x002EF116, 0x002F1F3F, 0x002F203F, 0x002F4391, 0x002F6B22, 0x002F6C22, 0x002F6D22, 0x002F95B7, 0x002EAE20, 0x002EB675, 0x002EE96B, 0x002F0CF6, 0x002F0C78, 0x002F0CB7, 0x002EED41, 0x002F30EF, 0x002F30B0, 0x002F6AE3, 0x002F6E22, 0x001E4461, 0x002EADE1, 0x002EB3D7, 0x002EB4A0, 0x002EDFBD, 0x002F1AF4, 0x002F1B66, 0x002F1BA2, 0x002EDF44, 0x002E7205, 0x002F36E5, 0x002E74C6, 0x002F714B, 0x002E9897, 0x002E98C6, 0x002E9948, 0x002E99BD, 0x002E9871, 0x002E940F, 0x002E98EA, 0x002E9919, 0x002E996E, 0x002E99F9, 0x002EDEAB, 0x002E757D, 0x002E909F, 0x002E7178, 0x002E718A, 0x002E719B, 0x002E71AD, 0x002E71BF, 0x002E74B5, 0x002E8251, 0x002FC95E, 0x002F2FA4, 0x002F0596, 0x002F35AF, 0x002F9578, 0x002FA2DC, 0x002F213F, 0x002F436F, 0x002FCFCF, 0x002F3BB3, 0x002EF908, 0x002EC0A2, 0x002EBE54, 0x002F00E9, 0x002F52A7, 0x002F5C7A, 0x002ECAFF, 0x002F83CE, 0x002F83A3, 0x002E7133, 0x002F3971, 0x002EC9E1, 0x002EF68C, 0x002ED219, 0x002EF663, 0x002F1B32, 0x002E7296, 0x002EE1C7, 0x002F477E, 0x002F4B33, 0x002EDF7C, 0x002EE49B, 0x0052F2EC, 0x002F11A1, 0x002F133C, 0x002EC8C3, 0x0052E11A, 0x002EBD31, 0x002F4AC1, 0x0052E3E6, 0x002E8145, 0x002E7749, 0x002E8773, 0x002E8DAA, 0x002E9442, 0x002E9BE5, 0x002EA0BA, 0x002EAE5F, 0x002EB11B, 0x002EB7B4, 0x002EBD65, 0x002ED236, 0x002EED80, 0x002EF2A6, 0x002F068F, 0x002F0A72, 0x002F0F07, 0x002F370D, 0x002F379E, 0x002F40E7, 0x002F462C, 0x002F8E2D, 0x002F90E9, 0x002F92BC, 0x003E3BFB, 0x004DDA9A, 0x004DDDA4, 0x002F21F9, 0x002FA202, 0x002EE64A, 0x002EA34A, 0x002E75A3, 0x002E8BF8, 0x002E7917, 0x002FBBEB, 0x002FB997, 0x001E3647, 0x002FB558, 0x002F6075, 0x002F4E54, 0x002ED7F7, 0x002EEA8A, 0x002F287A, 0x002E8C6E, 0x002EDDA9, 0x002F314A, 0x002EDCF7, 0x002EC479, 0x002EA658, 0x002EE7EE, 0x002E85AD, 0x002F2B88, 0x002F06A3, 0x002F9DBA, 0x002F8B00, 0x002FC9B1, 0x002EF3EE, 0x002F3392, 0x002EFB3A, 0x002EB4DF, 0x002F07F5, 0x002ED313, 0x002ED535, 0x002EDFF9, 0x0052E4C9, 0x002F14F9, 0x0052E6E6, 0x002FA3F1, 0x002E9EA7, 0x002EE4DE, 0x002ECC0D, 0x002F83F5, 0x00530212, 0x002F3C09, 0x0052E914, 0x002F64DD, 0x002F5022, 0x002F71A6, 0x002F95F6, 0x002F69E3, 0x002FAD13, 0x002F4115, 0x0052F63F, 0x002FD344. No rowed method body is defined inline. AIGuardRetaliateReturnState::onEnter at 0x005452CB pushes zero for the fourth AdjustDestination argument at 0x00545329 before calling 0x002FCFCF at 0x0054533E; Zero Hour AIPathfind.h also declares that default as NULL.
*/

#pragma once
#ifndef BFME2_AIPATHFIND_H
#define BFME2_AIPATHFIND_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"
#include "PathfindZoneManager.h"

class Bridge;
class HierarchicalPath;
struct ICoord2DBase;
class Locomotor;
class LocomotorSet;
struct ObjWithPos;
class Object;
enum ObjectID;
class Path;
class PathNode;
class PathfindCell;
enum PathfindLayerEnum;
struct PathfinderCellIndex;
class PolygonTrigger;
class Rva001E48E8;
class Rva002C9B80Owner;
class Rva002CB35CObj;
class Rva002E6C79;
struct Rva002E6F92Info;
struct Rva002E7261Info;
struct Rva002E7B29Info;
class Rva002E7E26;
struct Rva002E7ED6Info;
struct Rva002E8145Info;
struct Rva002E85ADInfo;
struct Rva002E93A7Info;
struct Rva002E99F9Arg1;
class Rva002E9D09;
struct Rva002EBC7FPair;
struct Rva002ECE6AInfo;
struct Rva002ED01EInfo;
struct Rva002ED15AInfo;
struct Rva002ED236Pos;
struct Rva002EDEABArg;
struct Rva002EE49BPosition;
struct Rva002F18D4Info;
struct Rva002F1BD5Info;
struct Rva002F3F7DInfo;
struct Rva002F4491Info;
struct Rva002F4D8BInfo;
struct Rva002F5925Info;
struct Rva002F600CInfo;
class Rva004DD9E3;
class Rva005348AD;
struct TCheckMovementInfo;
class Vector3;

class PathfindServicesInterface
{
public:
    virtual Path *slot00(Object *, const LocomotorSet &, const Coord3D *, const Coord3D *, bool *);
    virtual Path *slot01(Object *, const LocomotorSet &, const Coord3D *, Coord3D *, bool, float, bool);
    virtual Path *slot02(Object *, const LocomotorSet &, const Coord3D *, Object *, const Coord3D *, Rva002C9B80Owner *, bool, bool *);
    virtual Path *slot03(Object *, const LocomotorSet &, const Coord3D *, Object *, const Coord3D *, Rva002C9B80Owner *);
    virtual Path *slot04(Object *, const LocomotorSet &, Path *, bool);
    virtual Path *slot05(Object *, const LocomotorSet &, const Coord3D *, const Coord3D *, const Coord3D *, float);
    virtual Path *FindCollisionFreeQuickPath(Object *, const Coord3D *, PathNode *);
};

class Pathfinder : public PathfindServicesInterface, public Snapshot
{
public:
    void removeUnitFromPathfindMap(Object *);
    char const * name(void)const;
    bool isViewBlockedByObstacle(Object const *,Object const *);
    void setDebugPathPosition(Coord3D const *);
    bool isAttackViewBlockedByObstacle(Object const *,Coord3D const *);
    unsigned char bfmeWrapE6E90(void *,void *,void *,void *,void *,void *);
    PathfindCell * getCell(PathfindLayerEnum,int,int);
    int rva002F95B7(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002F600CInfo *);
    int rva002EAE20(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002E6F92Info *);
    int rva002EB675(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002E7ED6Info *);
    int rva002EE96B(Coord3D *,Coord3D const *);
    int iterateCellsAlongLine(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002ED15AInfo *);
    int iterateCellsAlongLine(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002ECE6AInfo *);
    int iterateCellsAlongLine(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002ED01EInfo *);
    int rva002EED41(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002E93A7Info *);
    int iterateCellsAlongLine(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002F1BD5Info *);
    int iterateCellsAlongLine(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002F18D4Info *);
    int rva002F6AE3(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002F3F7DInfo *);
    Pathfinder(void);
    void * getObstacleID(int,int);
    int rva002EADE1(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002E7ED6Info *);
    int rva002EB3D7(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002E7B29Info *);
    int rva002EB4A0(Coord3D const *,Coord3D const *,PathfindLayerEnum,void *);
    int AdjustGroundPathPosition(Coord3D const *,Coord3D *);
    int IsLinePassable(void *,void *,PathfindLayerEnum,Coord3D const *,Coord3D const *,void *,int,int);
    int IsLinePassableForOptimize(void *,void *,PathfindLayerEnum,Coord3D const *,Coord3D const *,void *);
    bool IsHordeMeleeLinePassable(void *,void *,PathfindLayerEnum,Coord3D const *,Coord3D const *);
    PathfindCell * Rva002EDF44(ObjWithPos *);
    void SetBridgeStateRepaired(int,bool);
    PathfindCell * rva002F36E5(void);
    void ChooseBestLocomotorForPosition(PathfindLayerEnum,Rva001E48E8 *,Coord3D const *);
    int MoveAlliesAwayFromDestination(Object *,Coord3D const *,Coord3D const *);
    bool IsWaterCell(int,int);
    bool IsCliffCell(int,int);
    bool IsImpassableCell(int,int);
    void GetCellType(int,void *,void *,void *,int);
    int GetGroundLayer(Coord3D const *);
    bool IsPointOnWall(int,bool);
    int isBlockedGateObstacleCell(int,int);
    int IsNonPinchedCliffCell(int,int);
    bool IsBuildRestrictedCell(Coord3D const *,bool,bool,int);
    int FindBrokenBridge(Rva002E99F9Arg1 *,Coord3D const * volatile,Coord3D const *);
    void SetDebugPath(Rva002EDEABArg *);
    bool IsPointOnRamp(Coord3D const *);
    bool IsValidMovementPositionForObject(Coord3D const *,int,int,Object const *);
    void AddObjectToPathfindMap(Object *);
    void RemoveObjectFromPathfindMap(Object *);
    void RemoveObjectGoalFromPathfindMap(Object *);
    void RemoveObjectFromPathfindMapKeepingGateFlags(Object *);
    int AddBridge(int);
    void SetDebugPathPosition(Coord3D const *);
    void TightenPath(Object *,LocomotorSet const &,Coord3D *,Coord3D const *);
    bool CheckForTarget(void *,void *,void *,Rva002CB35CObj *,void *,void *,void *,void *,Coord3D *);
    Path * BuildActualPath(Object *,int,Coord3D const *,PathfindCell *,bool,bool,bool);
    Rva005348AD * MakeHierarchicalPathPassable(void *,Rva002E6C79 *,bool);
    int iterateCellsAlongLine(Coord3D const *,Coord3D const *,PathfindLayerEnum,Rva002F4D8BInfo *);
    bool CanApproachToTarget(Object *,Coord3D const *,Rva002C9B80Owner *,bool);
    virtual ~Pathfinder(void);
    void AddToOpenList(PathfindCell *);
    bool AdjustDestination(Object *,LocomotorSet const &,Coord3D *,Coord3D const * = 0);
    bool AdjustTargetDestination(Object *,int,int,int,Coord3D const *);
    Path * BuildGroundPath(Coord3D const *,PathfindCell *,bool,int);
    int CalcCollisionFreeExtraCosts(Object *,PathfindCell *,Rva002EBC7FPair *,PathfindLayerEnum,int,int,bool);
    int CalcExtraCosts(Object *,PathfindCell *,Rva002EBC7FPair *,int,int,bool);
    bool CheckDestination(Object *,int,int,PathfindLayerEnum,int,bool,int *,bool);
    bool CheckForAdjust(Object *,LocomotorSet const &,bool,int,int,PathfindLayerEnum,int,bool,Coord3D *,Coord3D const *,float,int *,int);
    int CheckPathCost(Object *,LocomotorSet const &,Coord3D const *,Coord3D const *);
    int CountOverlapHordeGoalUnits(Object *,Coord3D const *);
    void ForceMapRecalculation(void);
    Path * GetAircraftPath(Object const *,Coord3D const *);
    int GetOverlapGoalUnits(Object *,Coord3D const *,int *);
    float GetWallHeight(PathfindLayerEnum,Coord3D const *,Coord3D *);
    bool IsGroundLineOnly(Coord3D const *,Coord3D const *);
    bool IsGroundPathPassable(Coord3D const *,PathfindLayerEnum,Coord3D const *,int);
    bool IsLineBlocked(void *,void *,PathfindLayerEnum,Coord3D const *,Coord3D const *);
    bool IsValidMovementTerrain(PathfindLayerEnum,Locomotor const *,Coord3D const *);
    void PrependCells(Path *,Coord3D const *,PathfindCell *,bool);
    bool QuickDoesPathExist(Object *,Coord3D const *,Coord3D const *,int);
    bool QuickDoesPathExistToStructure(Object *,Coord3D const *,Object *,int);
    PathfindCell * Rva002EDF7C(ObjWithPos *,ICoord2D *);
    bool rva002EE49B(Object *,Rva002EE49BPosition,Rva002EE49BPosition);
    void Rva0052F2EC(void);
    void UpdateLayer(Object *,PathfindLayerEnum);
    int _GetAdjacentUnits(Object *,Coord3D const *,int *);
    int _GetOverlapUnits(Object *,Coord3D const *,int *);
    static void classifyMapCell(int,int,PathfindCell *);
    bool queueForPath(ObjectID);
    bool rva002F4AC1(ICoord2D const *,int,int,Object *,PathfindLayerEnum,int,Rva002E7261Info *,void *,void *);
    void rva0052E3E6(PolygonTrigger *,bool);
    int rva002E7749(void *,int,int,int,int,bool);
    int ProcessConvexPoly(int *,int *,int,int,Rva002E7E26 *);
    void NewMap(void);
    bool rva002E9442(Vector3 const &,Vector3 const &,Vector3 *);
    bool CircleClipsTallBuilding(Coord3D const *,Coord3D const *,float,unsigned int,Coord3D *);
    bool rva002EA0BA(Object *,PathfindCell *,TCheckMovementInfo &,ObjectID *);
    bool rva002EAE5F(ICoord2D const *,int,ICoord2D *,void *);
    bool rva002EB11B(ICoord2D const *,int,ICoord2D *,void *);
    int ProcessConvexPoly(int *,int *,int,int,Rva002E9D09 *);
    bool QueueForCollisionResponsePath(ObjectID);
    PathfindLayerEnum rva002ED236(Object *,Rva002ED236Pos);
    int IterateCellsInRectangle(ICoord2DBase const *,ICoord2DBase const *,float,int,Rva002E9D09 *);
    void AdjustLayer(Object *);
    PathfindCell * rva002F068F(void);
    int rva002F0A72(PathfindCell *,PathfindCell *);
    void ProcessPathfindQueue(void);
    int rva002F370D(void);
    bool rva002F379E(ICoord2D *,int,void *);
    int rva002F40E7(void);
    void rva002F462C(void);
    bool rva002F8E2D(ICoord2D const *,int,ICoord2D *,void *);
    bool rva002F90E9(ICoord2D *,int,void *);
    bool rva002F92BC(ICoord2D const *,int,ICoord2D *,void *);
    void rva003E3BFB(ObjectID);
    int ProcessConvexPoly(int *,int *,int,int,Rva004DD9E3 *);
    int IterateCellsInRectangle(ICoord2DBase const *,ICoord2DBase const *,float,int,Rva004DD9E3 *);
    virtual void xfer(Xfer *);
    bool AdjustHordeMeleeDestination(Object *,void *,Coord3D *);
    bool IsValidObjectMovement(Object *,Coord3D const *,Coord3D const *);
    bool checkForMovement(Object *,TCheckMovementInfo &);
    void clip(Coord3D *,Coord3D *);
    PathfindCell * rva002E8BF8(PathfindLayerEnum,Coord3D const *);
    PathfinderCellIndex Rva002E7917(bool,Coord3D const *);
    Path * InternalFindPath(Object *,LocomotorSet const &,Coord3D const *,Coord3D const *,HierarchicalPath *,bool *);
    Path * FindSafePath(Object *,LocomotorSet const &,Coord3D const *,Coord3D const *,Coord3D const *,float);
    void * rva001E3647Pos(int,Coord3D const *);
    Path * PatchPath(Object *,LocomotorSet const &,Path *,bool);
    Path * GetHordeUnitPath(Object *,Coord3D const *);
    void CheckChangeLayers(PathfindCell *,Object *);
    bool adjustToMeleeDestination(Object *,LocomotorSet const &,Coord3D *);
    bool rva002EEA8A(ICoord2D const *,int,ICoord2D *,void *,int);
    bool adjustToPossibleDestination(Object *,LocomotorSet const &,Coord3D *);
    void AdjustMeleeOffset(Object *,Object *,Coord3D *);
    bool AdjustToNearestValidCell(Coord3D *);
    bool isAttackViewBlockedByObstacle(Object const *,Coord3D const &,Object const *,Coord3D const &);
    bool AdjustToNearestGroundCell(Coord3D *);
    bool rva002EC479(Object *,Coord3D const *,Object *);
    bool rva002EA658(Object *,TCheckMovementInfo &,ICoord2D const *);
    bool getClosestPointOnLand(Coord3D const *,Object *,Coord3D *);
    void SnapClosestGoalPosition(Object *,Coord3D *);
    bool IsValidHordeMemberRegularMovement(Object *,Coord3D const *,Coord3D const *,Coord3D const *);
    Path * GetMoveAwayFromPath(Object *,Object *,Path *,Object *,Path *);
    int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *,ICoord2D const *,int,LocomotorSet const &,bool,bool,int,ICoord2D *,Object *,int);
    Path * FindAttackPathSideways(Object *,LocomotorSet const &,Coord3D const *,Object *,Coord3D const *,Rva002C9B80Owner *);
    bool rva002EF3EE(Object *,Coord3D *,Object *,bool);
    bool rva002F3392(PathNode *,PathNode *,unsigned int,Coord3D *,Coord3D *,Coord3D *);
    void rva002EFB3A(void);
    int IterateCellsInRectangle(ICoord2DBase const *,ICoord2DBase const *,float,int,Rva002E7E26 *);
    bool rva002F07F5(Object *,Coord3D const *);
    bool rva002ED313(Object *);
    bool rva002ED535(Object *,Coord3D *);
    bool rva002EDFF9(Object *,Coord3D *);
    void rva0052E4C9(Object *,bool);
    Object * rva002F14F9(Object *,Object *);
    bool rva0052E6E6(int,int,PathfindCell *,PolygonTrigger *,int,bool);
    Path * FindClosestPath(Object *,LocomotorSet const &,Coord3D const *,Coord3D *,bool,float,bool);
    bool rva002E9EA7(Object *,int,int,PathfindLayerEnum,int,unsigned char,int *);
    void AdjustFlingDestination(Object *,Coord3D const *,Coord3D *);
    bool rva002ECC0D(Object *,Coord3D const *);
    int rva002F83F5(PathfindCell *,PathfindCell *,LocomotorSet const &,bool,bool,int,ICoord2D *,Object *,int);
    void rva00530212(Object *,bool,bool,bool);
    bool MoveAllies(Object *,Path *,bool);
    void rva0052E914(int,int,PathfindCell *,Bridge *,bool,PathfindCell *,float);
    virtual Path * FindCollisionFreeQuickPath(Object *,Coord3D const *,PathNode *);
    void rva002F5022(ICoord2D const &,ICoord2D const &,PathfindCell *,PathfindCell *,unsigned short,unsigned short *,int &,int,int &);
    Path * FindGroundPath(Object *,Coord3D const *,Coord3D const *,int);
    Path * FindAttackPath(Object *,LocomotorSet const &,Coord3D const *,Object *,Coord3D const *,Rva002C9B80Owner *,bool,bool *);
    bool rva002F4115(Object *,int,int,LocomotorSet *);
    void ClassifyWall(Object *,bool);
    Path * FindPath(Object *,LocomotorSet const &,Coord3D const *,Coord3D const *,bool *);
protected:
    Path * FindClosestHierarchicalPath(bool,LocomotorSet const &,Object *,Coord3D const *,Coord3D const *,bool,Coord3D *);
    Path * FindHierarchicalPath(bool,LocomotorSet const &,Object *,Coord3D const *,Coord3D const *,bool);
    Path * internal_findHierarchicalPath(bool,int,Object *,Coord3D const *,Coord3D const *,bool,bool,Coord3D *);
private:
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002E7261Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002E6F92Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002E7B29Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002E7ED6Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002E93A7Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002ECE6AInfo *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002ED01EInfo *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002ED15AInfo *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002F18D4Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002F1BD5Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002F3F7DInfo *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002F5925Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002F4D8BInfo *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002F600CInfo *);
    int rva002E8251(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002E7ED6Info *);
    int rva002E8145(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002E8145Info *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002E85ADInfo *);
    int iterateCellsAlongLine(ICoord2D const *,ICoord2D const *,PathfindLayerEnum,Rva002F4491Info *);

public:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;

private:
    bool m_isMapReady;
    unsigned char m_unknown09[3];
    void *m_field0C;
    PathfindCell **m_map;
    IRegion2D m_extent;
    unsigned char m_unknown24[0x34 - 0x24];
    void *m_field34;
    unsigned char m_unknown38[0x48 - 0x38];
    ObjectID m_ignoreObstacleID;
    Coord3D m_field4C;
    Path *m_field58;
    Bridge *m_field5C;
    unsigned char m_unknown60[0x460 - 0x60];
    PathfindZoneManager m_zoneManager;
    unsigned char m_unknown1BEB4[0x1D200 - 0x1BEB4];
};

typedef char PathfinderAllocationSize[(sizeof(Pathfinder) == 0x1D200) ? 1 : -1];

#endif
