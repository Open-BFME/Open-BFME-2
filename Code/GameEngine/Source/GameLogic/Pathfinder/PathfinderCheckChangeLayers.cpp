// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// ?CheckChangeLayers@Pathfinder@@QAEXPAVPathfindCell@@PAVObject@@@Z @0x002F4E54 (462B).
// Layer-change expansion of the A* search for a closed cell: opens the cell on the
// connected layer (connection bits 10..15 of the cell flags) and, when the cell
// carries a waypoint valid for the unit, the cells at the waypoint's links.
// The equal-arm receiver on from->info keeps retail's EBX/EDI colouring
// (W7-S2 r4 sweepchain). Views are the minimal subset of the bank's Pathfinder view.
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
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};
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
	// 0x00364551 / 0x00365E98 (unrowed): Zero Hour's optimize step with a
	// BFME facing hint, and a final pass toward a direction (unnamed).
	void rva00364551(Object *obj, LocomotorSurfaceTypeMask surfaces, Bool blocked, const float *facing);
	void rva00365E98(Object *obj, const Coord3D *dir, LocomotorSurfaceTypeMask surfaces, Bool blocked);
private:
	char m_pad[0x28];
};

struct PathfinderCostCellInfo { Int x,y; };
void ji_00629952();
class PathfindCell
{
public:
	// The packed cell word at +0x0C: type in bits 0-3, layer in bits 4-9.
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_OBSTACLE = 4,
		CELL_IMPASSABLE = 5
	};
	enum { LAYER_GROUND = 1 };

	void SetOpen(Bool open);
	void SetParentCell(int *);
	Int getXIndex() const { return m_pathInfo->x; }
	Int getYIndex() const { return m_pathInfo->y; }
	// 0x0052DD75 (unrowed): an angle for the cell from a facing, a count and
	// a weight (unnamed).
	float rva0052DD75(float facing, Int count, float weight);
	CellType getType() const { return (CellType)(m_info & 0xf); }
	Int getLayer() const { return (m_info & 0x3f0) >> 4; }

private:
	PathfinderCostCellInfo *m_pathInfo;
	char m_pad04[8];
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
	LocomotorSurfaceTypeMask getLegalSurfaces() const
	{
	 return m_template->m_surfaces;
	}
	float getMaxSpeed(Object *obj) const;
private:
	void *m_vtbl; // +0x00
	const LocomotorTemplate *m_template; // +0x04
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
	char m_pad20[0x28 - 0x20];
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
	bool rva002CB35C(int p1, void *p2, void *p3, void *p4, float p5, int p6);
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
class Rva002E6C79
{
public:
	Int rva002E6C79();
	Rva002F35AFCell *m_00;
	Rva002E6C79 *next() { return (Rva002E6C79 *)rva002E6C79(); }
};
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
};


struct Rva002EBC7FPair
{
public:
	int x; // +0x00
	int y; // +0x04
};
void *rva002EBC7F(void *,void *,Rva002EBC7FPair *,int);
#include <math.h>
class AIUpdateInterface {
public:
    bool isAircraftThatAdjustsDestination() const;
    int rva0026417F(bool);
    char gap[0x1f0];
    Locomotor *locomotor;
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
    char gap18[8];
    PathCollisionNode *goals;
    PathCollisionNode *reservations;
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
struct ICoord2DBase
{
public:
	int x; // +0x00
	int y; // +0x04
};
class Rva002E6DC4;
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
extern "C" void *theLogicRandomLogFile;

struct In002E6BA1 { int x,y; };
#include "ICoord2D.h"
class MixFileInfoBuffer;
extern int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,int,In002E6BA1 *);
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
int isGroundOrBridgeLayer(int);
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
class Rva003F69C0Object { public: void set(int *,int); };
class Waypoint
{
public:
	bool isValidUnitType(Object *);
	Waypoint *getLink(int) const;
	Int word0; // +0x00
	Int id; // +0x04
	void *name; // +0x08
	Coord3D m_location; // +0x0C
	char m_pad18[0x4];
	Waypoint *m_next; // +0x1C
	char m_pad20[0x24];
	Waypoint *chainNext; // +0x44
	Int word48; // +0x48
	Int linkCount; // +0x4C
};
struct PathChangeInfoView {
    int x,y;
    void *parent;
    unsigned int state;
    unsigned short totalCost,costSoFar;
};
struct PathChangeCellView {
    PathChangeInfoView *info;
    Waypoint *waypoint;
    int word8;
    unsigned int flags;
};

class Pathfinder
{
public:
	void CheckChangeLayers(PathfindCell *,Object *);
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
	char m_pad000[0x10];
	int m_unknown10;
	char m_pad014[0x10];
    Int m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY;
    char m_pad034[0x5c-0x34];
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

// ?Pathfinder::SetBridgeStateRepaired present-unmatched
void Pathfinder::CheckChangeLayers(PathfindCell *parent,Object *object)
{
    PathChangeCellView *from=reinterpret_cast<PathChangeCellView *>(parent);
    int connection=(from->flags>>10)&63;
    In002E6BA1 coord;
    if (connection) {
        int x=from->info->x;int y=from->info->y;coord.x=x;coord.y=y;
        PathfindCell *cell;
        if (static_cast<unsigned char>(isGroundOrBridgeLayer(connection))) cell=getCell(PATHFIND_LAYER_GROUND,x,coord.y);
        else cell=getCell(static_cast<PathfindLayerEnum>(connection),x,coord.y);
        if (cell && !static_cast<unsigned char>(reinterpret_cast<const Rva002E6AF3 *>(cell)->get()) &&
            !static_cast<unsigned char>(reinterpret_cast<Rva002E6B06 *>(cell)->rva002E6B06())) {
            PathChangeCellView *to=reinterpret_cast<PathChangeCellView *>(cell);
            if (!to->info) {
                if (TheMixFileInfoPool==reinterpret_cast<int>(to->info)) Rva0052DBCDInit();
                to->info=reinterpret_cast<PathChangeInfoView *>(Rva002E8B7AInit(reinterpret_cast<MixFileInfoBuffer **>(&TheMixFileInfoPool),reinterpret_cast<int>(cell),&coord));
            } else to->info->state=0;
            cell->SetParentCell(reinterpret_cast<int *>(parent));
            to->info->costSoFar=(from->info ? from->info : from->info)->costSoFar;
            to->info->totalCost=from->info->totalCost;
            AddToOpenList(cell);
        }
    }
    Waypoint *waypoint=from->waypoint;
    if (waypoint && object && waypoint->isValidUnitType(object)) {
        if (!m_1C1CC.empty() && m_1C1CC.back().m_zone==waypoint->id) m_1C1CC.pop_back();
        for (int i=0;i<waypoint->linkCount;++i) {
            Waypoint *linked=waypoint->getLink(i);
            if (linked) {
                PathfindCell *cell=static_cast<PathfindCell *>(rva001E3647Pos(1,&linked->m_location));
                if (cell && !static_cast<unsigned char>(reinterpret_cast<const Rva002E6AF3 *>(cell)->get()) &&
                    !static_cast<unsigned char>(reinterpret_cast<Rva002E6B06 *>(cell)->rva002E6B06())) {
                    ICoord2D *coordinate=Rva002E7875WorldToCell(reinterpret_cast<ICoord2D *>(&coord),true,&linked->m_location);
                    PathChangeCellView *to=reinterpret_cast<PathChangeCellView *>(cell);
                    if (!to->info) {
                        if (TheMixFileInfoPool==reinterpret_cast<int>(to->info)) Rva0052DBCDInit();
                        to->info=reinterpret_cast<PathChangeInfoView *>(Rva002E8B7AInit(reinterpret_cast<MixFileInfoBuffer **>(&TheMixFileInfoPool),reinterpret_cast<int>(cell),reinterpret_cast<In002E6BA1 *>(coordinate)));
                    } else to->info->state=0;
                    reinterpret_cast<Rva003F69C0Object *>(cell)->set(reinterpret_cast<int *>(parent),reinterpret_cast<int>(waypoint));
                    to->info->costSoFar=from->info->costSoFar;
                    to->info->totalCost=from->info->totalCost;
                    AddToOpenList(cell);
                }
            }
        }
    }
}
