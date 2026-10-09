// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
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
struct PathfinderTemplateView {
    char pad[0x64];
    char *nameBuffer;
    char pad68[0x108-0x68];
    unsigned char kinds[24];
    __forceinline bool hasKind(int bit) const { return (kinds[bit/8] & (1<<(bit%8)))!=0; }
    __forceinline const char *name() const { return nameBuffer ? nameBuffer+8 : ""; }
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
#include "../../../../Libraries/Include/Lib/Coord3D.h"
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

	void rva0052DAE9(Bool open);
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
class Rva002F70E5Context { public: Bool rva002F70E5(unsigned int,Int); };
class Pathfinder
{
public:
	Bool rva002F92BC(const ICoord2D *,Int,ICoord2D *,void *);
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
void Pathfinder::SetBridgeStateRepaired(PathfindLayerEnum layer, Bool repaired)
{
	if (((Rva0036666B *)&m_layers[layer])->rva0036666B()) {
		if (m_layers[layer].setDestroyed(!repaired)) {
			m_zoneManager.rva00531481();
		}
	}
}

void Pathfinder::ForceMapRecalculation()
{
	if (m_unknown10 != 0) {
		Rva0052F2EC();
	}
}

// WB 0xD3EA20 dispatches the ground-layer line test to the rowed helper.
// The retail ABI reuses endWorld's dead parameter slot for callback context.
#pragma optimize("y", off)
// ?Pathfinder::IsGroundLineOnly present-unmatched
Bool Pathfinder::IsGroundLineOnly(const Coord3D *startWorld,
	const Coord3D *endWorld)
{
	return !rva002EADE1(startWorld, endWorld, PATHFIND_LAYER_GROUND,
		(Rva002E7ED6Info *)&endWorld);
}
#pragma optimize("y", on)

// WB 0xD60940 identifies AddToOpenList; retail marks the cell open, then
// appends its pointer through the thiscall helper at 0x002F3738. The queue
// receiver is Pathfinder+0x1D1F0 in the target body.
void Pathfinder::AddToOpenList(PathfindCell *cell)
{
	((PathfindCell *)cell)->rva0052DAE9(true);
	((Rva002F3738 *)((char *)this + 0x1d1f0))->rva002F3738((void **)&cell);
}

// WB 0xD3E820 identifies IsGroundPathPassable. Retail builds callback context
// from this and pathDiameter, then delegates the cell walk to 0x002EED41.
Bool Pathfinder::IsGroundPathPassable(const Coord3D *startWorld,
	PathfindLayerEnum layer, const Coord3D *endWorld, Int pathDiameter)
{
	Rva002E93A7Info info;
	info.m_04 = pathDiameter;
	info.m_00 = this;
	return !rva002EED41(startWorld, endWorld, layer, &info);
}

// WB 0xD4F090 builds the 0x002E7B02 callback context from source and copies
// its adjusted Coord3D back only when the rowed 0x002EB3D7 walk succeeds.
// ?Pathfinder::AdjustGroundPathPosition present-unmatched
Int Pathfinder::AdjustGroundPathPosition(const Coord3D &source,
	Coord3D &destination)
{
	Rva002E7B02 context((Int)this, 4,
		*(const _Rva002E7B02Cell *)&source);
	Int adjusted = rva002EB3D7(&source, &destination, PATHFIND_LAYER_GROUND,
		(Rva002E7B29Info *)&context);
	if (adjusted != 0) {
		destination = *(Coord3D *)((char *)&context + 8);
	}
	return adjusted;
}

// WB 0xD58AF0: after its two debug-only initialization assertions, the wrapper
// forwards isHuman, the LocomotorSet surface mask, obj, from, to, crusher,
// closestOK=true, and adjustedTo to internal_findHierarchicalPath.
Path *Pathfinder::FindClosestHierarchicalPath(Bool isHuman,
	const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
	const Coord3D *to, Bool crusher, Coord3D *adjustedTo)
{
	return internal_findHierarchicalPath(isHuman, locomotorSet.getValidSurfaces(),
		obj, from, to, crusher, true, adjustedTo);
}

// WB 0xD588A0 maps this six-argument wrapper to internal_findHierarchicalPath;
// its local Coord3D receives the optional adjusted destination.
Path *Pathfinder::FindHierarchicalPath(Bool isHuman,
	const LocomotorSet &locomotorSet, Object *obj, const Coord3D *from,
	const Coord3D *to, Bool crusher)
{
	Coord3D adjustedTo;
	return internal_findHierarchicalPath(isHuman, locomotorSet.getValidSurfaces(),
		obj, from, to, crusher, false, &adjustedTo);
}

// Pathfinder::IsValidMovementTerrain, retail 0x002E7296 (158 bytes): WB's
// name for Zero Hour's Pathfinder::validMovementTerrain (AIPathfind.cpp),
// whose body this is; the per-type surfaces come from the table instead of
// validLocomotorSurfacesForCellType.
Bool Pathfinder::IsValidMovementTerrain(PathfindLayerEnum layer, const Locomotor *locomotor, const Coord3D *pos)
{
	Int x = realToIntFloor(pos->x * 0.1f);
	Int y = realToIntFloor(pos->y * 0.1f);

	PathfindCell *toCell = getCell(layer, x, y);
	if (toCell == 0)
		return false;
	if (toCell->getType() == PathfindCell::CELL_OBSTACLE) return true;
	if (toCell->getType() == PathfindCell::CELL_IMPASSABLE) return true;
	if (toCell->getLayer() != PathfindCell::LAYER_GROUND && toCell->getType() == PathfindCell::CELL_CLEAR)
		return true;
	// check validity of destination cell
	LocomotorSurfaceTypeMask acceptableSurfaces = g_00DBD33C[toCell->getType()];
	if ((locomotor->getLegalSurfaces() & acceptableSurfaces) == 0)
		return false;
	return true;
}

// Pathfinder_FuncTightenPath::Pathfinder_FuncTightenPath, retail 0x002EE43A
// (97 bytes). Name from WorldBuilder (pathfinder.cpp line 11307,
// wb-name-unverified); fields follow Zero Hour's TightenPathStruct.
Pathfinder_FuncTightenPath::Pathfinder_FuncTightenPath(Pathfinder *pathfinder,
	Object *obj, const LocomotorSet &locomotorSet, PathfindLayerEnum layer,
	const Coord3D &goal)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_locomotorSet = &locomotorSet;
	m_layer = layer;
	copyCoord3D(&m_goal, &goal);
	zeroCoord3D(&m_destPos);
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_foundDest = false;
}

// Pathfinder::TightenPath, retail 0x002FC95E (83 bytes). Name from
// WorldBuilder (pathfinder.cpp line 11334, wb-name-unverified); Zero Hour's
// Pathfinder::tightenPath with the struct turned into a functor: walks the
// cells from `from` to `to` and moves `from` to the last good position found.
void Pathfinder::TightenPath(Object *obj, const LocomotorSet &locomotorSet,
	Coord3D *from, const Coord3D *to)
{
	Pathfinder_FuncTightenPath info(this, obj, locomotorSet,
		TheTerrainLogic->getLayerForDestination(obj, from), *to);
	rva002F95B7(from, to, info.m_layer, (Rva002F600CInfo *)&info);
	if (info.m_foundDest)
		*from = info.m_destPos;
}

// Pathfinder_IsCheckForMeleeHordeAdjust::Pathfinder_IsCheckForMeleeHordeAdjust,
// retail 0x002ED72B (139 bytes). Name from WorldBuilder (pathfinder.cpp line
// 4570, wb-name-unverified); isHuman/radius/layer follow Zero Hour's
// checkForAdjust setup.
Pathfinder_IsCheckForMeleeHordeAdjust::Pathfinder_IsCheckForMeleeHordeAdjust(
	Pathfinder *pathfinder, Object *obj, void *arg, const Coord3D &goal,
	float range)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_08 = arg;
	m_range = range;
	m_24 = 0;
	copyCoord3D(&m_goal, &goal);
	m_isHuman = (m_obj->getControllingPlayer() && m_obj->getControllingPlayer()->m_playerType == 1) ? 0 : 1;
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(obj, &goal);
}

// Pathfinder_IsCheckForAdjust::Pathfinder_IsCheckForAdjust, retail 0x002ED484
// (177 bytes). Name from WorldBuilder (pathfinder.cpp, wb-name-unverified);
// the sibling of Pathfinder_IsCheckForMeleeHordeAdjust, taking its layer
// from the optional second position when one is given.
Pathfinder_IsCheckForAdjust::Pathfinder_IsCheckForAdjust(Pathfinder *pathfinder,
	Object *obj, void *arg, const Coord3D &goal, const Coord3D *layerPos,
	float range, Int arg6)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_08 = arg;
	m_layerPos = layerPos;
	m_range = range;
	m_28 = 0;
	m_2C = arg6;
	copyCoord3D(&m_goal, &goal);
	m_isHuman = (m_obj->getControllingPlayer() && m_obj->getControllingPlayer()->m_playerType == 1) ? 0 : 1;
	Rva002EBCA7Split(m_obj, &m_radius, &m_center);
	m_layer = TheTerrainLogic->getLayerForDestination(obj, &m_goal);
	if (m_layerPos)
		m_layer = TheTerrainLogic->getLayerForDestination(0, m_layerPos);
}

// Pathfinder::CheckForTarget, retail 0x002F2FA4 (123 bytes). Name from
// WorldBuilder (pathfinder.cpp line 9429, wb-name-unverified). When the
// rowed 0x002F1C25 test passes, takes the 0x002EBC59 cell position and keeps
// it in `out` if the weapon probe (range 10) accepts it.
Bool Pathfinder::CheckForTarget(void *obj, void *a2, void *a3,
	Rva002CB35CObj *weapon, void *a5, void *a6, void *a7, void *a8,
	Coord3D *out)
{
	if (bfmeWrapE6E90(obj, a2, a3, (void *)1, a7, a8))
	{
		Coord3D cell;
		Coord3D pos = *(Coord3D *)rva002EBC59(&cell, obj, (Int)a2, (Int)a3, 1);
		if (weapon->rva002CB35C((Int)obj, &pos, a5, a6, 10.0f, 1))
		{
			*out = pos;
			return true;
		}
	}
	return false;
}

// Pathfinder::BuildActualPath, retail 0x002F0596 (249 bytes). Name from
// WorldBuilder (pathfinder.cpp lines 10785..10786, wb-name-unverified); Zero
// Hour's buildActualPath (new Path, prependCells, optimize) with BFME's
// facing hint and final direction pass.
Path *Pathfinder::BuildActualPath(Object *obj, LocomotorSurfaceTypeMask surfaces,
	const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Bool blocked,
	Bool faceDirection)
{
	Path *path = new Path;
	PrependCells(path, fromPos, goalCell, center);
	float facing[2];
	facing[0] = 0.0f;
	facing[1] = 0.0f;
	if (m_1BEB6)
	{
		float orientation = obj->m_orientation;
		float angle = goalCell->rva0052DD75(orientation, 10, 0.5f);
		facing[0] = Cos(angle);
		facing[1] = Sin(angle);
	}
	path->rva00364551(obj, surfaces, blocked, m_1BEB6 ? facing : 0);
	if (faceDirection)
	{
		Coord3D dir = *((const Thing *)obj)->getUnitDirectionVector2D();
		path->rva00365E98(obj, &dir, surfaces, blocked);
	}
	return path;
}

// Pathfinder::MakeHierarchicalPathPassable, retail 0x002F35AF (308 bytes).
// Name from WorldBuilder (pathfinder.cpp lines 10858..10859,
// wb-name-unverified). Records each hop of the node list at +0x1C1CC, then
// builds a hierarchical path over its cells, marking each cell (or, when
// expanding, the 3x3 block of 16-cell zones around it) in the zone manager.
Rva005348AD *Pathfinder::MakeHierarchicalPathPassable(void *, Rva002E6C79 *path, Bool expand)
{
	Rva002E6C79 *node;
	for (node = path; node->next(); node = node->next())
	{
		Rva002F35AFCell *cell = node->m_00;
		if ((cell ? cell->m_0C : 0) && node->next())
		{
			Rva002F35AFHop hop;
			hop.m_zone = (cell ? cell->m_0C : 0)->m_04;
			hop.m_position.x = node->next()->m_00->x;
			hop.m_position.y = node->next()->m_00->y;
			m_1C1CC.push_back(hop);
		}
	}
	Rva005348AD *result = new Rva005348AD;
	for (node = path; node; node = node->next())
	{
		if (expand)
		{
			for (Int dx = -16; dx <= 16; dx += 16)
				for (Int dy = -16; dy <= 16; dy += 16)
					m_zoneManager.rva005314C6(node->m_00->x + dx, node->m_00->y + dy, 1);
		}
		else
		{
			m_zoneManager.rva005314C6(node->m_00->x, node->m_00->y, 1);
		}
		result->rva00534557(node->m_00);
	}
	result->rva00534AAE();
	return result;
}

// Pathfinder::CanApproachToTarget, retail 0x002FA2DC (277 bytes). Name from
// WorldBuilder (pathfinder.cpp lines 4692..4693, callgraph evidence). Probes
// the eight cells around the target at the approach range (150, or the
// weapon's larger 0x002C9B80 range) with the 0x002E9ACC functor along a line
// from the target; true on the first hit. Copying the target through the
// inline Coord3D::set helper (not struct assignment) is what gives retail's
// frame: with `pos = *targetPos` cl keeps the loop counters in memory and
// moves the range out of the dead `obj` home (0.74 -> exact).
Bool Pathfinder::CanApproachToTarget(Object *obj, const Coord3D *targetPos,
	Rva002C9B80Owner *weapon, Bool flag)
{
	char *ai = obj->m_258;
	if (!ai)
		return false;
	float range = 150.0f;
	unsigned char byte = 0;
	if (weapon)
	{
		float weaponRange = weapon->rva002C9B80(obj, 0.0f);
		if (weaponRange > range)
			range = weaponRange;
		byte = weapon->m_04->get();
	}
	Rva002E9ACC functor(this, obj, (Rva002E8BCFSrc const *)(ai + 0x1CC), byte, flag);
	for (Int i = -1; i < 2; i++)
	{
		for (Int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;
			Coord3D pos;
			copyCoord3D(&pos, targetPos);
			pos.x += i * range;
			pos.y += j * range;
			functor.m_1E = 1;
			functor.m_1F = 0;
			iterateCellsAlongLine(targetPos, &pos,
				TheTerrainLogic->getLayerForDestination(0, targetPos),
				(Rva002F4D8BInfo *)&functor);
			if (functor.m_found)
				return true;
		}
	}
	return false;
}

// Retail 0x002EC0A2..0x002EC3CE (812 bytes), exact /O1 /G7 /arch:SSE.
// Identity: WB 0x00D32F30, Pathfinder/pathfinder.cpp assertions 772..851;
// its name, three conflict passes, arrival-time comparison and seven-argument
// thiscall agree with native. The named BFME1 and GeneralsMD AIPathfind source
// has no corresponding method; this is reconstruction from native and WB.
// Layouts and helper bindings above are proved by native loads/call sites,
// independently of WB's debug-only assertions and shifted Object offsets.
// Standard math.h supplies sqrt's compiler declaration; a bare extern makes
// the two x87 result stores interleave with stack cleanup instead of retail.
int Pathfinder::CalcCollisionFreeExtraCosts(Object *object,PathfindCell *parent,Rva002EBC7FPair *destination,PathfindLayerEnum layer,int lower,int upper,bool ignoreReservations)
{
    Rva002EBC7FPair oldMin,oldMax;
    if (parent) {
        PathCollisionInfo *info=reinterpret_cast<PathCollisionCell *>(parent)->info;
        oldMin.x=info->x-lower; oldMin.y=info->y-lower;
        oldMax.x=info->x+upper; oldMax.y=info->y+upper;
    }
    Rva002EBC7FPair minimum,maximum;
    minimum.x=destination->x-lower; minimum.y=destination->y-lower;
    maximum.x=destination->x+upper; maximum.y=destination->y+upper;
    float ourArrival=-1.0f;
    int cost=0;
    for (int x=minimum.x;x<maximum.x;++x) {
        for (int y=minimum.y;y<maximum.y;++y) {
            if (parent && x>=oldMin.x && x<oldMax.x && y>=oldMin.y && y<oldMax.y) continue;
            PathCollisionCell *cell=reinterpret_cast<PathCollisionCell *>(getCell(layer,x,y));
            if (!cell || !cell->info) continue;
            for (PathCollisionNode *node=cell->info->occupants;node;node=node->next) {
                Object *other=node->object;
                if (other==object || other->container==object) continue;
                bool enemies=object->getRelationship(other)==ENEMIES;
                if (!object->getAI() || !other->getAI()) continue;
                if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))>static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) continue;
                if (other->IsAtGoalPosition()) return -1;
                if (object->getAI()->locomotor && other->getAI()->locomotor) {
                    Coord3D target;
                    rva002EBC7F(&target,object,destination,1);
                    if (ourArrival<0.0f) {
                        float dx=object->position[0]-target.x;
                        float dy=object->position[1]-target.y;
                        Rva001E46E1 *locomotor=object->getAI()->locomotor;
                        float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                        ourArrival=distance/locomotor->rva001E46E1(object);
                    }
                    float dx=other->position[0]-target.x;
                    float dy=other->position[1]-target.y;
                    Rva001E46E1 *locomotor=other->getAI()->locomotor;
                    float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                    float otherArrival=distance/locomotor->rva001E46E1(other);
                    if (otherArrival<ourArrival) cost+=4;
                } else cost+=8;
            }
            for (PathCollisionNode *node=cell->info->goals;node;node=node->next) {
                Object *other=node->object;
                if (other==object || other->container==object) continue;
                bool enemies=object->getRelationship(other)==ENEMIES;
                if (!object->getAI() || !other->getAI()) continue;
                if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))<=static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) return -1;
            }
            if (!ignoreReservations) {
                for (PathCollisionNode *node=cell->info->reservations;node;node=node->next) {
                    Object *other=node->object;
                    if (other==object) continue;
                    bool enemies=object->getRelationship(other)==ENEMIES;
                    if (!object->getAI() || !other->getAI()) continue;
                    if (static_cast<unsigned>(object->getAI()->rva0026417F(enemies))<=static_cast<unsigned>(other->getAI()->rva0026417F(enemies))) return -1;
                }
            }
        }
    }
    return cost;
}

// Retail 0x002EBE54..0x002EC0A2 (590 bytes), exact /O1 /G7 /arch:SSE.
// WB 0x00D32350 names Pathfinder::CalcExtraCosts and asserts oldCell at line635.
// Six-argument ABI, destination bounds, old-cell layer, enemy filtering,
// priority and shifted 4/8 movement costs are established independently by
// native bytes. WB's old-cell overlap expression has mutually exclusive y
// comparisons and is dead; retail emits no overlap exclusion or old bounds.
// No same-named BFME1/GeneralsMD donor method was found. Reconstructed from
// native/WB using the independently verified CalcCollisionFreeExtraCosts
// layouts, priority bool ABI and standard math declaration above.
int Pathfinder::CalcExtraCosts(Object *object,PathfindCell *oldCell,Rva002EBC7FPair *destination,int lower,int upper,bool ignoreEnemies)
{
    if (!oldCell) return 0;
    Rva002EBC7FPair minimum,maximum;
    minimum.x=destination->x-lower; minimum.y=destination->y-lower;
    maximum.x=destination->x+upper; maximum.y=destination->y+upper;
    // The completed radius parameters become the shift and accumulated cost
    // for this stage (native dead homes +0x18 and +0x14). References retain
    // meaningful stage names without losing the verified storage lifetime.
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
                        Rva001E46E1 *locomotor=object->getAI()->locomotor;
                        float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                        ourArrival=distance/locomotor->rva001E46E1(object);
                    }
                    float dx=other->position[0]-target.x;
                    float dy=other->position[1]-target.y;
                    Rva001E46E1 *locomotor=other->getAI()->locomotor;
                    float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                    float otherArrival=distance/locomotor->rva001E46E1(other);
                    if (!(otherArrival<ourArrival)) continue;
                    amount=4;
                }
                cost+=amount>>reduction;
            }
        }
    }
    return cost;
}

// WorldBuilder names this body GetWallHeight (WB 0x00D3ED70). ZH supplies
// the Bridge height/containment semantics, while retail establishes the
// layer selection, ramp handling, four cell-corner probes and ABI.
// Native 0x002EF68C, 636 bytes; bridge head +0x5C, height[layer] +0x1BE78.
float Pathfinder::GetWallHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal)
{
    PathfindCell *cell = static_cast<PathfindCell *>(rva001E3647Pos(layer, pos));
    if (cell && layer != PATHFIND_LAYER_GROUND && cell->getLayer() != layer) {
        PathfindLayerEnum actual = static_cast<PathfindLayerEnum>(cell->getLayer());
        if (actual == 16) {
            if (IsPointOnRamp(pos)) layer = actual;
        } else layer = actual;
    }
    if (layer == PATHFIND_LAYER_GROUND)
        return TheTerrainLogic->getGroundHeight(pos->x, pos->y, normal);
    if (static_cast<unsigned char>(Rva002E6E8AGet(layer))) {
        float height = m_wallLayerHeights[layer - 17];
        if (normal) {
            normal->x = 0.0f;
            normal->y = 0.0f;
            normal->z = 1.0f;
        }
        return height;
    }
    if (layer == 16) {
        for (Bridge *bridge = m_bridges; bridge; bridge = bridge->m_next) {
            if (bridge->isPointOnBridge(pos)) {
                PathfindLayerEnum wallLayer = rva002ED236(0, *pos);
                float height = bridge->getBridgeHeight(pos, normal);
                float result;
                if (static_cast<unsigned char>(Rva002E6E8AGet(wallLayer))) {
                    result = reinterpret_cast<Rva002E7482 *>(this)->rva002E7482(wallLayer) > height
                        ? reinterpret_cast<Rva002E7482 *>(this)->rva002E7482(wallLayer) : height;
                } else result = height;
                return result;
            }
        }
        Coord3D corner0 = *pos;
        corner0.x -= 10.0f;
        corner0.y -= 10.0f;
        Coord3D corner1 = corner0;
        corner1.x += 20.0f;
        Coord3D corner2 = corner1;
        corner2.y += 20.0f;
        Coord3D corner3 = corner0;
        corner3.y += 20.0f;
        for (Bridge *bridge = m_bridges; bridge; bridge = bridge->m_next) {
            if (bridge->isPointOnBridge(&corner0) || bridge->isPointOnBridge(&corner1) ||
                bridge->isPointOnBridge(&corner2) || bridge->isPointOnBridge(&corner3)) {
                PathfindLayerEnum wallLayer = rva002ED236(0, *pos);
                float height = bridge->getBridgeHeight(pos, normal);
                float result;
                if (static_cast<unsigned char>(Rva002E6E8AGet(wallLayer))) {
                    result = reinterpret_cast<Rva002E7482 *>(this)->rva002E7482(wallLayer) > height
                        ? reinterpret_cast<Rva002E7482 *>(this)->rva002E7482(wallLayer) : height;
                } else result = height;
                return result;
            }
        }
    }
    return pos->z;
}

// CheckDestination identity is established by the native diagnostic strings;
// Zero Hour checkDestination supplies the cell iteration purpose. BFME2 adds
// horde/narrow-passage radius overrides and a geometry-aware rectangle query.
// Template kind bytes, human extent, AI and containment accesses are retail facts.
Bool Pathfinder::CheckDestination(Object *obj,Int cellX,Int cellY,PathfindLayerEnum layer,
    Int radius,Bool center,Int *out,Bool flag)
{
    PathfinderCheckCoordinates coordinates;
    if (g_00E03745 && g_00DFEFF0) {
        fprintf((PathfinderLogFile *)g_00DFEFF0,
            "          Pathfinder::CheckDestination called with: obj=%s(%d), cell=%d,%d, layer=%d, iRadius=%d, centerInCell=%s",
            obj->m_template->name(), obj->getID(), cellX,cellY,layer,radius,center?"TRUE":"FALSE");
    }
    if (obj->m_template->hasKind(109)) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          horde");
        if (layer==PATHFIND_LAYER_GROUND && !flag) {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          layer is LAYER_GROUND");
            rva002E79A8((int)&coordinates.point,1,cellX,cellY,1);
            if (((TerrainLogicCheckDestination *)TheTerrainLogic)->slotC8(&coordinates.point)) {
                if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          narrow passage area");
                radius=1; center=true;
            }
        } else {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          layer != LAYER_GROUND, layer=%d",layer);
            radius=1; center=true;
        }
    }
    if (obj->m_template->hasKind(90) && obj->m_template->hasKind(8) && layer!=PATHFIND_LAYER_GROUND) {
        radius=1; center=false;
    }
    Int upper=radius;
    if (center) ++upper;
    if (obj->rva0028AFBB()) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          human controlled");
        if (cellX-radius<m_extentLowX || cellX+upper>m_extentHighX || cellY-radius<m_extentLowY || cellY+upper>m_extentHighY) {
            if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"            returning false");
            return false;
        }
    }
    Bool aircraft=false;
    Int ignored=0, objectId=0;
    const LocomotorSet *locomotors=0;
    if (obj->getAI()) {
        if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          I have an AI");
        ignored=((const Rva0006E009DwordField *)obj->getAI())->get();
        aircraft=obj->getAI()->isAircraftThatAdjustsDestination();
        objectId=obj->getID();
        locomotors=(const LocomotorSet *)((char *)obj->getAI()+0x1cc);
    }
    *out=0;
    Rva002E7C99 info;
    info.rva002E7C99((int)this,(int)obj,(int)out,0,ignored,flag,(int)locomotors);
    if (!aircraft && obj->m_template->hasKind(186)) {
        ICoord2DBase &position=coordinates.cells.position;
        position.x=cellX;position.y=cellY;
        GeometryShape shape;
        ((const GeometryInfo *)((char *)obj+0xa8))->rva006BD9C0(shape);
        ICoord2DBase &size=coordinates.cells.size;
        size.x=(int)((shape.major*2.0f+4.0f)*0.1f);
        size.y=(int)((shape.minor*2.0f+4.0f)*0.1f);
        void *contain=*(void **)((char *)obj+0x250);
        if (contain && ((PathfinderContain31 *)contain)->slot7C()) {
            Int count=((PathfinderContain28 *)contain)->slot70();
            if (count>0) {
                float fraction=(float)((PathfinderContain69 *)contain)->slot114(0)/count;
                size.x=(int)((size.x-2.0f)*fraction+2.0f);
                size.y=(int)((size.y-2.0f)*fraction+2.0f);
            }
        }
        return !rva002EED80(&position,&size,obj->GetGoalAngle(),layer,(Rva002E9D09 *)&info);
    }
    if (g_00E03745 && g_00DFEFF0) {
        fprintf((PathfinderLogFile *)g_00DFEFF0,"          BEGIN cell iteration (deep innards), i from %d to %d, j from %d to %d",
            cellX-radius,cellX+upper,cellY-radius,cellY+upper);
    }
    for (Int i=cellX-radius;i<cellX+upper;++i) {
        for (Int j=cellY-radius;j<cellY+upper;++j) {
            PathfindCell *cell=getCell(layer,i,j);
            if (!cell) {
                if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          OFF THE MAP, return false: i=%d, j=%d",i,j);
                return false;
            }
            if (aircraft) {
                if (((Rva0052DB4D *)cell)->rva0052DB4D(objectId)) {
                    if (g_00E03745 && g_00DFEFF0) fprintf((PathfinderLogFile *)g_00DFEFF0,"          checkForAircraft=TRUE, return false: i=%d, j=%d",i,j);
                    return false;
                }
            } else if (((Rva002E9D09 *)&info)->rva002E9D09((Object *)cell,0,0)) return false;
        }
    }
    return true;
}

// The 59-byte executable gap between the verified split helper ending BCF6
// and queueForPath at BD31 is a complete constructor ending in RET. Its stores
// reproduce the GeometryShape initialization in CheckDestination, including
// the name and two tail flags. The original owner name is unproven; this
// address-named adapter reuses the independently supported 36-byte shape view.
struct Rva002EBCF6 : GeometryShape { Rva002EBCF6(); };
Rva002EBCF6::Rva002EBCF6() {}

// The native debug draw call sites push coord/float/duration/12-byte color;
// the layer reset call supplies only ECX. Both release bodies fold to the
// existing single RET at B3FD0. Separate full C++ providers preserve their ABIs.
struct PathfinderDebugColor { float red,green,blue; };
void Rva000B3FD0PathDebug(const Coord3D *,float,Int,PathfinderDebugColor);



// Retail 2F0A72..2F0B4D: search cost through the hierarchical waypoint list.
// Native callers 2FA3F1/2FAD13 establish Pathfinder receiver and cell ABI.
// Info +0 begins with x/y; native vector +1C1CC contains 12B (zone,position).
// ZH costToGoal supplies the grid-cost purpose; WB D642F0 shows the unsigned
// accumulator expression and coordinate copy. No donor name is claimed.
Int Pathfinder::rva002F0A72(PathfindCell *cell, PathfindCell *goal)
{
    unsigned int cost = 0;
    Int x = cell->getXIndex(), y = cell->getYIndex();
    for (_STL::vector<Rva002F35AFHop>::iterator it = m_1C1CC.end();
         it != m_1C1CC.begin(); --it)
    {
        PathfinderCostCellInfo point = (it - 1)->m_position;
        Int nx = point.x, ny = point.y;
        Int dx = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(x - nx);
        Int dy = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(y - ny);
        if (dx > dy)
            cost = (cost + 14 * dy) + (cost + 10 * (dx - dy));
        else
            cost = (cost + 14 * dx) + (cost + 10 * (dy - dx));
        cost += 1400;
        x = nx;
        y = ny;
    }
    Int dx = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(x - goal->getXIndex());
    Int dy = reinterpret_cast<Int(__cdecl *)(Int)>(ji_00629952)(y - goal->getYIndex());
    if (dx > dy)
        return 14 * dy + cost + 10 * (dx - dy);
    return 14 * dx + cost + 10 * (dy - dx);
}

// BFME1 clean IterateCircular1 donor at actual reference checkout 9cbfb551.
// Target700B boundary2F92BC..2F9578, WB D6AD60 and native horde-adjust caller
// establish traversal/ABI; callback70E5 is independently rowed. Retail shortens
// the failure literal and keeps all five predicate calls external.
Bool Pathfinder::rva002F92BC(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (g_00E03745 && g_00DFEFF0)
	{
		fprintf((PathfinderLogFile *)g_00DFEFF0,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F70E5Context *targetSearch = (Rva002F70E5Context *)adjustTargetInfoData;
	if (targetSearch->rva002F70E5(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && g_00DFEFF0)
			fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tfunc failed");

	Int bestOffsetDistanceSquared = 0;
	Int ringExtent = 1;
	Int cellOffsetX = 0;
	Int cellOffsetY = 0;

	while (remainingCellBudget > 0)
	{
		remainingCellBudget -= 4 * ringExtent + 2;
		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F70E5(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F70E5(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F70E5(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F70E5(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
					foundCell->x=scanCenterCell->x+cellOffsetX;
					foundCell->y=scanCenterCell->y+cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			if (g_00E03745 && g_00DFEFF0)
				fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && g_00DFEFF0)
		fprintf((PathfinderLogFile *)g_00DFEFF0, "\t\ttotal failure. found");
	return false;
}

