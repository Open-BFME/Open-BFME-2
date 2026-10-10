// ?rva002F14F9@Pathfinder@@QAEPAVObject@@PAV2@0@Z
// partial score=0.884140089824434 date=2026-10-10
// ?rva002F14F9@Pathfinder@@QAEPAVObject@@PAV2@0@Z
// cl: /I. /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// wb-lead 2.000 callgraph: Pathfinder::SetBridgeStateRepaired at 0x002E7205.
// Identity evidence: the GeneralsMD AIPathfind.cpp implementation
// Pathfinder::changeBridgeState checks the selected layer, sets its destroyed
// state to the inverse of repaired, then dirties zones with the repaired flag.
// GeneralsMD BridgeBehavior calls that method on bridge damage and repair.
// Target call sites resolve to rowed Rva0036666B at 0x0036666B, unrowed callee
// 0x0036736E and rowed PathfindZoneManager::rva00531481 at 0x00531481. The unrowed
// callee pin is supported by its selected-layer callsite and the GeneralsMD
// PathfindLayer::setDestroyed(Bool) donor. Target arithmetic gives 64-byte
// layers at +0x60 and the final manager-like subobject at +0x460.
#include <vector>
#include <new>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
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
// Relationship order is established by the rowed Object::getRelationship.
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
enum ObjectStatusTypes { QuickStatus49=49 };
class Weapon;enum WeaponSlotType { WEAPONSLOT_PRIMARY=0 };
class Object
{
public:
	Player *getControllingPlayer() const;
 Object *rva002931F5(bool);
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
 void *rva0028C1A9() const;
 float rva00263763(const void *) const;
 bool rva0028F518();
 Bool testStatus(ObjectStatusTypes) const;
	Relationship getRelationship(const Object *) const;
    int rva0028B511() const;
    bool rva002E6B89();
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
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};
struct Rva002E7ED6Info;
class Pathfinder;
// Native aircraft-path node ABI agrees with the rowed ctor and prepend provider.
class PathNode {
public:
    PathNode(const Coord3D *,PathfindLayerEnum) throw();
    PathNode *next,*previous,*nextOptimized;
    Coord3D position;
    PathfindLayerEnum layer;
    Bool canOptimize;
    Int portalID;
};
struct Rva002EDEABArg;
struct Rva002E93A7Info
{
	Pathfinder *m_00;
	Int m_04;
};
class Waypoint { public: Int word0,id;void *name;Coord3D location;char pad18[0x44-0x18];Waypoint *chainNext;Int word48,linkCount; };
class PathfindCell;
class Path
{
 friend class Pathfinder;
public:
 void rva00265596(const Coord3D *,PathfindLayerEnum,Int);
	Path();										///< matched 0x00363DC8
	// 0x00364551 / 0x00365E98 (unrowed): Zero Hour's optimize step with a
	// BFME facing hint, and a final pass toward a direction (unnamed).
	void rva00364551(Object *obj, LocomotorSurfaceTypeMask surfaces, Bool blocked, const float *facing);
	void rva00365E98(Object *obj, const Coord3D *dir, LocomotorSurfaceTypeMask surfaces, Bool blocked);
private:
	void *word0;PathNode *firstNode;Int word8;char wordC;Bool blockedByAlly;char padE[0x28-0xe];
};

struct Rva002E8C23Pair { Int x,y; };
int __cdecl Rva002E8C4DCall(int,unsigned char,Rva002E8C23Pair *,int);
bool Rva002EBBFBIsOdd(void *);
struct ICoord2D;
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
extern "C" double __cdecl fabs(double);
struct PathfinderCostCellInfo { Int x,y; };
struct PathfinderGroundInfo { PathfinderCostCellInfo position;Int parent;Waypoint *parentWaypoint;unsigned short totalCost,costSoFar;char pad14[0x2c-0x14];unsigned int flags; };
struct In002E6BA1 { Int x,y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,Int,In002E6BA1 *);
class Rva002E6AF3 { public: Int get() const; };
class Rva002E6B06 { public: Int rva002E6B06(); };
class Rva002E6C79;
struct Rva002E8BCFSrc;
class Rva002E8BCF { public: Rva002E8BCF(const Rva002E8BCFSrc *,Bool,Int,Bool); Int surfaces;Bool field4,field5;Int maxLayer;Bool fieldC; };
class Rva002E6DC4 { public: Bool rva002E6DC4(void *,void *); };

void ji_00629952();
struct Rva002F35AFCell;
class Rva002E6C79
{
public:
	Int rva002E6C79();
	Rva002F35AFCell *m_00;
	Rva002E6C79 *next() { return (Rva002E6C79 *)rva002E6C79(); }
};
class PathfindCell
{
 friend class Pathfinder;
public:
	// The packed cell word at +0x0C: type in bits 0-3, layer in bits 4-9.
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
	unsigned short quickZone()const {return (unsigned short)word8;}
 Int getXIndex() const { return m_pathInfo->position.x; }
	Int getYIndex() const { return m_pathInfo->position.y; }
	// 0x0052DD75 (unrowed): an angle for the cell from a facing, a count and
	// a weight (unnamed).
	float rva0052DD75(float facing, Int count, float weight);
	CellType getType() const { return (CellType)(m_info & 0xf); }
	Int getLayer() const { return (m_info & 0x3f0) >> 4; }
 PathfindCell *getParentCell(){return (PathfindCell *)((Rva002E6C79 *)this)->rva002E6C79();}
 Waypoint *getParentWaypoint()const {return m_pathInfo?m_pathInfo->parentWaypoint:0;}

private:
	PathfinderGroundInfo *m_pathInfo;
	Waypoint *waypoint;Int word8;
	unsigned int m_info;			// +0x0C
};

// A locomotor's legal surfaces live in its template (+0x04) at +0x14.
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

// The surfaces each cell type allows, indexed by type (VA 0x00DBD33C,
// defined in Rva002E6DC4Check.cpp).
extern unsigned int g_00DBD33C[16];

extern "C" __declspec(dllimport) double __cdecl floor(double);
float Sin(float x);
float Cos(float x);

// REAL_TO_INT_FLOOR: the IAT floor then an x87 round-to-integer store.
static __forceinline Int realToIntFloor(float f)
{
	float floored = (float)floor((double)f);
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

// The per-object radius/centre split (rowed 0x002EBCA7).
void Rva002EBCA7Split(void *obj, Int *radius, unsigned char *center);
struct Rva002F600CInfo;

// Coord3D::set(const Coord3D *) as Zero Hour's header defines it inline.
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

// Pathfinder_FuncTightenPath (0x34 bytes): WorldBuilder's functor for
// TightenPath's line walk, Zero Hour's TightenPathStruct plus the goal.
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

// Pathfinder_IsCheckForAdjust (0x3C bytes): WorldBuilder's functor for the
// destination-adjust check; Zero Hour's checkForAdjust info plus the goal,
// an optional second position whose layer wins, a float and a word.
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

// Pathfinder_IsCheckForMeleeHordeAdjust (0x34 bytes): WorldBuilder's functor
// for the melee/horde destination check; Zero Hour's checkForAdjust info
// (isHuman, radius/centre, layer) plus a float and the goal.
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

// The rowed cell-centre helper 0x002EBC59 (returns its out Coord3D) and the
// pinned 0x002CB35C range probe (WorldBuilder: Weapon::isWithinAttackRange).
void *rva002EBC59(void *out, void *obj, Int a2, Int a3, Int a4);
class Rva002CB35CObj
{
public:
	Bool rva002CB35C(Int a1, void *pos, void *a3, void *a4, float range, Int a6);
};

// CanApproachToTarget's helpers. The rowed 0x002C9B80 range query returns a
// float; its +0x04 member answers the rowed byte getter 0x002C9400.
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
// The 0x24-byte cell-query functor (rowed constructor 0x002E9ACC); the line
// walk 0x002F6C22 calls its 0x002F4D8B callback, which sets +0x1C on a hit.
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

// A hierarchical path node list (rowed 0x002E6C79 gives the next node) whose
// +0 points at a cell record: x, y, and at +0x0C a zone record whose +0x04
// is kept.
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

struct Rva002E8C23Param;
Int Rva002E8C23Call(Int,unsigned char,Rva002E8C23Param *);
// The 12-byte record +0x1C1CC collects per hop (zone, next cell x/y).
struct Rva002F35AFHop
{
	Int m_zone;
	PathfinderCostCellInfo m_position;
};
// The 0x14-byte hierarchical path (rowed constructor 0x005348AD); 0x00534557
// adds a cell and 0x00534AAE finishes it (WorldBuilder: computeOrderMap).
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
	void rva00531481();
	void rva005314C6(Int x, Int y, unsigned char flag);
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
// Native 0x002EC0A2 reads Object nodes at cell-info +0x14, +0x20 and +0x24.
// The list-role labels below describe the three observed conflict passes;
// their original member spellings are not established. Nodes link at +0 and
// carry Object* at +8; native Object position/AI/container are +0x38/+0x258/+0x274.
struct PathCollisionNode { PathCollisionNode *next; void *word4; Object *object; };
struct PathCollisionInfo {
    int x,y;
    char gap08[0x14-8];
    PathCollisionNode *occupants;
    PathCollisionNode *hordeGoalNodes; // Native/WB horde query list at+18.
    char gap1C[4];
    PathCollisionNode *goals;
    PathCollisionNode *reservations;
    ObjectID fallbackID; // Native/WB fallback lookup when +20 list is empty.
};
struct PathCollisionCell { PathCollisionInfo *info; };
// Native bridge list links at +4; height and containment use existing
// independently admitted Bridge providers from the terrain-logic family.
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
// Native 0x002F01B6 addresses this 12-byte floating scratch first. Later
// 0x002F0369 stores integer position at scratch+4 and diameter at scratch+12.
// The two phases do not overlap; this local union preserves that 20-byte reuse.
union PathfinderCheckCoordinates {
    Coord3D point;
    struct IntegerLayout { int reserved; ICoord2DBase position,size; } cells;
};
struct PathfinderLogFile;
extern "C" int __cdecl fprintf(PathfinderLogFile *,const char *,...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;

struct ICoord2D { Int x,y; };
class Rva002F6F90Context { public: Bool rva002F6F90(unsigned int,Int); };
class Rva002F70E5Context { public: Bool rva002F70E5(unsigned int,Int); };
class Rva002E7440 { public: Bool rva002E7440(Int,Int); };
class Rva002E7414 { public: Int rva002E7414(Int,Int); };
class Rva002F336AOwner { public: Bool rva002F336A(Int,Int); };
struct PathfinderOpenQueue {PathfindCell **first,**last;Bool empty()const{return first==last;}PathfindCell *front()const{return *first;}};
struct ICoord2D;
struct Rva002E7261Info;
class Pathfinder
{
public:
 Bool CheckForAdjust(Object *,const LocomotorSet &,Bool,Int,Int,PathfindLayerEnum,Int,Bool,Coord3D *,const Coord3D *,float,Int *,Int);
 Object *rva002F14F9(Object *,Object *);
 Bool QuickDoesPathExist(Object *,const Coord3D *,const Coord3D *,Int);
 Bool IsValidMovementPositionForObject(const Coord3D *,Int,Int,const Object *);
 Bool rva002F4115(Object *,Int,Int,LocomotorSet *);
 Bool rva002F4AC1(const ICoord2D *,Int,Int,Object *,PathfindLayerEnum,Int,Rva002E7261Info *,void *,void *);
 PathfindCell *rva002F068F();
    Path *GetAircraftPath(const Object *,const Coord3D *);
    int _GetOverlapUnits(Object *,const Coord3D *,int *);
    int GetOverlapGoalUnits(Object *,const Coord3D *,int *);
    int CountOverlapHordeGoalUnits(Object *,const Coord3D *);
    int _GetAdjacentUnits(Object *,const Coord3D *,int *);
    Bool rva002E9BE5(const Coord3D *,const Coord3D *,float,unsigned,Coord3D *);
    Bool rva002F3392(PathNode *,PathNode *,unsigned,Coord3D *,Coord3D *,Coord3D *);
    void SetDebugPath(Rva002EDEABArg *);
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
    Int rva002EED80(const ICoord2DBase *,const ICoord2DBase *,float,int,Rva002E9D09 *);
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
	// WorldBuilder's Pathfinder::PrependCells (0x002EE1C7, unrowed).
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
	Int iterateCellsAlongLine(const ICoord2D *,const ICoord2D *,PathfindLayerEnum,Rva002E7261Info *);
	char m_pad000[8];Bool m_isMapReady;char m_pad009[7];
	int m_unknown10;
	char m_pad014[0x10];
    Int m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY;
    MixFileInfoBuffer *m_closedList;Bool m_isTunneling;char m_pad039[0x5c-0x39];
	Bridge *m_bridges;
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;
	char m_pad461[0x1BEB6 - 0x461];
	Bool m_1BEB6;		// +0x1BEB6: paths get a facing hint from the goal cell
	char m_pad1BEB7[5];
	float m_wallLayerHeights[48];
	char m_pad1BF7C[0x1C1CC - 0x1BF7C];
	_STL::vector<Rva002F35AFHop> m_1C1CC;	// +0x1C1CC
 char pad1c1d8[0x1d1f0-0x1c1d8];PathfinderOpenQueue m_openCells;
};

class Rva002E99F9Sub460
{
public:
	unsigned short rva0053241F(void *, unsigned short);
	unsigned short rva00531FD4(void *, unsigned short);
};

// The 0x002E8045 walk calls this ABI view. The callback at 0x002E7261
// writes its result key at +8 and cell coordinates at +0xC/+0x10.
struct Rva002E7261Info
{
	Pathfinder *m_pathfinder;
	Int m_arg;
	Int m_key;
	ICoord2D m_position;
	Int cellCallback(PathfindCell *, PathfindCell *, Int, Int);
};


class PathfinderOverlapTerrainView:public PathfinderNativeSlots<44> { public: virtual bool objectInteractsWithBridgeLayer(Object *,int); };
int Rva002E6E6CGet(int);
extern int g_Va00DFECD0;
extern GameLogic *TheGameLogic;
int Rva002E9B31Get(void *);

static const float PATHFINDER_CELL_INV=1.0f/10.0f;
__declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = realToIntFloor(pos->x * PATHFINDER_CELL_INV);
		iy = realToIntFloor(pos->y * PATHFINDER_CELL_INV);
	} else {
		ix = realToIntFloor(pos->x * PATHFINDER_CELL_INV + 0.5f);
		iy = realToIntFloor(pos->y * PATHFINDER_CELL_INV + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}

__declspec(noinline) struct ICoord2D *__cdecl Rva002EBC14Cell(struct ICoord2D *out, void *p, const struct Coord3D *pos)
{
	Rva002E7875WorldToCell(out, Rva002EBBFBIsOdd(p), pos);
	return out;
}

__declspec(noinline) void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest)
{
	int v = Rva002E9B31Get(p);
	int h = v / 2;
	*outHalf = h;
	*outRest = v - h;
}
class Weapon {
public:
 float getAttackRange(const Object *) const;
 bool isWithinAttackRange(const Object *,const Object *,float,int) const;
 void *m_00;Rva002C9400ByteField *m_definition;
};
class PathfinderAttackContainView:public PathfinderNativeSlots<6> {public:virtual int slot18();};
// Native2F14F9..2F18D4 RET8. WB D3BD40 is the same perimeter/range scan,
// original method name unresolved. Owned adjacent-unit query proves the
// shared layer/footprint/stamp views; each additional filter follows retail.
Object *Pathfinder::rva002F14F9(Object *obj,Object *target)
{
 if(target) {Object *container=target->rva002931F5(false);if(container)target=container;}
 ICoord2D cell;int below,above;
 Rva002EBC14Cell(&cell,obj,(const Coord3D *)obj->position);
 Rva002EBCD6Split(obj,&below,&above);
 cell.x-=below;cell.y-=below;
 int extent=below+above;
 int layers[2];layers[0]=obj->rva0028B511();int layerCount=1;
 if(!(unsigned char)Rva002E6E6CGet(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(obj,layers[0])){layers[1]=1;layerCount=2;}
 ++g_Va00DFECD0;
 const Weapon *weapon=obj->getCurrentWeapon(0);
 if(!weapon || !weapon->m_definition->get())return 0;
 int relatedID=0;
 if(obj->testStatus((ObjectStatusTypes)65)) {
  void *contain=obj->rva002931F5(false)->rva0028C1A9();
  if(contain)relatedID=((PathfinderAttackContainView *)contain)->slot18();
 }
 int range=realToIntFloor(weapon->getAttackRange(obj)/10.0f+0.1f);
 Object *best=0;float bestDistance=1e10f;
 while(range-->=0) {
  for(int i=extent;i>=0;--i) {
   for(int side=0;side<4;++side) {
    int x,y;
    switch(side) {
     case 0:x=cell.x+i;y=cell.y-1;break;
     case 1:x=cell.x+extent;y=cell.y+i;break;
     case 2:x=cell.x+extent-i-1;y=cell.y+extent;break;
     case 3:x=cell.x-1;y=cell.y+extent-i-1;break;
    }
    for(int k=0;k<layerCount;++k) {
     PathCollisionCell *c=(PathCollisionCell *)getCell((PathfindLayerEnum)layers[k],x,y);
     if(c && c->info) {
      if(c->info->fallbackID) {
       Object *candidate=TheGameLogic->findObjectByID(c->info->fallbackID);
       if(candidate) {
        Relationship relation=obj->getRelationship(candidate);
        if(!candidate->rva002E6B89() && !(*(const unsigned char *)((const char *)candidate+0x438)&1)
         && (relation==ENEMIES || (candidate->m_template->hasKind(50) && relation==NEUTRAL))
         && (!target || candidate==target)
         && (candidate==target || !candidate->m_template->hasKind(130))
         && weapon->isWithinAttackRange(obj,candidate,0.0f,1)) {
          float distance=obj->rva00263763(candidate);
          if(distance<bestDistance){bestDistance=distance;best=candidate;}
        }
       }
      }
      for(PathCollisionNode *node=c->info->goals;node;node=node->next) {
       if(node->object->rva002E6B89())continue;
       Object *candidate=node->object;
       if((*(const unsigned char *)((const char *)candidate+0x438)&1) || candidate->rva0028F518())continue;
       if(candidate->testStatus((ObjectStatusTypes)15) && !candidate->testStatus((ObjectStatusTypes)17))continue;
       if(fabs(candidate->position[2]-obj->position[2])>10.0f)continue;
       Relationship relation=obj->getRelationship(candidate);
       if(relatedID!=candidate->getID() && relatedID!=*(const int *)((const char *)candidate+0x78)) {
        if(relation==ALLIES)continue;
        if(!candidate->m_template->hasKind(50) && relation==NEUTRAL)continue;
       }
       if(target && candidate!=target && candidate->container!=target)continue;
       if(weapon->isWithinAttackRange(obj,candidate,0.0f,1)) {
        float distance=obj->rva00263763(candidate);
        if(distance<bestDistance){bestDistance=distance;best=candidate;}
       }
      }
     }
    }
   }
  }
  extent+=2;--cell.x;--cell.y;
 }
 return best;
}
