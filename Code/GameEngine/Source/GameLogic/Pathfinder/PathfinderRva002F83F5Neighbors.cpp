// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// Pathfinder neighbour expansion, retail 0x002F83F5 (1803 bytes, RET 0x24); address-named, with Zero Hour
// examineNeighboringCells and WorldBuilder D5BBE0 as semantic guides. Select-any copies of the rowed callees
// that receive local addresses stay visible, so cl keeps those locals unaliased as retail's frame requires.
// stlport
#include <vector>
typedef bool Bool;
typedef int Int;
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
struct PathfinderTemplateView
{
public:
	__forceinline bool hasKind(int bit) const
	{
	 return (kinds[bit/8] & (1<<(bit%8)))!=0;
	}
	__forceinline const char *name() const
	{
	 return nameBuffer ? nameBuffer+8 : "";
	}
	__forceinline unsigned testKindWord(unsigned bit)const{return ((const unsigned*)kinds)[bit>>5]&(1U<<(bit&31));}
	char m_pad00[0x64];
	char *nameBuffer; // +0x64
	char m_pad68[0xA0];
	unsigned char kinds[24]; // +0x108
	char m_pad120[0x44C];
	Int priority; // +0x56C
	char m_pad570[0xC4];
	Bool flag; // +0x634
	char m_pad635[0x3];
};
enum Relationship { ENEMIES=0, NEUTRAL=1, ALLIES=2 };
class Object
{
public:
Player *getControllingPlayer() const;
Relationship getRelationship(const Object *) const;
bool IsAtGoalPosition() const;
bool rva0028AFBB() const;
Bool canCrushOrSquishNoAlly(Object *,Int);
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
class GlobalData
{
public:
	char prefix[0x9b8]; // +0x00
	int m_flag9B8; // +0x9B8
	char m_pad9BC[0x804];
	unsigned int limitMs; // +0x11C0
	char m_pad11C4[0x24];
	int cellsPerFrame; // +0x11E8
	char m_pad11EC[0xC];
	int m_maxCellsAdjustTargetDestination; // +0x11F8
	char m_pad11FC[0x20];
	unsigned callbackLimit; // +0x121C
};
extern GlobalData *TheWritableGlobalData;
#include <math.h>
struct PathfinderCostCellInfo { Int x,y; };
class Waypoint;
struct PathfinderGroundInfo
{
public:
	PathfinderCostCellInfo position; // +0x00
	Int parent; // +0x08
	Waypoint *parentWaypoint; // +0x0C
	unsigned short totalCost; // +0x10
	unsigned short costSoFar; // +0x12
	char m_pad14[0x14];
	Int obstacleID; // +0x28
	unsigned int flags; // +0x2C
};
struct In002E6BA1 { Int x,y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,Int,In002E6BA1 *);
class Rva002E6AF3
{
public:
	int get() const;
};
class Rva002E6B06
{
public:
	int rva002E6B06();
};
class Rva002E6C79;
struct Rva002E8BCFSrc;
class Rva002E8BCF { public: Rva002E8BCF(){} Rva002E8BCF(const Rva002E8BCFSrc *,Bool,Int,Bool); Int surfaces;Bool field4,field5;Int maxLayer;Bool fieldC; };
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
	char m_pad00[0x48];
private:
	void *m_48; // +0x48
};

void ji_00629952();
class PathfindCell
{
friend class Pathfinder;friend struct Rva002F5925Info;
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
else m_pathInfo->parentWaypoint=0;
}
void rva0052DAE9(Bool open);
Int getXIndex() const { return m_pathInfo->position.x; }
Int getYIndex() const { return m_pathInfo->position.y; }
float rva0052DD75(float facing, Int count, float weight);
CellType getType() const { return (CellType)(m_info & 0xf); }
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
	LocomotorSurfaceTypeMask getLegalSurfaces() const
	{
	 return m_template->m_surfaces;
	}
	float getMaxSpeed(Object *obj) const;
private:
	void *m_vtbl; // +0x00
	const LocomotorTemplate *m_template; // +0x04
};

extern unsigned int g_00DBD33C[16];

#include <math.h>
float Sin(float x);
float Cos(float x);

// REAL_TO_INT_FLOOR: the IAT floor then an x87 round-to-integer store.
static __forceinline Int realToIntFloor(float f)
{
float floored = floor(f);
long i;
__asm {
fld [floored]
fistp [i]
}
return i;
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
	bool rva002CB35C(int p1, void *p2, void *p3, void *p4, float p5, int p6);
};

class Rva002C9400ByteField
{
public:
unsigned char get() const;
};
class Rva002C9B80Owner
{
public:
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
	bool rva0036736E(bool flag);
	char m_pad00[0x34];
	int m_a34; // +0x34
	int m_b38; // +0x38
};

struct IRegion2D;
class Xfer;
class PathfindLayer
{
public:
	void ClassifyWallCells();
	void ClassifyBridgeCells();
	void allocateCells(const IRegion2D *extent);
	__declspec(noinline) void rva000B3FD0();
	bool setDestroyed(bool destroyed);
	void rva003666FD(Xfer *xfer);
	void rva00366DEC();
	PathfindCell *getCell(int,int);
private:
	char storage[0x40]; // +0x00
};

class PathfindZoneManager
{
public:
void rva00531481();
void rva005314C6(Int x, Int y, unsigned char flag);
unsigned char IsPassable(Int,Int);
};

struct Rva002EBC7FPair
{
public:
	int x; // +0x00
	int y; // +0x04
};
struct PathfinderCellPoint;
// Rowed 0x002E79A8 returns its cell point through the hidden first argument; this caller
// forwards that buffer, so it calls the rowed symbol through the five-slot cdecl view.
PathfinderCellPoint __cdecl rva002E79A8(bool, int, int, PathfindLayerEnum);
typedef void (__cdecl *Rva002E79A8View)(int, unsigned char, int, int, int);
__declspec(noinline) inline void *rva002EBC7F(void *a1, void *a2, Rva002EBC7FPair *a3, int a4)
{
	((Rva002E79A8View)&rva002E79A8)((int)a1, Rva002EBBFBIsOdd(a2), a3->x, a3->y, a4);
	return a1;
}
#include <math.h>
class AIUpdateInterface {
public:
Object *getCurrentVictim() const;
bool isAircraftThatAdjustsDestination() const;
int rva0026417F(bool);
char gap[0x1f0];
Locomotor *locomotor;
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
struct ICoord2DBase
{
public:
	int x; // +0x00
	int y; // +0x04
};
class Rva002E9D09
{
public:
	int rva002E9D09(Object *a1, int a2, int a3);
private:
	Rva002E6DC4 *m_check0; // +0x00
	Object *m_holder4; // +0x04
	int *m_counter8; // +0x08
	bool m_cC; // +0x0C
	char m_pad0D[0x3];
	int m_10; // +0x10
	bool m_14; // +0x14
	char m_pad15[0x3];
	Rva002E8BCFSrc *m_18; // +0x18
};
class Rva002E7C99
{
public:
	void *rva002E7C99(int a, int b, int c, unsigned char d, int e, unsigned char f, int g);
private:
	int m_00; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	unsigned char m_0C; // +0x0C
	unsigned char m_0D[3]; // +0x0D
	int m_10; // +0x10
	unsigned char m_14; // +0x14
	unsigned char m_15[3]; // +0x15
	int m_18; // +0x18
};
class Rva0006E009DwordField
{
public:
	int get()const;
};
class Rva0052DB4D
{
public:
	Bool rva0052DB4D(Int);
};
union PathfinderCheckCoordinates {
Coord3D point;
struct IntegerLayout { int reserved; ICoord2DBase position,size; } cells;
};
struct PathfinderLogFile;
#include <stdio.h>
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;

#include "Lib/ICoord2D.h"
struct TCheckMovementInfo { ICoord2D cell;PathfindLayerEnum layer;Int radius;Bool centerInCell,considerTransient;char pad12[2];Int options,ignore;Rva002E8BCF movement;Int allyFixedCount;Bool flag30,flag31,allyGoal;char pad33;Int blockedCells; };
class Rva002E6FDF
{
public:
	Rva002E6FDF *rva002E6FDF();
	int m_00; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	unsigned char m_10; // +0x10
	unsigned char m_11; // +0x11
	char m_pad12[0x2];
	int m_14; // +0x14
	int m_18; // +0x18
	int m_1C; // +0x1C
	unsigned char m_20; // +0x20
	unsigned char m_21; // +0x21
	char m_pad22[0x2];
	int m_24; // +0x24
	unsigned char m_28; // +0x28
	char m_pad29[0x3];
	int m_2C; // +0x2C
	unsigned char m_30; // +0x30
	unsigned char m_31; // +0x31
	unsigned char m_32; // +0x32
	char m_pad33[0x1];
	int m_34; // +0x34
};
class Rva002EAB6F {public:Rva002EAB6F(Int,const Rva002E8BCFSrc *,unsigned char,Int,Object *,unsigned char,Int,Int);int m0;Rva002E8BCF m4;unsigned char m14,m15;int m18;Object*m1C;int m20,m24;char pad28[8];int m30;};
struct Rva002F5925Info;
struct BurningCell {char pad[6];unsigned short count;char pad8[12];};
struct BurningGrid {char pad[0x70];BurningCell **cells;char word74[4];Int width,height;};
class Rva002872BA;extern Rva002872BA *TheTriggerManager;
Int isGroundOrBridgeLayer(Int);
class Rva002F6F90Context { public: Bool rva002F6F90(unsigned int,Int); };
class Rva002F70E5Context { public: Bool rva002F70E5(unsigned int,Int); };
class Rva002E7440 { public: Bool rva002E7440(Int,Int); };
class Rva002E7414 { public: Int rva002E7414(Int,Int); };
class Rva002F336AOwner
{
public:
	bool rva002F336A(int,int);
private:
	Pathfinder *pf; // +0x00
	void *object; // +0x04
	unsigned char mode; // +0x08
	char m_pad09[0x3];
	void *radius; // +0x0C
	Coord3D *out; // +0x10
	void *target; // +0x14
	void *targetPosition; // +0x18
	Rva002CB35CObj *weapon; // +0x1C
};
class Pathfinder
{
friend struct Rva002F5925Info;
public:
Int rva002F83F5(PathfindCell *,PathfindCell *,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
Bool rva002EA658(Object *,TCheckMovementInfo &,const ICoord2D *);

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
Int m_mapLowX,m_mapLowY,m_mapHighX,m_mapHighY;
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
_STL::vector<Rva002F35AFHop> m_1C1CC;	// +0x1C1CC
};

__declspec(noinline) inline int Pathfinder::CalcExtraCosts(Object *object,PathfindCell *oldCell,Rva002EBC7FPair *destination,int lower,int upper,bool ignoreEnemies)
{
if (!oldCell) return 0;
Rva002EBC7FPair minimum,maximum;
minimum.x=destination->x-lower; minimum.y=destination->y-lower;
maximum.x=destination->x+upper; maximum.y=destination->y+upper;
int &reduction=upper;
reduction=0;
if (lower>=4) reduction=2;
else if (lower>1) reduction=1;
float ourArrival=-1.0f;
int &cost=lower;
cost=0;
for (int x=minimum.x;x<maximum.x;++x) {
for (int y=minimum.y;y<maximum.y;++y) {
PathCollisionCell *cell=reinterpret_cast<PathCollisionCell *>(getCell(static_cast<PathfindLayerEnum>(oldCell->getLayer()),x,y));
if (!cell || !cell->info) continue;
for (PathCollisionNode *node=cell->info->occupants;node;node=node->next) {
Object *other=node->object;
if (other==object || other->container==object) continue;
bool enemies=object->getRelationship(other)==ENEMIES;
if (enemies && ignoreEnemies) continue;
if (!object->getAI() || !other->getAI()) continue;
if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))>static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) continue;
int amount;
if (other->IsAtGoalPosition() || !object->getAI()->locomotor || !other->getAI()->locomotor) amount=8;
else {
Coord3D target;
rva002EBC7F(&target,object,destination,1);
if (ourArrival<0.0f) {
float dx=object->position[0]-target.x;
float dy=object->position[1]-target.y;
Locomotor *locomotor=object->getAI()->locomotor;
float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
ourArrival=distance/locomotor->getMaxSpeed(object);
}
float dx=other->position[0]-target.x;
float dy=other->position[1]-target.y;
Locomotor *locomotor=other->getAI()->locomotor;
float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
float otherArrival=distance/locomotor->getMaxSpeed(other);
if (!(otherArrival<ourArrival)) continue;
amount=4;
}
cost+=amount>>reduction;
}
}
}
return cost;
}

struct Rva002EBCF6 : GeometryShape { Rva002EBCF6(); };

struct PathfinderDebugColor { float red,green,blue; };
void Rva000B3FD0PathDebug(const Coord3D *,float,Int,PathfinderDebugColor);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
__declspec(noinline) inline Rva002E6FDF *Rva002E6FDF::rva002E6FDF()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_11 = 0;
	m_14 = 0;
	m_18 = 0;
	_ReadWriteBarrier();
	m_24 = -1;
	m_1C = 0;
	m_20 = 0;
	m_21 = 0;
	m_28 = 0;
	m_2C = 0;
	m_31 = 0;
	m_32 = 0;
	m_30 = 0;
	m_34 = 0;
	return this;
}

struct Rva002E6DC4_P1
{
	unsigned int m_0;
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	int m_8;
	unsigned char m_C;
};
struct Rva002E6DC4_P2Inner
{
	char m_pad[0x28];
	void *m_28;
};
struct Rva002E6DC4_P2
{
	Rva002E6DC4_P2Inner *m_0;
	char m_pad4[8];
	unsigned int m_C;
};
__declspec(noinline) inline bool Rva002E6DC4::rva002E6DC4(void *a_raw, void *b_raw)
{
	Rva002E6DC4_P1 *a = (Rva002E6DC4_P1 *)a_raw;
	Rva002E6DC4_P2 *b = (Rva002E6DC4_P2 *)b_raw;
	if (!b)
		return false;
	unsigned int flags = b->m_C;
	unsigned char b18 = (unsigned char)(flags >> 18);
	if ((b18 & 1) != 0 && a->m_5 != 0)
		return false;
	unsigned int low = flags & 0xF;
	switch (low) {
	case 3:
		if ((flags & 0x3F0) != 0x10)
			return false;
		break;
	case 4: {
		void *chase = b->m_0 ? b->m_0->m_28 : 0;
		if (chase == m_48)
			return true;
		break;
	}
	default:
		break;
	}
	if ((a->m_0 & g_00DBD33C[low]) == 0)
		return false;
	unsigned char b17 = (unsigned char)(flags >> 17);
	if (a->m_4 != 0 && (b17 & 1) != 0)
		return false;
	if (a->m_C != 0) {
		unsigned char b22 = (unsigned char)(flags >> 22);
		if (((b22 & 1) == 0) && low == 4)
			return false;
	}
	int v = a->m_8;
	if (v < 0 || (int)((flags >> 19) & 3) <= v)
		return true;
	return false;
}

static __forceinline Bool nativeBurning(BurningGrid *grid,const Coord3D &point){Int fireX=realToIntFloor((point.x+0.5f)*0.1f);Int fireY=realToIntFloor((point.y+0.5f)*0.1f);if(fireX>=0 && fireX<grid->width && fireY>=0 && fireY<grid->height)return grid->cells[fireX][fireY].count>0;return false;}
class StateMachine
{
public:
	Object *getGoalObject();
};
struct CheckMovementAIView
{
	unsigned char m_pad00[0x30];
	StateMachine *m_stateMachine;	// +0x30
};
struct CheckMovementObjectNode
{
	CheckMovementObjectNode *m_next;
	int m_04;
	Object *m_object;	// +0x08
};
struct CheckMovementCellInfo
{
	unsigned char m_pad00[0x14];
	int m_14;
	unsigned char m_pad18[0x20 - 0x18];
	CheckMovementObjectNode *m_objects;	// +0x20
};
struct CheckMovementCell
{
	Int getType() const { return m_flags & 0xf; }
	Int getLayer() const { return (m_flags >> 4) & 0x3f; }
	Bool rvaBit18() const { return (Bool)((m_flags >> 18) & 1); }
	Bool rvaInfo14() const { return m_info ? m_info->m_14 != 0 : false; }
	Bool hasObjects() const { return m_info ? m_info->m_objects != 0 : false; }
	CheckMovementObjectNode *getObjects() const { return m_info ? m_info->m_objects : 0; }

	CheckMovementCellInfo *m_info;
	unsigned char m_pad04[0x0C - 0x04];
	unsigned int m_flags;	// +0x0C
};
static __forceinline void checkCellFlags(Pathfinder *pf, Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info)
{
	if (cell->getType() == 5)
		info.blockedCells++;
	if (cell->rvaBit18() && obj->rva0028AFBB())
		info.blockedCells++;
	if (info.options & 8)
	{
		Int layer = cell->getLayer();
		if (info.layer != layer)
		{
			if (info.layer == 1 && layer != 0x10)
				info.blockedCells++;
			else if ((unsigned char)Rva002E6E8AGet(info.layer) && layer != 0x10)
				info.blockedCells++;
		}
	}
	if ((info.options & 4) && !((Rva002E6DC4 *)pf)->rva002E6DC4(&info.movement, cell))
		info.blockedCells++;
}

static __forceinline Bool checkPairCellUnits(Object *&obj, CheckMovementCell *cell, TCheckMovementInfo &info, Int *lastID)
	{
		if (cell->rvaInfo14())
			info.allyGoal = true;

		for (CheckMovementObjectNode *node = cell->getObjects(); node; node = node->m_next)
		{
			Object *unit = node->m_object;
			if (unit == obj || unit->getID() == info.ignore || unit->getID() == *lastID) continue;
			*lastID = (Int)unit->getID();

			Bool check = false;
			Bool isAlly;
			unsigned occupied=cell->hasObjects();
			Object *owner=obj;
			if (occupied)
			{
				isAlly = owner->getRelationship(unit) == ALLIES;
				if (isAlly)
					info.flag31 = true;
				if (info.considerTransient)
					check = true;
				if (!isAlly && (info.options & 0x10))
					check = true;
			}
			if (unit->IsAtGoalPosition())
			{
				isAlly = owner->getRelationship(unit) == ALLIES;
				check = true;
			}
			if (!check)
				continue;

			if (isAlly && owner->m_template->testKindWord(0x74) && unit->m_template->testKindWord(0x74))
				continue;
			if (owner->m_template->testKindWord(0x7D) && unit->m_template->testKindWord(8))
				continue;
			if (isAlly && owner->m_template->testKindWord(0xBA) && !unit->m_template->testKindWord(0xBA))
			{
				info.allyGoal = false;
				continue;
			}
			if (owner->m_template->testKindWord(0xBB))
			{
				info.allyGoal = false;
				continue;
			}

			if (isAlly)
			{
				if (!unit->getAI())
					return false;
				if (info.options & 2)
					return false;
				info.allyFixedCount = 1;
				if (unit->m_template->testKindWord(0xBA) && !owner->m_template->testKindWord(0xBA))
					return false;
				continue;
			}

			if (owner->canCrushOrSquishNoAlly(unit, 2))
				continue;
			if (!(info.options & 0x11))
				continue;
			AIUpdateInterface *ai = obj->getAI();
			if (!ai)
				return false;
			Object *goal = ((CheckMovementAIView*)ai)->m_stateMachine->getGoalObject();
			if (goal)
			{
				if (unit == goal || unit->container == goal)
					continue;
				goal = goal->container;
				if (goal && (unit == goal || unit->container == goal))
					continue;
			}
			Object *victim = ai->getCurrentVictim();
			if (!victim)
				return false;
			if (unit == victim || unit->container == victim)
				continue;
			victim = victim->container;
			if (!victim)
				return false;
			if (unit == victim || unit->container == victim)
				continue;
			return false;
		}
		return true;
	}
__declspec(noinline) inline Bool Pathfinder::rva002EA658(Object *obj, TCheckMovementInfo &info, const ICoord2D *otherCell)
{
	info.allyFixedCount = 0;
	info.flag31 = false;
	info.allyGoal = false;
	info.flag30 = false;
	info.blockedCells = 0;

	Int numCellsAbove = info.radius;
	if (info.centerInCell)
		numCellsAbove++;

	Int lastID = (Int)0;
	for (Int i = info.cell.x - info.radius; i < info.cell.x + numCellsAbove; i++)
	{
		Bool inOtherX = i >= otherCell->x - info.radius && i < otherCell->x + numCellsAbove;
		for (Int j = info.cell.y - info.radius; j < info.cell.y + numCellsAbove; j++)
		{
			CheckMovementCell *cell = (CheckMovementCell*)getCell(info.layer, i, j);
			if (!cell)
				return false;
			if (inOtherX && j >= otherCell->y - info.radius && j < otherCell->y + numCellsAbove)
			{
				checkCellFlags(this,obj, cell, info);
			}
			else
			{
				checkCellFlags(this,obj,cell,info);
				if (!checkPairCellUnits(obj, cell, info, &lastID))
					return false;
			}
		}
	}
	return true;
}

#include <string.h>
#pragma intrinsic(memset)
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

class MixFileInfoBuffer
{
private:
	friend class Rva002E6BA1;
public:
	friend MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in);
private:
	void bfmeUnlink();
public:
	int x; // +0x00
	int y; // +0x04
	char m_pad08[0x4];
	Int m_0C; // +0x0C
	unsigned short m_totalCost; // +0x10
	unsigned short m_costSoFar; // +0x12
	char m_pad14[0x18];
	unsigned int m_flags; // +0x2C
};

// Rehomed 0x002E8B7A (33 B), original Rva002E8B7AInit.cpp: takes the pool
// head, unlinks it (0x002E6BE2) and initializes it for the cell (0x002E6BA1).
__declspec(noinline) inline void Rva002E6BA1::rva002E6BA1(int a, In002E6BA1 *b)
{
	m_30 = a;
	m_00 = b->x;
	m_04 = b->y;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_12 = 0;
	memset(m_14, 0, 20);
	m_2C &= 0xffffffe0;
	m_28 = 0;
	++TheMixFileInfoCount;
}
__declspec(noinline) inline MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int a, In002E6BA1 *in)
{
	MixFileInfoBuffer *node = *pp;
	node->bfmeUnlink();
	((Rva002E6BA1 *)node)->rva002E6BA1(a, in);
	return node;
}

struct Rva002E8BCFSrc{char pad[0x10];int m10;char m14;bool m15;};
struct Rva002F5925Info
{
public:
	int cellCallback(PathfindCell*,PathfindCell*,int,int);
	Pathfinder *pathfinder; // +0x00
	char data4[16]; // +0x04
	bool center; // +0x14
	bool human; // +0x15
	char m_pad16[0x2];
	int radius; // +0x18
	Object *object; // +0x1C
	PathfindCell *goal; // +0x20
	int ignoreID; // +0x24
	ICoord2D previous; // +0x28
	int range; // +0x30
};
extern unsigned PathfinderSearchCellsVisited;
__declspec(noinline) inline Int Pathfinder::iterateCellsAlongLine( const ICoord2D *startCell, 
	const ICoord2D *destinationCell, PathfindLayerEnum layer, 
	Rva002F5925Info *callbackInfo ) 
{ 
	Int delta_x = abs( destinationCell->x - startCell->x ); 
	Int delta_y = abs( destinationCell->y - startCell->y ); 
 
	Int xinc2, yinc1, xinc1, numpixels, numadd, den; 
	Int yinc2, num; 
	if (delta_x >= delta_y) 
	{ 
		numpixels = delta_x + 1; 
		num = 2 * delta_y - delta_x; 
		numadd = delta_y << 1; 
		den = 2 * (delta_y - delta_x); 
		xinc2 = 1; 
		yinc2 = 0; 
		yinc1 = 1; 
		xinc1 = 1; 
	} 
	else 
	{ 
		numpixels = delta_y + 1; 
		num = 2 * delta_x - delta_y; 
		numadd = delta_x << 1; 
		den = 2 * (delta_x - delta_y); 
		yinc2 = 1; 
		xinc2 = 0; 
		yinc1 = 1; 
		xinc1 = 1; 
	} 
 
	if (startCell->x > destinationCell->x) 
	{ 
		xinc2 = -xinc2; 
		xinc1 = -1; 
	} 
	if (startCell->y > destinationCell->y) 
	{ 
		yinc2 = -yinc2; 
		yinc1 = -1; 
	} 
 
	Int x = startCell->x; 
	Int y = startCell->y; 
	PathfindCell *previousCell = 0; 
	for (Int curpixel = 0; curpixel < numpixels; curpixel++) 
	{ 
		PathfindCell *currentCell = getCell( layer, x, y ); 
		if (currentCell == 0) 
			return 0; 
 
		Int ret = callbackInfo->cellCallback( previousCell, currentCell, x, y ); 
		if (ret != 0) 
			return ret; 
		previousCell = currentCell; 
 
		if (num < 0) 
		{ 
			num += numadd; 
			x += xinc2; 
			y += yinc2; 
		} 
		else 
		{ 
			num += den; 
			x += xinc1; 
			y += yinc1; 
		} 
	} 
	return 0; 
}

struct NeighborWorldPoint:Coord3D {NeighborWorldPoint(){} ~NeighborWorldPoint(){}};
__declspec(noinline) inline Int Pathfinder::rva002F83F5(PathfindCell *parentCell,PathfindCell *goalCell,const LocomotorSet &locomotorSet,Bool isHuman,Bool centerInCell,Int radius,ICoord2D *startCellNdx,Object *obj,Int attackMode)
{
if(obj->m_template->hasKind(109)||obj->m_template->hasKind(191)){radius=1;centerInCell=true;}
Bool canPathThroughUnits=false;
if(obj->getAI())canPathThroughUnits=*(Bool *)((char *)obj->getAI()+0x3ba);
if(!m_isTunneling && !locomotorSet.isDownhillOnly() && goalCell && !(parentCell->getXIndex()&3) && !(parentCell->getYIndex()&3)) {
const ICoord2D *start=(const ICoord2D *)parentCell->m_pathInfo;
ICoord2D end; if(m_1C1CC.empty()){end=*(const ICoord2D*)goalCell->m_pathInfo;}else{end=*(const ICoord2D*)&m_1C1CC.back().m_position;}PathfindLayerEnum layer=(PathfindLayerEnum)parentCell->getLayer();
iterateCellsAlongLine(start,&end,layer,(Rva002F5925Info *)&Rva002EAB6F((Int)this,(const Rva002E8BCFSrc *)&locomotorSet,centerInCell,radius,obj,isHuman,(Int)goalCell,m_1C1CC.empty()?attackMode:0));
}
{
Int cellCount=0;
TCheckMovementInfo info;((Rva002E6FDF *)&info)->rva002E6FDF();
info.layer=(PathfindLayerEnum)parentCell->getLayer();info.centerInCell=centerInCell;info.radius=radius;
info.options=12;if(!obj->m_template->hasKind(90))info.options|=16;
info.ignore=obj->getAI()?((Rva0006E009DwordField *)obj->getAI())->get():0;
info.considerTransient=true;Int priority=obj->m_template->priority;Bool flag=obj->m_template->flag;
info.movement=Rva002E8BCF((const Rva002E8BCFSrc *)&locomotorSet,!flag,priority-1,obj->rva0028AFBB());
// expand search to neighboring orthogonal cells
static Int deltaX[]={1,0,-1,0,1,-1,-1,1};static Int deltaY[]={0,1,0,-1,1,1,-1,-1};
Bool storage[8];Bool (&neighborFlags)[8]=storage;
for(Int i=0;i<8;++i) {
neighborFlags[i]=false;
// determine neighbor cell to try
Int x=parentCell->getXIndex()+deltaX[i],y=parentCell->getYIndex()+deltaY[i];ICoord2D coords={x,y};
// get the neighboring cell
PathfindCell *newCell=getCell((PathfindLayerEnum)parentCell->getLayer(),x,y);
// check if cell is on the map
if(!newCell)continue;
// check if this neighbor cell is already on the open (waiting to be tried)
// or closed (already tried) lists
if((unsigned char)((Rva002E6B06 *)newCell)->rva002E6B06() || (unsigned char)((Rva002E6AF3 *)newCell)->get())continue;
if(newCell->getLayer()!=parentCell->getLayer() && !(info.movement.surfaces&64) && newCell->getLayer()!=((parentCell->m_info>>10)&63) && ((newCell->m_info>>10)&63)!=parentCell->getLayer() && (((parentCell->m_info>>10)&63)!=16 || ((newCell->m_info>>10)&63)!=((parentCell->m_info>>10)&63)))continue;
if(isHuman){
// check if new cell is in logical map.	(computer can move off logical map)
if(x<m_extentLowX)continue;if(y<m_extentLowY)continue;if(x>m_extentHighX)continue;if(y>m_extentHighY)continue;}
// make sure one of the adjacent sides is open.
if(i>=4 && !neighborFlags[i&3] && !neighborFlags[(i+1)&3])continue;
// do the gravity check here
if(locomotorSet.isDownhillOnly()) {
NeighborWorldPoint fromPoint;fromPoint.x=(float)(parentCell->getXIndex()*10);fromPoint.y=(float)(parentCell->getYIndex()*10);fromPoint.z=TheTerrainLogic->getGroundHeight(fromPoint.x,fromPoint.y,0);
NeighborWorldPoint toPoint;toPoint.x=(float)(x*10);toPoint.y=(float)(y*10);toPoint.z=TheTerrainLogic->getGroundHeight(toPoint.x,toPoint.y,0);
if(fromPoint.z<toPoint.z)continue;
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
} else {
//Note to self - only turn off tunneling after check for movement.jba. 
if(movementValid)m_isTunneling=false;}
if(!newCell->m_pathInfo)++cellCount;
newCell->allocateInfo((In002E6BA1 *)&coords);
unsigned int newCostSoFar=0;
Int dx=goalCell?abs(x-goalCell->getXIndex()):3;
Int dy=goalCell?abs(y-goalCell->getYIndex()):3;
if(newCell->getType()==2 && !(unsigned char)(newCell->m_info>>16&1)) {
NeighborWorldPoint fromPoint;fromPoint.x=(float)(parentCell->getXIndex()*10);fromPoint.y=(float)(parentCell->getYIndex()*10);fromPoint.z=TheTerrainLogic->getGroundHeight(fromPoint.x,fromPoint.y,0);
NeighborWorldPoint toPoint;toPoint.x=(float)(x*10);toPoint.y=(float)(y*10);toPoint.z=TheTerrainLogic->getGroundHeight(toPoint.x,toPoint.y,0);
if(fabs(fromPoint.z-toPoint.z)<10.0f)newCostSoFar=98;
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
Coord3D point;point.x=(float)(x*10);point.y=(float)(y*10);Bool burning=nativeBurning((BurningGrid*)TheTriggerManager,point);
if(burning)newCostSoFar+=10;
newCell->m_pathInfo->costSoFar=(unsigned short)newCostSoFar;
// keep track of path we're building - point back to cell we moved here from
newCell->SetParentCell((Int *)parentCell);
if(m_isTunneling)remaining=0; // find the closest valid cell.
newCell->m_pathInfo->totalCost=(unsigned short)(newCell->m_pathInfo->costSoFar+remaining);
AddToOpenList(newCell);
}
return cellCount;
}
}

// ?bfmeAnchorRva002F83F5 absent-from-retail
Int bfmeAnchorRva002F83F5(Pathfinder *p,PathfindCell *a,PathfindCell *b,const LocomotorSet &l,Bool h,Bool c,Int r,ICoord2D *s,Object *o,Int m){return p->rva002F83F5(a,b,l,h,c,r,s,o,m);}
