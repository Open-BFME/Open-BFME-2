// cl: /ICode/Libraries/Include /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /Ow
// Pathfinder::FindAttackPathSideways, retail 0x002FC9B1 (1566 B), with the
// callees that share its translation unit: ExamineNeighboringCellsForSidewaysAttack
// 0x002F8B00 (re-homed here from pathfinder.cpp), the init 0x002E6BA1 and a
// select-any copy of rva002F83F5 (rowed in PathfinderRva002F83F5Neighbors.cpp).
// Lab evidence: the target only reproduces retail with those callee bodies
// visible and /Ow; pathfinder.cpp cannot take /Ow.
// Target facts: bool at 0x00DBD4AC passed as faceDirection of the primary
// attack-path build, int at 0x00DFF0CC cleared before the search. The
// m_1BEB6 set/clear around BuildActualPath is two volatile stores and the
// surface mask a volatile read of the locomotor set +0x10.
// Structural inference: the body follows WorldBuilder's sideways attack search.
// stlport
#include <vector>
typedef bool Bool;
typedef int Int; typedef float Real; struct Coord3D;
enum PathfindLayerEnum
{
PATHFIND_LAYER_UNKNOWN = 0,
PATHFIND_LAYER_GROUND = 1
};
typedef int LocomotorSurfaceTypeMask;

class LocomotorSet
{
public:
Bool isDownhillOnly()const{return m_downhillOnly;}
LocomotorSurfaceTypeMask getValidSurfaces() const
{
return m_validLocomotorSurfaces;
}
private:
char m_pad[0x10];
LocomotorSurfaceTypeMask m_validLocomotorSurfaces;
Bool m_downhillOnly;
Bool m_scalesWalls;
};

class Player
{
public:
char m_pad00[0x5c];
Int m_playerType;		// +0x5C (1: computer)
};
class AIUpdateInterface;
struct PathfinderTemplateView {
char pad[0x64];
char *nameBuffer;
char pad68[0x108-0x68];
unsigned char kinds[24];
char pad120[0x56c-0x120];Int priority;char pad570[0x634-0x570];Bool flag;
__forceinline bool hasKind(int bit) const { return (kinds[bit/8] & (1<<(bit%8)))!=0; }
__forceinline const char *name() const { return nameBuffer ? nameBuffer+8 : ""; }
};
enum Relationship { ENEMIES=0, NEUTRAL=1, ALLIES=2 };
class Object
{
public:
Player *getControllingPlayer() const;
 Int rva0028B511() const; char rva00294815(); void rva0028C2DD(Coord3D *) const; bool isSignificantlyAboveTerrain() const; const Coord3D *getPosition() const {return (const Coord3D*)position;} Real getOrientation() const {return m_orientation;}
Relationship getRelationship(const Object *) const;
bool IsAtGoalPosition() const;
bool rva0028AFBB() const;
float GetGoalAngle() const;
__forceinline int getID() const { return *(const int *)((const char *)this+0x74); }
AIUpdateInterface *getAI() const { return reinterpret_cast<AIUpdateInterface *>(m_258); }
void *m_vtable;
PathfinderTemplateView *m_template;
char m_pad08[0x38-8];
float position[3];
float m_orientation;				// +0x44
char m_pad48[0x258 - 0x48];
char *m_258;						// +0x258 (WorldBuilder +0x260: CanApproachToTarget's gate)
char m_pad25C[0x274-0x25C];
Object *container;
};
#include "Lib/Coord3D.h"
#include "../../Common/Thing/thing.h"
struct Rva002E7ED6Info;
class Pathfinder;
struct Rva002E93A7Info
{
Pathfinder *m_00;
Int m_04;
};
class PathfindCell;
class Path
{
public:
Path();										///< matched 0x00363DC8
void rva00364551(Object *obj, LocomotorSurfaceTypeMask surfaces, Bool blocked, const float *facing);
void rva00365E98(Object *obj, const Coord3D *dir, LocomotorSurfaceTypeMask surfaces, Bool blocked);
private:
char m_pad[0x28];
};

struct Rva002E8C23Pair { Int x,y; };
int __cdecl Rva002E8C4DCall(int,unsigned char,Rva002E8C23Pair *,int);
bool Rva002EBBFBIsOdd(void *);
struct ICoord2D;
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
class GlobalData { public: char pad[0x11F0];Int searchRadius; char pad11f4[0x1218-0x11f4]; unsigned sidewaysAttackLimit; };
extern GlobalData *TheWritableGlobalData;
extern "C" double __cdecl fabs(double);
struct PathfinderCostCellInfo { Int x,y; };
struct PathfinderGroundInfo { PathfinderCostCellInfo position;Int parent,state;unsigned short totalCost,costSoFar;char pad14[0x28-0x14];Int obstacleID;unsigned int flags; };
struct In002E6BA1 { Int x,y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,Int,In002E6BA1 *);
class Rva002E6AF3 { public: Int get() const; };
class Rva002E6B06 { public: Int rva002E6B06(); };
class Rva002E6C79;
struct Rva002E8BCFSrc;
class Rva002E8BCF { public: Rva002E8BCF(){} Rva002E8BCF(const Rva002E8BCFSrc *,Bool,Int,Bool); Int surfaces;Bool field4,field5;Int maxLayer;Bool fieldC; };
class Rva002E6DC4 { public: Bool rva002E6DC4(void *,void *); };

void ji_00629952();
class PathfindCell
{
friend class Pathfinder;
public:
enum CellType
{
CELL_CLEAR = 0,
CELL_OBSTACLE = 4,
CELL_IMPASSABLE = 5
};
enum { LAYER_GROUND = 1 };

Bool StartPathfind(Int);void ReleaseInfo();void SetParentCell(Int *);void PutOnClosedList(MixFileInfoBuffer **);Int CalcCostSoFar(const Rva002E6C79 *);
__forceinline void allocateInfo(In002E6BA1 *pos) {
if(!m_pathInfo) { if(!TheMixFileInfoPool)Rva0052DBCDInit();m_pathInfo=(PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool,(Int)this,pos); }
else m_pathInfo->state=0;
}
void rva0052DAE9(Bool open);
Int getXIndex() const { return m_pathInfo->position.x; }
Int getYIndex() const { return m_pathInfo->position.y; }
float rva0052DD75(float facing, Int count, float weight);
__declspec(dllimport) CellType getType() const { return (CellType)(m_info & 0xf); }
Int getLayer() const { return (m_info & 0x3f0) >> 4; }

private:
PathfinderGroundInfo *m_pathInfo;
char m_pad04[8];
unsigned int m_info;			// +0x0C
};

struct LocomotorTemplate
{
char m_pad00[0x14];
LocomotorSurfaceTypeMask m_surfaces;	// +0x14
};

class Locomotor
{
public:
LocomotorSurfaceTypeMask getLegalSurfaces() const { return m_template->m_surfaces; }

private:
void *m_vtbl;
const LocomotorTemplate *m_template;	// +0x04
};

extern unsigned int g_00DBD33C[16];

extern "C" __declspec(dllimport) double __cdecl floor(double);
float Sin(float x);
float Cos(float x);

static __forceinline Int realToIntFloor(float f)
{
float floored = (float)floor((double)f);
return (Int)floored;
}

class Rva002F3738
{
public:
void rva002F3738(void **entry);
};

struct _Rva002E7B02Cell
{
Int x;
Int y;
Int z;
};

class Rva002E7B02
{
public:
Rva002E7B02(Int a, Int b, const _Rva002E7B02Cell &cell);
private:
Int m_00;
Int m_04;
Int m_08;
Int m_0C;
Int m_10;
};

struct Rva002E7B29Info;

template<int N> class PathfinderNativeSlots : public PathfinderNativeSlots<N-1> { public: virtual void unusedSlot(PathfinderNativeSlots<N> *); };
template<> class PathfinderNativeSlots<0> {};
class TerrainLogicCheckDestination : public PathfinderNativeSlots<50> { public: virtual bool slotC8(const Coord3D *); };
class PathfinderContain28 : public PathfinderNativeSlots<28> { public: virtual int slot70(); };
class PathfinderContain31 : public PathfinderNativeSlots<31> { public: virtual void *slot7C(); };
class PathfinderContain69 : public PathfinderNativeSlots<69> { public: virtual unsigned int slot114(int); };
class TerrainLogicWaterQuery : public PathfinderNativeSlots<19> { public: virtual bool slot4C(float,float,float *,void *,void *); };
class TerrainLogic
{
public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual float getGroundHeight(float x, float y, Coord3D *normal);
virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D *,Bool);
PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

void Rva002EBCA7Split(void *obj, Int *radius, unsigned char *center);
struct Rva002F600CInfo;

static __forceinline void zeroCoord3D(Coord3D *dst)
{
dst->x = 0.0f;
dst->y = 0.0f;
dst->z = 0.0f;
}
static __forceinline void copyCoord3D(Coord3D *dst, const Coord3D *src)
{
dst->x = src->x;
dst->y = src->y;
dst->z = src->z;
}

class Pathfinder_FuncTightenPath
{
public:
Pathfinder_FuncTightenPath(Pathfinder *pathfinder, Object *obj,
const LocomotorSet &locomotorSet, PathfindLayerEnum layer,
const Coord3D &goal);

Pathfinder *m_pathfinder;				// +0x00
Object *m_obj;							// +0x04
const LocomotorSet *m_locomotorSet;		// +0x08
Int m_radius;							// +0x0C
unsigned char m_center;					// +0x10
PathfindLayerEnum m_layer;				// +0x14
Bool m_foundDest;						// +0x18
Coord3D m_goal;							// +0x1C
Coord3D m_destPos;						// +0x28
};

class Pathfinder_IsCheckForAdjust
{
public:
Pathfinder_IsCheckForAdjust(Pathfinder *pathfinder, Object *obj,
void *arg, const Coord3D &goal, const Coord3D *layerPos, float range,
Int arg6);

Pathfinder *m_pathfinder;				// +0x00
Object *m_obj;							// +0x04
void *m_08;								// +0x08
Bool m_isHuman;							// +0x0C
unsigned char m_center;					// +0x0D
Int m_radius;							// +0x10
const Coord3D *m_layerPos;				// +0x14
PathfindLayerEnum m_layer;				// +0x18
float m_range;							// +0x1C
Rva002E8C23Pair fallback;
Int m_28;								// +0x28
Int m_2C;								// +0x2C
Coord3D m_goal;							// +0x30
};

class Pathfinder_IsCheckForMeleeHordeAdjust
{
public:
Pathfinder_IsCheckForMeleeHordeAdjust(Pathfinder *pathfinder, Object *obj,
void *arg, const Coord3D &goal, float range);

Pathfinder *m_pathfinder;				// +0x00
Object *m_obj;							// +0x04
void *m_08;								// +0x08
Bool m_isHuman;							// +0x0C
unsigned char m_center;					// +0x0D
Int m_radius;							// +0x10
PathfindLayerEnum m_layer;				// +0x14
float m_range;							// +0x18
char m_pad1C[0x24 - 0x1C];
Int m_24;								// +0x24
Coord3D m_goal;							// +0x28
};

void *rva002EBC59(void *out, void *obj, Int a2, Int a3, Int a4);
class Rva002CB35CObj
{
public:
Bool rva002CB35C(Int a1, void *pos, void *a3, void *a4, float range, Int a6);
};

class Rva002C9400ByteField
{
public:
unsigned char get() const;
};
// Weapon::isWithinAttackRange 0x002CB35C (WorldBuilder name).
#include "../../../Include/GameLogic/Weapon.h"
class Rva002C9B80Owner
{
public:
Bool isWithinAttackRange(Object *,const Coord3D *,Object *,const Coord3D *,float,Bool);
float rva002C9B80(void *a, float b);
void *m_00;
Rva002C9400ByteField *m_04;				// +0x04
};
struct Rva002E8BCFSrc;
struct Rva002F4D8BInfo;
class Rva002E9ACC
{
public:
Rva002E9ACC(void *a1, Object *obj, Rva002E8BCFSrc const *src,
unsigned char a4, unsigned char a5);
char m_pad00[0x1C];
Bool m_found;							// +0x1C
unsigned char m_1D;						// +0x1D
unsigned char m_1E;						// +0x1E
unsigned char m_1F;						// +0x1F
unsigned char m_20;						// +0x20
};

struct Rva002F35AFZone
{
Int m_00;
Int m_04;
};
struct Rva002F35AFCell
{
Int x;
Int y;
Int m_08;
Rva002F35AFZone *m_0C;
};
class Rva002E6C79
{
public:
Int rva002E6C79();
Rva002F35AFCell *m_00;
Rva002E6C79 *next() { return (Rva002E6C79 *)rva002E6C79(); }
};
struct Rva002F35AFHop
{
Int m_zone;
PathfinderCostCellInfo m_position;
};
class Rva005348AD
{
public:
Rva005348AD();
void rva00534557(Rva002F35AFCell *cell);
void rva00534AAE();
private:
char m_pad[0x14];
};

class Rva0036666B
{
public:
bool rva0036666B();
};

class PathfindLayer
{
public:
bool setDestroyed(bool destroyed);
__declspec(noinline) void rva000B3FD0();
private:
char m_pad[0x40];
};

class PathfindZoneManager
{
public:
void rva005312BE(); void rva00531300();
void rva00531481();
void rva005314C6(Int x, Int y, unsigned char flag);
unsigned char IsPassable(Int,Int);
};


struct Rva002EBC7FPair { int x,y; };
void *rva002EBC7F(void *,void *,Rva002EBC7FPair *,int);
#include <math.h>
class Rva001E46E1 { public: float rva001E46E1(Object *); };
class AIUpdateInterface {
public:
bool isAircraftThatAdjustsDestination() const;
int rva0026417F(bool);
char gap[0x1f0];
Rva001E46E1 *locomotor;
};
struct PathCollisionNode { PathCollisionNode *next; void *word4; Object *object; };
struct PathCollisionInfo {
int x,y;
char gap08[0x14-8];
PathCollisionNode *occupants;
char gap18[8];
PathCollisionNode *goals;
PathCollisionNode *reservations;
};
struct PathCollisionCell { PathCollisionInfo *info; };
class Bridge {
public:
bool isPointOnBridge(const Coord3D *pos);
float getBridgeHeight(const Coord3D *pos, Coord3D *normal);
void *m_00;
Bridge *m_next;
};
struct Rva002ED236Pos {
float x, y, z;
Rva002ED236Pos(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
~Rva002ED236Pos() {}
};
int Rva002E6E8AGet(int layer);
class Rva002E7482 { public: float rva002E7482(int layer); };

#include "ascii_string.h"
struct GeometryShape {
int type; float height,major,minor;
float offsetX,offsetY,offsetZ;
AsciiString name;
bool enabled,opaque21;
__forceinline GeometryShape() : type(0),height(1),major(1),minor(1),offsetX(0),offsetY(0),offsetZ(0),enabled(true),opaque21(true) {}
};
class GeometryInfo { public: void rva006BD9C0(GeometryShape &) const; };
struct ICoord2DBase { int x,y; };
class Rva002E9D09 { public: int rva002E9D09(Object *,int,int); };
class Rva002E7C99 {
public:
void *rva002E7C99(int,int,int,unsigned char,int,unsigned char,int);
char fields[28];
};
class Rva0006E009DwordField { public: int get() const; };
class Rva0052DB4D { public: bool rva0052DB4D(int); };
void rva002E79A8(int,unsigned char,int,int,int);
union PathfinderCheckCoordinates {
Coord3D point;
struct IntegerLayout { int reserved; ICoord2DBase position,size; } cells;
};
struct PathfinderLogFile;
extern "C" int __cdecl fprintf(PathfinderLogFile *,const char *,...);
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
struct TCheckMovementInfo { ICoord2D cell;PathfindLayerEnum layer;Int radius;Bool centerInCell,considerTransient;char pad12[2];Int options,ignore;Rva002E8BCF movement;Int allyFixedCount;Bool flag30,flag31,allyGoal;char pad33;Int blockedCells; };
class Rva002E6FDF { public:Rva002E6FDF *rva002E6FDF(); };
class Rva002EAB6F {public:Rva002EAB6F(Int,const Rva002E8BCFSrc *,unsigned char,Int,Object *,unsigned char,Int,Int);char fields[0x34];};
struct Rva002F5925Info;
struct BurningCell {char pad[6];unsigned short count;char pad8[12];};
struct BurningGrid {char pad[0x70];BurningCell **cells;char word74[4];Int width,height;};
class Rva002872BA;extern Rva002872BA *TheTriggerManager;
Int isGroundOrBridgeLayer(Int);
class Rva002F6F90Context { public: Bool rva002F6F90(unsigned int,Int); };
class Rva002F70E5Context { public: Bool rva002F70E5(unsigned int,Int); };
class Rva002E7440 { public: Bool rva002E7440(Int,Int); };
class Rva002E7414 { public: Int rva002E7414(Int,Int); };
class Rva002F336AOwner { public: Bool rva002F336A(Int,Int); };
struct PathfinderCellIndex : ICoord2D {PathfinderCellIndex(){} PathfinderCellIndex(const PathfinderCellIndex& v) {x=v.x;y=v.y;} };
class Pathfinder
{
public:
Path *FindAttackPathSideways(Object *,const LocomotorSet &,const Coord3D *,Object *,const Coord3D *,Rva002C9B80Owner *);
 Int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *,const ICoord2D *,Int,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
 Bool isAttackViewBlockedByObstacle(const Object *,const Coord3D &,const Object *,const Coord3D &);

PathfinderCellIndex Rva002E7917(Bool,const Coord3D *);
Int rva002F83F5(PathfindCell *,PathfindCell *,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
Bool rva002EA658(Object *,TCheckMovementInfo &,const ICoord2D *);
__forceinline Path *BuildAttackPath(Object *obj,const LocomotorSet &locos,const Coord3D *from,PathfindCell *goal,Bool center,Bool blocked,Bool faceDirection) {
 *(volatile Bool*)&m_1BEB6=true;
 int surf=*(volatile int*)((char*)&locos+0x10);
 Path *path=BuildActualPath(obj,surf,from,goal,center,blocked,faceDirection);
 m_1BEB6=false;
 return path;
}


Bool rva002EAE5F(const ICoord2D *,Int,ICoord2D *,void *);
Bool rva002EB11B(const ICoord2D *,Int,ICoord2D *,void *);
Bool rva002F379E(ICoord2D *,Int,void *);
Bool AdjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
Int CheckPathCost(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *);
Bool rva002F8E2D(const ICoord2D *,Int,ICoord2D *,void *);
Bool rva002F90E9(ICoord2D *,Int,void *);
Bool rva002F92BC(const ICoord2D *,Int,ICoord2D *,void *);
PathfindCell *rva002E8BF8(PathfindLayerEnum,const Coord3D *);
PathfindCell *rva002F36E5();Int rva002F40E7();void CheckChangeLayers(PathfindCell *,Object *);
Int rva002F0A72(PathfindCell *,PathfindCell *);
float GetWallHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal);
void *rva001E3647Pos(int layer, const Coord3D *pos);
bool IsPointOnRamp(const Coord3D *pos);
PathfindLayerEnum rva002ED236(Object *obj, Rva002ED236Pos pos);
Bool CheckDestination(Object *,Int,Int,PathfindLayerEnum,Int,Bool,Int *,Bool);
Int IterateCellsInRectangle(const ICoord2DBase *,const ICoord2DBase *,float,int,Rva002E9D09 *);
void SetBridgeStateRepaired(PathfindLayerEnum layer, Bool repaired);
void ForceMapRecalculation();
void Rva0052F2EC();
int rva002EADE1(const Coord3D *a, const Coord3D *b,
PathfindLayerEnum layer, Rva002E7ED6Info *info);
int rva002EED41(const Coord3D *startWorld, const Coord3D *endWorld,
PathfindLayerEnum layer, Rva002E93A7Info *info);
int rva002EB3D7(const Coord3D *startWorld, const Coord3D *endWorld,
PathfindLayerEnum layer, Rva002E7B29Info *info);
Bool IsGroundLineOnly(const Coord3D *startWorld,
const Coord3D *endWorld);
Bool IsGroundPathPassable(const Coord3D *startWorld,
PathfindLayerEnum layer, const Coord3D *endWorld, Int pathDiameter);
void AddToOpenList(PathfindCell *cell);
int CalcExtraCosts(Object *,PathfindCell *,Rva002EBC7FPair *,int,int,bool);
int CalcCollisionFreeExtraCosts(Object *,PathfindCell *,Rva002EBC7FPair *,PathfindLayerEnum,int,int,bool);
PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);	// 0x002E6D62
Bool IsValidMovementTerrain(PathfindLayerEnum layer, const Locomotor *locomotor, const Coord3D *pos);
Int AdjustGroundPathPosition(const Coord3D &source, Coord3D &destination);
unsigned char bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
Bool CheckForTarget(void *obj, void *a2, void *a3, Rva002CB35CObj *weapon,
void *a5, void *a6, void *a7, void *a8, Coord3D *out);
Path *BuildActualPath(Object *obj, LocomotorSurfaceTypeMask surfaces,
const Coord3D *fromPos, PathfindCell *goalCell, Bool center,
Bool blocked, Bool faceDirection);
void PrependCells(Path *path, const Coord3D *fromPos, PathfindCell *goalCell, Bool center);
Rva005348AD *MakeHierarchicalPathPassable(void *unused, Rva002E6C79 *path, Bool expand);
void TightenPath(Object *obj, const LocomotorSet &locomotorSet, Coord3D *from, const Coord3D *to);
int rva002F95B7(const Coord3D *from, const Coord3D *to, PathfindLayerEnum layer, Rva002F600CInfo *info);
Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *destination, PathfindLayerEnum layer, Rva002F4D8BInfo *callbackInfo);
Bool CanApproachToTarget(Object *obj, const Coord3D *targetPos, Rva002C9B80Owner *weapon, Bool flag);
protected:
Path *FindHierarchicalPath(Bool isHuman,
const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
const Coord3D *to, Bool crusher);
Path *FindClosestHierarchicalPath(Bool isHuman,
const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
const Coord3D *to, Bool crusher, Coord3D *adjustedTo);
Path *internal_findHierarchicalPath(Bool isHuman,
LocomotorSurfaceTypeMask locomotorSurface, Object *obj,
const Coord3D *from, const Coord3D *to, Bool crusher, Bool closestOK,
Coord3D *adjustedTo);
private:
Int iterateCellsAlongLine(const ICoord2D *,const ICoord2D *,PathfindLayerEnum,Rva002F5925Info *);
char m_pad000[8];Bool m_isMapReady;char m_pad009[7];
int m_unknown10;
char m_pad014[0x10];
Int m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY;
MixFileInfoBuffer *m_closedList;Bool m_isTunneling;char m_pad039[0x48-0x39];Int m_ignoreObstacleID;char pad4c[0x5c-0x4c];
Bridge *m_bridges;
PathfindLayer m_layers[16];
PathfindZoneManager m_zoneManager;
char m_pad461[0x1BEB6 - 0x461];
Bool m_1BEB6;		// +0x1BEB6: paths get a facing hint from the goal cell
char m_pad1BEB7[5];
float m_wallLayerHeights[48];
char m_pad1BF7C[0x1C1CC - 0x1BF7C];
_STL::vector<Rva002F35AFHop> m_1C1CC; Int m_searchWord,m_destMineshaft;	// +0x1C1CC
};




// The three search-functor ctors (0x002EE43A, 0x002ED72B, 0x002ED484) are
// owned by pathfinder.cpp; this unit only declares them.









struct Rva002EBCF6 : GeometryShape { Rva002EBCF6(); };

struct PathfinderDebugColor { float red,green,blue; };
void Rva000B3FD0PathDebug(const Coord3D *,float,Int,PathfinderDebugColor);









// ?Pathfinder::rva002F83F5 present-unmatched
inline __declspec(noinline) Int Pathfinder::rva002F83F5(PathfindCell *parentCell,PathfindCell *goalCell,const LocomotorSet &locomotorSet,Bool isHuman,Bool centerInCell,Int radius,ICoord2D *startCellNdx,Object *obj,Int attackMode)
{
if(obj->m_template->hasKind(109)||obj->m_template->hasKind(191)){radius=1;centerInCell=true;}
Bool canPathThroughUnits=false;
if(obj->getAI())canPathThroughUnits=*(Bool *)((char *)obj->getAI()+0x3ba);
if(!m_isTunneling && !locomotorSet.isDownhillOnly() && goalCell && !(parentCell->getXIndex()&3) && !(parentCell->getYIndex()&3)) {
ICoord2D end;const ICoord2D *endPtr;
if(m_1C1CC.empty()){endPtr=(ICoord2D *)goalCell->m_pathInfo;}
else {endPtr=(ICoord2D *)&m_1C1CC.back().m_position;}
end=*endPtr;PathfindLayerEnum layer=(PathfindLayerEnum)parentCell->getLayer();Rva002EAB6F query((Int)this,(const Rva002E8BCFSrc *)&locomotorSet,centerInCell,radius,obj,isHuman,(Int)goalCell,m_1C1CC.empty()?attackMode:0);
iterateCellsAlongLine((const ICoord2D *)parentCell->m_pathInfo,&end,layer,(Rva002F5925Info *)&query);
}
Int cellCount=0;
TCheckMovementInfo info;((Rva002E6FDF *)&info)->rva002E6FDF();
info.layer=(PathfindLayerEnum)parentCell->getLayer();info.radius=radius;info.centerInCell=centerInCell;
info.options=12;if(!obj->m_template->hasKind(90))info.options=28;
info.ignore=obj->getAI()?((Rva0006E009DwordField *)obj->getAI())->get():0;
Int priority=obj->m_template->priority;Bool flag=obj->m_template->flag;info.considerTransient=true;
info.movement=Rva002E8BCF((const Rva002E8BCFSrc *)&locomotorSet,!flag,priority-1,obj->rva0028AFBB());
static Int deltaX[]={1,0,-1,0,1,-1,-1,1};static Int deltaY[]={0,1,0,-1,1,1,-1,-1};
Bool neighborFlags[8];
for(Int i=0;i<8;++i) {
neighborFlags[i]=false;
Int x=parentCell->getXIndex()+deltaX[i],y=parentCell->getYIndex()+deltaY[i];ICoord2D coords={x,y};
PathfindCell *newCell=getCell((PathfindLayerEnum)parentCell->getLayer(),x,y);
if(!newCell)continue;
if((unsigned char)((Rva002E6B06 *)newCell)->rva002E6B06() || (unsigned char)((Rva002E6AF3 *)newCell)->get())continue;
if(newCell->getLayer()!=parentCell->getLayer() && !(info.movement.surfaces&64) && newCell->getLayer()!=((parentCell->m_info>>10)&63) && ((newCell->m_info>>10)&63)!=parentCell->getLayer() && (((parentCell->m_info>>10)&63)!=16 || ((newCell->m_info>>10)&63)!=((parentCell->m_info>>10)&63)))continue;
if(isHuman){if(x<m_extentLowX)continue;if(y<m_extentLowY)continue;if(x>m_extentHighX)continue;if(y>m_extentHighY)continue;}
if(i>=4 && !neighborFlags[i&3] && !neighborFlags[(i+1)&3])continue;
if(locomotorSet.isDownhillOnly()) {
float oldZ=TheTerrainLogic->getGroundHeight((float)(parentCell->getXIndex()*10),(float)(parentCell->getYIndex()*10),0);
float newZ=TheTerrainLogic->getGroundHeight((float)(x*10),(float)(y*10),0);
if(oldZ<newZ)continue;
}
Bool movementValid=((Rva002E6DC4 *)this)->rva002E6DC4(&info.movement,newCell);
Bool tunnelingValid=false;
if(m_isTunneling)tunnelingValid=(newCell->getLayer()==parentCell->getLayer());
if(!movementValid && !tunnelingValid){newCell->allocateInfo((In002E6BA1 *)&coords);newCell->PutOnClosedList(&m_closedList);continue;}
neighborFlags[i]=true;
info.cell.x=x;info.cell.y=y;
if(!rva002EA658(obj,info,(const ICoord2D *)parentCell->m_pathInfo)) {
if(!tunnelingValid){newCell->allocateInfo((In002E6BA1 *)&coords);newCell->PutOnClosedList(&m_closedList);continue;}
++info.blockedCells;
} else {if(movementValid)m_isTunneling=false;}
if(!newCell->m_pathInfo)++cellCount;
newCell->allocateInfo((In002E6BA1 *)&coords);
unsigned int newCostSoFar=0;
Int dx=goalCell?abs(x-goalCell->getXIndex()):3;
Int dy=goalCell?abs(y-goalCell->getYIndex()):3;
if(newCell->getType()==2 && !(unsigned char)(newCell->m_info>>16&1)) {
float oldZ=TheTerrainLogic->getGroundHeight((float)(parentCell->getXIndex()*10),(float)(parentCell->getYIndex()*10),0);
float newZ=TheTerrainLogic->getGroundHeight((float)(x*10),(float)(y*10),0);
if(fabs(oldZ-newZ)<10.0f)newCostSoFar=98;
} else if((unsigned char)(newCell->m_info>>16)&1 || (unsigned char)(newCell->m_info>>23)&1){if(dx+dy>3)newCostSoFar=10;}
newCell->m_pathInfo->flags&=~1U;
if(info.allyFixedCount){newCostSoFar+=14;if(!canPathThroughUnits)newCell->m_pathInfo->flags|=1;}
Int remaining=0;
if(goalCell){remaining=rva002F0A72(newCell,goalCell);if(attackMode && info.allyGoal)newCostSoFar+=30;}
if((unsigned char)isGroundOrBridgeLayer(newCell->getLayer()) && !m_zoneManager.IsPassable(x,y) && !((unsigned char)(newCell->m_info>>21)&1))newCostSoFar+=1000;
if(newCell->getType()==4){Int obstacle=newCell->m_pathInfo?newCell->m_pathInfo->obstacleID:0;if(obstacle!=m_ignoreObstacleID)newCostSoFar+=1000;}
newCostSoFar+=info.blockedCells*10;
if(m_isTunneling && !((Rva002E6DC4 *)this)->rva002E6DC4(&info.movement,newCell))newCostSoFar+=100;
if((unsigned char)(newCell->m_info>>21)&1)newCostSoFar>>=1;
newCostSoFar+=newCell->CalcCostSoFar((const Rva002E6C79 *)parentCell);
newCostSoFar+=CalcExtraCosts(obj,parentCell,(Rva002EBC7FPair *)&coords,info.radius,info.radius+(info.centerInCell?1:0),true);
Int fireX=realToIntFloor(((float)(x*10)+0.5f)*0.1f);
Int fireY=realToIntFloor(((float)(y*10)+0.5f)*0.1f);
BurningGrid *grid=(BurningGrid *)TheTriggerManager;
Bool burning=false;
if(fireX>=0 && fireX<grid->width && fireY>=0 && fireY<grid->height)burning=grid->cells[fireX][fireY].count>0;
if(burning)newCostSoFar+=10;
newCell->m_pathInfo->costSoFar=(unsigned short)newCostSoFar;
newCell->SetParentCell((Int *)parentCell);
if(m_isTunneling)remaining=0;
newCell->m_pathInfo->totalCost=(unsigned short)(newCell->m_pathInfo->costSoFar+remaining);
AddToOpenList(newCell);
}
return cellCount;
}

#include "../../Common/PartitionRangeQueryCallView.h"
struct PathfinderAttackCoord : Coord3D
{
	__forceinline PathfinderAttackCoord() {}
	__forceinline PathfinderAttackCoord(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }
	__forceinline PathfinderAttackCoord(const PathfinderAttackCoord &pathfinderAttackCoord) { x = pathfinderAttackCoord.x; y = pathfinderAttackCoord.y; z = pathfinderAttackCoord.z; }
};

inline float sqr(float v) { return v * v; }
// MathCoord2D lifetime view from the native/WB companion and current Pathfinder TU.
class MathCoord2D
{
public:
	MathCoord2D() {}
	MathCoord2D(const MathCoord2D &that) : x(that.x), y(that.y) {}
	MathCoord2D(float ix, float iy) : x(ix), y(iy) {}
	MathCoord2D(Int ix, Int iy) : x((float)ix), y((float)iy) {}
	~MathCoord2D() {}
	MathCoord2D &operator*=(float v) {x*=v;y*=v;return *this;}
 MathCoord2D &operator+=(const MathCoord2D &v) {x+=v.x;y+=v.y;return *this;}
	__forceinline float GetLengthEstimate() const {return fabs(x)>fabs(y)?fabs(x)+fabs(y)*0.25f:fabs(y)+fabs(x)*0.25f;}
 float dot(const MathCoord2D &mathCoord2D) const { return y * mathCoord2D.y + x * mathCoord2D.x; }
	MathCoord2D &operator-=(const MathCoord2D &c) { x -= c.x; y -= c.y; return *this; }
	__forceinline float GetLength() const { return (float)sqrt(x * x + sqr(y)); }
	__forceinline void Normalize() { float length=GetLength(); float inv=1.0f/length; x *= inv; y *= inv; }
	float x;
	float y;
};

float Sin(float x);
float Cos(float x);


class Rva002EAD62 { public: void rva002EAD62(); };
class HierarchicalPath {public: Int lookUpPositionOnPath(const Coord3D*);};
struct PathfinderAttackHandle
{
	Path *path;
	__forceinline PathfinderAttackHandle(Path *p) : path(p) {}
	__forceinline ~PathfinderAttackHandle() { ((Rva002EAD62 *)this)->rva002EAD62(); }
};

extern unsigned int PathfinderSearchCellsVisited;
// Retail 0x009BD4AC, initialised true (.data byte 01).
bool PathfinderFaceGoalFlag = true;
void Rva002EBCA7Split(void *,Int *,unsigned char *);
struct PathfinderCellPoint : Coord3D {
 __forceinline PathfinderCellPoint() {}
 __forceinline PathfinderCellPoint(const PathfinderCellPoint &pathfinderCellPoint) { x=pathfinderCellPoint.x; y=pathfinderCellPoint.y; z=pathfinderCellPoint.z; }
 __forceinline ~PathfinderCellPoint() {}
};
PathfinderCellPoint rva002E79A8(Bool center, Int x, Int y, PathfindLayerEnum layer);
PathfinderCellPoint Rva002E8C23Call(Bool center, PathfindCell *cell);

extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
extern int TheMixFileInfoCount;

// Rehomed 0x002E6BA1 (65 B), original Rva002E6BA1Init.cpp: initializer
// copying the cell position plus the owner at +0x30, zeroing +0x08/+0x0C,
// the cost words and +0x14 x5, masking +0x2C, zeroing +0x28, counting.
class Rva002E6BA1
{
public:
	void rva002E6BA1(int a, In002E6BA1 *b);

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned short m_10;
	unsigned short m_12;
	int m_14[5];
	int m_28;
	int m_2C;
	int m_30;
};

// pathfinder.cpp owns the row. This TU's /Ow lets the scheduler hoist the
// b->y load and the counter update, and this copy comes first in link order,
// so the volatile accesses and the barrier keep retail's non-/Ow schedule.
// Defining it here (not declaring it) keeps the rows' frames retail.
inline __declspec(noinline) void Rva002E6BA1::rva002E6BA1(int a, In002E6BA1 *b)
{
	m_30 = a;
	*(volatile int *)&m_00 = b->x;
	m_04 = ((volatile In002E6BA1 *)b)->y;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_12 = 0;
	memset(m_14, 0, 20);
	m_2C &= 0xffffffe0;
	m_28 = 0;
	_ReadWriteBarrier();
	++TheMixFileInfoCount;
}

class MixFileInfoBuffer
{
private:
	void bfmeUnlink();
	friend class Rva002E6BA1;
public:
	friend MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in);
};

// Rehomed 0x002E8B7A (33 B), original Rva002E8B7AInit.cpp: takes the pool
// head, unlinks it (0x002E6BE2) and initializes it for the cell (0x002E6BA1).
// Select-any like the visible copy in pathfinder.cpp, which owns the row.
inline __declspec(noinline) MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in)
{
	MixFileInfoBuffer *node = *pp;
	node->bfmeUnlink();
	((Rva002E6BA1 *)node)->rva002E6BA1(a, in);
	return node;
}


// Keep the converter's canonical floor/FISTP machinery from pathfinder.cpp.
// A C++ float-to-int cast emits _ftol2 instead of retail's x87 store. The
// converter stays visible for caller escape analysis, as in its owner unit.
static __forceinline Int worldToCellFloor(float f)
{
	float floored = (float)floor((double)f);
	long i;
	__asm {
		fld [floored]
		fistp [i]
	}
	return i;
}

inline __declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = worldToCellFloor(pos->x * (1.0f / 10.0f));
		iy = worldToCellFloor(pos->y * (1.0f / 10.0f));
	} else {
		ix = worldToCellFloor(pos->x * (1.0f / 10.0f) + 0.5f);
		iy = worldToCellFloor(pos->y * (1.0f / 10.0f) + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}


inline MathCoord2D operator-(MathCoord2D left, const MathCoord2D &right)
{
	left -= right;
	return left;
}
inline MathCoord2D operator+(MathCoord2D left, const MathCoord2D &right)
{
	left.x += right.x; left.y += right.y;
	return left;
}

Int Pathfinder::ExamineNeighboringCellsForSidewaysAttack(PathfindCell *parentCell,const ICoord2D *targetNdx,Int offset,const LocomotorSet &locomotorSet,Bool isHuman,Bool centerInCell,Int radius,ICoord2D *startCellNdx,Object *obj,Int attackDistance)
{
	ICoord2D goalNdx;
	Int px1=parentCell->getXIndex();
	Int px2=parentCell->getXIndex();
	Int py1=parentCell->getYIndex();
	Int py2=parentCell->getYIndex();
	Int distSqr=(px1-targetNdx->x)*(px2-targetNdx->x)+(py1-targetNdx->y)*(py2-targetNdx->y);
	if(distSqr*5*5<(offset+attackDistance)*(offset+attackDistance)){
		float orientation=obj->m_orientation;
		float angle=parentCell->rva0052DD75(orientation,10,0.5f);
		MathCoord2D parentWorld(parentCell->getXIndex()*10,parentCell->getYIndex()*10);
		float s=Sin(angle);
		MathCoord2D dir;
		dir.x=Cos(angle);
		dir.y=s;
		MathCoord2D targetWorld(targetNdx->x*10,targetNdx->y*10);
		if(centerInCell){
			parentWorld.x+=5.0f;
			parentWorld.y+=5.0f;
		}
		MathCoord2D delta=targetWorld-parentWorld;
		float dot=dir.dot(delta);
		dir*=dot;
		MathCoord2D p=parentWorld+dir;
		p-=targetWorld;
		if(p.GetLengthEstimate()<0.0001f){
			p.x=dir.y;
			p.y=-dir.x;
		}
		p.Normalize();
		p*=(float)offset;
		p+=targetWorld;
		goalNdx=Rva002E7917(centerInCell,(const Coord3D *)&p);
	}else{
		goalNdx=*targetNdx;
	}
	PathfindCell *goalCell=getCell(PATHFIND_LAYER_GROUND,goalNdx.x,goalNdx.y);
	if(!goalCell)return 0;
	Bool hadInfo=goalCell->m_pathInfo!=0;
	if(!hadInfo)goalCell->allocateInfo((In002E6BA1 *)&goalNdx);
	Int count=rva002F83F5(parentCell,goalCell,locomotorSet,isHuman,centerInCell,radius,startCellNdx,obj,attackDistance);
	if(!hadInfo){
		if(!(unsigned char)((Rva002E6AF3 *)goalCell)->get()&&!(unsigned char)((Rva002E6B06 *)goalCell)->rva002E6B06())goalCell->ReleaseInfo();
	}
	return count;
}

Path *Pathfinder::FindAttackPathSideways(Object *obj, const LocomotorSet &locos, const Coord3D *from, Object *victim, const Coord3D *victimPos, Rva002C9B80Owner *weapon)
{
	if (!m_isMapReady)
		return 0;
	if (!obj->getAI())
		return 0;
	m_searchWord = 0;
	m_destMineshaft = 0;
	Int radius;
	Bool center;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&center);
	obj->rva0028AFBB();
	Bool isHuman = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1)
		isHuman = false;
	PathfinderAttackCoord goal(*victimPos);
	if (victim && victim->m_template->hasKind(150))
		victim->rva0028C2DD(&goal);
	m_zoneManager.rva005312BE();
	PathfinderAttackCoord adjusted(goal);
	PathfinderAttackHandle hierarchical(FindClosestHierarchicalPath(isHuman, locos, obj, from, &goal, obj->rva00294815() > 0, &adjusted));
	if (hierarchical.path)
	{
		if (adjusted.x != goal.x || adjusted.y != goal.y)
		{
			if (!((Weapon *)weapon)->isWithinAttackRange(obj, &adjusted, victim, victimPos, 10.0f, false))
				return 0;
		}
	}
	else
	{
		m_zoneManager.rva00531300();
	}
	Int attackDistance = (Int)((Weapon *)weapon)->getAttackDistance(obj, victim, victimPos) + 30;
	Bool checkLOS;
	if (!victim)
		checkLOS = true;
	else
		checkLOS = !victim->isSignificantlyAboveTerrain();
	PathfinderAttackCoord objPos(*obj->getPosition());
	ICoord2D startIndex;
	Rva002E7875WorldToCell(&startIndex, center, &objPos);
	PathfindCell *parent = rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(), &objPos);
	if (!parent)
		return 0;
	PathfindCell *startCell = parent;
	parent->allocateInfo((In002E6BA1 *)&startIndex);
	parent->StartPathfind(0);
	ICoord2D goalIndex;
	Rva002E7875WorldToCell(&goalIndex, true, victim ? victim->getPosition() : victimPos);
	Int sideOffset = (Int)((Weapon *)weapon)->getAttackDistance(obj, victim, victimPos) - 10;
	AddToOpenList(parent);
	unsigned int count = 0;
	PathfinderSearchCellsVisited = 0;
	PathfindCell *acceptable = 0;
	PathfindCell *closest = 0;
	Int closestOrder = 0;
	Int dx = goalIndex.x - parent->getXIndex();
	Int dy = goalIndex.y - parent->getYIndex();
	float closestDistance = (float)(dx * dx + dy * dy);
	Int acceptableDistance = 9999999;
	closestDistance *= 0.9f;
	while ((parent = rva002F36E5()) != 0)
	{
		PathfinderCellPoint cellCenter = Rva002E8C23Call(center, parent);
		if (hierarchical.path)
		{
			Int order = ((HierarchicalPath *)hierarchical.path)->lookUpPositionOnPath((const Coord3D *)parent->m_pathInfo);
			Int cdx = goalIndex.x - parent->getXIndex();
			Int cdy = goalIndex.y - parent->getYIndex();
			float distance = (float)(cdx * cdx + cdy * cdy);
			if (order > closestOrder || (order == closestOrder && distance < closestDistance))
			{
				closest = parent;
				closestOrder = order;
				closestDistance = distance;
			}
		}
		Int destinationDistance = 0;
		Int cellState = parent->m_pathInfo ? parent->m_pathInfo->state : 0;
		if (!cellState && ((Weapon *)weapon)->isWithinAttackRange(obj, &cellCenter, victim, victimPos, 10.0f, true))
		{
			if (CheckDestination(obj, parent->getXIndex(), parent->getYIndex(), (PathfindLayerEnum)parent->getLayer(), radius, center, &destinationDistance, false))
			{
				Bool blocked = false;
				if (checkLOS)
					blocked = isAttackViewBlockedByObstacle(obj, cellCenter, victim, *victimPos);
				if (startCell == parent)
				{
					blocked = true;
				}
				else
				{
					PathfinderCellPoint pos = Rva002E8C23Call(center, parent);
					float px = pos.x - objPos.x;
					float py = pos.y - objPos.y;
					if (px * px + py * py < 5.0f * 5.0f)
						blocked = true;
				}
				if (!blocked)
				{
					float angle = parent->rva0052DD75(obj->getOrientation(), 10, 0.5f);
					MathCoord2D dir(Cos(angle), Sin(angle));
					MathCoord2D cellWorld(parent->getXIndex() * 10, parent->getYIndex() * 10);
					MathCoord2D goalWorld(goalIndex.x * 10, goalIndex.y * 10);
					if (center)
					{
						cellWorld.x += 5.0f;
						cellWorld.y += 5.0f;
					}
					MathCoord2D v(cellWorld);
					v -= goalWorld;
					v.Normalize();
					_STL::swap(v.x,v.y); v.x=-v.x;
					if (fabs(dir.dot(v)) < 0.85f)
						blocked = true;
				}
				if (!blocked && destinationDistance > 1)
				{
					blocked = true;
					if (destinationDistance < acceptableDistance)
					{
						acceptable = parent;
						acceptableDistance = destinationDistance;
					}
				}
				if (!blocked)
				{
					parent->PutOnClosedList(&m_closedList);
					Path *path = BuildAttackPath(obj, locos, obj->getPosition(), parent, center, false, PathfinderFaceGoalFlag);
					rva002F40E7();
					return path;
				}
			}
		}
		parent->PutOnClosedList(&m_closedList);
		if (count < TheWritableGlobalData->sidewaysAttackLimit)
		{
			CheckChangeLayers(parent, obj);
			count += ExamineNeighboringCellsForSidewaysAttack(parent, &goalIndex, sideOffset, locos, isHuman, center, radius, &startIndex, obj, attackDistance);
		}
	}
	if (acceptable) {
		Path *path = BuildAttackPath(obj, locos, obj->getPosition(), acceptable, center, false, true);
		rva002F40E7();
		return path;
	}
	if (closest) {
		Path *path = BuildAttackPath(obj, locos, obj->getPosition(), closest, center, false, true);
		rva002F40E7();
		return path;
	}
	m_isTunneling = false;
	rva002F40E7();
	return 0;
}
