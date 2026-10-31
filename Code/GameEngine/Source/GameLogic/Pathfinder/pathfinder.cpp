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
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &lhs, const unsigned int &rhs)
{
    return lhs < rhs ? rhs : lhs;
}
}
#include <cstdlib>
#include <cstring>
void Rva00030830FreeAllocation(void *);
// Retail STL storage frees through the rowed game allocator at 0x00030830,
// not the CRT import; the same route PersistentStorageThread.cpp takes.
#define free Rva00030830FreeAllocation
#include <vector>
#undef free
#include <new>
#include "../../Common/GameLogicObjectLookupView.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0,
	PATHFIND_LAYER_GROUND = 1
};
typedef int LocomotorSurfaceTypeMask;

#include "ascii_string.h"
class LocomotorSet
{
public:
	const char *name() const { return m_nameString.str(); }
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
	char m_gap16[2];
	AsciiString m_nameString;
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
    AsciiString nameString;
    char pad68[0x108-0x68];
    unsigned char kinds[24];
    char pad120[0x56c-0x120];Int priority;char pad570[0x634-0x570];Bool flag;
    __forceinline bool hasKind(int bit) const { return (kinds[bit/8] & (1<<(bit%8)))!=0; }
    // The same KindOf bit read as BitFlags words (dword tests in retail).
    __forceinline unsigned int testKindWord(unsigned int bit) const { return ((const unsigned int *)kinds)[bit>>5] & (1u<<(bit&31)); }
    // The same bit as a 0/1 value (retail shr/and when stored to a Bool).
    __forceinline Bool kindBit(unsigned int bit) const { return (((const unsigned int *)kinds)[bit>>5] >> (bit&31)) & 1; }
    __forceinline const char *name() const { return nameString.str(); }
};
enum Relationship { ENEMIES=0, NEUTRAL=1, ALLIES=2 };
enum ObjectStatusTypes { QuickStatus49=49, MoveAlliesStatus5A=0x5A };
// KindOf bit Object::isKindOf (0x0006F039) is asked for by Pathfinder::MoveAllies.
enum KindOfType { MoveAlliesKind9A=0x9A };
enum NameKeyType { NAMEKEY_INVALID=0 };
class Module;
struct Coord3D;
struct AttackGeometry{char gap[0x10];float radial;float getRadial()const{return radial;}};
class Object
{
public:
 __forceinline const AttackGeometry& getAttackGeometry()const{return (*reinterpret_cast<const AttackGeometry *>((const char*)this+0xa8));}
 char rva00294815();
 bool isSignificantlyAboveTerrain()const;
friend class Rva002F23A6;
public:
	Player *getControllingPlayer() const;
 Bool testStatus(ObjectStatusTypes) const;
	Relationship getRelationship(const Object *) const;
	Bool isKindOf(KindOfType) const;	// 0x0006F039
	Bool rva002931BA();	// 0x002931BA
    int rva0028B511() const;
    Object *rva002931F5(Bool);
void rva0028C2DD(Coord3D*)const;
const Coord3D *getPosition()const{return (const Coord3D*)position;}
protected:Module *findModule(NameKeyType)const;
public:
    bool rva002E6B89();
	bool IsAtGoalPosition() const;
	Bool canCrushOrSquishNoAlly(Object *other, Int test);
	bool rva0028AFBB() const;
	bool rva0028AC62() const;
	const struct Rva0028AC4EEntry *rva0028AC4E() const;
	float GetGoalAngle() const;
    __forceinline int getID() const { return *(const int *)((const char *)this+0x74); }
	AIUpdateInterface *getAI() const { return reinterpret_cast<AIUpdateInterface *>(m_258); }
	__forceinline const PathfinderTemplateView *getTemplate() const { return m_template; }
	void *m_vtable;
	PathfinderTemplateView *m_template;
	char m_pad08[0x38-8];
	float position[3];
	float m_orientation;				// +0x44
	char m_pad48[0x78 - 0x48];
	ObjectID m_id78;					// +0x78: MoveAllies skips a unit whose ID (+0x74) equals this
	char m_pad7C[0x258 - 0x7C];
	char *m_258;						// +0x258 (WorldBuilder +0x260: CanApproachToTarget's gate)
	char m_pad25C[0x274-0x25C];
	Object *container;
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/Thing/thing.h"
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
    const Coord3D *getPosition() const { return &position; }
    PathNode *getNextOptimized() const { return nextOptimized; }
    PathNode *getPrevious() const { return previous; }
    PathfindLayerEnum getLayer() const { return layer; }
};
struct Rva002EDEABArg;
struct Rva002E93A7Info
{
	Pathfinder *m_00;
	Int m_04;
};
class Waypoint { public:
 Bool isValidUnitType(Object *); Waypoint *getLink(Int) const;
 Int word0,id;void *name;Coord3D location;Int word18;Waypoint *next;
 char pad20[0x44-0x20];Waypoint *chainNext;Int word48,linkCount;
 char pad50[0x60-0x50];Int type;
};
class PathfindCell;
class Path
{
 friend class Pathfinder;friend struct Rva002F5925Info;
public:
 void prependNode(const Coord3D *,PathfindLayerEnum,Int);
	Path();										///< matched 0x00363DC8
	// 0x00364551 / 0x00365E98 (unrowed): Zero Hour's optimize step with a
	// BFME facing hint, and a final pass toward a direction (unnamed).
	void rva00364551(Object *obj, LocomotorSurfaceTypeMask surfaces, Bool blocked, const float *facing);
	void rva00365E98(Object *obj, const Coord3D *dir, LocomotorSurfaceTypeMask surfaces, Bool blocked);
	void appendNode(const Coord3D *pos, PathfindLayerEnum layer, Int portal);
	void SetLastNodePortal(Int portal);
	void Lock() { m_refCount++; }
	void Unlock() { if (m_refCount) m_refCount--; }
private:
	Int m_refCount;PathNode *firstNode;PathNode *lastNode;char wordC;Bool blockedByAlly;char padE[0x28-0xe];
};

struct Rva002E8C23Pair { Int x,y; };
struct PathfinderCellPoint : Coord3D {
	__forceinline PathfinderCellPoint() {}
	__forceinline PathfinderCellPoint(const PathfinderCellPoint &pathfinderCellPoint) { x = pathfinderCellPoint.x; y = pathfinderCellPoint.y; z = pathfinderCellPoint.z; }
	__forceinline ~PathfinderCellPoint() {}
};
PathfinderCellPoint rva002E79A8(Bool centerInCell, Int cellX, Int cellY, PathfindLayerEnum layer);
// The int-form callers hand 0x002E79A8 their hidden result pointer directly
// (cdecl struct return: the hidden result pointer is the first argument).
typedef void (__cdecl *Rva002E79A8HiddenResultForm)(int, unsigned char, int, int, int);
#define RVA002E79A8_HIDDEN ((Rva002E79A8HiddenResultForm)(PathfinderCellPoint (*)(Bool, Int, Int, PathfindLayerEnum))rva002E79A8)
static __forceinline void rva002E79A8(int out, unsigned char center, int x, int y, int layer)
{
	RVA002E79A8_HIDDEN(out, center, x, y, layer);
}
// ?Rva002E8C4DCall@@YAHHEPAURva002E8C23Pair@@H@Z, retail 0x002E8C4D (33 bytes):
// cdecl cell-centre wrapper forwarding the cell's x/y to 0x002E79A8. Defined
// here, ahead of its Pathfinder callers, because cl 7.1 reads the body: knowing
// it keeps no reference to the cell is what fixes AdjustDestination's schedule.
int __cdecl Rva002E8C4DCall(int a1, unsigned char a2, Rva002E8C23Pair *a3, int a4)
{
	rva002E79A8(a1, a2, a3->x, a3->y, a4);
	return a1;
}
bool Rva002EBBFBIsOdd(void *);
struct ICoord2D;
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
#include <math.h>
struct PathfinderCostCellInfo { Int x,y; };
struct PathfinderGroundInfo { PathfinderCostCellInfo position;Int parent;Waypoint *parentWaypoint;unsigned short totalCost,costSoFar;char pad14[0x28-0x14];ObjectID obstacleID;unsigned int flags; };
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
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
private:
	char m_pad[0x48];
	void *m_48;
};

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

 Bool IsObstaclePresent(ObjectID) const;
 Int CalcCostToHierGoal(PathfindCell *);
 bool getPinched()const{return ((m_info>>16)&1)!=0;}
 bool getBit23()const{return ((m_info>>23)&1)!=0;}
 Bool StartPathfind(Int);void ReleaseInfo();void SetParentCell(Int *);void PutOnClosedList(MixFileInfoBuffer **);Int CalcCostSoFar(const Rva002E6C79 *);
 __forceinline void allocateInfo(In002E6BA1 *pos) {
  if(!m_pathInfo) { if(!TheMixFileInfoPool)Rva0052DBCDInit();m_pathInfo=(PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool,(Int)this,pos); }
  else m_pathInfo->parentWaypoint=0;
 }
	void SetOpen(Bool open);
	unsigned short quickZone()const {return (unsigned short)word8;}
 Int getXIndex() const { return m_pathInfo->position.x; }
	Int getYIndex() const { return m_pathInfo->position.y; }
	// 0x0052DD75 (unrowed): an angle for the cell from a facing, a count and
	// a weight (unnamed).
	float rva0052DD75(float facing, Int count, float weight);
	__declspec(dllimport) __forceinline CellType getType() const { return (CellType)(m_info & 0xf); }
	Int getLayer() const { return (m_info & 0x3f0) >> 4; }
	Int getConnectLayer() const { return (m_info >> 10) & 0x3f; }
	Bool rvaBit16() const { return (Bool)((m_info >> 16) & 1); }
 PathfindCell *getParentCell(){return (PathfindCell *)((Rva002E6C79 *)this)->rva002E6C79();}
 Waypoint *getParentWaypoint()const {return m_pathInfo?m_pathInfo->parentWaypoint:0;}
 ObjectID getObstacleID() const { return m_pathInfo ? m_pathInfo->obstacleID : (ObjectID)0; }

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
	float getMaxSpeed(Object *obj) const;
	__declspec(dllimport) __forceinline LocomotorSurfaceTypeMask getLegalSurfaces() const { return m_template->m_surfaces; }

private:
	void *m_vtbl;
	const LocomotorTemplate *m_template;	// +0x04
};

// The surfaces each cell type allows, indexed by type (VA 0x00DBD33C,
// defined in Rva002E6DC4Check.cpp).
// g_00DBD33C: VA 0x00DBD33C (.data), the cell-type surface table; exact retail initial dwords.
unsigned int g_00DBD33C[16] = {
	0x00000009, 0x0000000A, 0x0000000C, 0x00000018,
	0x00000028, 0x00000048, 0x00000048, 0x00000088,
	0x00000000, 0x3E490FDB, 0x41A00000, 0x41A00000,
	0x00000000, 0x00000001, 0x00000000, 0xFFFFFFFF
};

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
	Rva002E8C23Pair m_1C;
	Int m_24;								// +0x24
	Coord3D m_goal;							// +0x28
};

// The rowed cell-centre helper 0x002EBC59 (returns its out Coord3D) and the
// pinned 0x002CB35C range probe (WorldBuilder: Weapon::isWithinAttackRange).
void *rva002EBC59(void *out, void *obj, Int a2, Int a3, Int a4);
class Rva002CB35CObj
{
public:
	__declspec(dllimport) Bool rva002CB35C(Int a1, void *pos, void *a3, void *a4, float range, Int a6);	// forwards to the rowed Weapon::isWithinAttackRange
};

// CanApproachToTarget's helpers. The rowed 0x002C9B80 range query returns a
// float; its +0x04 member answers the rowed byte getter 0x002C9400.
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
// Weapon::isWithinAttackRange 0x002CB35C (WorldBuilder name).
#include "../../../Include/GameLogic/Weapon.h"
// ?PathfinderWeaponRangeAdapter absent-from-retail
__forceinline Bool Rva002CB35CObj::rva002CB35C(Int a1, void *pos, void *a3, void *a4, float range, Int a6)
{
	return ((Weapon *)this)->isWithinAttackRange((Object *)a1, (const Coord3D *)pos, (Object *)a3, (const Coord3D *)a4, range, a6 != 0);
}
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

// The 12-byte record +0x1C1CC collects per hop (zone, next cell x/y).
struct Rva002F35AFHop
{
	Int m_zone;
	PathfinderCostCellInfo m_position;
};
// The 0x14-byte hierarchical path (rowed constructor 0x005348AD); 0x00534557
// adds a cell and 0x00534AAE finishes it (WorldBuilder: computeOrderMap).
class Rva00534AAE { public: void rva00534AAE(); };
class Rva00534557 { public: void rva00534557(const int *cell); };
class Rva005348AD
{
public:
	Rva005348AD();
	/* the rowed Rva00534557::rva00534557 */ __declspec(dllimport) __forceinline void rva00534557(Rva002F35AFCell *cell) { ((Rva00534557 *)this)->rva00534557((const int *)cell); }
	/* the rowed Rva00534AAE::rva00534AAE */ __declspec(dllimport) __forceinline void rva00534AAE() { ((Rva00534AAE *)this)->rva00534AAE(); }
private:
	char m_pad[0x14];
};

class Rva0036666B
{
public:
	bool rva0036666B();
	bool rva0036736E(bool destroyed);	// rowed 0x0036736E (PathfindLayer::setDestroyed body)
};

class PathfindLayer
{
public:
	/* the rowed Rva0036666B::rva0036736E */ __declspec(dllimport) __forceinline bool setDestroyed(bool destroyed) { return ((Rva0036666B *)this)->rva0036736E(destroyed); }
    __declspec(noinline) void rva000B3FD0();
private:
	char m_pad[0x40];
};

class PathfindZoneManager
{
public:
	void rva005312BE();
 Bool rva00532069(Int,Int);Bool rva005315C8(Int,Int);Int GetPortal(Int,Int,Int);
 unsigned char IsPassable(Int,Int);
	void rva00531300();
	void rva00531481();
	void rva005314C6(Int x, Int y, unsigned char flag);
};


struct Rva002EBC7FPair { int x,y; };
// The rowed 0x002EBC7F body (AI/Rva002EBC7F.cpp), visible here so that the pair
// CalcCollisionFreeExtraCosts hands it does not escape and rva002ECC0D's info stays local.
__declspec(noinline) inline void *rva002EBC7F(void *a1, void *a2, Rva002EBC7FPair *a3, int a4)
{
	RVA002E79A8_HIDDEN((int)a1, Rva002EBBFBIsOdd(a2), a3->x, a3->y, a4);
	return a1;
}
#include <math.h>
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1, CMD_FROM_AI = 2 };
struct AICommandParms;
// The AICommandInterface subobject sits at AIUpdateInterface+0x20 (callers add ecx,0x20).
class AICommandInterface {
public:
    virtual void aiDoCommand(const AICommandParms *parms) = 0;
    void aiMoveAwayFromUnit(Object *obj, const Coord3D *pos, CommandSourceType cmdSource);	// 0x0026C411
};
// The update-module part: Pathfinder::MoveAllies calls vftable slots 0x1B8/0x1BC (unnamed).
class AIUpdateModuleView : public PathfinderNativeSlots<110> {
public:
    virtual Bool slot1B8();
    virtual Bool slot1BC();
    char m_pad04[0x20 - 4];
};
class AIUpdateInterface : public AIUpdateModuleView, public AICommandInterface {
public:
    bool findNearestLabeledContactPointOnTarget(Object *,Coord3D *,const Coord3D *,bool);
    bool isAircraftThatAdjustsDestination() const;
    int rva0026417F(bool);
    Object *getCurrentVictim() const;
    Bool isMoving() const;	// 0x00264688
    char gap[0x1f0 - 0x24];
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

// Native 0x002F01B6 addresses this 12-byte floating scratch first. Later
// 0x002F0369 stores integer position at scratch+4 and diameter at scratch+12.
// The two phases do not overlap; this local union preserves that 20-byte reuse.
union PathfinderCheckCoordinates {
    Coord3D point;
    struct IntegerLayout { int reserved; ICoord2DBase position,size; } cells;
};
// Retail logging calls the direct CRT fprintf thunk. Keep math and other
// headers on their existing imported-binding configuration.
#pragma push_macro("_CRTIMP")
#undef _CRTIMP
#define _CRTIMP
#include <stdio.h>
#pragma pop_macro("_CRTIMP")
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
// A cell index returned by value (hidden pointer): ICoord2D with a field-wise
// copy constructor, like PathfinderCellPoint below.
struct PathfinderCellIndex : ICoord2D {
	__forceinline PathfinderCellIndex() {}
	__forceinline PathfinderCellIndex(const PathfinderCellIndex &pathfinderCellIndex) { x = pathfinderCellIndex.x; y = pathfinderCellIndex.y; }
};
class Rva002F6F90Context { public: Bool rva002F6F90(unsigned int,Int); };
class Rva002F70E5Context { public: Bool rva002F70E5(unsigned int,Int); };
class Rva002E7440 {
public:
    Rva002E7440(Pathfinder *owner) : pf(owner) {}
    Bool rva002E7440(Int,Int);
private:
    Pathfinder *pf;
};
class Rva002E7414 {
public:
    Rva002E7414(Pathfinder *owner) : pf(owner) {}
    Int rva002E7414(Int,Int);
private:
    Pathfinder *pf;
};
class Rva002F336AOwner { public: Bool rva002F336A(Int,Int); };
struct PathfinderOpenQueue {PathfindCell **first,**last;Bool empty()const{return first==last;}PathfindCell *front()const{return *first;}};
struct ICoord2D;
struct Rva002E7261Info;
struct PathfinderMineshaft { Int m_00; Int m_portal; Int m_08; Coord3D m_position; };
struct TCheckMovementInfo;
class HierarchicalPath;
class Rva002E7E26;
class Rva002E7DF5;
// The rowed 0x002E6F8B clear of a water-scan result and the rowed atan2
// helper 0x000422A0 used by rva002ED535.
struct Rva002E6F92Info { Coord3D position; Bool found; };
class Rva002E6F8B { public: Rva002E6F8B *rva002E6F8B(); };
double Rva000422A0Atan2(float,float);
struct Rva002F4491Info;
class Pathfinder
{
public:
 Path *FindAttackPath(Object *,const LocomotorSet &,const Coord3D *,Object *,const Coord3D *,Rva002C9B80Owner *,Bool,Bool *);
 Bool isAttackViewBlockedByObstacle(const Object *,const Coord3D &,const Object *,const Coord3D &);
private:
 Int iterateCellsAlongLine(const ICoord2D *,const ICoord2D *,PathfindLayerEnum,Rva002F4491Info *);
public:
 Path *FindGroundPath(Object *,const Coord3D *,const Coord3D *,Int);
 Int rva002E7749(void *,Int,Int,Int,Int,Bool);
 Path *BuildGroundPath(const Coord3D *,PathfindCell *,Bool,Int);
 void rva002F5022(const ICoord2D &,const ICoord2D &,PathfindCell *,PathfindCell *,unsigned short,unsigned short *,Int &,Int,Int &);
// Native vtable C053F8: slots 0..9 are modeled as placeholders (the rows that
// own them keep their non-virtual spellings); FindCollisionFreeQuickPath is slot
// 10. The vptr takes the first four bytes of the old leading pad.
virtual void QuickPathReserved0()=0;
virtual void QuickPathReserved1()=0;
virtual void QuickPathReserved2()=0;
virtual void QuickPathReserved3()=0;
virtual void QuickPathReserved4()=0;
virtual void QuickPathReserved5()=0;
virtual void QuickPathReserved6()=0;
virtual void QuickPathReserved7()=0;
virtual void QuickPathReserved8()=0;
virtual void QuickPathReserved9()=0;
virtual Path *FindCollisionFreeQuickPath(Object *,const Coord3D *,PathNode *);
 Bool rva002F07F5(Object *,const Coord3D *);
 Bool IsValidHordeMemberRegularMovement(Object *,const Coord3D *,const Coord3D *,const Coord3D *);
 Bool AdjustToNearestValidCell(Coord3D *);
 Bool AdjustToNearestGroundCell(Coord3D *);
bool rva002ED313(Object*);
void AdjustMeleeOffset(Object*,Object*,Coord3D*);
Bool rva002EEA8A(const ICoord2D*,Int,ICoord2D*,void*,Int);
 Bool adjustToMeleeDestination(Object*,const LocomotorSet&,Coord3D*);
 Bool adjustToPossibleDestination(Object*,const LocomotorSet&,Coord3D*);
 void SnapClosestGoalPosition(Object *,Coord3D *);
 Bool CheckForAdjust(Object *,const LocomotorSet &,Bool,Int,Int,PathfindLayerEnum,Int,Bool,Coord3D *,const Coord3D *,float,Int *,Int);
 Bool QuickDoesPathExist(Object *,const Coord3D *,const Coord3D *,Int);
 Bool IsValidMovementPositionForObject(const Coord3D *,Int,Int,const Object *);
 Bool rva002F4115(Object *,Int,Int,LocomotorSet *);
 Bool rva002F4AC1(const ICoord2D *,Int,Int,Object *,PathfindLayerEnum,Int,Rva002E7261Info *,void *,void *);
 PathfindCell *rva002F068F();
 Path *FindSafePath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,const Coord3D *,float);
 Path *PatchPath(Object *,const LocomotorSet &,Path *,Bool);
 Path *GetHordeUnitPath(Object *,const Coord3D *);
 Bool rva002EF3EE(Object *,Coord3D *,Object *,Bool);
 PathfindCell *Rva002EDF7C(struct ObjWithPos *,ICoord2D *);
    Path *GetAircraftPath(const Object *,const Coord3D *);
    int _GetOverlapUnits(Object *,const Coord3D *,int *);
    int GetOverlapGoalUnits(Object *,const Coord3D *,int *);
    int CountOverlapHordeGoalUnits(Object *,const Coord3D *);
    Bool rva002ECC0D(Object *,const Coord3D *);
    int _GetAdjacentUnits(Object *,const Coord3D *,int *);
    Bool CircleClipsTallBuilding(const Coord3D *,const Coord3D *,float,unsigned,Coord3D *);
    Bool rva002F3392(PathNode *,PathNode *,unsigned,Coord3D *,Coord3D *,Coord3D *);
    void SetDebugPath(Rva002EDEABArg *);
	Bool rva002EAE5F(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002EB11B(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002F379E(ICoord2D *,Int,void *);
	Bool AdjustDestination(Object *,const LocomotorSet &,Coord3D *,const Coord3D *);
	Bool rva002ED535(Object *,Coord3D *);
	Bool IsWaterCell(Int,Int);
	Int rva002EAE20(const Coord3D *,const Coord3D *,PathfindLayerEnum,Rva002E6F92Info *);
	Bool AdjustHordeMeleeDestination(Object *,void *,Coord3D *);
	Int CheckPathCost(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *);
	Bool rva002F8E2D(const ICoord2D *,Int,ICoord2D *,void *);
	Bool rva002F90E9(ICoord2D *,Int,void *);
	Bool rva002F92BC(const ICoord2D *,Int,ICoord2D *,void *);
 PathfindCell *rva002E8BF8(PathfindLayerEnum,const Coord3D *);
 PathfindCell *rva002F36E5();Int rva002F40E7();void CheckChangeLayers(PathfindCell *,Object *);
	Path *InternalFindPath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,HierarchicalPath *,Bool *);
	Path *FindPath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,Bool *);
	Int rva002F83F5(PathfindCell *,PathfindCell *,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
	Path *GetMoveAwayFromPath(Object *,Object *,Path *,Object *,Path *);
	Path *FindClosestPath(Object *,const LocomotorSet &,const Coord3D *,Coord3D *,Bool,float,Bool);
	Int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *,const ICoord2D *,Int,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
	Bool rva002EA658(Object *,TCheckMovementInfo &,const ICoord2D *);
 Bool checkForMovement(Object *,TCheckMovementInfo &);
	Bool rva002EDFF9(Object *,Coord3D *);
	void clip(Coord3D *,Coord3D *);
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
	PathfinderCellIndex Rva002E7917(bool center, const Coord3D *pos);	// 0x002E7917 clamp wrapper
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
	Bool MoveAllies(Object *obj, Path *path, Bool force);
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
	Int iterateCellsAlongLine(const ICoord2D *,const ICoord2D *,PathfindLayerEnum,struct Rva002F5925Info *);
	char m_pad004[4];Bool m_isMapReady;char m_pad009[7];
	int m_unknown10;
	ICoord2D m_clampLo, m_clampHi;	// +0x14 cell extent the 0x002E7917 clamp uses
    Int m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY;
    MixFileInfoBuffer *m_closedList;Bool m_isTunneling;char m_pad039[0x48-0x39];
	ObjectID m_ignoreObstacleID;	// +0x48
	char m_pad04C[0x5c-0x4c];
	Bridge *m_bridges;
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;
	char m_pad461[0x1BEB6 - 0x461];
	Bool m_1BEB6;		// +0x1BEB6: paths get a facing hint from the goal cell
	char m_pad1BEB7[5];
	float m_wallLayerHeights[48];
	char m_pad1BF7C[0x1C1BC - 0x1BF7C];
	Int m_moveAlliesDepth;	// +0x1C1BC: MoveAllies recursion latch
	char m_pad1C1C0[0x1C1CC - 0x1C1C0];
	_STL::vector<Rva002F35AFHop> m_1C1CC;	// +0x1C1CC
 // +0x1C1D8/+0x1C1DC: mine-shaft portals; WorldBuilder asserts m_destMineshaft
 // on the second. Each carries a zone/portal ID at +4 and its position at +0xC.
 PathfinderMineshaft *m_srcMineshaft,*m_destMineshaft;
 char pad1c1e0[0x1d1f0-0x1c1e0];PathfinderOpenQueue m_openCells;
public:
	Bool getClosestPointOnLand(const Coord3D *position, Object *object, Coord3D *out);
	Int IterateCellsInRectangle(const ICoord2DBase *center, const ICoord2DBase *diameter, float angle, int layer, Rva002E7E26 *visitor);
	Int ProcessConvexPoly(Int *xPts, Int *yPts, Int numEdges, Int layer, Rva002E7E26 *visitor);
 int rva002EB4A0(const Coord3D *a, const Coord3D *b, PathfindLayerEnum layer, void *info);
 void AdjustFlingDestination(Object *obj, const Coord3D *from_, Coord3D *to);
private:
 Int iterateCellsAlongLine(const ICoord2D *, const ICoord2D *, PathfindLayerEnum, struct Rva002E85ADInfo *);
};

class Rva002E99F9Sub460
{
public:
	unsigned short rva0053241F(void *, unsigned short);
 unsigned short rva00532041(Int,Int,Int,struct Rva00532041Record **);
 bool rva005318DB(void *,void *,void *);
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

// Native 0x002F4AC1..0x002F4B33 (114 bytes, RET36). WB's four calls pass
// this argument order; retail confirms the changed-cell key at info+8.
Bool Pathfinder::rva002F4AC1(const ICoord2D *start, Int dx, Int dy,
	Object *object, PathfindLayerEnum layer, Int expected,
	Rva002E7261Info *info, void *lookup, void *context)
{
	ICoord2D endpoint = *start;
	endpoint.x += dx;
	endpoint.y += dy;
	iterateCellsAlongLine(start, &endpoint, layer, info);
	if (info->m_key != -1)
	{
		Int actual = ((Rva002E99F9Sub460 *)((char *)this + 0x460))
			->rva0053241F(lookup, (unsigned short)info->m_key);
		if (expected == actual || rva002F4115(object, expected, actual,
			(LocomotorSet *)context))
			return true;
	}
	return false;
}

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
	((PathfindCell *)cell)->SetOpen(true);
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

// scratch: Pathfinder::rva002EB4A0 rehomed (0x002EB4A0, 63 B)
int Pathfinder::rva002EB4A0(const Coord3D *lhs, const Coord3D *rhs, PathfindLayerEnum layer, void *info)
{
	ICoord2D tmp1;
	ICoord2D tmp2;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmp2, true, lhs), Rva002E7875WorldToCell(&tmp1, true, rhs), layer, (struct Rva002E85ADInfo *)info);
}

struct Rva0028AC4EQ { char pad00[0x14]; Int value14; };
struct Rva0028AC4EEntry { char pad00[4]; Rva0028AC4EQ *next; };
struct FlingInfo { Int surfaces; Bool notFlag; Bool computer; Int radius; Bool atAC62; };
struct FlingVisitor { Pathfinder *finder; Coord3D *found; PathfindLayerEnum layer; FlingInfo info; Bool alive; };
void Pathfinder::AdjustFlingDestination(Object *obj, const Coord3D *from_, Coord3D *to)
{
	Bool centered = Rva002EBBFBIsOdd(obj);
	Coord3D from;
	copyCoord3D(&from, from_);
	if (!centered) {
		from.x += 5.0f;
		from.y += 5.0f;
		to->x += 5.0f;
		to->y += 5.0f;
	}
	const Rva0028AC4EEntry *loco = obj->rva0028AC4E();
	Int surfaces = 1;
	if (loco) surfaces = loco->next->value14;
	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	Bool atAC62 = obj->rva0028AC62();
	Bool computer = obj->rva0028AFBB();
	FlingInfo info;
	info.surfaces = surfaces;
	info.notFlag = !flag;
	info.computer = computer;
	info.radius = priority - 1;
	info.atAC62 = atAC62;
	Coord3D found;
	copyCoord3D(&found, &from);
	Bool alive = !(*((const unsigned char *)obj + 0x438) & 1);
	FlingVisitor visitor;
	visitor.finder = this;
	visitor.found = &found;
	visitor.layer = (PathfindLayerEnum)obj->rva0028B511();
	visitor.info = info;
	visitor.alive = alive;
	if (rva002EB4A0(&from, to, PATHFIND_LAYER_GROUND, &visitor)) *to = found;
	if (!centered) {
		to->x -= 5.0f;
		to->y -= 5.0f;
	}
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

// Retail 0x002ED535 (502 bytes, RET 8), between the two adjust checks above:
// a unit of kind 191 whose destination is not a water cell is moved to the
// first scan result (the rowed 0x002EAE20) found toward it, else to one found
// along a quarter-turn fan of pi/16 steps on either side, at twice the
// distance. WorldBuilder 0xD438C0 is the unnamed debug body. The step is a
// writable .data float (0x009BD360, read only here).
static float s_waterScanAngleStep = 0.19634954f;
Bool Pathfinder::rva002ED535(Object *obj, Coord3D *dest)
{
	if (!obj->m_template->hasKind(191) || IsWaterCell((Int)dest, 1))
		return true;
	Coord3D start;
	copyCoord3D(&start, (Coord3D *)obj->position);
	Rva002E6F92Info info;
	((Rva002E6F8B *)&info)->rva002E6F8B();
	rva002EAE20(&start, dest, PATHFIND_LAYER_GROUND, &info);
	if (info.found)
	{
		*dest = info.position;
		dest->z = start.z;
		return true;
	}
	float radius;
	float angle;
	{
		Coord3D delta;
		copyCoord3D(&delta, dest);
		delta.x -= start.x;
		delta.y -= start.y;
		delta.z -= start.z;
		radius = delta.length() * 2;
		angle = Rva000422A0Atan2(delta.x, delta.y) + s_waterScanAngleStep;
	}
	float end = angle + 1.5707963705062866f;
	for (; end > angle; angle = (s_waterScanAngleStep + angle) + s_waterScanAngleStep)
	{
		if (info.found)
			break;
		float cosine = cosf(angle);
		float sine = sinf(angle);
		float dx = cosine * radius;
		Coord3D next;
		next.x = start.x + dx;
		float dy = sine * radius;
		next.y = start.y + dy;
		next.z = dest->z;
		rva002EAE20(&start, &next, PATHFIND_LAYER_GROUND, &info);
		if (!info.found)
		{
			next.x = start.x - dx;
			next.y = start.y - dy;
			rva002EAE20(&start, &next, PATHFIND_LAYER_GROUND, &info);
		}
		if (info.found)
		{
			*dest = info.position;
			dest->z = start.z;
		}
	}
	return true;
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
                        Locomotor *locomotor=object->getAI()->locomotor;
                        float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                        ourArrival=distance/locomotor->getMaxSpeed(object);
                    }
                    float dx=other->position[0]-target.x;
                    float dy=other->position[1]-target.y;
                    Locomotor *locomotor=other->getAI()->locomotor;
                    float distance=static_cast<float>(sqrt(dy*dy+dx*dx));
                    float otherArrival=distance/locomotor->getMaxSpeed(other);
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
inline __declspec(noinline) int Pathfinder::CalcExtraCosts(Object *object,PathfindCell *oldCell,Rva002EBC7FPair *destination,int lower,int upper,bool ignoreEnemies)
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
    if (g_00E03745 && theLogicRandomLogFile) {
        fprintf((FILE *)theLogicRandomLogFile,
            "          Pathfinder::CheckDestination called with: obj=%s(%d), cell=%d,%d, layer=%d, iRadius=%d, centerInCell=%s",
            obj->getTemplate()->name(), obj->getID(), cellX,cellY,layer,radius,center?"TRUE":"FALSE");
    }
    if (obj->m_template->hasKind(109)) {
        if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"          horde");
        if (layer==PATHFIND_LAYER_GROUND && !flag) {
            if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"          layer is LAYER_GROUND");
            rva002E79A8((int)&coordinates.point,1,cellX,cellY,1);
            if (((TerrainLogicCheckDestination *)TheTerrainLogic)->slotC8(&coordinates.point)) {
                if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"          narrow passage area");
                radius=1; center=true;
            }
        } else {
            if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"          layer != LAYER_GROUND, layer=%d",layer);
            radius=1; center=true;
        }
    }
    if (obj->m_template->hasKind(90) && obj->m_template->hasKind(8) && layer!=PATHFIND_LAYER_GROUND) {
        radius=1; center=false;
    }
    Int upper=radius;
    if (center) ++upper;
    if (obj->rva0028AFBB()) {
        if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"          human controlled");
        if (cellX-radius<m_extentLowX || cellX+upper>m_extentHighX || cellY-radius<m_extentLowY || cellY+upper>m_extentHighY) {
            if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"            returning false");
            return false;
        }
    }
    Bool aircraft=false;
    Int ignored=0, objectId=0;
    const LocomotorSet *locomotors=0;
    if (obj->getAI()) {
        if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"          I have an AI");
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
        return !IterateCellsInRectangle(&position,&size,obj->GetGoalAngle(),layer,(Rva002E9D09 *)&info);
    }
    if (g_00E03745 && theLogicRandomLogFile) {
        fprintf((FILE *)theLogicRandomLogFile,"          BEGIN cell iteration (deep innards), i from %d to %d, j from %d to %d",
            cellX-radius,cellX+upper,cellY-radius,cellY+upper);
    }
    for (Int i=cellX-radius;i<cellX+upper;++i) {
        for (Int j=cellY-radius;j<cellY+upper;++j) {
            PathfindCell *cell=getCell(layer,i,j);
            if (!cell) {
                if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"          OFF THE MAP, return false: i=%d, j=%d",i,j);
                return false;
            }
            if (aircraft) {
                if (((Rva0052DB4D *)cell)->rva0052DB4D(objectId)) {
                    if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"          checkForAircraft=TRUE, return false: i=%d, j=%d",i,j);
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
	if (g_00E03745 && theLogicRandomLogFile)
	{
		fprintf((FILE *)theLogicRandomLogFile,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F70E5Context *targetSearch = (Rva002F70E5Context *)adjustTargetInfoData;
	if (targetSearch->rva002F70E5(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && theLogicRandomLogFile)
			fprintf((FILE *)theLogicRandomLogFile, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "\t\tfunc failed");

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
			if (g_00E03745 && theLogicRandomLogFile)
				fprintf((FILE *)theLogicRandomLogFile, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "\t\ttotal failure. found");
	return false;
}


// BFME1 IterateCircular1 predicate donor 9cbfb551 and retail2F8E2D..2F90E9.
Bool Pathfinder::rva002F8E2D(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (g_00E03745 && theLogicRandomLogFile)
	{
		fprintf((FILE *)theLogicRandomLogFile,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F6F90Context *targetSearch = (Rva002F6F90Context *)adjustTargetInfoData;
	if (targetSearch->rva002F6F90(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && theLogicRandomLogFile)
			fprintf((FILE *)theLogicRandomLogFile, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "\t\tfunc failed");

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
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
			if (g_00E03745 && theLogicRandomLogFile)
				fprintf((FILE *)theLogicRandomLogFile, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "\t\ttotal failure. found");
	return false;
}


// BFME1 IterateCircular2 clean donor 9cbfb551; retail2F90E9..2F92BC.
Bool Pathfinder::rva002F90E9(ICoord2D *scanCenterCell, Int remainingCellBudget, void *adjustTargetInfoData)
{
	if (g_00E03745 && theLogicRandomLogFile)
	{
		fprintf((FILE *)theLogicRandomLogFile,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F6F90Context *targetSearch = (Rva002F6F90Context *)adjustTargetInfoData;
	if (targetSearch->rva002F6F90(scanCenterCell->x, scanCenterCell->y))
	{
		return true;
	}

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
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F6F90(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			return true;
		}
	}

	return false;
}

// BFME1 circular1 donor9cbfb551; native boundary and callback ABI.
Bool Pathfinder::rva002EAE5F(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (g_00E03745 && theLogicRandomLogFile)
	{
		fprintf((FILE *)theLogicRandomLogFile,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002E7414 *targetSearch = (Rva002E7414 *)adjustTargetInfoData;
	if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && theLogicRandomLogFile)
			fprintf((FILE *)theLogicRandomLogFile, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "\t\tfunc failed");

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
				if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if ((unsigned char)targetSearch->rva002E7414(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
			if (g_00E03745 && theLogicRandomLogFile)
				fprintf((FILE *)theLogicRandomLogFile, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "\t\ttotal failure. found");
	return false;
}



// BFME1 circular1 donor9cbfb551; native boundary and callback ABI.
Bool Pathfinder::rva002EB11B(const ICoord2D *scanCenterCell, Int remainingCellBudget, ICoord2D *foundCell, void *adjustTargetInfoData)
{
	if (g_00E03745 && theLogicRandomLogFile)
	{
		fprintf((FILE *)theLogicRandomLogFile,
			"\t\tIterateCircular1 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002E7440 *targetSearch = (Rva002E7440 *)adjustTargetInfoData;
	if (targetSearch->rva002E7440(scanCenterCell->x, scanCenterCell->y))
	{
		if (g_00E03745 && theLogicRandomLogFile)
			fprintf((FILE *)theLogicRandomLogFile, "\t\tfunc succeeded found=%d,%d", scanCenterCell->x, scanCenterCell->y);
		foundCell->x=scanCenterCell->x;
		foundCell->y=scanCenterCell->y;
		return true;
	}
	if (g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "\t\tfunc failed");

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
				if (targetSearch->rva002E7440(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if (targetSearch->rva002E7440(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if (targetSearch->rva002E7440(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
				if (targetSearch->rva002E7440(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
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
			if (g_00E03745 && theLogicRandomLogFile)
				fprintf((FILE *)theLogicRandomLogFile, "\t\tbest return true. found=%d,%d", foundCell->x, foundCell->y);
			return true;
		}
	}

	if (g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile, "\t\ttotal failure. found");
	return false;
}



// BFME1 circular2 donor9cbfb551; native467B target callback forwarder.
Bool Pathfinder::rva002F379E(ICoord2D *scanCenterCell, Int remainingCellBudget, void *adjustTargetInfoData)
{
	if (g_00E03745 && theLogicRandomLogFile)
	{
		fprintf((FILE *)theLogicRandomLogFile,
			"\t\tIterateCircular2 called with center=%d,%d, maxCells=%d",
			scanCenterCell->x, scanCenterCell->y, remainingCellBudget);
	}

	Rva002F336AOwner *targetSearch = (Rva002F336AOwner *)adjustTargetInfoData;
	if (targetSearch->rva002F336A(scanCenterCell->x, scanCenterCell->y))
	{
		return true;
	}

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
				if (targetSearch->rva002F336A(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = ringExtent; stepsRemaining > 0; --stepsRemaining)
		{
			++cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F336A(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetX;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F336A(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		for (Int stepsRemaining = 0; stepsRemaining <= ringExtent; ++stepsRemaining)
		{
			--cellOffsetY;
			if (bestOffsetDistanceSquared == 0
				|| cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY < bestOffsetDistanceSquared)
			{
				if (targetSearch->rva002F336A(scanCenterCell->x + cellOffsetX, scanCenterCell->y + cellOffsetY))
				{
					bestOffsetDistanceSquared = cellOffsetX * cellOffsetX + cellOffsetY * cellOffsetY;
				}
			}
		}

		if (bestOffsetDistanceSquared == 0)
		{
			ringExtent += 2;
		}
		else
		{
			return true;
		}
	}

	return false;
}



// BF1 checkPathCost from clean PathfinderStepD4F90 donor9cbfb551; native
// 2F5C7A..2F600C RET16 and WB D5F9F0 independently name CheckPathCost.
Int Pathfinder::CheckPathCost(Object *obj,const LocomotorSet &locomotorSet,const Coord3D *from,const Coord3D *rawTo)
{
 if(!m_isMapReady)return 0;
 const Int MAX_COST=0x7fff0000;
 Int cellCount=0;
 Coord3D adjustTo;copyCoord3D(&adjustTo,rawTo);
 PathfindLayerEnum goalLayer=TheTerrainLogic->getLayerForDestination(obj,&adjustTo);
 PathfindCell *goal=rva002E8BF8(goalLayer,&adjustTo);
 if(!goal)return MAX_COST;
 Bool center;Int radius;Rva002EBCA7Split(obj,&radius,(unsigned char *)&center);
 PathfindCell *parent;
 {
 ICoord2D start;Rva002E7875WorldToCell(&start,true,from);
 PathfindLayerEnum fromLayer=TheTerrainLogic->getLayerForDestination(obj,from);
 parent=(PathfindCell *)rva001E3647Pos(fromLayer,from);
 if(!parent)return MAX_COST;
 {
 ICoord2D end;ICoord2D *ep=Rva002E7875WorldToCell(&end,true,&adjustTo);
 goal->allocateInfo((In002E6BA1 *)ep);
 if(parent!=goal)parent->allocateInfo((In002E6BA1 *)&start);
 }
 }
 Int priority=obj->m_template->priority;Bool flag=obj->m_template->flag;
 Rva002E8BCF info((const Rva002E8BCFSrc *)&locomotorSet,!flag,priority-1,obj->rva0028AFBB());
 if(!((Rva002E6DC4 *)this)->rva002E6DC4(&info,parent)) {parent->ReleaseInfo();goal->ReleaseInfo();return MAX_COST;}
 parent->StartPathfind((Int)goal);
 parent->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parent,goal);
 AddToOpenList(parent);
 while((parent=rva002F36E5())!=0) {
  parent->PutOnClosedList(&m_closedList);
  if(parent==goal) {Int cost=parent->m_pathInfo->totalCost;m_isTunneling=false;rva002F40E7();return cost;}
  if(cellCount>500)continue;
  CheckChangeLayers(parent,obj);
  static Int deltaX[]={1,0,-1,0,1,-1,-1,1};
  static Int deltaY[]={0,1,0,-1,1,1,-1,-1};
  const Int adjacent[5]={0,1,2,3,0};
  Bool neighborFlags[8]={false,false,false,false,false,false,false};
  for(Int i=0;i<8;++i) {
   neighborFlags[i]=false;
   ICoord2D coords={parent->getXIndex()+deltaX[i],parent->getYIndex()+deltaY[i]};ICoord2D next=coords;
   
   PathfindCell *neighbor=getCell((PathfindLayerEnum)parent->getLayer(),next.x,next.y);
   if(!neighbor)continue;
   if((unsigned char)((Rva002E6AF3 *)neighbor)->get() || (unsigned char)((Rva002E6B06 *)neighbor)->rva002E6B06())continue;
   if(i>=4 && !neighborFlags[adjacent[i-4]] && !neighborFlags[adjacent[i-3]])continue;
   if(!((Rva002E6DC4 *)this)->rva002E6DC4(&info,neighbor))continue;
   neighborFlags[i]=true;neighbor->allocateInfo((In002E6BA1 *)&next);++cellCount;
   Int cost=neighbor->CalcCostSoFar((const Rva002E6C79 *)parent);
   cost+=CalcExtraCosts(obj,parent,(Rva002EBC7FPair *)&next,radius,radius+(center?1:0),true);
   neighbor->m_pathInfo->flags&=~1U;
   neighbor->SetParentCell((Int *)parent);
   neighbor->m_pathInfo->costSoFar=(unsigned short)cost;
   Int remaining=rva002F0A72(neighbor,goal);
   neighbor->m_pathInfo->totalCost=(unsigned short)(neighbor->m_pathInfo->costSoFar+remaining);
   AddToOpenList(neighbor);
  }
 }
 m_isTunneling=false;rva002F40E7();goal->ReleaseInfo();return MAX_COST;
}

// Same-TU callees of GetHordeUnitPath. Retail compiled the cell-info pool
// helpers (0x002E8B7A, 0x002E6BA1) and the ICoord2D equality body in this
// unit: with the bodies visible the cell indices passed to them are not
// escaped, so startCellNdx/goalCellNdx/newCellCoord share retail's frame slots.
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

inline __declspec(noinline) void Rva002E6BA1::rva002E6BA1(int lhs, In002E6BA1 *rhs)
{
	m_30 = lhs;
	m_00 = rhs->x;
	m_04 = rhs->y;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_12 = 0;
	memset(m_14, 0, 20);
	m_2C &= 0xffffffe0;
	m_28 = 0;
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
inline __declspec(noinline) MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, Int lhs, In002E6BA1 *in)
{
	MixFileInfoBuffer *node = *pp;
	node->bfmeUnlink();
	((Rva002E6BA1 *)node)->rva002E6BA1(lhs, in);
	return node;
}

// ICoord2D::operator== (0x00004CAD, owner icoord.cpp): the header inline
// retail kept out of line under /O1; only its visibility matters here.
inline bool ICoord2D::operator==(const ICoord2DBase &that) const
{
	return x == that.x && y == that.y;
}

// Pathfinder::GetHordeUnitPath, retail 0x002F6075 (1128 bytes) RET 8. WorldBuilder
// D61920 names it (pathfinder.cpp:11593-11641); caller micropathToPosition
// 0x0026412B. A 200-cell bounded A* from the object cell to the destination
// cell, shaped like CheckPathCost above.
Path *Pathfinder::GetHordeUnitPath(Object *obj, const Coord3D *destination)
{
	m_ignoreObstacleID = (ObjectID)0;
	Bool centerInCell = Rva002EBBFBIsOdd(obj);
	const Coord3D *objPos = (const Coord3D *)obj->position;
	ICoord2D startCellNdx;
	{
		Coord3D from;
		from.x = objPos->x;
		from.y = objPos->y;
		from.z = objPos->z;
		// 0x002E7917 through its hidden-result ABI, writing startCellNdx in place.
		typedef void (Pathfinder::*CellOut)(ICoord2D *, bool, const Coord3D *);
		(this->*reinterpret_cast<CellOut>(&Pathfinder::Rva002E7917))(&startCellNdx, centerInCell, &from);
	}
	ICoord2D goalCellNdx;
	Rva002E7875WorldToCell(&goalCellNdx, centerInCell, destination);
	if (startCellNdx == *(const ICoord2DBase *)&goalCellNdx)
		return 0;

	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	char *ai = obj->m_258;
	Rva002E8BCF info((const Rva002E8BCFSrc *)(ai + 0x1cc), !flag, priority - 1, obj->rva0028AFBB());
	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(obj, destination);
	PathfindCell *goalCell = getCell(destinationLayer, goalCellNdx.x, goalCellNdx.y);
	if (!goalCell)
		return 0;
	if (!((Rva002E6DC4 *)this)->rva002E6DC4(&info, goalCell))
		return 0;
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindCell *parentCell = getCell(layer, startCellNdx.x, startCellNdx.y);
	if (!parentCell)
		return 0;

	goalCell->allocateInfo((In002E6BA1 *)&goalCellNdx);
	parentCell->allocateInfo((In002E6BA1 *)&startCellNdx);
	parentCell->StartPathfind((Int)goalCell);
	parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
	AddToOpenList(parentCell);

	Int cellCount = 0;
	for (parentCell = rva002F36E5(); parentCell != 0; parentCell = rva002F36E5())
	{
		if (parentCell == goalCell)
		{
			Path *path = new Path;
			PrependCells(path, objPos, goalCell, centerInCell);
			path->wordC = 1;
			rva002F40E7();
			goalCell->ReleaseInfo();
			return path;
		}
		parentCell->PutOnClosedList(&m_closedList);
		if (cellCount > 200)
			break;
		CheckChangeLayers(parentCell, obj);

		static Int deltaX[] = {1, 0, -1, 0, 1, -1, -1, 1};
		static Int deltaY[] = {0, 1, 0, -1, 1, 1, -1, -1};
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8];
		for (Int i = 0; i < 8; ++i)
		{
			neighborFlags[i] = false;
			Int newX = parentCell->getXIndex() + deltaX[i];
			Int newY = parentCell->getYIndex() + deltaY[i];
			ICoord2D newCellCoord;
			newCellCoord.x = newX;
			newCellCoord.y = newY;
			PathfindCell *newCell = getCell((PathfindLayerEnum)parentCell->getLayer(), newX, newY);
			if (!newCell)
				continue;
			if ((unsigned char)((Rva002E6B06 *)newCell)->rva002E6B06())
				continue;
			if ((unsigned char)((Rva002E6AF3 *)newCell)->get())
				continue;
			if (newCell->getLayer() != parentCell->getLayer()
				&& newCell->getLayer() != parentCell->getConnectLayer()
				&& newCell->getConnectLayer() != parentCell->getLayer()
				&& !(parentCell->getConnectLayer() == 16 && newCell->getConnectLayer() == parentCell->getConnectLayer()))
				continue;
			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
				continue;
			if (!((Rva002E6DC4 *)this)->rva002E6DC4(&info, newCell))
			{
				newCell->allocateInfo((In002E6BA1 *)&newCellCoord);
				newCell->PutOnClosedList(&m_closedList);
				continue;
			}
			neighborFlags[i] = true;
			if (!newCell->m_pathInfo)
				cellCount++;
			newCell->allocateInfo((In002E6BA1 *)&newCellCoord);
			Int newCostSoFar = newCell->CalcCostSoFar((const Rva002E6C79 *)parentCell);
			Int dx = abs(newX - goalCell->getXIndex());
			Int dy = abs(newY - goalCell->getYIndex());
			if (newCell->rvaBit16() && dx + dy > 3)
				newCostSoFar += 10;
			newCell->m_pathInfo->flags &= ~1U;
			Int costRemaining = rva002F0A72(newCell, goalCell);
			if (newCell->getType() == PathfindCell::CELL_OBSTACLE)
				newCostSoFar += 1000;
			newCell->m_pathInfo->costSoFar = (unsigned short)newCostSoFar;
			newCell->SetParentCell((Int *)parentCell);
			newCell->m_pathInfo->totalCost = newCell->m_pathInfo->costSoFar + costRemaining;
			AddToOpenList(newCell);
		}
	}
	rva002F40E7();
	goalCell->ReleaseInfo();
	return 0;
}

// Pathfinder::AdjustDestination, retail [0x002FCFCF,0x002FD344) RET16, 885
// bytes. WorldBuilder D43BA0 names Pathfinder::AdjustDestination (assert
// lines 4455..4457); clean BFME1 PathfinderAdjustDestination003F6090 (donor
// 9cbfb551) supplies the semantic and control spine. Target facts: projectile
// kind bit 25, water kind bit 191 through TerrainLogic slot 0x4C, layer-height
// slot 0x1C, kind mask 0x4000 on template word 0x108 selecting the layer, the
// spiral search budget at TheWritableGlobalData+0x11F0, the found-cell copy
// through Rva002E8C4DCall, and the tighten/cost group check.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct PathfinderSearchRadiusView { char pad[0x11F0]; Int searchRadius; };
static __forceinline Coord3D adjustCellCenter(bool center,Rva002E8C23Pair *cell,PathfindLayerEnum layer) {
	Coord3D pos;return *(Coord3D *)Rva002E8C4DCall((int)&pos,center,cell,layer);
}
static __forceinline Bool findAdjustedCell(Pathfinder *finder,ICoord2D *cell,Bool center,Coord3D *dest,Pathfinder_IsCheckForAdjust *info) {
	ICoord2D found={0,0};
	if(!finder->rva002F8E2D(cell,((const PathfinderSearchRadiusView *)TheWritableGlobalData)->searchRadius,&found,info))return false;
	if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"  got %d,%d",found.x,found.y);
	*dest=adjustCellCenter(center,(Rva002E8C23Pair *)&found,info->m_layer);return true;
}
Bool Pathfinder::AdjustDestination(Object *obj,const LocomotorSet &locomotorSet,Coord3D *dest,const Coord3D *groupDest)
{
	if(g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile,"  Pathfinder::AdjustDestination() onEnter dest=%g,%g,%g",dest->x,dest->y,dest->z);
	if(obj->m_template->hasKind(25)) {
		if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"  projectile return TRUE");
		return true;
	}
	Bool center=Rva002EBBFBIsOdd(obj);
	ICoord2D cell;Rva002E7875WorldToCell(&cell,center,dest);
	if(g_00E03745 && theLogicRandomLogFile)
		fprintf((FILE *)theLogicRandomLogFile,"  AdjDest obj=%i, dest=%g,%g,%g, center=%i",obj->getID(),dest->x,dest->y,dest->z,center?1:0);
	PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,dest);
	float height=0.0f;
	if(groupDest)height=groupDest->z;
	else if(!obj->m_template->hasKind(191) || !((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(dest->x,dest->y,&height,0,0))
		height=TheTerrainLogic->getLayerHeight(dest->x,dest->y,layer,0,true);
	Pathfinder_IsCheckForAdjust info(this,obj,(void *)&locomotorSet,*dest,groupDest,height,(*(const unsigned int *)obj->m_template->kinds & 0x4000)?layer:PATHFIND_LAYER_UNKNOWN);
	if(findAdjustedCell(this,&cell,center,dest,&info)) {
		Bool badGroup=false;
		if(groupDest) {
			if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        groupDest tighten path case...");
			TightenPath(obj,locomotorSet,dest,groupDest);
			Int cost=CheckPathCost(obj,locomotorSet,groupDest,dest);
			Int dx=(Int)fabs(groupDest->x-dest->x);
			Int dy=(Int)fabs(groupDest->y-dest->y);
			Int distance=dx+dy;
			if(distance*1.4f<cost) {
				badGroup=true;
				if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        badGroup = true in tighten case");
			}
		}
		if(!badGroup)return true;
	}
	if(info.m_28) {
		if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"  got with allies %d,%d",info.fallback.x,info.fallback.y);
		*dest=adjustCellCenter(center,&info.fallback,info.m_layer);return true;
	}
	if(groupDest) {
		if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"  IterateCircular with groupDest");
		return rva002F90E9(&cell,((const PathfinderSearchRadiusView *)TheWritableGlobalData)->searchRadius,&Pathfinder_IsCheckForAdjust(this,obj,(void *)&locomotorSet,*dest,0,dest->z,info.m_2C));
	}
	if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"  got NOTHING");
	return false;
}

// 0x002E79A8 (186 B): the cell-to-world centre, WorldBuilder D4DC20 (Zero
// Hour's adjustCoordToCell returning the point): the cell corner plus a half
// cell (centred) or a small inset, scaled by the cell size; ground cells take
// the water height when there is water, else the layer height.
PathfinderCellPoint rva002E79A8(Bool centerInCell, Int cellX, Int cellY, PathfindLayerEnum layer)
{
	PathfinderCellPoint pos;
	if (centerInCell) {
		pos.x = ((float)cellX + 0.5f) * 10.0f;
		pos.y = ((float)cellY + 0.5f) * 10.0f;
	} else {
		pos.x = ((float)cellX + 0.05f) * 10.0f;
		pos.y = ((float)cellY + 0.05f) * 10.0f;
	}
	if (layer != PATHFIND_LAYER_GROUND || !((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(pos.x, pos.y, &pos.z, 0, 0))
		pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer, 0, true);
	return pos;
}
// 0x002E8C23 (42 B): a cell's centre point, returned through the hidden pointer.
// In-TU so PatchPath's cell centre stays unescaped and shares goalPos's slot.
PathfinderCellPoint Rva002E8C23Call(Bool centerInCell, PathfindCell *cell)
{
	return rva002E79A8(centerInCell, cell->getXIndex(), cell->getYIndex(), (PathfindLayerEnum)cell->getLayer());
}
void Pathfinder::PrependCells(Path *path,const Coord3D *fromPos,PathfindCell *goalCell,Bool center)
{
 Coord3D pos;
 PathfindCell *cell,*prevCell=0;
 Bool goalCellNull=(goalCell->getParentCell()==0);
 for(cell=goalCell;cell->getParentCell();cell=cell->getParentCell()) {
  pos=Rva002E8C23Call(center,cell);
  if(prevCell && cell->getXIndex()==prevCell->getXIndex() && cell->getYIndex()==prevCell->getYIndex()) {
   PathfindLayerEnum layer=(PathfindLayerEnum)cell->getLayer();
   if(layer==PATHFIND_LAYER_GROUND)layer=(PathfindLayerEnum)prevCell->getLayer();
   path->firstNode->layer=layer;continue;
  }
  Bool canOptimize=true;
  if(cell->getType()==2) {
   if(prevCell && prevCell->getType()!=2) {if(path->firstNode)path->firstNode->canOptimize=false;}
  } else {if(prevCell && prevCell->getType()==2)canOptimize=false;}
  if(cell->getParentWaypoint()) {
   Waypoint *parent=cell->getParentWaypoint();
   Int id=parent->id;pos=parent->location;
   if(id!=0x7fffffff) {
    if(cell->waypoint) {
     if(path->firstNode){path->firstNode->portalID=cell->waypoint->id;path->firstNode->canOptimize=false;}
     path->prependNode(&cell->waypoint->location,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
    }
    Waypoint *link=cell->getParentWaypoint()->chainNext;
    while(link) {
     if(path->firstNode){path->firstNode->portalID=link->id;path->firstNode->canOptimize=false;}
     path->prependNode(&link->location,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
     if(link->linkCount!=0)break;
     link=link->chainNext;
    }
    if(path->firstNode){path->firstNode->portalID=id;path->firstNode->canOptimize=false;}
   }
  }
  path->prependNode(&pos,TheTerrainLogic->getLayerForDestination(0,&pos),0x7fffffff);
  path->firstNode->canOptimize=canOptimize;
  if(cell->m_pathInfo->flags&1)path->blockedByAlly=true;
  if(prevCell)prevCell->m_pathInfo->parent=0;
  prevCell=cell;
 }
 if(cell && cell->m_pathInfo) {
  if(goalCellNull) {pos=Rva002E8C23Call(center,cell);path->prependNode(&pos,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);}
  if(fromPos->x!=path->firstNode->position.x || fromPos->y!=path->firstNode->position.y)
   path->prependNode(fromPos,(PathfindLayerEnum)cell->getLayer(),0x7fffffff);
 }
}

PathfindCell *Pathfinder::rva002F068F(){PathfindCell *cell=0;if(!m_openCells.empty())cell=m_openCells.front();return cell;}
// Semantic source: BFME1 verified donor0bef414b, AIPathfind.cpp getAircraftPath.
// Target facts: WB D31B00 and native2F3971..2F3B6B RET8; AI+258,
// locomotor+1F0 and appearance3; node pool, ctor, prepend and debug providers.
// Unlike the donor, retail replaces current->next three times without moving
// the cursor to the middle inserted node. Preserve that observed behavior.
// The 48-byte local scratch aggregate describes compiler storage only; its
// start/p3 union reproduces dead-start reuse proved by the retail stack accesses.
class Rva00065964ObjectPool { public: void *rva002635C2() throw(); };
extern Rva00065964ObjectPool g_pathNodePool;
template<int N> class AircraftSlots:public AircraftSlots<N-1>{public:virtual void slot(AircraftSlots<N>*);};
template<> class AircraftSlots<0>{};
struct AircraftLocomotorTemplate { char prefix[0x74];int appearance; };
struct AircraftLocomotor { void *vtable; AircraftLocomotorTemplate *data; };
class AircraftAIView:public AircraftSlots<109>{
public:
 virtual unsigned avoidObject();
 char prefix04[0x1f0-4]; AircraftLocomotor *locomotor;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class AI;
extern AI *TheAI;
struct PathfinderAircraftAIView { char prefix[0x10]; Pathfinder *pathfinder; };
static __forceinline PathNode *makeAircraftNode(const Coord3D *p) {
 void *memory=g_pathNodePool.rva002635C2();
 return memory?new(memory)PathNode(p,PATHFIND_LAYER_GROUND):0;
}
static __forceinline void appendAircraftNode(PathNode *current,PathNode *node) {
 current->next=node;
 if(node) node->previous=current;
}
Path *Pathfinder::GetAircraftPath(const Object *object,const Coord3D *to)
{
 Path *path=new Path;
 AircraftAIView *ai=reinterpret_cast<AircraftAIView *>(object->getAI());
 unsigned avoid=0;
 if(ai) avoid=ai->avoidObject();
 bool clips=false;
 if(ai && ai->locomotor && ai->locomotor->data->appearance==3) clips=true;
 // Local scratch only: retain the target-proven relative homes, not a retail class layout.
 struct { Coord3D p1,p2; union { Coord3D start; Coord3D p3; } stage; Coord3D adjusted; } scratch;
 scratch.adjusted.x=to->x; scratch.adjusted.y=to->y; scratch.adjusted.z=to->z;
 if(clips) CircleClipsTallBuilding(reinterpret_cast<const Coord3D *>(object->position),to,100.0f,avoid,&scratch.adjusted);
 path->prependNode(&scratch.adjusted,PATHFIND_LAYER_GROUND,0x7fffffff);
 // Native start-coordinate storage is later reused for the third detour output.
 scratch.stage.start.x=object->position[0]; scratch.stage.start.y=object->position[1]; scratch.stage.start.z=to->z;
 path->prependNode(&scratch.stage.start,PATHFIND_LAYER_GROUND,0x7fffffff);
 int limit=20;
 for(PathNode *node=path->firstNode;node && node->next;) {
  if(rva002F3392(node,node->next,avoid,&scratch.p1,&scratch.p2,&scratch.stage.p3)) {
   appendAircraftNode(node,makeAircraftNode(&scratch.stage.p3));
   appendAircraftNode(node,makeAircraftNode(&scratch.p2));
   appendAircraftNode(node,makeAircraftNode(&scratch.p1));
  }
  node=node->next;
  if(--limit<0) break;
 }
 for(PathNode *node=path->firstNode;node && node->next;node=node->next) node->nextOptimized=node->next;
 path->wordC=true;
 if(*(int *)((char *)TheWritableGlobalData+0x9b8)==1) reinterpret_cast<PathfinderAircraftAIView *>(TheAI)->pathfinder->SetDebugPath((Rva002EDEABArg *)path);
 return path;
}

// WB D3AF90 and native2EC8C3..2EC9E1 identify the sixteen-ID goal-node query.
// BFME1 donor0bef PathfinderRva003E5E40 demonstrates visible provider bodies
// for output escape analysis. These three current BFME2 providers are exact
// here; keeping calls out of line lets MSVC reuse dead radius/cell slots.
class PathfinderOverlapTerrainView:public PathfinderNativeSlots<44> { public: virtual bool objectInteractsWithBridgeLayer(Object *,int); };
int isGroundOrBridgeLayer(int);
extern int g_Va00DFECD0;
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
void Rva002EBCD6Split(void *,int *,int *);
int Pathfinder::_GetOverlapUnits(Object *object,const Coord3D *position,int *out)
{
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)isGroundOrBridgeLayer(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 ++g_Va00DFECD0;
 object->rva002E6B89();
 for(int x=cell.x-below;x<cell.x+above;++x) {
  for(int y=cell.y-below;y<cell.y+above;++y) {
   for(int k=0;k<numLayers;++k) {
    PathCollisionCell *pathCell=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[k],x,y));
    if(pathCell && pathCell->info) {
     for(PathCollisionNode *node=pathCell->info->goals;node;node=node->next) {
      if(node->object->rva002E6B89()) continue;
      out[count++]=node->object->getID();
      if(count==16) return count;
     }
    }
   }
  }
 }
 return count;
}



// Rehomed canonical converter: original PathfindShimWorldToCell.cpp,162B.
// Reuses this TU's existing floor/fistp codegen helper; no new asm is added.
static const float PATHFINDER_CELL_INV = 1.0f / 10.0f;
inline __declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
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

//
// ?Rva002EBC14Cell@@YAPAUICoord2D@@PAU1@PAXPBUCoord3D@@@Z, retail 0x002EBC14 (32 bytes).
// Free __cdecl (ICoord2D*, void*, const Coord3D*) -> ICoord2D*: odd = IsOdd(p),
// WorldToCell(out, odd, pos), return out. Evidence: retail pushes pos then p,
// calls IsOdd, pops p dead into ecx (ecx never read, so not __thiscall),
// pushes eax/out, calls WorldToCell, reloads out into eax, caller-cleans 0xc.
// Callees: the rowed parity test 0x002EBBFB (Rva002EBBFBIsOdd.cpp, rowed with
// an unsigned char result) and the converter rehomed above.
// Retail passes the parity result straight on with no test/setne, so it is
// a bool here, through the bool spelling pinned at the same address; the
// parity body compiles identically under either result type.
struct ICoord2D;
struct Coord3D;
struct ICoord2D *__cdecl Rva002E7875WorldToCell(struct ICoord2D *out, bool center, const struct Coord3D *pos);
bool __cdecl Rva002EBBFBIsOdd(void *p);

inline __declspec(noinline) struct ICoord2D *__cdecl Rva002EBC14Cell(struct ICoord2D *out, void *p, const struct Coord3D *pos)
{
	Rva002E7875WorldToCell(out, Rva002EBBFBIsOdd(p), pos);
	return out;
}

// ?Rva002EBCD6Split@@YAXPAXPAH1@Z @0x002EBCD6 32B unlock 9 callers
// Evidence: sibling Split at 0x002EBCA7 in Rva002EBBFBIsOdd.cpp; retail calls rowed Get then cdq-sub-sar half store then remainder store.
int __cdecl Rva002E9B31Get(void *p);
__declspec(noinline) inline void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest)
{
	int v = Rva002E9B31Get(p);
	int h = v / 2;
	*outHalf = h;
	*outRest = v - h;
}

// WB D3B2A0 / native2EC9E1..2ECAFF: list+14, unique IDs, capacity16.
int Pathfinder::GetOverlapGoalUnits(Object *object,const Coord3D *position,int *out)
{
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)isGroundOrBridgeLayer(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 ++g_Va00DFECD0;
 object->rva002E6B89();
 for(int x=cell.x-below;x<cell.x+above;++x) {
  for(int y=cell.y-below;y<cell.y+above;++y) {
   for(int k=0;k<numLayers;++k) {
    PathCollisionCell *pathCell=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[k],x,y));
    if(pathCell && pathCell->info) {
     for(PathCollisionNode *node=pathCell->info->occupants;node;node=node->next) {
      if(node->object->rva002E6B89()) continue;
      out[count++]=node->object->getID();
      if(count==16) return count;
     }
    }
   }
  }
 }
 return count;
}

// WB D3B5B0 / native2ECAFF..2ECC0D: self skipped; same horde1, other2.
int Pathfinder::CountOverlapHordeGoalUnits(Object *object,const Coord3D *position)
{
 if (!object->container) return 0;
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)isGroundOrBridgeLayer(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 for(int x=cell.x-below;x<cell.x+above;++x) {
  for(int y=cell.y-below;y<cell.y+above;++y) {
   for(int k=0;k<numLayers;++k) {
    PathCollisionCell *pathCell=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[k],x,y));
    if(pathCell && pathCell->info) {
     for(PathCollisionNode *node=pathCell->info->hordeGoalNodes;node;node=node->next) {
      if(node->object==object) continue;
      if(node->object->container==object->container) ++count;
      else count+=2;
     }
    }
   }
  }
 }
 return count;
}


// WB D3B920 / native2F133C..2F14F9: perimeter query, up to16 unique IDs.
extern GameLogic *TheGameLogic;
int Pathfinder::_GetAdjacentUnits(Object *object,const Coord3D *position,int *out)
{
 ICoord2D cell;
 int below,above;
 int layers[2];
 Rva002EBC14Cell(&cell,object,position);
 Rva002EBCD6Split(object,&below,&above);
 layers[0]=object->rva0028B511();
 int numLayers=1;
 if (!(unsigned char)isGroundOrBridgeLayer(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(object,layers[0])) {
  layers[1]=1; numLayers=2;
 }
 int count=0;
 ++g_Va00DFECD0;
 object->rva002E6B89();
 for(int x=cell.x-below-1;x<cell.x+above+1;++x) {
  int step=(x==cell.x-below-1 || x==cell.x+above)?1:below+above+1;
  for(int y=cell.y-below-1;y<cell.y+above+1;y+=step) {
   for(int k=0;k<numLayers;++k) {
    PathCollisionCell *pathCell=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[k],x,y));
    if(pathCell && pathCell->info) {
     for(PathCollisionNode *node=pathCell->info->goals;node;node=node->next) {
      if(node->object->rva002E6B89()) continue;
      out[count++]=node->object->getID();
      if(count==16) return count;
     }
     if(!pathCell->info->goals) {
      Object *fallback=TheGameLogic->findObjectByID((ObjectID)(pathCell->info?pathCell->info->fallbackID:0));
      if(fallback && !fallback->rva002E6B89()) {
       out[count++]=fallback->getID();
       if(count==16) return count;
      }
     }
    }
   }
  }
 }
 return count;
}


// Native2F477E..2F4ABF RET16 full835. ZH clientSafeQuickDoesPathExist
// supplies terrain-zone reachability; BFME2-specific object status, template
// priority, surface override, complete diagnostics and waypoint-zone fallback
// are reconstructed independently from this target. Caller ABI/pin retained.
struct Rva002CECAETarget;
void AppendInLogicUpdateOnly(Rva002CECAETarget *,const char *,...);
class Rva0028B984ByteField {public:unsigned char get()const;};
Bool Pathfinder::QuickDoesPathExist(Object *obj,const Coord3D *from,const Coord3D *to,Int overrideSet)
{
 if(g_00E03745 && theLogicRandomLogFile) AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,
  "\t\t  Pathfinder::QuickDoesPathExist() called with: obj=%s(%d), from=%g,%g,%g, to=%g,%g,%g",
  ((const AsciiString *)((const char *)obj->m_template+0x64))->str(),obj->getID(),from->x,from->y,from->z,to->x,to->y,to->z);
 if(obj->testStatus(QuickStatus49)) {
  if(g_00E03745 && theLogicRandomLogFile)AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,"\t\t  Pathfinder::QuickDoesPathExist() Failure 1");return false;
 }
 if(((Rva0028B984ByteField *)obj)->get()==1) {
  if(g_00E03745 && theLogicRandomLogFile)AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,"\t\t  Pathfinder::QuickDoesPathExist() Success 1");return true;
 }
 LocomotorSet *set;
 char *ai=obj->m_258;
if(!overrideSet && !ai) {if(g_00E03745 && theLogicRandomLogFile)AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,"\t\t  Pathfinder::QuickDoesPathExist() Failure 2");return false;} if(overrideSet)set=(LocomotorSet *)overrideSet;else set=(LocomotorSet *)(ai+0x1CC);
 if(!(set->getValidSurfaces()&0x8F)) {
  if(g_00E03745 && theLogicRandomLogFile)AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,"\t\t  Pathfinder::QuickDoesPathExist() Failure 3");return false;
 }
 PathfindLayerEnum destinationLayer=TheTerrainLogic->getLayerForDestination(obj,to);
 PathfindLayerEnum fromLayer=TheTerrainLogic->getLayerForDestination(obj,from);
 PathfindCell *parent=rva002E8BF8(fromLayer,from);
 PathfindCell *goal=rva002E8BF8(destinationLayer,to);
 if(goal->getType()==2) {
  if(g_00E03745 && theLogicRandomLogFile)AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,"\t\t  Pathfinder::QuickDoesPathExist() Failure 4");return false;
 }
 Bool terrain=false;Int priority=obj->m_template->priority;Bool flag=obj->m_template->flag;
 Rva002E8BCF info((const Rva002E8BCFSrc *)set,!flag,priority-1,obj->rva0028AFBB());
 Rva002E99F9Sub460 *zones=(Rva002E99F9Sub460 *)&m_zoneManager;
 Int zone1=zones->rva0053241F(&info,parent->quickZone());
 if(parent->getType()==4)terrain=true;
 Int zone2=zones->rva0053241F(&info,goal->quickZone());
 if(goal->getType()==4)terrain=true;
 if(terrain) {
  zone1=zones->rva00531FD4(&info,parent->quickZone());
  zone1=zones->rva0053241F(&info,(unsigned short)zone1);
  zone1=zones->rva00531FD4(&info,(unsigned short)zone1);
  zone2=zones->rva00531FD4(&info,goal->quickZone());
  zone2=zones->rva0053241F(&info,(unsigned short)zone2);
  zone2=zones->rva00531FD4(&info,(unsigned short)zone2);
 }
 if(!IsValidMovementPositionForObject(to,destinationLayer,set->getValidSurfaces(),obj)) {
  if(g_00E03745 && theLogicRandomLogFile)AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,"\t\t  Pathfinder::QuickDoesPathExist() Failure 5");return false;
 }
 if(zone1==zone2) {
  if(g_00E03745 && theLogicRandomLogFile)AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,"\t\t  Pathfinder::QuickDoesPathExist() Success 2");return true;
 }
 if(g_00E03745 && theLogicRandomLogFile)AppendInLogicUpdateOnly((Rva002CECAETarget *)theLogicRandomLogFile,"\t\t  Pathfinder::QuickDoesPathExist() Default Exit");
 return rva002F4115(obj,zone1,zone2,(LocomotorSet *)overrideSet);
}

// Native 0x002F52A7..0x002F57E6, RET52. WB D58CF0 identifies
// Pathfinder::CheckForAdjust; ZH checkForAdjust is the semantic guide.
// Retail adds diagnostic logging, layer-footprint and original-Z checks.
Bool Pathfinder::CheckForAdjust(Object *obj, const LocomotorSet &loco,
 Bool isHuman, Int cellX, Int cellY, PathfindLayerEnum layer, Int radius,
 Bool center, Coord3D *dest, const Coord3D *groupDest, float originalZ,
 Int *options, Int onlyIfLayer)
{
 if (g_00E03745 && theLogicRandomLogFile)
  fprintf((FILE *)theLogicRandomLogFile,
   "\t\t  Pathfinder::CheckForAdjust called with: obj=%s(%d), loco=%s, isHuman=%s, cell=%d,%d, layer=%d, iRadius=%d, center=%s, groupDest=%g,%g,%g, originalZ=%g, onlyIfLayer=%d",
   ((const AsciiString *)((const char *)obj->m_template+0x64))->str(),obj->getID(),
   ((const AsciiString *)((const char *)&loco+0x18))->str(),isHuman?"TRUE":"FALSE",
   cellX,cellY,layer,radius,center?"TRUE":"FALSE",
   groupDest?groupDest->x:-1.0f,groupDest?groupDest->y:-1.0f,groupDest?groupDest->z:-1.0f,
   originalZ,onlyIfLayer);
 PathfindCell *cell=getCell(layer,cellX,cellY);
 if (!cell) {
  if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"        cellP is NULL, return FALSE.");
  return false;
 }
 if(cell->getType()==2) {
  if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"        cellP is CLIFF, return FALSE.");
  return false;
 }
 if(isHuman) {
  if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"        isHuman is TRUE");
  if(cellX<m_extentLowX || cellY<m_extentLowY || cellX>m_extentHighX || cellY>m_extentHighY) {
   if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"        cell %d,%d is outside m_logicalExtent lo:%d,%d hi:%d,%d",cellX,cellY,m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY);
   return false;
  }
 }
 if(!CheckDestination(obj,cellX,cellY,layer,radius,center,options,false)) {
  if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"        CheckDestination failed, return false");
  return false;
 }
 if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"        CheckDestination passed");
 Coord3D temporary;
 Coord3D adjustDest=*(Coord3D *)rva002EBC59(&temporary,obj,cellX,cellY,cell->getLayer());
 if(!obj->m_template->hasKind(12)) {
  if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"        object is not kindof aircraft");
  if(onlyIfLayer) {
   if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"        onlyIfLayer=%d",onlyIfLayer);
   Int extraRadius=radius;
   if(center)extraRadius=radius+1;
   for(Int i=cellX-radius;i<cellX+extraRadius;++i) {
    for(Int j=cellY-radius;j<cellY+extraRadius;++j) {
     PathfindCell *ground=getCell((PathfindLayerEnum)onlyIfLayer,i,j);
     if(!ground || ground->getLayer()!=onlyIfLayer) {
      if(g_00E03745) {
       if(ground) {
        if(theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        ground unit failed iteration: i=%d, j=%d, cell=VALID, cellLayer=%d, onlyIfLayer",i,j,ground->getLayer(),onlyIfLayer);
       } else {
        if(theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        ground unit failed iteration: i=%d, j=%d, cell=NULL, onlyIfLayer",i,j,onlyIfLayer);
       }
      }
      return false;
     }
    }
   }
  }
  if(originalZ>0.0f && fabs(adjustDest.z-originalZ)>50.0f) {
   if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        MinasTirith check failed, return FALSE: originalZ=%g, adjustDest.z=%g",originalZ,adjustDest.z);
   return false;
  }
  Bool adjustedPathExists=QuickDoesPathExist(obj,(const Coord3D *)obj->position,&adjustDest,0);
  if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        adjustedPathExists=%s",adjustedPathExists?"TRUE":"FALSE");
  if(!QuickDoesPathExist(obj,(const Coord3D *)obj->position,dest,0)) {
   if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        QuickDoesPathExist1 fails. Try adjusted destination");
   if(QuickDoesPathExist(obj,dest,&adjustDest,0)) {
    if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        QuickDoesPathExist2 succeeds. adjustedPathExists");
    adjustedPathExists=true;
   }
  } else {
   if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        QuickDoesPathExist1 succeeds");
  }
  if(!adjustedPathExists) {
   if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        returning false because adjustedPathExists is false");
   return false;
  }
 }
 if(g_00E03745 && theLogicRandomLogFile)fprintf((FILE *)theLogicRandomLogFile,"        dest calculated to be %g,%g,%g and returning true",adjustDest.x,adjustDest.y,adjustDest.z);
 *dest=adjustDest;
 return true;
}

// Pathfinder::AdjustHordeMeleeDestination, retail 0x002FA202 (218 bytes).
// Name from WorldBuilder (pathfinder.cpp line 4599, wb-name-unverified);
// Zero Hour's checkForAdjust purpose with the melee/horde functor: searches
// around dest's cell for one the functor accepts (else the functor's
// fallback cell at +0x1C when +0x24 is set) and moves dest there. The
// spiral-search budget lives at TheWritableGlobalData+0x11F4. The middle
// parameter travels opaquely into the functor's void* slot (callers pass
// the AI's LocomotorSet); spelling it void* keeps this TU free of the AI
// header the sibling AdjustDestination needs.
struct PathfinderHordeMeleeRadiusView { char pad[0x11F4]; Int searchRadius; };
static __forceinline Bool findHordeMeleeCell(Pathfinder *finder,const ICoord2D *cell,Bool center,Coord3D *dest,Pathfinder_IsCheckForMeleeHordeAdjust *info) {
	ICoord2D found={0,0};
	if(!finder->rva002F92BC(cell,((const PathfinderHordeMeleeRadiusView *)TheWritableGlobalData)->searchRadius,&found,info))return false;
	*dest=adjustCellCenter(center,(Rva002E8C23Pair *)&found,info->m_layer);return true;
}
Bool Pathfinder::AdjustHordeMeleeDestination(Object *obj,void *arg,Coord3D *dest)
{
	if(obj->m_template->hasKind(25))return true;
	Bool center=Rva002EBBFBIsOdd(obj);
	ICoord2D cell;Rva002E7875WorldToCell(&cell,center,dest);
	Pathfinder_IsCheckForMeleeHordeAdjust info(this,obj,arg,*dest,TheTerrainLogic->getLayerHeight(dest->x,dest->y,TheTerrainLogic->getLayerForDestination(obj,dest),0,true));
	if(findHordeMeleeCell(this,&cell,center,dest,&info))return true;
	if(info.m_24){*dest=adjustCellCenter(center,&info.m_1C,info.m_layer);return true;}
	return false;
}
// Pathfinder::InternalFindPath, retail [0x002FBBEB,0x002FC95E) RET24, 3443
// bytes. WorldBuilder D55050 names it (its "CritterDesync" log strings and the
// pathfinder.cpp asserts); the A* spine is Zero Hour's internalFindPath. BFME
// adds the CRC log, the KindOf 186 forward goal offset and its retry from the
// unshifted goal, the checkForMovement destination probes, the mine-shaft
// redirect, the hierarchical-path closest-cell fallback and the early give-up
// distance. The 9-argument neighbour expansion 0x002F83F5 is Zero Hour's
// examineNeighboringCells call shape (unnamed in WorldBuilder).
struct TCheckMovementInfo
{
	ICoord2D cell;					// +0x00
	PathfindLayerEnum layer;		// +0x08
	Int radius;						// +0x0C
	Bool centerInCell;				// +0x10
	Bool m_11;
	unsigned char m_pad12[2];
	unsigned int m_14;				// +0x14 option bits
	ObjectID m_18;					// +0x18 an object to ignore
	unsigned char m_1C[0x10];		// +0x1C the mover's Rva002E8BCF
	Int m_2C;
	Bool m_30,m_31,m_32;
	unsigned char m_pad33;
	Int m_34;
};
class Rva002E6FDF
{
public:
	Rva002E6FDF *rva002E6FDF();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_11;
	char m_pad12[2];
	int m_14;
	int m_18;
	int m_1C;
	unsigned char m_20;
	unsigned char m_21;
	char m_pad22[2];
	int m_24;
	unsigned char m_28;
	char m_pad29[3];
	int m_2C;
	unsigned char m_30;
	unsigned char m_31;
	unsigned char m_32;
	char m_pad33[1];
	int m_34;
};
class HierarchicalPath { public: Int lookUpPositionOnPath(const Coord3D *); };
struct PathfinderCellLimitView { char pad[0x1210]; unsigned int maxCells; };
extern unsigned int PathfinderSearchCellsVisited;	// 0x00DFF0CC, also cleared by FindSafePath
// A cell centre temporary passed on by address.
static __forceinline Coord3D *cellPointArg(const PathfinderCellPoint &pathfinderCellPoint) { return (Coord3D *)&pathfinderCellPoint; }
// A Bool argument travels as its whole stack dword (push dword ptr [bool]).
static __forceinline void *boolArg(const Bool &value) { return *(void *const *)&value; }
static __forceinline Bool pathfinderLogOn() { return g_00E03745 && theLogicRandomLogFile; }
static __forceinline void pathfinderLog(const char *text) { fprintf((FILE *)theLogicRandomLogFile,text); }
// Coord2D::Rotate(float) inlined: the CRT pair runs, then fsincos replaces it.
static __forceinline void rotateOffset(float &x, float &y, float angle)
{
	float sine = sinf(angle);
	float cosine = cosf(angle);
	__asm
	{
		fld angle
		fsincos
		fstp cosine
		fstp sine
	}
	float rotated = x * cosine - y * sine;
	y = y * cosine + x * sine;
	x = rotated;
}
static __forceinline void setInfoCell(TCheckMovementInfo &info, ICoord2D pathCell) { info.cell = pathCell; }
static __forceinline void setInfoCellYX(TCheckMovementInfo &info, ICoord2D pathCell) { info.cell.y = pathCell.y; info.cell.x = pathCell.x; }
// 0x002E75A3 (304 B), rehomed from AI/PathfinderRva002E75A3.cpp: retail compiles
// it in this object, so InternalFindPath's &clipFrom/&adjustTo stay local.
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
bool __cdecl ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2, IRegion2D *clipRegion);
// Retail floors through math.h's float overload (floor(float) -> floorf), not
// realToIntFloor's direct double call: the extra inline level moves a pop ecx.
static __forceinline float clipCellFloor(float f)
{
	return floor(f);
}
static __forceinline long clipCellRound(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
void Pathfinder::clip(Coord3D *lhs, Coord3D *rhs)
{
	ICoord2D p2;
	ICoord2D p1;
	IRegion2D *clip = (IRegion2D *)&m_clampLo;
	ICoord2D c2;
	ICoord2D c1;
	p1.x = clipCellRound(clipCellFloor(lhs->x * PATHFINDER_CELL_INV));
	p1.y = clipCellRound(clipCellFloor(lhs->y * PATHFINDER_CELL_INV));
	p2.x = clipCellRound(clipCellFloor(rhs->x * PATHFINDER_CELL_INV));
	p2.y = clipCellRound(clipCellFloor(rhs->y * PATHFINDER_CELL_INV));
	if (!ClipLine2D(&p1, &p2, &c1, &c2, clip))
		return;
	float base = 0.05f;
	if (p1.x != c1.x || p1.y != c1.y) {
		lhs->x = (float)(c1.x * 10) + base;
		lhs->y = (float)(c1.y * 10) + base;
	}
	if (p2.x != c2.x || p2.y != c2.y) {
		rhs->x = (float)(c2.x * 10) + base;
		rhs->y = (float)(c2.y * 10) + base;
	}
}
// 0x002E6FDF (59 B), rehomed from Rva002E6FDFClear.cpp.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
inline __declspec(noinline) Rva002E6FDF *Rva002E6FDF::rva002E6FDF()
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

// 0x002E6DC4 (168 B), rehomed from Rva002E6DC4Check.cpp: retail compiles it in
// this object, so &info.m_1C handed to it from checkForMovement stays local.
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
inline __declspec(noinline) bool Rva002E6DC4::rva002E6DC4(void *a_raw, void *b_raw)
{
	Rva002E6DC4_P1 *lhs = (Rva002E6DC4_P1 *)a_raw;
	Rva002E6DC4_P2 *rhs = (Rva002E6DC4_P2 *)b_raw;
	if (!rhs)
		return false;
	unsigned int flags = rhs->m_C;
	unsigned char b18 = (unsigned char)(flags >> 18);
	if ((b18 & 1) != 0 && lhs->m_5 != 0)
		return false;
	unsigned int low = flags & 0xF;
	switch (low) {
	case 3:
		if ((flags & 0x3F0) != 0x10)
			return false;
		break;
	case 4: {
		void *chase = rhs->m_0 ? rhs->m_0->m_28 : 0;
		if (chase == m_48)
			return true;
		break;
	}
	default:
		break;
	}
	if ((lhs->m_0 & g_00DBD33C[low]) == 0)
		return false;
	unsigned char b17 = (unsigned char)(flags >> 17);
	if (lhs->m_4 != 0 && (b17 & 1) != 0)
		return false;
	if (lhs->m_C != 0) {
		unsigned char b22 = (unsigned char)(flags >> 22);
		if (((b22 & 1) == 0) && low == 4)
			return false;
	}
	int v = lhs->m_8;
	if (v < 0 || (int)((flags >> 19) & 3) <= v)
		return true;
	return false;
}
// 0x002ECC0D (WB D3D140): obj fits at pos when every footprint cell exists and passes the mover's
// surface check, checkForMovement accepts it and CalcCollisionFreeExtraCosts reports no conflict.
Bool Pathfinder::rva002ECC0D(Object *obj, const Coord3D *pos)
{
	TCheckMovementInfo info;
	((Rva002E6FDF *)&info)->rva002E6FDF();
	Rva002EBCA7Split(obj, &info.radius, (unsigned char *)&info.centerInCell);
	{
		ICoord2D cell;	// shares its slot with the later locomotor view
		info.cell = *Rva002E7875WorldToCell(&cell, info.centerInCell, pos);
	}
	info.layer = (PathfindLayerEnum)obj->rva0028B511();
	{
		Int priority = obj->m_template->priority;
		Bool flag = obj->m_template->flag;
		AIUpdateInterface *ai = obj->getAI();
		Rva002E8BCF movement((const Rva002E8BCFSrc *)((const char *)ai + 0x1cc), !flag, priority - 1, obj->rva0028AFBB());
		Int i, j;
		for (i = -info.radius; i < info.radius; i++) {
			for (j = -info.radius; j < info.radius; j++) {
				PathfindCell *cell = getCell(info.layer, info.cell.x + i, info.cell.y + j);
				if (!cell)
					return false;
				if (!((Rva002E6DC4 *)this)->rva002E6DC4(&movement, cell))
					return false;
			}
		}
	}
	info.m_11 = false;
	info.m_14 = obj->m_template->testKindWord(90) ? 1 : 16;
	info.m_18 = obj->getAI() ? (ObjectID)((Rva0006E009DwordField *)obj->getAI())->get() : (ObjectID)0;
	if (!checkForMovement(obj, info))
		return false;
	return CalcCollisionFreeExtraCosts(obj, 0, (Rva002EBC7FPair *)&info, info.layer,
		info.radius, info.radius + (info.centerInCell ? 1 : 0), false) == 0;
}
// 0x002EA34A (782 B), rehomed from PathfinderCheckForMovement.cpp.
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
		info.m_34++;
	if (cell->rvaBit18() && obj->rva0028AFBB())
		info.m_34++;
	if (info.m_14 & 8)
	{
		Int layer = cell->getLayer();
		if (info.layer != layer)
		{
			if (info.layer == 1 && layer != 0x10)
				info.m_34++;
			else if ((unsigned char)Rva002E6E8AGet(info.layer) && layer != 0x10)
				info.m_34++;
		}
	}
	if ((info.m_14 & 4) && !((Rva002E6DC4 *)pf)->rva002E6DC4(info.m_1C, cell))
		info.m_34++;
}
static __forceinline Bool checkCellUnits(Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info, ObjectID *lastID)
{
	if (cell->rvaInfo14())
		info.m_32 = true;

	for (CheckMovementObjectNode *node = cell->getObjects(); node; node = node->m_next)
	{
		Object *unit = node->m_object;
		if (unit == obj)
			continue;
		if (unit->getID() == info.m_18)
			continue;
		if (unit->getID() == *lastID)
			continue;
		*lastID = (ObjectID)unit->getID();

		Bool check = false;
		Bool isAlly;
		if (cell->hasObjects())
		{
			isAlly = obj->getRelationship(unit) == ALLIES;
			if (isAlly)
				info.m_31 = true;
			if (info.m_11)
				check = true;
			if (!isAlly && (info.m_14 & 0x10))
				check = true;
		}
		if (unit->IsAtGoalPosition())
		{
			isAlly = obj->getRelationship(unit) == ALLIES;
			check = true;
		}
		if (!check)
			continue;

		if (isAlly && obj->m_template->testKindWord(0x74) && unit->m_template->testKindWord(0x74))
			continue;
		if (obj->m_template->testKindWord(0x7D) && unit->m_template->testKindWord(8))
			continue;
		if (isAlly && obj->m_template->testKindWord(0xBA) && !unit->m_template->testKindWord(0xBA))
		{
			info.m_32 = false;
			continue;
		}
		if (obj->m_template->testKindWord(0xBB))
		{
			info.m_32 = false;
			continue;
		}

		if (isAlly)
		{
			if (!unit->getAI())
				return false;
			if (info.m_14 & 2)
				return false;
			info.m_2C = 1;
			if (unit->m_template->testKindWord(0xBA) && !obj->m_template->testKindWord(0xBA))
				return false;
			continue;
		}

		if (obj->canCrushOrSquishNoAlly(unit, 2))
			continue;
		if (!(info.m_14 & 0x11))
			continue;
		AIUpdateInterface *ai = obj->getAI();
		if (!ai)
			return false;
		Object *goal = ((CheckMovementAIView *)ai)->m_stateMachine->getGoalObject();
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
static __forceinline Bool checkCell(Pathfinder *pf, Object *obj, CheckMovementCell *cell, TCheckMovementInfo &info, ObjectID *lastID)
{
	checkCellFlags(pf, obj, cell, info);
	return checkCellUnits(obj, cell, info, lastID);
}
static __forceinline Bool checkPairCellUnits(Object *&obj, CheckMovementCell *cell, TCheckMovementInfo &info, Int *lastID)
	{
		if (cell->rvaInfo14())
			info.m_32 = true;

		for (CheckMovementObjectNode *node = cell->getObjects(); node; node = node->m_next)
		{
			Object *unit = node->m_object;
			if (unit == obj || unit->getID() == info.m_18 || unit->getID() == *lastID) continue;
			*lastID = (Int)unit->getID();

			Bool check = false;
			Bool isAlly;
			unsigned occupied=cell->hasObjects();
			Object *owner=obj;
			if (occupied)
			{
				isAlly = owner->getRelationship(unit) == ALLIES;
				if (isAlly)
					info.m_31 = true;
				if (info.m_11)
					check = true;
				if (!isAlly && (info.m_14 & 0x10))
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
				info.m_32 = false;
				continue;
			}
			if (owner->m_template->testKindWord(0xBB))
			{
				info.m_32 = false;
				continue;
			}

			if (isAlly)
			{
				if (!unit->getAI())
					return false;
				if (info.m_14 & 2)
					return false;
				info.m_2C = 1;
				if (unit->m_template->testKindWord(0xBA) && !owner->m_template->testKindWord(0xBA))
					return false;
				continue;
			}

			if (owner->canCrushOrSquishNoAlly(unit, 2))
				continue;
			if (!(info.m_14 & 0x11))
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
	info.m_2C = 0;
	info.m_31 = false;
	info.m_32 = false;
	info.m_30 = false;
	info.m_34 = 0;

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
				checkCellFlags(this, obj, cell, info);
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
Bool Pathfinder::checkForMovement(Object *obj, TCheckMovementInfo &info)
{
	info.m_2C = 0;
	info.m_31 = false;
	info.m_32 = false;
	info.m_30 = false;
	info.m_34 = 0;

	Int numCellsAbove = info.radius;
	if (info.centerInCell)
		numCellsAbove++;

	ObjectID lastID = (ObjectID)0;
	for (Int i = info.cell.x - info.radius; i < info.cell.x + numCellsAbove; i++)
	{
		for (Int j = info.cell.y - info.radius; j < info.cell.y + numCellsAbove; j++)
		{
			CheckMovementCell *cell = (CheckMovementCell *)getCell(info.layer, i, j);
			if (!cell)
				return false;
			if (!checkCell(this, obj, cell, info, &lastID))
				return false;
		}
	}
	return true;
}
static __forceinline void readMoverInfo(TCheckMovementInfo &info, Object *obj)
{
	char *ai = obj->m_258;
	info.m_18 = ai ? (ObjectID)((const Rva0006E009DwordField *)ai)->get() : (ObjectID)0;
}
struct Gen_p12pod {Int a[3];};
// Use the byte-verified out-of-line erase owner at 0x002A133B.
namespace _STL {
template <> Gen_p12pod *vector<Gen_p12pod, allocator<Gen_p12pod> >::erase(Gen_p12pod *, Gen_p12pod *);
}

// 0x002E7964 (68 B), rehomed from AI/Rva002E7964BoundedWorldToCell.cpp: the
// world-to-cell conversion bounded by the cell extent at +0x14 (x = -1 outside).
class Rva002E7964 {
public:
 void rva002E7964(ICoord2D*,unsigned char,const Coord3D*);
 char pad[0x14];IRegion2D extent;
};
__declspec(noinline) inline void Rva002E7964::rva002E7964(ICoord2D *out,unsigned char center,const Coord3D *pos){
 ICoord2D tmp;
 typedef ICoord2D *(__cdecl *CellCall)(ICoord2D*,unsigned char,const Coord3D*);
 reinterpret_cast<CellCall>(Rva002E7875WorldToCell)(&tmp,center,pos);
 if(tmp.x<extent.lo.x || tmp.y<extent.lo.y || tmp.x>extent.hi.x || tmp.y>extent.hi.y)tmp.x=-1;
 *(out?out:out)=tmp;
}
// 0x001E3647 (50 B), rehomed from Common/PathfinderRva001E3647.cpp: the cell
// under a world position, NULL outside the extent. Defined ahead of PatchPath:
// cl then sees goalPos does not escape and hoists its initial loads (y first).
void *Pathfinder::rva001E3647Pos(int layer, const Coord3D *pos)
{
	ICoord2D tmp;
	((Rva002E7964 *)this)->rva002E7964(&tmp, 1, pos);
	void *cell = 0;
	if (tmp.x >= 0)
		cell = getCell((PathfindLayerEnum)layer, tmp.x, tmp.y);
	return cell;
}
struct PathfinderPatchLimitView { char pad[0x120C]; unsigned int maxCells; };
struct Rva002F5925Info {Pathfinder *pathfinder;char data4[16];bool center,human;char pad16[2];int radius;Object*object;PathfindCell*goal;int ignoreID;ICoord2D previous;int range;int cellCallback(PathfindCell*,PathfindCell*,int,int);};
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
class Rva002EAB6F {public:Rva002EAB6F(Int,const Rva002E8BCFSrc *,unsigned char,Int,Object *,unsigned char,Int,Int);int m0;Rva002E8BCF m4;unsigned char m14,m15;int m18;Object*m1C;int m20,m24;char pad28[8];int m30;};
struct BurningCell {char pad[6];unsigned short count;char pad8[12];};
struct BurningGrid {char pad[0x70];BurningCell **cells;char word74[4];Int width,height;};
class Rva002872BA;extern Rva002872BA *TheTriggerManager;
struct NeighborMovementInfo { ICoord2D cell;PathfindLayerEnum layer;Int radius;Bool centerInCell,considerTransient;char pad12[2];Int options,ignore;Rva002E8BCF movement;Int allyFixedCount;Bool flag30,flag31,allyGoal;char pad33;Int blockedCells; };
struct NeighborWorldPoint:Coord3D {NeighborWorldPoint(){} ~NeighborWorldPoint(){}};
static __forceinline Int neighborRealToIntFloor(float f){float floored=floor(f);long i;__asm { fld [floored] } __asm { fistp [i] } return i;}
static __forceinline Bool nativeBurning(BurningGrid *grid,const Coord3D &point){Int fireX=neighborRealToIntFloor((point.x+0.5f)*0.1f);Int fireY=neighborRealToIntFloor((point.y+0.5f)*0.1f);if(fireX>=0 && fireX<grid->width && fireY>=0 && fireY<grid->height)return grid->cells[fireX][fireY].count>0;return false;}
// Shared neighbor body from PathfinderSidewaysAttack.cpp; the index is unused.
// ?Pathfinder::rva002F83F5 present-unmatched
inline __declspec(noinline) Int Pathfinder::rva002F83F5(PathfindCell *parentCell,PathfindCell *goalCell,const LocomotorSet &locomotorSet,Bool isHuman,Bool centerInCell,Int radius,ICoord2D *startCellNdx,Object *obj,Int attackMode)
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
NeighborMovementInfo info;((Rva002E6FDF *)&info)->rva002E6FDF();
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
if(!rva002EA658(obj,*(TCheckMovementInfo *)&info,(const ICoord2D *)parentCell->m_pathInfo)) {
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
Path *Pathfinder::PatchPath(Object *obj,const LocomotorSet &locomotorSet,Path *originalPath,Bool blocked)
{
	if (!originalPath) return 0;
	Bool centerInCell;
	Int radius;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&centerInCell);
	Bool isHuman = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1) isHuman = false;
	_STL::vector<Gen_p12pod> *hops = (_STL::vector<Gen_p12pod> *)&m_1C1CC;
	hops->erase(hops->begin(), hops->end());
	m_zoneManager.rva00531300();
	unsigned int cellCount = 0;
	Coord3D currentPosition;
	copyCoord3D(&currentPosition, (const Coord3D *)obj->position);
	ICoord2D startCellNdx;
	Rva002E7875WorldToCell(&startCellNdx, true, (const Coord3D *)obj->position);
	PathfindCell *parentCell = rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(), &currentPosition);
	if (!parentCell) return 0;
	if (!obj->m_258) return 0;
	m_isTunneling = false;
	parentCell->allocateInfo((In002E6BA1 *)&startCellNdx);
	parentCell->StartPathfind(0);
	AddToOpenList(parentCell);
	PathNode *startNode;
	PathfindCell *candidateGoal;
	{
	Coord3D goalPos;
	copyCoord3D(&goalPos, &(originalPath->lastNode)->position);
	float dx = goalPos.x - currentPosition.x;
	float dy = goalPos.y - currentPosition.y;
	float goalDeltaSqr = dx*dx + dy*dy;
	ICoord2D cellCoord;
	for (startNode = originalPath->lastNode; startNode != originalPath->firstNode; startNode = startNode->previous) {
		Rva002E7875WorldToCell(&cellCoord, true, &startNode->position);
		TCheckMovementInfo info;
		((Rva002E6FDF *)&info)->rva002E6FDF();
		info.cell = cellCoord;
		info.layer = startNode->layer;
		info.centerInCell = centerInCell;
		info.radius = radius;
		info.m_11 = blocked;
		Int cx = cellCoord.x - startCellNdx.x;
		Int cy = cellCoord.y - startCellNdx.y;
		if (cx < -2 || cx > 2) info.m_11 = false;
		if (cy < -2 || cy > 2) info.m_11 = false;
		info.m_14 = (obj->m_template->testKindWord(90) ? 1U : 16U) | 2U;
		readMoverInfo(info, obj);
		if (!checkForMovement(obj, info)) break;
		float nx = startNode->position.x - currentPosition.x;
		float ny = startNode->position.y - currentPosition.y;
		float dist = nx*nx + ny*ny;
		if (dist < goalDeltaSqr) { goalPos = startNode->position; goalDeltaSqr = dist; }
	}
	if (startNode == originalPath->lastNode) { rva002F40E7(); return 0; }
	candidateGoal = (PathfindCell *)rva001E3647Pos(1, &goalPos);
	candidateGoal->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&cellCoord, true, &goalPos));
	}
	PathfinderSearchCellsVisited = 0;
	while ((parentCell = rva002F36E5()) != 0) {
		PathfinderCellPoint cellCenter = Rva002E8C23Call(centerInCell, parentCell);
		PathNode *matchNode;
		Bool found = false;
		for (matchNode = originalPath->lastNode; matchNode != startNode; matchNode = matchNode->previous) {
			if (cellCenter.x == matchNode->position.x && cellCenter.y == matchNode->position.y) { found = true; break; }
		}
		if (found) {
			m_isTunneling = false;
			Path *path = new Path;
			for (PathNode *node = originalPath->lastNode; node != matchNode; node = node->previous)
				path->prependNode(&node->position, node->layer, 0x7FFFFFFF);
			PrependCells(path, (const Coord3D *)obj->position, parentCell, centerInCell);
			path->rva00364551(obj, locomotorSet.getValidSurfaces(), blocked, 0);
			rva002F40E7();
			parentCell->ReleaseInfo();
			candidateGoal->ReleaseInfo();
			return path;
		}
		parentCell->PutOnClosedList(&m_closedList);
		if (cellCount < ((const PathfinderPatchLimitView *)TheWritableGlobalData)->maxCells) {
			CheckChangeLayers(parentCell, obj);
			cellCount += rva002F83F5(parentCell, 0, locomotorSet, isHuman, centerInCell, radius, &startCellNdx, obj, 0);
		}
	}
	m_isTunneling = false;
	rva002F40E7();
	candidateGoal->ReleaseInfo();
	return 0;
}

Path *Pathfinder::FindSafePath(Object *obj,const LocomotorSet &loco,const Coord3D *from,
const Coord3D *repulsor1,const Coord3D *repulsor2,float radius)
{
if(!m_isMapReady)return 0;
Bool center;Int cellRadius;Rva002EBCA7Split(obj,&cellRadius,(unsigned char *)&center);
float repulsorDistance=radius*radius;Int count=0;Bool human=true;
if(obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType==1)human=false;
_STL::vector<Gen_p12pod> *hops=(_STL::vector<Gen_p12pod> *)&m_1C1CC;hops->erase(hops->begin(),hops->end());m_zoneManager.rva00531300();
PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(),(Coord3D *)obj->position);
if(!parent || !obj->m_258)return 0;
ICoord2D *startCell;{ICoord2D start;Rva002E7875WorldToCell(&start,true,(Coord3D *)obj->position);
parent->allocateInfo((In002E6BA1 *)&start);startCell=&start;}parent->StartPathfind(0);AddToOpenList(parent);
PathfinderSearchCellsVisited=0;float farthest=0;
while((parent=rva002F36E5())!=0) {
PathfinderCellPoint cellCenter=Rva002E8C23Call(center,parent);
float dx=cellCenter.x-repulsor1->x,dy=cellCenter.y-repulsor1->y;
float distance=dx*dx+dy*dy;
dx=cellCenter.x-repulsor2->x;dy=cellCenter.y-repulsor2->y;
float distance2=dx*dx+dy*dy;Bool ok=false;
if(distance>distance2)distance=distance2;
if(distance>repulsorDistance)ok=true;
if(!rva002F068F() && count>0)ok=true;
if(distance>farthest){farthest=distance;if(count>2000)ok=true;}
if(ok && bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)cellRadius,boolArg(center))) {
Path *path=BuildActualPath(obj,loco.getValidSurfaces(),(Coord3D *)obj->position,parent,center,false,true);
rva002F40E7();parent->ReleaseInfo();return path;
}
parent->PutOnClosedList(&m_closedList);CheckChangeLayers(parent,obj);
count+=rva002F83F5(parent,0,loco,human,center,cellRadius,startCell,obj,0);
}
m_isTunneling=false;rva002F40E7();return 0;
}
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"
Bool LineInRegion(const Coord2D *,const Coord2D *,const Region2D *);
int Rva002E9B31Get(void *);
// Evidence: WB lead D35600 names Pathfinder::GetMoveAwayFromPath (reverse/wb_name_leads.csv);
// BFME1/ZH getMoveAwayFromPath is the semantic guide. The Coord2D pair is declared in the
// segment loop body (one load of nextOptimized), via PathNode's getPosition/getNextOptimized.
// 0x002F9DBA: a flood search from the mover's cell for the nearest cell whose
// box (grown by both movers' radii) avoids both avoided paths and objects.
Path *Pathfinder::GetMoveAwayFromPath(Object *obj,Object *otherObj,Path *pathToAvoid,Object *otherObj2,Path *path)
{
 if(!m_isMapReady)return 0;
 Bool isHuman=true;
 if(obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType==1)isHuman=false;
 ((_STL::vector<Gen_p12pod> *)&m_1C1CC)->clear();
 m_zoneManager.rva00531300();
 ICoord2D start;Rva002EBC14Cell(&start,obj,(const Coord3D *)obj->position);
 PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(),(const Coord3D *)obj->position);
 if(!parent)return 0;
 AIUpdateInterface *ai=obj->getAI();if(!ai)return 0;
 Int priority=obj->m_template->priority;
 Bool flag=obj->m_template->flag;
 Rva002E8BCF movement((const Rva002E8BCFSrc *)((const char *)ai+0x1cc),!flag,priority-1,obj->rva0028AFBB());
 m_isTunneling=false;
 if(!((Rva002E6DC4 *)this)->rva002E6DC4(&movement,parent))m_isTunneling=true;
 TCheckMovementInfo info;
 ((Rva002E6FDF *)&info)->rva002E6FDF();
 Int &radius=info.radius;Bool &center=info.centerInCell;
 Rva002EBCA7Split(obj,&radius,(unsigned char *)&center);
 info.cell=start;info.layer=(PathfindLayerEnum)obj->rva0028B511();
 info.m_14=(*(const unsigned *)((const char *)obj->m_template+0x110)&0x4000000)?1:16;
 info.m_11=false;
 info.m_18=obj->getAI()?(ObjectID)((Rva0006E009DwordField *)obj->getAI())->get():(ObjectID)0;
 if(!checkForMovement(obj,info))m_isTunneling=true;
 parent->allocateInfo((In002E6BA1 *)&start);parent->StartPathfind(0);AddToOpenList(parent);
 float boxHalfWidth=radius*10-2.5f;
 if(center)boxHalfWidth+=5.0f;
 boxHalfWidth+=Rva002E9B31Get(otherObj)*10*0.5f;
 PathfinderSearchCellsVisited=0;
 const LocomotorSet &locomotorSet=*(const LocomotorSet *)((const char *)obj->getAI()+0x1cc);
 while((parent=rva002F36E5())!=0) {
  Region2D bounds;
  PathfinderCellPoint cellCenter=Rva002E8C23Call(center,parent);
  bounds.lo.x=cellCenter.x-boxHalfWidth;bounds.lo.y=cellCenter.y-boxHalfWidth;
  bounds.hi.x=cellCenter.x+boxHalfWidth;bounds.hi.y=cellCenter.y+boxHalfWidth;
  PathNode *node;
  Bool overlap=false;
  if(bounds.lo.x<obj->position[0] && bounds.hi.x>obj->position[0] && bounds.lo.y<obj->position[1] && bounds.hi.y>obj->position[1])overlap=true;
  if(pathToAvoid) {
   for(node=pathToAvoid->firstNode;node && node->getNextOptimized();node=node->getNextOptimized()) {
    Coord2D first,last;first.x=node->getPosition()->x;first.y=node->getPosition()->y;
    last.x=node->getNextOptimized()->getPosition()->x;last.y=node->getNextOptimized()->getPosition()->y;
    if(LineInRegion(&first,&last,&bounds)){overlap=true;break;}
   }
  }
  if(bounds.lo.x<otherObj->position[0] && bounds.hi.x>otherObj->position[0] && bounds.lo.y<otherObj->position[1] && bounds.hi.y>otherObj->position[1])overlap=true;
  if(!overlap && path) {
   for(node=path->firstNode;node && node->getNextOptimized();node=node->getNextOptimized()) {
    Coord2D first,last;first.x=node->getPosition()->x;first.y=node->getPosition()->y;
    last.x=node->getNextOptimized()->getPosition()->x;last.y=node->getNextOptimized()->getPosition()->y;
    if(LineInRegion(&first,&last,&bounds)){overlap=true;break;}
   }
  }
  if(!overlap && start.x==parent->getXIndex() && start.y==parent->getYIndex())overlap=true;
  if(!overlap && bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)radius,boolArg(center))) {
   m_isTunneling=false;
   Path *newPath=BuildActualPath(obj,movement.surfaces,(const Coord3D *)obj->position,parent,center,false,true);
   rva002F40E7();parent->ReleaseInfo();return newPath;
  }
  parent->PutOnClosedList(&m_closedList);
  CheckChangeLayers(parent,obj);
  rva002F83F5(parent,0,locomotorSet,isHuman,center,radius,&start,obj,0);
 }
 m_isTunneling=false;rva002F40E7();return 0;
}

float g_00DBD338 = 0.010000000707805157f;	// retail RVA 0x009BD338 (.data), defined here
class Rva0053476A{public:~Rva0053476A();};
class Rva002EAD62 { public: void rva002EAD62();Rva0053476A *m_ptr; };
void Rva002EAD62::rva002EAD62(){delete m_ptr;}

class Rva002EAD39 { public: void rva002EAD39(Rva0053476A *); };
// Owner of the hierarchical path the closest search consults.
struct PathfinderAttackHandle
{
	Path *path;
	__forceinline PathfinderAttackHandle(Path *p) : path(p) {}
	__forceinline ~PathfinderAttackHandle() { ((Rva002EAD62 *)this)->rva002EAD62(); }
};
// WB D48830 supplies FindClosestPath identity and target-specific stages;
// ZH findClosestPath supplies closest-cell and hierarchical search semantics.
inline __declspec(noinline) float Coord3D::length()const{return(float)sqrt(x*x+y*y+z*z);}
inline __declspec(noinline) float Coord3D::GetLength()const{float lhs=x,rhs=y,pathCell=z;return(float)sqrt(lhs*lhs+rhs*rhs+pathCell*pathCell);}
inline __declspec(noinline) float Coord3D::Normalize(){float len=GetLength();float scale=1.0f/len;x*=scale;y*=scale;z*=scale;return len;}
Path *Pathfinder::FindClosestPath(Object *obj,const LocomotorSet &locos,const Coord3D *from,
Coord3D *rawTo,Bool blocked,float multiplier,Bool moveAllies)
{
 m_srcMineshaft=0;
 m_destMineshaft=0;
 Bool human=true;
 if(obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType==1)human=false;
 if(!locos.getValidSurfaces())return 0;
 if(!m_isMapReady)return 0;
 m_isTunneling=false;
 Bool throughUnits=false;
 if(obj->getAI())throughUnits=*((const Bool *)obj->getAI()+0x3ba);
 Int radius;
 Bool center;
 Rva002EBCA7Split(obj,&radius,(unsigned char *)&center);
 Coord3D adjusted;
 copyCoord3D(&adjusted,rawTo);
 if(!QuickDoesPathExist(obj,from,&adjusted,false))
 {
  Coord3D delta;
  delta.x=adjusted.x-from->x;
  delta.y=adjusted.y-from->y;
  delta.z=0;
  Int steps=-1-(Int)(delta.length()*(-1.0f/30.0f));
  if(steps>5)steps=5;
  delta.Normalize();
  delta.x*=30.0f;
  delta.y*=30.0f;
  delta.z*=30.0f;
  for(Int i=0;i<steps;++i)
  {
   adjusted.x-=delta.x;
   adjusted.y-=delta.y;
   adjusted.z-=delta.z;
   if(QuickDoesPathExist(obj,from,&adjusted,false))break;
  }
 }
 Coord3D destination;
 copyCoord3D(&destination,&adjusted);
 if(!center)
 {
  destination.x+=5.0f;
  destination.y+=5.0f;
 }
 Coord3D clippedFrom;
 copyCoord3D(&clippedFrom,from);
 clip(&clippedFrom,&destination);
 ICoord2D startIndex;
 Rva002E7875WorldToCell(&startIndex,true,from);
 PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(),&clippedFrom);
 if(!parent)return 0;
 Int priority=obj->m_template->priority;
 Bool flag=obj->m_template->flag;
 Rva002E8BCF movement((const Rva002E8BCFSrc *)&locos,!flag,priority-1,obj->rva0028AFBB());
 if(!((Rva002E6DC4 *)this)->rva002E6DC4(&movement,parent))m_isTunneling=true;
 {
  TCheckMovementInfo info;
  ((Rva002E6FDF *)&info)->rva002E6FDF();
  info.cell=startIndex;
  info.layer=(PathfindLayerEnum)obj->rva0028B511();
  info.centerInCell=center;
  info.radius=radius;
  info.m_11=blocked;
  info.m_14=obj->m_template->testKindWord(90)?1:16;
  readMoverInfo(info,obj);
  if(!checkForMovement(obj,info))m_isTunneling=true;
 }
 Bool gotHierarchical=false;
 ((_STL::vector<Gen_p12pod> *)&m_1C1CC)->clear();
 PathfinderAttackHandle hierarchical(0);
 if(m_isTunneling)m_zoneManager.rva00531300();
 else
 {
  m_zoneManager.rva005312BE();
  Path *path=FindClosestHierarchicalPath(human,locos,obj,from,&adjusted,false,&destination);
  ((Rva002EAD39 *)&hierarchical)->rva002EAD39((Rva0053476A *)path);
  if(hierarchical.path)gotHierarchical=true;
  else m_zoneManager.rva00531300();
 }
 PathfindLayerEnum destinationLayer=(PathfindLayerEnum)TheTerrainLogic->getLayerForDestination(0,&destination);
 PathfindCell *goal=rva002E8BF8(destinationLayer,&destination);
 if(!goal)return 0;
 Bool goalOnObstacle=false;
 if(m_ignoreObstacleID)
 {
  Object *goalObj=TheGameLogic->findObjectByID(m_ignoreObstacleID);
  if(goalObj)
  {
   PathfindCell *ignoreCell=rva002E8BF8((PathfindLayerEnum)goalObj->rva0028B511(),(const Coord3D *)goalObj->position);
   PathfinderGroundInfo *goalInfo=goal->m_pathInfo;
   if((goalInfo?goalInfo->obstacleID:(ObjectID)0)==ignoreCell->getObstacleID() && (goalInfo?goalInfo->obstacleID:(ObjectID)0))
   {
    Object *newObstacle=TheGameLogic->findObjectByID(goalInfo?goalInfo->obstacleID:(ObjectID)0);
    if(newObstacle && newObstacle->m_template->hasKind(35))
    {
     m_ignoreObstacleID=goalInfo?goalInfo->obstacleID:(ObjectID)0;
     goalOnObstacle=true;
    }
    else
    {
     if(m_ignoreObstacleID==(goalInfo?goalInfo->obstacleID:(ObjectID)0))goalOnObstacle=true;
    }
   }
  }
 }
 Bool startedStuck=m_isTunneling;
 { ICoord2D goalIndex; goal->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&goalIndex,true,&destination)); }
 if(parent!=goal)
 {
  ICoord2D parentIndex; parent->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&parentIndex,true,&clippedFrom));
 }
 parent->StartPathfind((Int)goal);
 parent->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parent,goal);
 PathfindCell *closest=0;
 float closestMetric=3.4028235e38f;
 Int closestOrder=0;
 float bestDistance=8.5070587e37f,bestScreenDistance=8.5070587e37f;
 PathfinderSearchCellsVisited=0;
 AddToOpenList(parent);
 Int count=0;
 Bool foundGoal=false;
 while((parent=rva002F36E5())!=0)
 {
  if(parent==goal)
  {
   if(goalOnObstacle || !closest || throughUnits || bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)radius,boolArg(center)))
   {
    m_isTunneling=false;
    Path *path=BuildActualPath(obj,locos.getValidSurfaces(),from,goal,center,blocked,true);
    rva002F40E7();
    parent->ReleaseInfo();
    goal->ReleaseInfo();
    return path;
   }
   foundGoal=true;
   parent->PutOnClosedList(&m_closedList);
   continue;
  }
  parent->PutOnClosedList(&m_closedList);
  float dx,dy,distance;
  if(!m_isTunneling && bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)radius,boolArg(center)) &&
  (!startedStuck || ((Rva002E6DC4 *)this)->rva002E6DC4(&movement,parent)))
  {
   dx=(float)abs(goal->getXIndex()-parent->getXIndex());
   dy=(float)abs(goal->getYIndex()-parent->getYIndex());
   distance=dy*dy+dx*dx;
   if(distance<bestDistance)
   {
    if(dx+dy>25.0f)
    {
     float metric=(float)sqrt((double)distance); metric+=25.0f;
     bestScreenDistance=(float)(metric*metric);
    }
    else bestScreenDistance=distance*4.0f;
    bestDistance=distance;
   }
   unsigned short cost=parent->m_pathInfo->costSoFar;
   distance+=(cost*(cost*g_00DBD338))*multiplier;
   distance+=(unsigned int)(((_STL::vector<Gen_p12pod> *)&m_1C1CC)->size()*10000U);
   if(hierarchical.path)
   {
    Int order=((HierarchicalPath *)hierarchical.path)->lookUpPositionOnPath((const Coord3D *)parent->m_pathInfo);
    if(order>closestOrder || (order==closestOrder && distance<closestMetric))
    {
     PathfinderCellPoint cellCenter=Rva002E8C23Call(center,parent);
     if(rva002EDFF9(obj,(Coord3D *)&cellCenter))
     {
      closest=parent;
      closestOrder=order;
      closestMetric=distance;
     }
    }
   }
   else if(distance<closestMetric)
   {
    PathfinderCellPoint cellCenter=Rva002E8C23Call(center,parent);
    if(rva002EDFF9(obj,(Coord3D *)&cellCenter))
    {
     closest=parent;
     closestMetric=distance;
    }
   }
  }
  dx=(float)abs(goal->getXIndex()-parent->getXIndex());
  dy=(float)abs(goal->getYIndex()-parent->getYIndex());
  distance=dy*dy+dx*dx;
  if(distance>bestScreenDistance)
  {
   Bool stop=false;
   if(!gotHierarchical)stop=true;
   if(count>2000)stop=true;
   if(distance<100.0f)stop=false;
   if(stop)continue;
  }
  if(!foundGoal)
  {
   CheckChangeLayers(parent,obj);
   count+=rva002F83F5(parent,goal,locos,human,center,radius,&startIndex,obj,0);
  }
 }
 if(closest)
 {
  m_isTunneling=false;
  adjusted.x=closest->getXIndex()*10+5.0f;
  adjusted.y=closest->getYIndex()*10+5.0f;
  Path *path=BuildActualPath(obj,locos.getValidSurfaces(),from,closest,center,blocked,true);
  rva002F40E7();
  goal->ReleaseInfo();
  return path;
 }
 m_isTunneling=false;
 rva002F40E7();
 goal->ReleaseInfo();
 return 0;
}

Path *Pathfinder::InternalFindPath(Object *obj, const LocomotorSet &locomotorSet, const Coord3D *from,
	const Coord3D *rawTo, HierarchicalPath *hierarchicalPath, Bool *destinationAdjusted)
{
	if (theLogicRandomLogFile)
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() called");
	Bool goalBlocked = false;
	Bool centerInCell = true;
	Int radius = 0;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&centerInCell);

	Bool isHuman = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 1");
		isHuman = false;
	}

	if (rawTo->x == 0.0f && rawTo->y == 0.0f) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 2 return NULL");
		return NULL;
	}
	if (!m_isMapReady) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 3 return NULL");
		return NULL;
	}

	Coord3D adjustTo;
	copyCoord3D(&adjustTo, rawTo);
	Coord3D clipFrom;
	copyCoord3D(&clipFrom, from);
	clip(&clipFrom, &adjustTo);

	if (!centerInCell) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 4");
		adjustTo.x += 5.0f;
		adjustTo.y += 5.0f;
	}
	Coord3D unshiftedTo;
	copyCoord3D(&unshiftedTo, &adjustTo);

	if (obj->m_template->testKindWord(186)) {
		float offsetX = 20.0f;
		float offsetY = 0.0f;
		rotateOffset(offsetX, offsetY, obj->GetGoalAngle() + 3.14159265359f);
		adjustTo.x += offsetX;
		adjustTo.y += offsetY;
	}

	m_isTunneling = false;
	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
	PathfindCell *goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
	if (goalCell == NULL) {
		if (!obj->m_template->testKindWord(186))
			return NULL;
		adjustTo = unshiftedTo;
		goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
		if (goalCell == NULL)
			return NULL;
	}

	TCheckMovementInfo info;
	Int blockers;
	ICoord2D *startCell;
	{
	ICoord2D cell;
	Rva002E7875WorldToCell(&cell, true, &adjustTo);
	((Rva002E6FDF *)&info)->rva002E6FDF();
	info.cell = cell;
	info.layer = destinationLayer;
	info.centerInCell = centerInCell;
	if (obj->m_template->testKindWord(90)) {
		info.radius = 1;
		info.m_14 = 0xC;
	} else {
		info.radius = 1;
		info.m_14 = 0x1C;
	}
	readMoverInfo(info, obj);
	info.m_11 = true;
	{
		Int priority = obj->m_template->priority;
		Bool flag = obj->m_template->flag;
		char *ai = obj->m_258;
		*(Rva002E8BCF *)info.m_1C = Rva002E8BCF((const Rva002E8BCFSrc *)(ai + 0x1CC), !flag, priority - 1, obj->rva0028AFBB());
	}
	if (!CheckDestination(obj, cell.x, cell.y, destinationLayer, radius, centerInCell, &blockers, true)
		|| !checkForMovement(obj, info)) {
		if (obj->m_template->testKindWord(186)) {
			adjustTo = unshiftedTo;
			destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
			goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
			if (goalCell == NULL)
				return NULL;
			{
			ICoord2D retryCell;
			ICoord2D *cell = Rva002E7875WorldToCell(&retryCell, true, &adjustTo);
			Int infoX = cell->x;
			Int infoY = cell->y;
			ICoord2D goal = *cell;
			info.cell.x = infoX;
			info.cell.y = infoY;
			if (!CheckDestination(obj, goal.x, goal.y, destinationLayer, radius, centerInCell, &blockers, true)
				|| !checkForMovement(obj, info))
				goalBlocked = true;
			}
		} else {
			goalBlocked = true;
		}
	}
	}

	{ ICoord2D startCellNdx; Rva002E7875WorldToCell(&startCellNdx, true, &clipFrom); startCell = &startCellNdx; }
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindCell *parentCell = rva002E8BF8(layer, &clipFrom);
	if (parentCell == NULL) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 7 return NULL");
		return NULL;
	}

	Bool viaMineshaft = false;
	if (m_srcMineshaft && m_destMineshaft && m_srcMineshaft != m_destMineshaft) {
		const Rva002F35AFHop *hopEnd = m_1C1CC.end();
		for (const Rva002F35AFHop *hop = m_1C1CC.begin(); hop != hopEnd; ++hop) {
			if (hop->m_zone == m_srcMineshaft->m_portal) {
				viaMineshaft = true;
				adjustTo = m_srcMineshaft->m_position;
				clip(&clipFrom, &adjustTo);
				unshiftedTo = adjustTo;
				destinationLayer = TheTerrainLogic->getLayerForDestination(NULL, &adjustTo);
				goalCell = (PathfindCell *)rva001E3647Pos(destinationLayer, &adjustTo);
				break;
			}
		}
	}

	{ ICoord2D pos2d; goalCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&pos2d, true, &adjustTo)); }
	if (parentCell != goalCell) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 8");
		ICoord2D pos2d;
		parentCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&pos2d, true, &clipFrom));
	}

	if (parentCell->getType() == PathfindCell::CELL_OBSTACLE
		&& (parentCell->m_pathInfo ? parentCell->m_pathInfo->obstacleID : (ObjectID)0) != m_ignoreObstacleID) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 9");
		m_isTunneling = true;
	} else {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 10");
		m_isTunneling = false;
	}

	if (((const Rva0028B984ByteField *)obj)->get()) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 11");
		parentCell->StartPathfind((Int)goalCell);
		parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
		AddToOpenList(parentCell);
		Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, false, true);
		rva002F40E7();
		goalCell->ReleaseInfo();
		if (pathfinderLogOn())
			fprintf((FILE *)theLogicRandomLogFile, "CritterDesync:    Pathfinder::InternalFindPath() 12 return %s", path ? "VALID" : "NULL");
		return path;
	}

	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	Rva002E8BCF moverInfo((const Rva002E8BCFSrc *)&locomotorSet, !flag, priority - 1, obj->rva0028AFBB());
	Rva002E99F9Sub460 *zones = (Rva002E99F9Sub460 *)&m_zoneManager;
	Int zone1 = zones->rva0053241F(&moverInfo, parentCell->quickZone());
	Int zone2 = zones->rva0053241F(&moverInfo, goalCell->quickZone());
	if (goalCell->IsObstaclePresent(m_ignoreObstacleID) || parentCell->IsObstaclePresent(m_ignoreObstacleID) || m_isTunneling) {
		zone2 = zones->rva00531FD4(&moverInfo, (unsigned short)zone2);
		zone2 = zones->rva0053241F(&moverInfo, (unsigned short)zone2);
		zone1 = zones->rva00531FD4(&moverInfo, (unsigned short)zone1);
		zone1 = zones->rva0053241F(&moverInfo, (unsigned short)zone1);
		if (g_00E03745 && theLogicRandomLogFile)
			fprintf((FILE *)theLogicRandomLogFile, "CritterDesync:    Pathfinder::InternalFindPath() 13");
	}
	if (zone1 != zone2) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:\tPathfinder::InternalFindPath() 13.5");
		if (!rva002F4115(obj, zone1, zone2, NULL))
			goalBlocked = true;
	}
	if (!IsValidMovementPositionForObject(&adjustTo, destinationLayer, locomotorSet.getValidSurfaces(), obj))
		goalBlocked = true;
	if (!IsValidMovementPositionForObject(from, layer, locomotorSet.getValidSurfaces(), obj)) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 16");
		m_isTunneling = true;
	}
	if (!m_isTunneling) {
		if (pathfinderLogOn())
			pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 17");
		((Rva002E6FDF *)&info)->rva002E6FDF();
		info.layer = (PathfindLayerEnum)parentCell->getLayer();
		info.centerInCell = centerInCell;
		info.radius = radius;
		info.m_14 = 0;
		readMoverInfo(info, obj);
		{ ICoord2D startCellNdx; info.cell = *Rva002E7875WorldToCell(&startCellNdx, true, &clipFrom); }
		info.m_11 = true;
		if (!checkForMovement(obj, info)) {
			if (pathfinderLogOn())
				pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 18");
			m_isTunneling = true;
		}
	}

	parentCell->StartPathfind((Int)goalCell);
	parentCell->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parentCell, goalCell);
	AddToOpenList(parentCell);

	Int cellCount = 0;
	PathfinderSearchCellsVisited = 0;
	PathfindCell *closestCell = NULL;
	Int closestPathIndex = 0;
	Int closestDist = 0x7fffffff;
	Int nearestGoalDist = 0x7fffffff;
	Int giveUpDist = 0x7fffffff;
	while ((parentCell = rva002F36E5()) != NULL) {
		if (parentCell == goalCell) {
			m_isTunneling = false;
			Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, false, false);
			if (viaMineshaft) {
				PathfindLayerEnum srcLayer = TheTerrainLogic->getLayerForDestination(NULL, &m_srcMineshaft->m_position);
				path->appendNode(&m_srcMineshaft->m_position, srcLayer, m_srcMineshaft->m_portal);
				PathfindLayerEnum destLayer = TheTerrainLogic->getLayerForDestination(NULL, &m_destMineshaft->m_position);
				path->appendNode(&m_destMineshaft->m_position, destLayer, 0x7fffffff);
				path->SetLastNodePortal(m_destMineshaft->m_portal);
			}
			Coord3D direction = *((const Thing *)obj)->getUnitDirectionVector2D();
			path->rva00365E98(obj, &direction, locomotorSet.getValidSurfaces(), false);
			rva002F40E7();
			parentCell->ReleaseInfo();
			if (pathfinderLogOn())
				fprintf((FILE *)theLogicRandomLogFile, "CritterDesync:    Pathfinder::InternalFindPath() 19 return %s", path ? "VALID" : "NULL");
			return path;
		}

		parentCell->PutOnClosedList(&m_closedList);
		if ((unsigned int)cellCount > ((const PathfinderCellLimitView *)TheWritableGlobalData)->maxCells) {
			if (pathfinderLogOn())
				pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 20 failed path break");
			break;
		}

		if (!m_isTunneling) {
			Int dx = abs(goalCell->getXIndex() - parentCell->getXIndex());
			Int dy = abs(goalCell->getYIndex() - parentCell->getYIndex());
			Int dist = dx*dx + dy*dy;
			if (dist < nearestGoalDist) {
				if (dx + dy > 25) {
					float reach = (float)sqrt((double)dist) + 25.0f;
					giveUpDist = (Int)(reach * reach);
				} else {
					giveUpDist = dist * 4;
				}
				nearestGoalDist = dist;
			}
			dist += (Int)m_1C1CC.size()*10*10*100;
			if (hierarchicalPath) {
				Int pathIndex = hierarchicalPath->lookUpPositionOnPath((const Coord3D *)parentCell->m_pathInfo);
				if (pathIndex > closestPathIndex || (pathIndex == closestPathIndex && dist < closestDist)) {
					closestDist = dist;
					closestPathIndex = pathIndex;
					if (bfmeWrapE6E90(obj, (void *)parentCell->getXIndex(), (void *)parentCell->getYIndex(),
							(void *)parentCell->getLayer(), (void *)radius, boolArg(centerInCell))
						&& ((Rva002E6DC4 *)this)->rva002E6DC4(&moverInfo, parentCell)
						&& rva002EDFF9(obj, cellPointArg(Rva002E8C23Call(centerInCell, parentCell))))
						closestCell = parentCell;
				}
			} else if (dist < closestDist) {
				closestDist = dist;
				if (bfmeWrapE6E90(obj, (void *)parentCell->getXIndex(), (void *)parentCell->getYIndex(),
						(void *)parentCell->getLayer(), (void *)radius, boolArg(centerInCell))
					&& ((Rva002E6DC4 *)this)->rva002E6DC4(&moverInfo, parentCell)
					&& rva002EDFF9(obj, cellPointArg(Rva002E8C23Call(centerInCell, parentCell))))
					closestCell = parentCell;
			}
		}

		if (goalBlocked) {
			Int dx = abs(goalCell->getXIndex() - parentCell->getXIndex());
			Int dy = abs(goalCell->getYIndex() - parentCell->getYIndex());
			Int dist = dx*dx + dy*dy;
			if (dist > giveUpDist) {
				Bool giveUp = false;
				if (hierarchicalPath == NULL)
					giveUp = true;
				if (cellCount > 2000)
					giveUp = true;
				if (dist < 100)
					giveUp = false;
				if (giveUp)
					continue;
			}
		}

		CheckChangeLayers(parentCell, obj);
		cellCount += rva002F83F5(parentCell, goalCell, locomotorSet, isHuman, centerInCell, radius, startCell, obj, 0);
	}

	if (pathfinderLogOn())
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 21");
	if (closestCell) {
		*destinationAdjusted = true;
		m_isTunneling = false;
		Path *path = BuildActualPath(obj, locomotorSet.getValidSurfaces(), from, closestCell, centerInCell, false, true);
		rva002F40E7();
		goalCell->ReleaseInfo();
		return path;
	}
	m_isTunneling = false;
	rva002F40E7();
	goalCell->ReleaseInfo();
	if (pathfinderLogOn())
		pathfinderLog("CritterDesync:    Pathfinder::InternalFindPath() 24 return NULL");
	return NULL;
}

// 0x002E7917: Rva002E7875WorldToCell clamped to the cell extent at +0x14.
PathfinderCellIndex Pathfinder::Rva002E7917(bool center, const Coord3D *pos)
{
	PathfinderCellIndex tmp;
	Rva002E7875WorldToCell(&tmp, center, pos);
	if (tmp.x < m_clampLo.x)
		tmp.x = m_clampLo.x;
	if (tmp.y < m_clampLo.y)
		tmp.y = m_clampLo.y;
	if (tmp.x > m_clampHi.x)
		tmp.x = m_clampHi.x;
	if (tmp.y > m_clampHi.y)
		tmp.y = m_clampHi.y;
	return tmp;
}
// 0x002E8BF8: world position to cell through the clamp wrapper.
PathfindCell *Pathfinder::rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos)
{
	PathfinderCellIndex cell = Rva002E7917(true, pos);
	return getCell(layer, cell.x, cell.y);
}

// 0x002EBCA7: splits Get(p) into half and odd bit.
void __cdecl Rva002EBCA7Split(void *p, int *outHalf, unsigned char *outOdd)
{
	int v = Rva002E9B31Get(p);
	*outHalf = v;
	*outOdd = (v % 2 == 1);
	*outHalf /= 2;
}



// Native 0x002ED7F7..0x002EDCF7 (1280 bytes), RET 12; WorldBuilder D45C80
// names AdjustToMeleeDestination in pathfinder.cpp:4872. The destination-cell
// zone must agree with the mover before the direct placement is tried. Failing
// that, the four-leg square spiral accepts only a closer reachable placement.
// Keep one counter across all four legs: its lifetime reuses the dead Object
// parameter slot. Natural cell/step and destination-cell/budget lifetimes
// reproduce the native frame without the old bank's forced storage unions.
// Initialize the walk budget before x/y to retain the native load scheduling.
struct Rva002ED7F7Budget{char pad[0x1200];int maxSteps;};
class Rva002EC3CEProbes{public:bool rva002EAA41(int,int,int,int,int,bool);bool rva002E7BF0(int,int,bool,int,int,int,void*,bool);};
static __forceinline void subtractMelee(Coord3D &lhs,const Coord3D&rhs){lhs.x-=rhs.x;lhs.y-=rhs.y; lhs.z-=rhs.z;}
static __forceinline float distanceMelee(const Coord3D&lhs){return lhs.z*lhs.z+lhs.y*lhs.y+lhs.x*lhs.x;}
bool Pathfinder::adjustToMeleeDestination(Object*obj,const LocomotorSet&set,Coord3D*dest){
 int i;
 int radius;Bool center;Rva002EBCA7Split(obj,&radius,(unsigned char*)&center);
 ICoord2D cell;((Rva002E7964*)this)->rva002E7964(&cell,center,dest);if(cell.x<0)return false;
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,dest);PathfindCell *destinationCell=getCell(layer,cell.x,cell.y);
 Coord3D from;from.x=obj->position[0];from.y=obj->position[1];from.z=obj->position[2];Coord3D delta;delta.x=from.x;delta.y=from.y;delta.z=from.z;subtractMelee(delta,*dest);float bestDist=distanceMelee(delta);
 ICoord2D start;Rva002E7875WorldToCell(&start,true,&from);PathfindLayerEnum fromLayer=(PathfindLayerEnum)obj->rva0028B511();PathfindCell *fromCell=rva002E8BF8(fromLayer,&from);if(!fromCell)return false;
 int width=obj->m_template->priority;bool centerOff=obj->m_template->flag;
 Rva002E8BCF query((const Rva002E8BCFSrc*)&set,!centerOff,width-1,obj->rva0028AFBB());
 Rva002E99F9Sub460 *zoneView=(Rva002E99F9Sub460*)&m_zoneManager;
 unsigned zone=zoneView->rva0053241F(&query,fromCell->quickZone());bool bridge=false;
 if(fromCell->getType()==4){bridge=true;unsigned ground=zoneView->rva00531FD4(&query,zone);zone=zoneView->rva0053241F(&query,ground);}
 if(zone==zoneView->rva0053241F(&query,destinationCell->quickZone())&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,cell.x,cell.y,layer,radius,center))return true;
 int left=((const Rva002ED7F7Budget*)TheWritableGlobalData)->maxSteps;int x=cell.x;int y=cell.y;int steps=1;
 while(left>0){
 for(i=steps;i>0;--i){++x;--left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}

 for(i=steps;i>0;--i){++y;--left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}
++steps;
 for(i=steps;i>0;--i){--x;--left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}

 for(i=steps;i>0;--i){--y;--left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}
++steps;
 }
 return false;
}
class BfmeTripleRC;
class Gen_003D5670 {public:Gen_003D5670(int,int,int,int,int,int,unsigned char,unsigned char,int,int,BfmeTripleRC*,unsigned char);unsigned char storage[0x3c];};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class DynamicPortalBehaviour {public:static Module *rva004608E0(Object*);};
class Rva004C5772CmpBoolField {public:bool get()const;};
// Native 0x002EEA8A..0x002EED41, RET 20; WB 0x00D69640 and its
// IterateCircular3 diagnostic prove this expanding-ring search. The callback
// first validates a cell, then ranks successful cells by squared distance.
// BFME 1 donor 9cbfb551 supplies the same traversal; target keeps distance
// calls out of line. Its real inline definition must stay visible: MSVC
// reuses center+offset across the read-only call only with that definition.
// The emitted 54-byte distance COMDAT is also identical to its existing owner.
class Rva002EC3CE {public: Bool rva002EC3CE(Int,Int);};
struct Rva002E8D74Pt
{
	char m_pad00[0x38];
	float m_38;
	float m_3C;
};

class Rva002E8D74
{
public:
	float rva002E8D74(int a, int b);
private:
	char m_pad00[0x28];
	Rva002E8D74Pt *m_28;
};

inline float Rva002E8D74::rva002E8D74(int lhs, int rhs)
{
	int x = lhs * 10;
	int y = rhs * 10;
	float dx = (float)x - m_28->m_38;
	float dy = (float)y - m_28->m_3C;
	return dx * dx + dy * dy;
}


struct MeleeSearchLimit {char pad[0x11ec];int searchLimit;};
struct SearchCoordinate:Coord3D {
 SearchCoordinate(const Coord3D &p){x=p.x;y=p.y;z=p.z;}
 SearchCoordinate(const SearchCoordinate &searchCoordinate){x=searchCoordinate.x;y=searchCoordinate.y;z=searchCoordinate.z;}
 void zero(){x=0;y=0;z=0;}
 void scale(float f){x*=f;y*=f;z*=f;}
 void add(const Coord3D &p){x+=p.x;y+=p.y;z+=p.z;}
};
class Rva002F23A6 {public:bool rva002F23A6(Object *,int,int,Coord3D *,Object *);};
typedef unsigned char (Pathfinder::*ProbeCall)(Object*,int,int,PathfindLayerEnum,int,bool);
// ?rva002EEA8A@Pathfinder@@QAE_NPBUICoord2D@@HPAU2@PAXH@Z
Bool Pathfinder::rva002EEA8A(const ICoord2D *searchCenterCell, Int maxCells,
	ICoord2D *foundCell, void *callbackData, Int iterationsAfterHit)
{
	Bool found = false;
	float best = 0.0f;
	Int remaining = 10000;

	if (g_00E03745 && theLogicRandomLogFile)
	{
		fprintf((FILE *)theLogicRandomLogFile,
			"\t\tIterateCircular3 called with center=%d,%d, maxCells=%d",
			searchCenterCell->x, searchCenterCell->y, maxCells);
	}

	Rva002EC3CE *info = (Rva002EC3CE *)callbackData;
	if (info->rva002EC3CE(searchCenterCell->x,searchCenterCell->y))
	{
		foundCell->x = searchCenterCell->x;
		foundCell->y = searchCenterCell->y;
		found = true;
		best = ((Rva002E8D74 *)info)->rva002E8D74(searchCenterCell->x,searchCenterCell->y);
		remaining = iterationsAfterHit;
	}

	Int side=1;
	Int x=0;
	Int y=0;
	for (; maxCells>0; side+=2)
	{
		if (--remaining <= 0)
			return found;
		maxCells -= 4 * side + 2;

		for (Int i=side; i>0; --i)
		{
			++x;
			float distance = ((Rva002E8D74 *)info)->rva002E8D74(searchCenterCell->x+x,searchCenterCell->y+y);
			if ((!found || !(distance >= best)) && info->rva002EC3CE(searchCenterCell->x+x,searchCenterCell->y+y))
			{
				foundCell->x = searchCenterCell->x + x;
				foundCell->y = searchCenterCell->y + y;
				found = true;
				best = distance;
				remaining = iterationsAfterHit;
			}
		}

		for (Int j=side; j>0; --j)
		{
			++y;
			float distance = ((Rva002E8D74 *)info)->rva002E8D74(searchCenterCell->x+x,searchCenterCell->y+y);
			if ((!found || !(distance >= best)) && info->rva002EC3CE(searchCenterCell->x+x,searchCenterCell->y+y))
			{
				foundCell->x = searchCenterCell->x + x;
				foundCell->y = searchCenterCell->y + y;
				found = true;
				best = distance;
				remaining = iterationsAfterHit;
			}
		}

		for (Int k=side; k>=0; --k)
		{
			--x;
			float distance = ((Rva002E8D74 *)info)->rva002E8D74(searchCenterCell->x+x,searchCenterCell->y+y);
			if ((!found || !(distance >= best)) && info->rva002EC3CE(searchCenterCell->x+x,searchCenterCell->y+y))
			{
				foundCell->x = searchCenterCell->x + x;
				foundCell->y = searchCenterCell->y + y;
				found = true;
				best = distance;
				remaining = iterationsAfterHit;
			}
		}

		for (Int n=side; n>=0; --n)
		{
			--y;
			float distance = ((Rva002E8D74 *)info)->rva002E8D74(searchCenterCell->x+x,searchCenterCell->y+y);
			if ((!found || !(distance >= best)) && info->rva002EC3CE(searchCenterCell->x+x,searchCenterCell->y+y))
			{
				foundCell->x = searchCenterCell->x + x;
				foundCell->y = searchCenterCell->y + y;
				found = true;
				best = distance;
				remaining = iterationsAfterHit;
			}
		}
	}

	return found;
}


// Native 0x002F23A6..0x002F2865, RET 20; WB 0x00D369A0 supplies
// the target-range, melee-offset and circular-cell search flow. The callable
// name is still unknown. Native Object/template fields and cell zone/flags
// below are observed offsets; the callback constructor is the rowed 0x3D5670.
// Keep the WorldToCell -> clamp -> lookup chain and ring helper visible to
// preserve the native frame and direction-vector arithmetic scheduling.
// ?rva002F23A6@Rva002F23A6@@QAE_NPAVObject@@HHPAUCoord3D@@0@Z
bool Rva002F23A6::rva002F23A6(Object *unit,int weapon,int locomotor,Coord3D *dest,Object *victim)
{
 Pathfinder *path=(Pathfinder *)this;
 Weapon *range=(Weapon *)weapon;
 if(range->isWithinAttackRange(unit,unit->getPosition(),victim,victim->getPosition(),0.0f,true) && path->rva002ED313(unit)) {
   *dest=*unit->getPosition();return true;
 }
 SearchCoordinate start(*unit->getPosition());
 Coord3D direction;
 ((const Thing*)unit)->getUnitDirectionVector2D(direction);
 direction.x*=10.0f;direction.y*=10.0f;
 start.add(direction);
 SearchCoordinate delta(start);
 delta.x-=dest->x;delta.y-=dest->y;delta.z=0;
 delta.normalize();delta.scale(10.0f);
 if((victim->m_template->hasKind(7)||victim->m_template->hasKind(60))&&!victim->m_template->hasKind(150))
   path->AdjustMeleeOffset(unit,victim,&delta);
 int radius;bool centered;
 Rva002EBCA7Split(unit,&radius,(unsigned char*)&centered);
 for(int attempt=0;attempt<2;++attempt) {
   victim->rva0028C2DD(dest);
   {const PathfinderTemplateView *vtemplate=victim->m_template;if(vtemplate->hasKind(150))delta.zero();}
   dest->x+=delta.x;dest->y+=delta.y;dest->z+=delta.z;
   if(!centered){dest->x+=5.0f;dest->y+=5.0f;}
   ICoord2D cell;
   ((Rva002E7964 *)this)->rva002E7964(&cell,1,dest);
   if(cell.x<0)return false;
   PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(unit,dest);
   PathfindCell *destinationCell=path->getCell(layer,cell.x,cell.y);
   PathfindLayerEnum originLayer=(PathfindLayerEnum)unit->rva0028B511();
   PathfindCell *originCell=path->rva002E8BF8(originLayer,&start);
   if(!originCell)return false;
   if(victim->m_template->hasKind(60)&&!victim->m_template->hasKind(150))layer=PATHFIND_LAYER_GROUND;
   int diameter=unit->m_template->priority;
   unsigned char special=unit->m_template->flag;
   Rva002E8BCF query((const Rva002E8BCFSrc *)locomotor,!special,diameter-1,unit->rva0028AFBB());
   Rva002E99F9Sub460 *zones=(Rva002E99F9Sub460 *)((char*)this+0x460);
   unsigned originZone=zones->rva0053241F(&query,*(const unsigned short*)((const char*)originCell+8));
   bool bridge=false;
   if((*(const unsigned*)((const char*)originCell+12)&15)==4) {
      bridge=true;
      originZone=zones->rva00531FD4(&query,(unsigned short)originZone);
      originZone=zones->rva0053241F(&query,(unsigned short)originZone);
   }
   unsigned destinationZone=zones->rva0053241F(&query,*(const unsigned short*)((const char*)destinationCell+8));
   if(originZone==destinationZone && (path->*reinterpret_cast<ProbeCall>(&Pathfinder::bfmeWrapE6E90))(unit,cell.x,cell.y,layer,radius,centered) && range->isWithinAttackRange(unit,unit->getPosition(),victim,dest,0.0f,true))return true;
   bool deployed=false;
   if(victim->m_template->hasKind(93)) {
      Module *portal=DynamicPortalBehaviour::rva004608E0(victim);
      static NameKeyType deployKey=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
      Module *power=victim->findModule(deployKey);
      if(portal && power && ((Rva004C5772CmpBoolField *)power)->get())deployed=true;
   }
   ICoord2D output;
   if(path->rva002EEA8A(&cell,((const MeleeSearchLimit*)TheWritableGlobalData)->searchLimit,&output,
      &Gen_003D5670((int)this,(int)&query,(int)unit,(int)victim,weapon,radius,centered,bridge,originZone,layer,(BfmeTripleRC *)dest,deployed),1))return true;
   if(victim->m_template->hasKind(150)&&layer!=PATHFIND_LAYER_GROUND) {
      if(path->rva002EEA8A(&cell,((const MeleeSearchLimit*)TheWritableGlobalData)->searchLimit*2,&output,
         &Gen_003D5670((int)this,(int)&query,(int)unit,(int)victim,weapon,radius,centered,bridge,originZone,PATHFIND_LAYER_GROUND,(BfmeTripleRC *)dest,deployed),1))return true;
   }
   if(delta.x*delta.x+delta.y*delta.y>1.0f)delta.zero();else break;
 }
 return false;
}

// BFME1 cee35b7d8 PathfinderAdjustToPossibleDestination semantic donor.
// WB D455F0; native 002F287A..002F2B88 RET12. One spiral counter spans
// all four legs, matching the sibling melee search and retail stack reuse.
static __forceinline bool possibleFootprint(Pathfinder *pathfinder,Object *object,int x,int y,int layer,int radius,bool center) {
 // Native RET24 uses four-byte words and tests only the final low-byte bool.
 typedef unsigned char (Pathfinder::*Call)(Object *,int,int,int,int,bool);
 Call typed=reinterpret_cast<Call>(&Pathfinder::bfmeWrapE6E90);
 return (pathfinder->*typed)(object,x,y,layer,radius,center)!=0;
}
bool Pathfinder::adjustToPossibleDestination(Object *object,const LocomotorSet &set,Coord3D *destination) {
 int radius; bool center;
 Rva002EBCA7Split(object,&radius,reinterpret_cast<unsigned char *>(&center));
 int count; int i,j,zone; bool obstacle; PathfindLayerEnum layer;
 // Radius/center remain live; coordinate locals end before the spiral.
 ICoord2D goal;
 reinterpret_cast<Rva002E7964 *>(this)->rva002E7964(&goal,center,destination);
 if(goal.x<0) return false;
 layer=TheTerrainLogic->getLayerForDestination(object,destination);
 Coord3D from;
 const PathfindCell *goalCell=getCell(layer,goal.x,goal.y);
 from.x=object->position[0];from.y=object->position[1];from.z=object->position[2];
 ICoord2D start;
 Rva002E7875WorldToCell(&start,true,&from);
 const PathfindLayerEnum startLayer=(PathfindLayerEnum)object->rva0028B511();
 PathfindCell *parent=rva002E8BF8(startLayer,&from);
 if((parent == 0)) return false;
 int maxLayer=object->m_template->priority;
 unsigned char aircraftFlag=object->m_template->flag;

 Rva002E99F9Sub460 *zones=reinterpret_cast<Rva002E99F9Sub460 *>((char *)this+0x460);
 Rva002E8BCF profile(reinterpret_cast<const Rva002E8BCFSrc *>(&set),aircraftFlag==0,maxLayer-1,object->rva0028AFBB());
 zone=zones->rva0053241F(&profile,parent->quickZone());
 obstacle=false;
 if((parent->m_info&15)==4) { obstacle=true;zone=zones->rva00531FD4(&profile,zone);zone=zones->rva0053241F(&profile,zone); }
 if(zone==zones->rva0053241F(&profile,goalCell->quickZone()) && possibleFootprint(this,object,goal.x,goal.y,layer,radius,center)) return true;
 int limit=*(int *)((char *)TheWritableGlobalData+0x11fc);
 i=goal.x;j=goal.y;
 int delta=1;
 while(limit>0) {
  for(count=delta;count>0;--count) {
   ++i;--limit;
   if(reinterpret_cast<Rva002EC3CEProbes *>(this)->rva002E7BF0((int)&profile,zone,center,i,j,layer,destination,obstacle) && possibleFootprint(this,object,i,j,layer,radius,center)) return true;
  }
  for(count=delta;count>0;--count) {
   ++j;--limit;
   if(reinterpret_cast<Rva002EC3CEProbes *>(this)->rva002E7BF0((int)&profile,zone,center,i,j,layer,destination,obstacle) && possibleFootprint(this,object,i,j,layer,radius,center)) return true;
  }
  ++delta;
  for(count=delta;count>0;--count) {
   --i;--limit;
   if(reinterpret_cast<Rva002EC3CEProbes *>(this)->rva002E7BF0((int)&profile,zone,center,i,j,layer,destination,obstacle) && possibleFootprint(this,object,i,j,layer,radius,center)) return true;
  }
  for(count=delta;count>0;--count) {
   --j;--limit;
   if(reinterpret_cast<Rva002EC3CEProbes *>(this)->rva002E7BF0((int)&profile,zone,center,i,j,layer,destination,obstacle) && possibleFootprint(this,object,i,j,layer,radius,center)) return true;
  }
  ++delta;
 }
 return false;
}

// ZH AIPathfind.cpp snapClosestGoalPosition semantic guide; retail strings
// name Pathfinder::SnapClosestGoalPosition. Native 002F2B88..002F2FA4 RET8.
class Rva0052DB73 { public: bool rva0052DB73(int); };
class Rva0052DB11 { public: bool rva0052DB11(int); };
static __forceinline bool snapDestination(Pathfinder *pathfinder,Object *obj,int x,int y,int layer,int radius,bool center) {
 typedef unsigned char (Pathfinder::*Call)(Object *,int,int,int,int,bool);
 Call typed=reinterpret_cast<Call>(&Pathfinder::bfmeWrapE6E90);
 return (pathfinder->*typed)(obj,x,y,layer,radius,center)!=0;
}
void Pathfinder::SnapClosestGoalPosition(Object *obj,Coord3D *pos)
{
 if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() called with pos=%g,%g,%g",pos->x,pos->y,pos->z);
 Int iRadius;
 bool center;
 Rva002EBCA7Split(obj,&iRadius,reinterpret_cast<unsigned char *>(&center));
 if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() iRadius=%d, center=%s",iRadius,center?"TRUE":"FALSE");
 ICoord2D cell;
 Rva002E7875WorldToCell(&cell,center,pos);
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,pos);
 {
  PathfinderCellPoint adjusted;
  *pos=*(Coord3D *)Rva002E8C4DCall((int)&adjusted,center,(Rva002E8C23Pair *)&cell,1);
 }
 if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination about to get called with cell=%d,%d, layer=%d, iRadius=%d, center=%s, pos=%g%g%g",cell.x,cell.y,layer,iRadius,center?"TRUE":"FALSE",pos->x,pos->y,pos->z);
 if(snapDestination(this,obj,cell.x,cell.y,layer,iRadius,center)) {
  if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination succeeds, returning...");
  return;
 }
 if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination fails, continuing...");
 Int i,j;
 for(i=cell.x-1;i<cell.x+2;i++) {
  for(j=cell.y-1;j<cell.y+2;j++) {
   if(snapDestination(this,obj,i,j,layer,iRadius,center)) {
    *pos=rva002E79A8(center,i,j,layer);
    if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination2 succeeds with cell=%d,%d, layer=%d, iRadius=%d, center=%s, pos=%g%g%g",cell.x,cell.y,layer,iRadius,center?"TRUE":"FALSE",pos->x,pos->y,pos->z);
    return;
   }
  }
 }
 if(iRadius==0) {
  for(i=cell.x-1;i<cell.x+2;i++) {
   for(j=cell.y-1;j<cell.y+2;j++) {
    PathfindCell *newCell=getCell(layer,i,j);
    if(newCell && ((Rva0052DB73 *)newCell)->rva0052DB73(obj->getID())) {
     *pos=rva002E79A8(center,i,j,layer);
     if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination3 succeeds with cell=%d,%d, layer=%d, iRadius=%d, center=%s, pos=%g%g%g",cell.x,cell.y,layer,0,center?"TRUE":"FALSE",pos->x,pos->y,pos->z);
     return;
    }
   }
  }
  for(i=cell.x-1;i<cell.x+2;i++) {
   for(j=cell.y-1;j<cell.y+2;j++) {
    PathfindCell *newCell=getCell(layer,i,j);
    if(newCell && !((Rva0052DB11 *)newCell)->rva0052DB11(obj->getID())) {
     *pos=rva002E79A8(center,i,j,layer);
     if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination4 succeeds with cell=%d,%d, layer=%d, iRadius=%d, center=%s, pos=%g%g%g",cell.x,cell.y,layer,0,center?"TRUE":"FALSE",pos->x,pos->y,pos->z);
     return;
    }
   }
  }
 }
 if(g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"CritterDesync: Pathfinder::SnapClosestGoalPosition() iRadius=%d>0 do nothing case, pos=%g%g%g",iRadius,pos->x,pos->y,pos->z);
}

// WB D36700 names AdjustMeleeOffset. Native 002E8C6E..002E8D74 RET12.
// MathCoord3D has a memberwise copy constructor and empty destructor; this
// local view preserves those lifetimes with the canonical 12-byte layout.
struct PathMeleeCoord : Coord3D
{
    PathMeleeCoord(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
    ~PathMeleeCoord() {}
    PathMeleeCoord &Scale(float scale)
    {
        x*=scale; y*=scale; z*=scale;
        return *this;
    }
    void Add(const Coord3D &p) { x+=p.x; y+=p.y; z+=p.z; }
};

static __forceinline void scaleMeleeOffset(Coord3D &p,float scale)
{
    p.x*=scale; p.y*=scale; p.z*=scale;
}

void Pathfinder::AdjustMeleeOffset(Object *object,Object *target,Coord3D *offset)
{
    int layer=target->rva0028B511();
    if (object->getAI() && object->getAI()->findNearestLabeledContactPointOnTarget(
            target,offset,(const Coord3D *)object->position,false))
        return;

    bool found=false;
    Coord3D center;
    target->rva0028C2DD(&center);
    // WB initializes the index here, after the center query. Its lifetime
    // also determines the destructive final SSE multiply in retail.
    int i;
    for (i=0;i<20;++i) {
        PathMeleeCoord point(*offset);
        point.Scale((float)i);
        point.Add(center);
        PathfindCell *cell=(PathfindCell *)rva001E3647Pos(layer,&point);
        if (!cell)
            break;
        if (target->m_template->kinds[7]&0x10) {
            if ((unsigned char)Rva002E6E8AGet((cell->m_info>>4)&0x3f))
                continue;
        } else if ((cell->m_info&0xf)==4) {
            continue;
        }
        found=true;
        break;
    }
    if (found)
        scaleMeleeOffset(*offset,(float)i);
}

// Rehomed 0x002E7440/66 from AI/Rva002E7440ValidCell.cpp. The real callback
// must be visible with the circular search: cl can then prove how its
// one-pointer context is used and delays that store in the 178-byte caller.
__declspec(noinline) inline Bool Rva002E7440::rva002E7440(Int x,Int y)
{
    PathfindCell *cell=pf->getCell(PATHFIND_LAYER_GROUND,x,y);
    if (cell) {
        unsigned int flags=*(unsigned int *)((char *)cell+12);
        unsigned char blocked=(unsigned char)(flags>>18);
        if (blocked&1)
            return false;
        unsigned int type=flags&15;
        if (type==2 || type==5 || type==4 || type==1)
            return false;
    }
    return true;
}

// Rehomed 0x002E7414/44 from Object/Rva002E7414.cpp for the same reason as
// the 002E7440 callback above: the ground-cell circular search 002EAE5F calls
// it, and a visible body lets cl delay the context store in the 178-byte
// AdjustToNearestGroundCell caller.
__declspec(noinline) inline Int Rva002E7414::rva002E7414(Int x,Int y)
{
    PathfindCell *cell=pf->getCell(PATHFIND_LAYER_GROUND,x,y);
    if (cell) {
        if ((*(unsigned int *)((char *)cell+12)&0x3f0)==0x10)
            return 1;
    }
    return 0;
}

// WB D465D0; native 002EDDA9..002EDE5B RET4. The search budget is +1208
// in the existing GlobalData owner, and the final height query is slot 1C.
Bool Pathfinder::AdjustToNearestValidCell(Coord3D *position)
{
    ICoord2D found;
    {
        ICoord2D cell;
        ((Rva002E7964 *)this)->rva002E7964(&cell,1,position);
        if (cell.x<0)
            return false;
        found.x=0;
        found.y=0;
        Rva002E7440 context(this);
        if (!rva002EB11B(&cell,*(Int *)((char *)TheWritableGlobalData+0x1208),&found,&context))
            return false;
    }
    position->x=found.x*10+1.0f;
    position->y=found.y*10+1.0f;
    position->z=TheTerrainLogic->getLayerHeight(position->x,position->y,PATHFIND_LAYER_GROUND,0,true);
    return true;
}

// Twin of AdjustToNearestValidCell: native 002EDCF7..002EDDA9 RET4, same body
// with the ground-cell scan 002EAE5F (its callback context is the 002E7414
// class, not 002E7440) and the +1204 search budget.
Bool Pathfinder::AdjustToNearestGroundCell(Coord3D *position)
{
    ICoord2D found;
    {
        ICoord2D cell;
        ((Rva002E7964 *)this)->rva002E7964(&cell,1,position);
        if (cell.x<0)
            return false;
        found.x=0;
        found.y=0;
        Rva002E7414 context(this);
        if (!rva002EAE5F(&cell,*(Int *)((char *)TheWritableGlobalData+0x1204),&found,&context))
            return false;
    }
    position->x=found.x*10+1.0f;
    position->y=found.y*10+1.0f;
    position->z=TheTerrainLogic->getLayerHeight(position->x,position->y,PATHFIND_LAYER_GROUND,0,true);
    return true;
}

// ---- getClosestPointOnLand and its visitor helpers (exact bank port) ----
struct _Rva002E7DF5Cell 
{
 int x, y, z;
 
}
;
class Rva002E7DF5

{
 public:
 Rva002E7DF5(int, const _Rva002E7DF5Cell &) throw();
 int owner;
 int sourceWords[3];
 Coord3D closest;
 float cost;
 bool found;
 
}
;
class Rva002E7E26 
{
 public:int rva002E7E26(Object*,int,int);
 int owner;
 Coord3D source,closest;
 float cost;
 bool found;
 
}
;
enum LandCellKind 
{
 LandClear=0, LandWater=1, LandSolid=7 
}
;
struct LandWordView 
{
 int a,b,c;
 unsigned packed;
 __forceinline LandCellKind getKind() const 
 {
  return (LandCellKind)(packed&15);
  
 }
 
}
;
struct LandLocalPoint : Coord3D 
{
 __forceinline void set(const float *p) 
 {
  x=p[0];
  y=p[1];
  z=p[2];
  
 }
 __forceinline void set(float a,float b,float c) 
 {
  x=a;
  y=b;
  z=c;
  
 }
 __forceinline void sub(const float *p) 
 {
  x-=p[0];
  y-=p[1];
  z-=p[2];
  
 }
 __forceinline float squared() const 
 {
  return x*x+y*y+z*z;
  
 }
 
}
;
inline int Rva002E7E26::rva002E7E26(Object *object,int x,int y)

{
 if (((LandWordView *)object)->getKind()==LandSolid) return 0;
 if (((LandWordView *)object)->getKind()==LandWater) return 0;
 if (((LandWordView *)object)->getKind()!=LandClear) return 0;
 LandLocalPoint point;
 point.set((float)(x*10),(float)(y*10),source.z);
 LandLocalPoint delta;
 delta.set(&source.x);
 delta.sub(&point.x);
 float distance=delta.squared();
 if (cost>distance) 
 {
  closest=point;
  cost=distance;
  found=true;
  
 }
 return 0;
 
}
class Rva002E6CFE

{
 public:
 int m_00;
// x in 24.8 fixed point
 int m_04;
// x step per row
 int m_08;
// rows left on this edge
 int m_0C;
// vertex index (used by the convex polygon walk)
 void rva002E6CFE(int a, int b, int c);
 bool rva002E6D2F();
 
}
;
// ?rva002E6CFE@Rva002E6CFE@@QAEXHHH@Z @0x002E6CFE 49B
__declspec(noinline) inline void Rva002E6CFE::rva002E6CFE(int lhs, int rhs, int pathCell)

{
 m_08 = pathCell;
 if (pathCell > 0) 
 {
  m_04 = ((rhs - lhs) << 8) / pathCell;
  m_00 = (m_04 / 2) + (lhs << 8);
  
 }
 
}
// ?rva002E6D2F@Rva002E6CFE@@QAE_NXZ @0x002E6D2F 19B
inline bool Rva002E6CFE::rva002E6D2F()

{
 m_00 += m_04;
 return --m_08 > 0;
 
}
#define nextIndex(i,n) ((i)+1==(n)?0:(i)+1)
#define prevIndex(i,n) ((i)!=0?(i)-1:(n)-1)
inline Int Pathfinder::ProcessConvexPoly( Int *xPts, Int *yPts, Int numEdges, Int layer, Rva002E7E26 *visitor )

{
 Int i;
 Int j = 1;
 for (i = 1; i < numEdges; i++) 
 {
  if (xPts[i] != xPts[j - 1] || yPts[i] != yPts[j - 1]) 
  {
   xPts[j] = xPts[i];
   yPts[j] = yPts[i];
   j++;
   
  }
  
 }
 numEdges = j;
 while (numEdges > 2 && xPts[0] == xPts[numEdges - 1] && yPts[0] == yPts[numEdges - 1]) 
 {
  numEdges--;
  
 }
 if (numEdges < 3) 
 {
  return -1;
  
 }
 Int topIdx = 0;
 Int maxY = 0;
 for (i = 1; i < numEdges; i++) 
 {
  if (yPts[i] < yPts[topIdx] || (yPts[i] == yPts[topIdx] && xPts[i] < xPts[topIdx]))
  topIdx = i;
  if (yPts[i] > maxY)
  maxY = yPts[i];
  
 }
 Int y = yPts[topIdx];
 Rva002E6CFE left;
 left.m_0C = topIdx;
 left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)],
 yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C] );
 left.m_0C = prevIndex(left.m_0C, numEdges);
 while (yPts[topIdx] == yPts[nextIndex(topIdx, numEdges)])
 topIdx = nextIndex(topIdx, numEdges);
 Rva002E6CFE right;
 right.m_0C = topIdx;
 right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)],
 yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C] );
 right.m_0C = nextIndex(right.m_0C, numEdges);
 while (y <= maxY) 
 {
  Int x = (left.m_00 + 0x80) / 256;
  Int xEnd = (right.m_00 + 0x80) / 256;
  while (x <= xEnd) 
  {
   PathfindCell *cell = getCell( (PathfindLayerEnum)layer, x, y );
   x++;
   if (!cell)
   continue;
   Int ret = visitor->rva002E7E26( (Object *)cell, x - 1, y );
   if (ret)
   return ret;
   
  }
  y++;
  if (!left.rva002E6D2F()) 
  {
   while (left.m_08 == 0) 
   {
    Int dy = yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C];
    if (dy < 0)
    break;
    left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)], dy );
    left.m_0C = prevIndex(left.m_0C, numEdges);
    
   }
   
  }
  if (!right.rva002E6D2F()) 
  {
   while (right.m_08 == 0) 
   {
    Int dy = yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C];
    if (dy < 0)
    break;
    right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)], dy );
    right.m_0C = nextIndex(right.m_0C, numEdges);
    if (right.m_08 < 0)
    return 0;
    
   }
   
  }
  
 }
 return 0;
 
}
#undef nextIndex
#undef prevIndex
inline int Pathfinder::IterateCellsInRectangle(const ICoord2DBase *center,const ICoord2DBase *diameter,float angle,int layer,Rva002E7E26 *visitor)

{
 if (diameter->x==1 && diameter->y==1) 
 {
  PathfindCell *cell=getCell((PathfindLayerEnum)layer,center->x,center->y);
  return cell ? visitor->rva002E7E26((Object *)cell,center->x,center->y) : 0;
  
 }
 int x[4],y[4];
 if (angle!=0.0f) 
 {
  float sine,cosine;
  __asm 
  {
   fld angle
   fsincos
   fstp cosine
   fstp sine 
  }
  float hx=diameter->x*0.5f,hy=diameter->y*0.5f;
  float cx=(float)center->x,cy=(float)center->y;
  x[0]=(int)(cx-hx*cosine+hy*sine);
  y[0]=(int)(cy-hy*cosine-hx*sine);
  x[1]=(int)(cx+hx*cosine+hy*sine);
  y[1]=(int)(cy-hy*cosine+hx*sine);
  x[2]=(int)(cx+hx*cosine-hy*sine);
  y[2]=(int)(cy+hy*cosine+hx*sine);
  x[3]=(int)(cx-hx*cosine-hy*sine);
  y[3]=(int)(cy+hy*cosine-hx*sine);
  
 }
 else 
 {
  int hx=diameter->x/2,hy=diameter->y/2;
  x[0]=x[3]=center->x-hx;
  y[0]=y[1]=center->y-hy;
  x[1]=x[2]=center->x+diameter->x-hx-1;
  y[2]=y[3]=center->y+diameter->y-hy-1;
  
 }
 return ProcessConvexPoly(x,y,4,layer,visitor);
 
}
extern float g_Va00BBB8E0;
__declspec(noinline) inline Rva002E7DF5::Rva002E7DF5(int lhs,const _Rva002E7DF5Cell &cell) throw()
{
 float f=g_Va00BBB8E0;
 owner=lhs;
 sourceWords[0]=cell.x;
 sourceWords[1]=cell.y;
 sourceWords[2]=cell.z;
 cost=f;
 found=false;
 
}
static __forceinline int landCells(const float & radius,const float & padding)
{
 const float & scale=2.0f;
 const float & inv=0.1f;
 return (int)(((radius+padding)*scale)*inv);
 
}
Bool Pathfinder::getClosestPointOnLand(const Coord3D *position, Object *object, Coord3D *out)

{
 if (((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(position->x, position->y, 0, 0, 0)) 
 {
  
  {
   GeometryShape shape;
   _ReadWriteBarrier();
   _ReadWriteBarrier();
   reinterpret_cast<const GeometryInfo *>((const char *)object + 0xa8)->rva006BD9C0(shape);
   int minorCells=landCells(shape.minor,(*reinterpret_cast<const float *>(&g_00DBD33C[11])));
   int majorCells=landCells(shape.major,(*reinterpret_cast<const float *>(&g_00DBD33C[10])));
   ICoord2DBase diameter = 
   {
    majorCells, minorCells 
   }
   ;
   Rva002E7DF5 visitor((int)this, *reinterpret_cast<const _Rva002E7DF5Cell *>(position));
   int y = realToIntFloor(position->y * 0.1f + 0.5f);
   int x = realToIntFloor(position->x * 0.1f + 0.5f);
   ICoord2DBase center = 
   {
    x, y 
   }
   ;
   IterateCellsInRectangle(&center, &diameter, object->m_orientation, 1, reinterpret_cast<Rva002E7E26 *>(&visitor));
   *out = visitor.closest;
   return visitor.found;
   
  }
  
 }
 else 
 {
  *out = *position;
  return true;
  
 }
 
}

// ?rva002EF3EE@Pathfinder@@QAE_NPAVObject@@PAUCoord3D@@0_N@Z, retail
// 0x002EF3EE..0x002EF663 (629B, RET16; WB D3C840). Clears the obstacle id,
// takes the cell of the target Object (0x002EDF7C), builds the 0x30-byte
// footprint check (0x002E7388 setter over the mover's movement info, layers
// and radius) and tests the destination cell (0x002E916A). Failing that it
// walks 15 samples t = i/16 from the destination toward the target, testing
// each new cell; a hit moves the destination there on the destination layer
// height. Without one the destination becomes the target cell centre
// (0x002E8C4D) and the result is false.
struct ObjWithPos;
class Rva0028CECFOwner;
struct Rva002E7388Pair;
class Rva002E7388Owner
{
public:
	Rva002E7388Owner *rva002E7388(int p1, Rva0028CECFOwner *p2, int p3, int p4,
		int p5, Rva002E7388Pair *p6, int p7, int p8, int p9);
	bool rva002E916A(int x, int y);
private:
	char m_pad[0x30];
};
// The movement-info value the 0x002E8BCF converting ctor builds (surfaces,
// !template flag, AFBB, priority-1), filled inline with its last byte from the
// mover (0x0028AC62). Retail homes the target cell directly after it (+0x10 of
// one 0x18-byte local, info -0x44 / cell -0x34), so the cell lives here.
struct Rva002EF3EEMoveInfo
{
	__forceinline void set(Int surfaces, Bool a, Int b, Bool c, Bool d)
	{
		m0 = surfaces;
		m4 = a;
		m5 = c;
		m8 = b;
		mC = d;
	}
	Int m0;
	Bool m4, m5;
	Int m8;
	Bool mC;
	ICoord2D targetCell;
};
// fast_float2long_round((float)floor(v)): the floor result handed by value to
// the x87 round-to-integer store. The TU's realToIntFloor (floor inside the
// helper) schedules fstp before the caller pop; retail pops first, as here.
static __forceinline long Rva002EF3EERound(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
Bool Pathfinder::rva002EF3EE(Object *obj, Coord3D *dest, Object *target, Bool flag)
{
	m_ignoreObstacleID = (ObjectID)0;
	Rva002EF3EEMoveInfo info;
	if (!Rva002EDF7C((ObjWithPos *)target, &info.targetCell))
		return false;
	Int priority = obj->m_template->priority;
	Bool templateFlag = obj->m_template->flag;
	Int surfaces = *(const Int *)(obj->m_258 + 0x1dc);
	info.set(surfaces, !templateFlag, priority - 1, obj->rva0028AFBB(), obj->rva0028AC62());
	Int radius;
	Bool center;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&center);
	ICoord2D cell;
	Rva002E7875WorldToCell(&cell, center, dest);
	// The rowed setter types its unused 9th parameter int: retail pushes the
	// flag argument's whole dword, so it is passed as that dword.
	Rva002E7388Owner check;
	check.rva002E7388((int)this, (Rva0028CECFOwner *)target, (int)&info, obj->rva0028B511(),
		target->rva0028B511(), (Rva002E7388Pair *)&info.targetCell, radius, radius + (center ? 1 : 0), reinterpret_cast<int &>(flag));
	if (check.rva002E916A(cell.x, cell.y))
		return true;
	ICoord2D last;
	last.y = -1;
	last.x = -1;
	for (Int i = 1; i < 16; ++i) {
		float t = i * (1.0f / 16.0f);
		float x = dest->x * (1.0f - t) + target->position[0] * t;
		float y = dest->y * (1.0f - t) + target->position[1] * t;
		ICoord2D sample;
		sample.x = center ? Rva002EF3EERound((float)floor(x * PATHFINDER_CELL_INV)) : Rva002EF3EERound((float)floor(x * PATHFINDER_CELL_INV + 0.5f));
		sample.y = center ? Rva002EF3EERound((float)floor(y * PATHFINDER_CELL_INV)) : Rva002EF3EERound((float)floor(y * PATHFINDER_CELL_INV + 0.5f));
		if (sample == *(const ICoord2DBase *)&last)
			continue;
		last = sample;
		if (check.rva002E916A(sample.x, sample.y)) {
			dest->x = x;
			dest->y = y;
			dest->z = TheTerrainLogic->getLayerHeight(dest->x, dest->y,
				TheTerrainLogic->getLayerForDestination(obj, dest), 0, true);
			return true;
		}
	}
	*dest = adjustCellCenter(center, (Rva002E8C23Pair *)&info.targetCell, (PathfindLayerEnum)target->rva0028B511());
	return false;
}

// Native 0x002F07F5..0x002F0A72, 637B RET8, directly after the rowed
// IsValidHordeMemberRegularMovement (0x002F06A3), which it calls first with the
// object's own position. It counts the other units in the object's footprint at
// its current cell, then fails the destination footprint when a bridge-edge cell
// (+0x0C bit 16) borders a cell of another layer, a cell fails the 0x002E6DC4
// movement query, the cells hold as many other units as the old footprint, or an
// occupant's AI (+0x258) has a positive +0x16C. Retail .data 0x00DBD318/0x00DBD328
// hold the {-1,1,0,0}/{0,0,-1,1} neighbour deltas. The destination cell reuses
// the origin ICoord2D through a block-scoped return temporary (retail frame 0x4C).
Bool Pathfinder::rva002F07F5(Object *obj,const Coord3D *dest)
{
 const Coord3D *from=obj->getPosition();
 if(!IsValidHordeMemberRegularMovement(obj,from,dest,from))return false;
 Int lastX; Int lastY;
 Int newCount=0;
 Int below; Int above;Rva002EBCD6Split(obj,&below,&above);
 Int layers[2];layers[0]=obj->rva0028B511();Int layerCount=1;
 if(!(unsigned char)isGroundOrBridgeLayer(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(obj,layers[0])) {
  layers[1]=1;layerCount=2;
 }
 Int oldCount=0;
 ICoord2D cell;
 {
  Rva002EBC14Cell(&cell,obj,from);
  Int x=cell.x-below; lastX=cell.x+above;
  for(;x<lastX;++x) {
   Int y=cell.y-below; lastY=cell.y+above;
   for(;y<lastY;++y)
    for(Int l=0;l<layerCount;++l) {
     PathCollisionCell *pathCell=reinterpret_cast<PathCollisionCell *>(getCell((PathfindLayerEnum)layers[l],x,y));
     if(pathCell && pathCell->info)for(PathCollisionNode *pathCollisionNode=pathCell->info->occupants;pathCollisionNode;pathCollisionNode=pathCollisionNode->next)if(pathCollisionNode->object!=obj)++oldCount;
    }
  }
 }
 {ICoord2D tmp;cell=*Rva002EBC14Cell(&tmp,obj,dest);}
 Int priority=obj->m_template->priority;Bool flag=obj->m_template->flag;char *ai=obj->m_258;
 Rva002E8BCF query((const Rva002E8BCFSrc *)(ai+0x1CC),!flag,priority-1,obj->rva0028AFBB());
 Int x=cell.x-below; lastX=cell.x+above;
 for(;x<lastX;++x) {
  Int y=cell.y-below; lastY=cell.y+above;
  for(;y<lastY;++y)
   for(Int l=0;l<layerCount;++l) {
    Int layer=layers[l];PathfindCell *pathCell=getCell((PathfindLayerEnum)layer,x,y);
    if(!pathCell)continue;
    if(pathCell->m_info & 0x10000) {
     static Int deltaX[]={-1,1,0,0};static Int deltaY[]={0,0,-1,1};
     for(Int i=0;i<4;++i) {
      PathfindCell *neighbor=getCell((PathfindLayerEnum)layer,x+deltaX[i],y+deltaY[i]);
      if(neighbor && ((neighbor->m_info>>4)&0x3F)!=layer)return false;
     }
    }
    PathCollisionInfo *info=reinterpret_cast<PathCollisionCell *>(pathCell)->info;
    if(info) {
     if(!((Rva002E6DC4 *)this)->rva002E6DC4(&query,pathCell))return false;
     for(PathCollisionNode *pathCollisionNode=info->occupants;pathCollisionNode;pathCollisionNode=pathCollisionNode->next) {
      if(pathCollisionNode->object==obj)continue;
      ++newCount;
      if(newCount>=oldCount)return false;
      Object *effective=pathCollisionNode->object->rva002931F5(true);if(!effective)effective=pathCollisionNode->object;
      char *other=effective->m_258;
      if(other && *(Int *)(other+0x16C)>0)return false;
     }
    }
   }
 }
 return true;
}



// Pathfinder::FindCollisionFreeQuickPath, retail 0x002F64DD (1286 bytes) RET 12.
// WorldBuilder D624A0 names it (pathfinder.cpp); native vtable C053F8 slot 10.
// GetHordeUnitPath's bounded A* extended to the path-node goal list, the
// collision-free extra costs and a 3000-cell cap. The two goal-cell guards
// stay separate returns: joined with || the shared return-0 block and the
// epilogue move to the end of the function.
Path *Pathfinder::FindCollisionFreeQuickPath(Object *obj, const Coord3D *to, PathNode *nodes)
{
	m_ignoreObstacleID = (ObjectID)0;
	Int radius;
	Bool center;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&center);
	const Coord3D *pos = obj->getPosition();
	Coord3D from;
	from.x = pos->x;
	from.y = pos->y;
	from.z = pos->z;
	ICoord2D startCell;
	Rva002E7875WorldToCell(&startCell, center, &from);
	ICoord2D goalCell;
	Rva002E7875WorldToCell(&goalCell, center, to);
	if (startCell == *(const ICoord2DBase *)&goalCell)
		return 0;
	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	char *ai = obj->m_258;
	Rva002E8BCF info((const Rva002E8BCFSrc *)(ai+0x1cc), !flag, priority - 1, obj->rva0028AFBB());
	PathfindLayerEnum goalLayer = TheTerrainLogic->getLayerForDestination(obj, to);
	PathfindCell *goals[20];
	goals[0] = getCell(goalLayer, goalCell.x, goalCell.y);
	Int numGoals = 1;
	if (!goals[0])
		return 0;
	if (!((Rva002E6DC4 *)this)->rva002E6DC4(&info, goals[0]))
		return 0;
	PathfindLayerEnum fromLayer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindCell *parent = rva002E8BF8(fromLayer, &from);
	if (!parent)
		return 0;
	goals[0]->allocateInfo((In002E6BA1 *)&goalCell);
	parent->allocateInfo((In002E6BA1 *)&startCell);
	parent->StartPathfind((Int)goals[0]);
	parent->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parent, goals[0]);
	AddToOpenList(parent);
	Int cellCount = 0;
	while (nodes && numGoals < 20)
	{
		nodes = nodes->next;
		if (nodes)
		{
			PathfindLayerEnum nodeLayer = nodes->layer;
			goals[numGoals] = (PathfindCell *)rva001E3647Pos(nodeLayer, &nodes->position);
			if (goals[numGoals])
				++numGoals;
		}
	}
	Path *path;
	while ((parent = rva002F36E5()) != 0)
	{
		for (Int g = 0; g < numGoals; ++g)
		{
			if (parent == goals[g])
			{
				path = new Path;
				PrependCells(path, pos, parent, center);
				path->wordC = 1;
				goto done;
			}
		}
		parent->PutOnClosedList(&m_closedList);
		if (cellCount > 3000)
			break;
		CheckChangeLayers(parent, obj);
		static Int deltaX[] = {1, 0, -1, 0, 1, -1, -1, 1};
		static Int deltaY[] = {0, 1, 0, -1, 1, 1, -1, -1};
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8];
		for (Int i = 0; i < 8; ++i)
		{
			neighborFlags[i] = false;
			ICoord2D coords={parent->getXIndex()+deltaX[i],parent->getYIndex()+deltaY[i]};ICoord2D next=coords;
			PathfindCell *neighbor = getCell((PathfindLayerEnum)parent->getLayer(), next.x, next.y);
			if (!neighbor)
				continue;
			if ((unsigned char)((Rva002E6B06 *)neighbor)->rva002E6B06())
				continue;
			if ((unsigned char)((Rva002E6AF3 *)neighbor)->get())
				continue;
			if (neighbor->getLayer() != parent->getLayer()
				&& neighbor->getLayer() != parent->getConnectLayer()
				&& neighbor->getConnectLayer() != parent->getLayer()
				&& !(parent->getConnectLayer() == 16 && neighbor->getConnectLayer() == parent->getConnectLayer()))
				continue;
			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
				continue;
			Int extra = CalcCollisionFreeExtraCosts(obj, parent, (Rva002EBC7FPair *)&next, (PathfindLayerEnum)neighbor->getLayer(), radius, radius + (center ? 1 : 0), true);
			if (extra < 0 || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, neighbor))
			{
				neighbor->allocateInfo((In002E6BA1 *)&next);
				neighbor->PutOnClosedList(&m_closedList);
				continue;
			}
			neighborFlags[i] = true;
			if (!neighbor->m_pathInfo)
			{
				++cellCount;
				if (!TheMixFileInfoPool)
					Rva0052DBCDInit();
				neighbor->m_pathInfo = (PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (Int)neighbor, (In002E6BA1 *)&next);
			}
			else
				neighbor->m_pathInfo->parentWaypoint = 0;
			Int cost = neighbor->CalcCostSoFar((const Rva002E6C79 *)parent);
			Int dx = abs(coords.x - goals[0]->getXIndex());
			Int dy = abs(coords.y - goals[0]->getYIndex());
			if ((neighbor->m_info & 0x10000) && dx + dy > 3)
				cost += 10;
			neighbor->m_pathInfo->flags &= ~1U;
			Int remaining = rva002F0A72(neighbor, goals[0]);
			if ((neighbor->m_info & 0xf) == 4)
				cost += 1000;
			neighbor->m_pathInfo->costSoFar = (unsigned short)(extra + cost);
			neighbor->SetParentCell((Int *)parent);
			neighbor->m_pathInfo->totalCost = (unsigned short)(neighbor->m_pathInfo->costSoFar + remaining);
			AddToOpenList(neighbor);
		}
	}
	path = 0;
done:
	rva002F40E7();
	goals[0]->ReleaseInfo();
	return path;
}

// Zero Hour Common/LatchRestore.h: restores the latched value when the scope
// ends. LatchRestore<int> ctor/dtor/deleting dtor are rowed at 0x002E7F52..
template <class T>
class LatchRestore
{
public:
	LatchRestore(T &dest, const T &src) : m_whereToRestore(dest)
	{
		m_valueToRestore = dest;
		dest = src;
	}
	virtual ~LatchRestore(void) { m_whereToRestore = m_valueToRestore; }
protected:
	T m_valueToRestore;
	T &m_whereToRestore;
};

// ?MoveAllies@Pathfinder@@QAE_NPAVObject@@PAVPath@@_N@Z, retail 0x002F3C09, 884 bytes.
// WorldBuilder 0xD47470 Pathfinder::MoveAllies (pathfinder.cpp): ZH moveAllies's
// purpose (ask allies on the path to step aside), but BFME samples each path
// segment cell by cell, handles a harvester branch and returns Bool.
// Shape facts from the WB twin: harvester bit cached first; ZH member latch
// (src temp then dest); no named dx/dy (the step loop recomputes the delta);
// node->getLayer() through the getter; each branch owns its testStatus,
// aiMoveAwayFromUnit and break. WorldToCell (0x002E7875) and the radius split
// (0x002EBCD6) are visible above: they receive &curCell/&nextCell and
// &radius/&numCellsAbove, and retail's allocation needs that.
Bool Pathfinder::MoveAllies(Object *obj, Path *path, Bool force)
{
	PathfinderTemplateView *initialTemplate = obj->m_template;
	Bool harvester = initialTemplate->kindBit(0x7d);
	if (!initialTemplate->hasKind(0xe) && !initialTemplate->hasKind(0x10) && !harvester && !path->blockedByAlly)
		return false;
	if (initialTemplate->hasKind(0xbb))
		return false;
	LatchRestore<Int> recursiveDepth(m_moveAlliesDepth, m_moveAlliesDepth + 1);
	if (m_moveAlliesDepth > 1)
		return false;
	Int radius, numCellsAbove;
	Rva002EBCD6Split(obj, &radius, &numCellsAbove);
	ObjectID ignoreId = (ObjectID)0;
	if (obj->getAI())
		ignoreId = (ObjectID)((Rva0006E009DwordField *)obj->getAI())->get();	// getIgnoredObstacleID
	path->Lock();
	Coord3D initialPosition;
	initialPosition.x = path->lastNode->position.x;
	initialPosition.y = path->lastNode->position.y;
	initialPosition.z = path->lastNode->position.z;
	for (PathNode *node = path->lastNode; node && node != path->firstNode; node = node->getPrevious()) {
		if (!node->getPrevious())
			break;
		ICoord2D curCell, nextCell;
		Rva002E7875WorldToCell(&curCell, true, node->getPosition());
		Rva002E7875WorldToCell(&nextCell, true, node->getPrevious()->getPosition());
		Int xSize = abs(nextCell.x - curCell.x);
		Int ySize = abs(nextCell.y - curCell.y);
		Int numSteps = xSize > ySize ? xSize : ySize;
		for (Int step = 0; step < numSteps; step++) {
			Int x = (nextCell.x - curCell.x) * step / numSteps + curCell.x;
			Int y = (nextCell.y - curCell.y) * step / numSteps + curCell.y;
			for (Int i = x - radius; i < x + numCellsAbove; i++) {
				for (Int j = y - radius; j < y + numCellsAbove; j++) {
					PathCollisionCell *cell = reinterpret_cast<PathCollisionCell *>(getCell(node->getLayer(), i, j));
					if (!cell || !cell->info)
						continue;
					for (PathCollisionNode *unitNode = cell->info->goals; unitNode; unitNode = unitNode->next) {
						if (unitNode->object == obj)
							continue;
						if (unitNode->object->getID() == ignoreId)
							continue;
						Object *other = unitNode->object;
						if (obj->m_template->testKindWord(0x74) && other->m_template->testKindWord(0x74))
							continue;
						if (other->m_template->hasKind(0xb6))
							continue;
						if (other->m_template->testKindWord(0x6d) && other->getID() == obj->m_id78)
							continue;
						if (other->isKindOf(MoveAlliesKind9A))
							continue;
						if (obj->getRelationship(other) != ALLIES)
							continue;
						if (obj->m_template->testKindWord(0x6d) && (other->m_template->testKindWord(0x6d) || other->rva002931BA()))
							continue;
						if (harvester && !other->m_template->hasKind(0x7d)) {
							if ((other->getAI()->slot1BC() || other->getAI()->isMoving()) && !force)
								continue;
							if (other->testStatus(MoveAlliesStatus5A))
								continue;
							other->getAI()->aiMoveAwayFromUnit(obj, &initialPosition, CMD_FROM_AI);
							break;
						} else if (other && other->getAI() && !other->getAI()->isMoving()) {
							if (!other->getAI()->slot1B8() && !force)
								continue;
							if (other->testStatus(MoveAlliesStatus5A))
								continue;
							other->getAI()->aiMoveAwayFromUnit(obj, &initialPosition, CMD_FROM_AI);
							break;
						}
					}
				}
			}
		}
	}
	path->Unlock();
	return true;
}


// Hierarchical search views: native2F71A6 and the complete WB D4FAE0 body
// establish these accessed fields; ZH/BF1 supply the search algorithm only.
class MineshaftPortalNetworkManager { public: Bool hasUsableNetwork(void *); };
// GameStateInit.cpp defines TheMineshaftPortalNetworkManager (0x00A01EDC); the
// GameEngineInit.cpp registration literal names it.
extern void *TheMineshaftPortalNetworkManager;
class HierarchyTerrain : public PathfinderNativeSlots<33> { public: virtual Waypoint *getFirstWaypoint(); };
class Rva002E6ECA { public: Int get() const; };
Int isGroundOrBridgeLayer(Int);
class Rva003F69C0Object { public: void set(Int *,Int); };
struct Disp32IntPair { Int x,y; };
class Rva005315B0IntPairField { public: void get(Disp32IntPair &); };
struct HierarchySearchOptions { Int surfaces;Bool passFlag,objectFlag;Int priority;Bool layerFlag; };
struct HierarchyLayerView { char pad[0x18];ICoord2D start,end;Int word28,zone;Bool destroyed; };
static __forceinline void hierarchySetParent(PathfindCell *cell,PathfindCell *parent,Waypoint *waypoint=0) {
 ((Rva003F69C0Object *)cell)->set((Int *)parent,(Int)waypoint);
}
static __forceinline bool hierarchyClosed(PathfindCell *cell) { return (unsigned char)((Rva002E6B06 *)cell)->rva002E6B06()!=0; }
static __forceinline bool hierarchyOpen(PathfindCell *cell) { return (unsigned char)((Rva002E6AF3 *)cell)->get()!=0; }
struct HierarchyPoint : public Coord3D { HierarchyPoint(){}
 HierarchyPoint(const HierarchyPoint &hierarchyPoint) { x=hierarchyPoint.x;y=hierarchyPoint.y;z=hierarchyPoint.z; }
 HierarchyPoint(const Coord3D &c) { x=c.x;y=c.y;z=c.z; }
 HierarchyPoint &operator=(const Coord3D &c) { *(Coord3D *)this=c;return *this; }
};

// Rehomed 0x002F5022 (645 B, RET 36), original PathfinderProcessHierarchicalCell.cpp:
// the hierarchical cell expansion (BF1 cee35b7d ProcessHierarchicalCell, ZH
// AIPathfind.cpp:7346 give purpose only). Retail compiled it in this unit: with
// its body visible internal_findHierarchicalPath below takes retail's frame
// (0x110, originalTo kept in its slot); declared only, the caller grows by a slot.
// Reload examinedCount in the scan; the pinched/bit-23 tests stay bool getters.
void Pathfinder::rva002F5022(const ICoord2D &scan,const ICoord2D &delta,PathfindCell *parent,PathfindCell *goal,unsigned short parentZone,unsigned short *examined,int &examinedCount,int profile,int &cellCount)
{
 if(scan.x<m_clampLo.x || scan.x>m_clampHi.x || scan.y<m_clampLo.y || scan.y>m_clampHi.y)return;
 if(parentZone==((Rva002E99F9Sub460 *)&m_zoneManager)->rva00532041(profile,scan.x,scan.y,(Rva00532041Record**)m_unknown10)) {
  PathfindCell *first=getCell(PATHFIND_LAYER_GROUND,scan.x,scan.y);
  if(hierarchyOpen(first) || hierarchyClosed(first))return;
  ICoord2D adjacent=scan;adjacent.x+=delta.x;adjacent.y+=delta.y;
  if(adjacent.x<m_clampLo.x || adjacent.x>m_clampHi.x || adjacent.y<m_clampLo.y || adjacent.y>m_clampHi.y)return;
  PathfindCell *next=getCell(PATHFIND_LAYER_GROUND,adjacent.x,adjacent.y);
  if(hierarchyOpen(next) || hierarchyClosed(next))return;
  unsigned short nextZone=((Rva002E99F9Sub460 *)&m_zoneManager)->rva00532041(profile,adjacent.x,adjacent.y,(Rva00532041Record**)m_unknown10);
  for(int j=0;j<examinedCount;++j) {
   if(examined[j]==nextZone){next->allocateInfo((In002E6BA1 *)&adjacent);next->PutOnClosedList(&m_closedList);return;}
  }
  if(!((Rva002E99F9Sub460 *)&m_zoneManager)->rva005318DB((void*)profile,first,next))return;
  first->allocateInfo((In002E6BA1 *)&scan);
  if(!hierarchyClosed(first) && !hierarchyOpen(first))first->PutOnClosedList(&m_closedList);
  next->allocateInfo((In002E6BA1 *)&adjacent);++cellCount;
  int currentCost=next->CalcCostToHierGoal(parent);
  int remainingCost=next->CalcCostToHierGoal(goal);
  if(next->getPinched() || first->getPinched() || next->getBit23() || first->getBit23())currentCost+=20;
  else {examined[examinedCount]=nextZone;++examinedCount;}
  next->m_pathInfo->costSoFar=parent->m_pathInfo->costSoFar+currentCost;
  next->m_pathInfo->totalCost=next->m_pathInfo->costSoFar+remainingCost;
  hierarchySetParent(next,parent);AddToOpenList(next);
 }
}

// Native 0x002F71A6..0x002F83A3 (4605 B, RET 32); WorldBuilder D4FAE0
// (pathfinder.cpp:7421..7827) is the unoptimised twin, ZH/BF1 AIPathfind.cpp's
// hierarchical search the algorithm guide. Target shapes: the mineshaft scan
// tests the waypoint type with a switch (WB switch temp), the first distance
// subtracts x in place and keeps y's difference in a temporary (retail stores
// the unsubtracted y), one reached-goal exit follows the portal block.
// CandidateStorage is a storage adapter, not a claimed original class.
struct HSO : HierarchySearchOptions { HSO(Int s,Bool a,Int b,Bool c,Bool d){surfaces=s;passFlag=a;objectFlag=c;priority=b;layerFlag=d;} };
Path *Pathfinder::internal_findHierarchicalPath(Bool isHuman,
 LocomotorSurfaceTypeMask surfaces,Object *obj,const Coord3D *from,
 const Coord3D *rawTo,Bool crusher,Bool closestOK,Coord3D *adjustedTo)
{
 union CandidateStorage {Waypoint *waypoint;PathfindCell *cell;};CandidateStorage candidate;
 if(rawTo->x==0.0f && rawTo->y==0.0f)return 0;
 if(!m_isMapReady)return 0;
 HierarchyPoint adjustTo(*rawTo);
 Coord3D *to=&adjustTo;
 HierarchyPoint clipFrom(*from);
 clip(&clipFrom,&adjustTo);
 m_isTunneling=false;
 Bool useMineshaft=false;
 HierarchyPoint originalTo(adjustTo);
 if(((MineshaftPortalNetworkManager *)TheMineshaftPortalNetworkManager)->hasUsableNetwork(obj->getControllingPlayer())) {
  float startDistance=0.0f,endDistance=0.0f;
  for(Waypoint *way=((HierarchyTerrain *)TheTerrainLogic)->getFirstWaypoint();way;way=way->next) {
   switch(way->type) { case 8: if((unsigned char)((Rva002E6ECA *)way)->get() && way->isValidUnitType(obj)) {
    if(rva001E3647Pos(TheTerrainLogic->getLayerForDestination(0,&way->location),&way->location)) {
     HierarchyPoint delta(way->location);
     delta.x-=obj->position[0];float dy=delta.y-obj->position[1];delta.z-=obj->position[2];
     float dist=delta.x*delta.x+dy*dy;
     if(!m_srcMineshaft || dist<startDistance) {m_srcMineshaft=(PathfinderMineshaft *)way;startDistance=dist;}
     delta=way->location;
     delta.x-=rawTo->x;delta.y-=rawTo->y;delta.z-=rawTo->z;
     dist=delta.x*delta.x+delta.y*delta.y;
     if(!m_destMineshaft || dist<endDistance) {m_destMineshaft=(PathfinderMineshaft *)way;endDistance=dist;}
    }
   } break; }
  }
  if(m_srcMineshaft && m_destMineshaft && m_srcMineshaft!=m_destMineshaft &&
     QuickDoesPathExist(obj,from,&m_srcMineshaft->m_position,0) &&
     QuickDoesPathExist(obj,&m_destMineshaft->m_position,rawTo,0)) {
   useMineshaft=true;adjustTo=m_srcMineshaft->m_position;clip(&clipFrom,&adjustTo);
  } else {m_srcMineshaft=0;m_destMineshaft=0;}
 }
 PathfindLayerEnum destinationLayer=TheTerrainLogic->getLayerForDestination(0,to);
 ICoord2D cell;Rva002E7875WorldToCell(&cell,true,to);
 PathfindCell *goalCell=getCell(destinationLayer,cell.x,cell.y);
 if(!goalCell)return 0;
 goalCell->allocateInfo((In002E6BA1 *)&cell);
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(0,from);
 PathfindCell *parentCell=rva002E8BF8(layer,&clipFrom);
 if(!parentCell)return 0;
 if(parentCell==goalCell) {goalCell->ReleaseInfo();return 0;}
 { ICoord2D startCellNdx;
 parentCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&startCellNdx,true,&clipFrom)); }
 if((parentCell->m_info & 15)==4 &&
    (parentCell->m_pathInfo?parentCell->m_pathInfo->obstacleID:(ObjectID)0)!=m_ignoreObstacleID) {
  goalCell->ReleaseInfo();parentCell->ReleaseInfo();return 0;
 }
 Int priority=obj->m_template->priority;
 Bool flag=obj->m_template->flag;
 HSO options(surfaces,!flag,priority-1,obj->rva0028AFBB(),obj->rva0028AC62());
 Rva002E99F9Sub460 *zones=(Rva002E99F9Sub460 *)&m_zoneManager;
 Int zone1=zones->rva0053241F(&options,parentCell->quickZone());
 Int zone2=zones->rva0053241F(&options,goalCell->quickZone());
 if((goalCell->m_info & 15)==4){zone2=zones->rva00531FD4(&options,(unsigned short)zone2);zone2=zones->rva0053241F(&options,(unsigned short)zone2);}
 if(!closestOK && !rva002F4115(obj,zone1,zone2,0)) {goalCell->ReleaseInfo();parentCell->ReleaseInfo();return 0;}
 parentCell->StartPathfind((Int)goalCell);
 parentCell->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parentCell,goalCell);
 Int cellCount=0;
 unsigned short goalBlockZone;
 ICoord2D goalBlockNdx;
 if((unsigned char)isGroundOrBridgeLayer(goalCell->getLayer())) {
  goalBlockZone=zones->rva00532041((Int)&options,goalCell->getXIndex(),goalCell->getYIndex(),(Rva00532041Record **)m_unknown10);
  goalBlockNdx.x=goalCell->getXIndex()/16;goalBlockNdx.y=goalCell->getYIndex()/16;
 } else {goalBlockZone=goalCell->quickZone();goalBlockNdx.x=-1;goalBlockNdx.y=-1;}
 AddToOpenList(parentCell);
 Int parentLayer=parentCell->getLayer();
 if(!(unsigned char)isGroundOrBridgeLayer(parentLayer)) {
  ICoord2D ndx=((HierarchyLayerView *)&m_layers[parentLayer])->start,toNdx=((HierarchyLayerView *)&m_layers[parentLayer])->end;
  PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
  PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
  if(end && start) {
   rva002F36E5();parentCell->PutOnClosedList(&m_closedList);
   start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);++cellCount;
   Int curCost=start->CalcCostToHierGoal(parentCell),remCost=start->CalcCostToHierGoal(goalCell);
   start->m_pathInfo->costSoFar=(unsigned short)curCost;start->m_pathInfo->totalCost=(unsigned short)remCost;
   hierarchySetParent(start,parentCell);AddToOpenList(start);
   ++cellCount;end->allocateInfo((In002E6BA1 *)&toNdx);
   curCost=end->CalcCostToHierGoal(parentCell);remCost=end->CalcCostToHierGoal(goalCell);
   end->m_pathInfo->costSoFar=(unsigned short)curCost;end->m_pathInfo->totalCost=(unsigned short)remCost;
   hierarchySetParent(end,parentCell);AddToOpenList(end);
  }
 }
 candidate.cell=0;
 float closestDistSqr=1.0e12f;
 PathfindCell *initialCell=parentCell;
 while((parentCell=rva002F36E5())!=0) {
  parentCell->PutOnClosedList(&m_closedList);
  unsigned short parentZone;
  if((unsigned char)isGroundOrBridgeLayer(parentCell->getLayer()))
   parentZone=zones->rva00532041((Int)&options,parentCell->getXIndex(),parentCell->getYIndex(),(Rva00532041Record **)m_unknown10);
  else parentZone=parentCell->quickZone();
  Bool reachedGoal=false;
  Int blockX=parentCell->getXIndex()/16,blockY=parentCell->getYIndex()/16;
  if(parentZone==goalBlockZone && (goalBlockNdx.x==-1 || (blockX==goalBlockNdx.x && blockY==goalBlockNdx.y)))reachedGoal=true;
  Disp32IntPair extent;((Rva005315B0IntPairField *)&m_zoneManager)->get(extent);
  if(!reachedGoal && m_zoneManager.rva00532069(parentCell->getXIndex(),parentCell->getYIndex())) {
   for(Int i=0;i<=15;++i) {
    HierarchyLayerView *bridge=(HierarchyLayerView *)&m_layers[i];
    if(!((Rva0036666B *)bridge)->rva0036666B() || bridge->destroyed)continue;
    ICoord2D ndx=bridge->start,toNdx=bridge->end;
    if(ndx.x/16!=blockX || ndx.y/16!=blockY) {toNdx=bridge->start;ndx=bridge->end;}
    if(ndx.x<0 || ndx.y<0)continue;
    _ReadWriteBarrier();
    if(toNdx.x<0 || toNdx.y<0)continue;
    if(ndx.x/16==blockX && ndx.y/16==blockY) {
     Int bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
     if(bridgeZone!=parentZone) {
      if(ndx.x/16==toNdx.x/16 && ndx.y/16==toNdx.y/16) {
       ICoord2D temp=ndx;ndx=toNdx;toNdx=temp;
       bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
      }
      if(bridgeZone!=parentZone)continue;
     }
     if(bridge->zone==goalBlockZone) {reachedGoal=true;break;}
     PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
     if(!end || hierarchyClosed(end) || hierarchyOpen(end))continue;
     PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
     if(!start || start==end)continue;
     if(start!=parentCell) {
      start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);
      if(!hierarchyClosed(start) && !hierarchyOpen(start))start->PutOnClosedList(&m_closedList);
     }
     end->allocateInfo((In002E6BA1 *)&toNdx);hierarchySetParent(end,start);++cellCount;
     Int curCost=end->CalcCostToHierGoal(start),remCost=end->CalcCostToHierGoal(goalCell);
     end->m_pathInfo->costSoFar=(unsigned short)(start->m_pathInfo->costSoFar+curCost);
     end->m_pathInfo->totalCost=(unsigned short)(end->m_pathInfo->costSoFar+remCost);
     hierarchySetParent(end,start);AddToOpenList(end);
    }
   }
  }
  Bool wasMineshaft=useMineshaft;
  if(reachedGoal) {
   if(useMineshaft) {
    useMineshaft=false;reachedGoal=false;adjustTo=originalTo;
    PathfindLayerEnum dest=TheTerrainLogic->getLayerForDestination(0,to);
    ICoord2D ndx;Rva002E7875WorldToCell(&ndx,true,to);
    goalCell=getCell(dest,ndx.x,ndx.y);goalCell->allocateInfo((In002E6BA1 *)&ndx);
    zone2=zones->rva0053241F(&options,goalCell->quickZone());
    if((unsigned char)isGroundOrBridgeLayer(goalCell->getLayer())) {
     goalBlockZone=zones->rva00532041((Int)&options,goalCell->getXIndex(),goalCell->getYIndex(),(Rva00532041Record **)m_unknown10);
     goalBlockNdx.x=goalCell->getXIndex()/16;goalBlockNdx.y=goalCell->getYIndex()/16;
    } else {goalBlockZone=goalCell->quickZone();goalBlockNdx.x=-1;goalBlockNdx.y=-1;}
   }
  }
  if(!reachedGoal && m_zoneManager.rva005315C8(parentCell->getXIndex(),parentCell->getYIndex())) {
   Int i=0;
   for(Waypoint *wp=(Waypoint *)m_zoneManager.GetPortal(parentCell->getXIndex(),parentCell->getYIndex(),i);
       wp;wp=(Waypoint *)m_zoneManager.GetPortal(parentCell->getXIndex(),parentCell->getYIndex(),++i)) {
    if(wp->type==8 && !wasMineshaft)continue;
    if(!wp->isValidUnitType(obj))continue;
    ICoord2D ndx;Rva002E7875WorldToCell(&ndx,true,&wp->location);
    for(Int j=0;j<wp->linkCount;++j) {
     Waypoint *link=wp->getLink(j);if(!link)continue;
     ICoord2D toNdx;Rva002E7875WorldToCell(&toNdx,true,&link->location);
     HierarchyLayerView *bridge=(HierarchyLayerView *)&m_layers[i];
     if(ndx.x/16!=blockX || ndx.y/16!=blockY) {toNdx=bridge->start;ndx=bridge->end;}
     if(ndx.x<0 || ndx.y<0)continue;
     if(toNdx.x<0 || toNdx.y<0)continue;
     _ReadWriteBarrier();
     if(ndx.x/16==blockX && ndx.y/16==blockY) {
      unsigned short bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
      if(bridgeZone!=parentZone)continue;
      if(bridge->zone==goalBlockZone) {reachedGoal=true;break;}
      PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
      if(!end || hierarchyClosed(end) || hierarchyOpen(end))continue;
      PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
      if(!start)continue;
      if(start!=parentCell) {
       start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);
       if(!hierarchyClosed(start) && !hierarchyOpen(start))start->PutOnClosedList(&m_closedList);
      }
      end->allocateInfo((In002E6BA1 *)&toNdx);hierarchySetParent(end,start,wp);++cellCount;
      Int curCost=0;if(wp->type==8)curCost=500;else curCost=end->CalcCostToHierGoal(start);
      Int remCost=end->CalcCostToHierGoal(goalCell);
      end->m_pathInfo->costSoFar=(unsigned short)(start->m_pathInfo->costSoFar+curCost);
      end->m_pathInfo->totalCost=(unsigned short)(end->m_pathInfo->costSoFar+remCost);
      hierarchySetParent(end,start,wp);AddToOpenList(end);
     }
    }
   }
  }
  if(reachedGoal){
   if(parentCell!=goalCell)hierarchySetParent(goalCell,parentCell);
   m_isTunneling=false;
   Path *path=(Path *)MakeHierarchicalPathPassable((void *)from,(Rva002E6C79 *)goalCell,((((const unsigned int *)obj->m_template->kinds)[5]>>31)&1)!=0);
   rva002F40E7();goalCell->ReleaseInfo();goalCell->ReleaseInfo();*adjustedTo=adjustTo;return path;
  }
  float dx=(float)((Int (__cdecl *)(Int))ji_00629952)(goalCell->getXIndex()-parentCell->getXIndex());
  float dy=(float)((Int (__cdecl *)(Int))ji_00629952)(goalCell->getYIndex()-parentCell->getYIndex());
  float distance=dx*dx+dy*dy;
  if(distance<closestDistSqr) {candidate.cell=parentCell;closestDistSqr=distance;}
  Int k; unsigned short examinedZones[16];Int examinedCount=0;
  if(blockX>0) {
   for(k=1;k<=16;++k) {
    ICoord2D ndx; ndx.x=blockX*16;ndx.y=blockY*16;ndx.y+=8;Int offset=k>>1;if(k&1)offset=-offset;ndx.y+=offset;ICoord2D delta={ -1,0 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (ndx.x>=m_extentLowX && ndx.x<=m_extentHighX && ndx.y>=m_extentLowY && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockX<extent.x-1) {
   examinedCount=0;
   for(k=1;k<=16;++k) {
    ICoord2D ndx; ndx.x=blockX*16+15;ndx.y=blockY*16;ndx.y+=8;Int offset=k>>1;if(k&1)offset=-offset;ndx.y+=offset;ICoord2D delta={ 1,0 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (ndx.x>=m_extentLowX && ndx.x<=m_extentHighX && ndx.y>=m_extentLowY && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockY>0) {
   examinedCount=0;
   for(k=1;k<=16;++k) {
    ICoord2D ndx; ndx.y=blockY*16;ndx.x=blockX*16;ndx.x+=8;Int offset=k>>1;if(k&1)offset=-offset;ndx.x+=offset;ICoord2D delta={ 0,-1 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (ndx.x>=m_extentLowX && ndx.x<=m_extentHighX && ndx.y>=m_extentLowY && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockY<extent.y-1) {
   examinedCount=0;
   for(k=1;k<=16;++k) {
    ICoord2D ndx; ndx.y=blockY*16+15;ndx.x=blockX*16;ndx.x+=8;Int offset=k>>1;if(k&1)offset=-offset;ndx.x+=offset;ICoord2D delta={ 0,1 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (ndx.x>=m_extentLowX && ndx.x<=m_extentHighX && ndx.y>=m_extentLowY && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
 }
 if(closestOK && candidate.cell && candidate.cell!=initialCell) {
  m_isTunneling=false;
  Coord3D closest;
  PathfinderGroundInfo *info=candidate.cell->m_pathInfo;
  *adjustedTo=*(Coord3D *)Rva002E8C4DCall((Int)&closest,1,(Rva002E8C23Pair *)info,1);
  Path *path=(Path *)MakeHierarchicalPathPassable((void *)from,(Rva002E6C79 *)candidate.cell,((((const unsigned int *)obj->m_template->kinds)[5]>>31)&1)!=0);
  rva002F40E7();goalCell->ReleaseInfo();return path;
 }
 _STL::vector<Gen_p12pod> *hops=(_STL::vector<Gen_p12pod> *)&m_1C1CC;hops->erase(hops->begin(),hops->end());
 m_isTunneling=false;rva002F40E7();goalCell->ReleaseInfo();return 0;
}

// Ground search 0x002F95F6; WB D337F0 and ZH/BFME1 algorithm provenance.
// The native hierarchical search and the same-unit 0x002F69E3 walk keep
// coordinate addresses local; real zone getters and HSO argument evaluation
// reproduce the native register allocation and Boolean argument spill.
struct Rva002F4491Info { Pathfinder *pathfinder; Bool center; char pad5[3]; PathfindCell *goal; Int diameter;
    Int cellCallback(PathfindCell *,PathfindCell *,Int,Int); };
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
struct GroundTriggerCell { char pad0[6]; unsigned short count; char pad8[12]; };
struct GroundTriggerGrid { char pad0[0x70]; GroundTriggerCell **cells; char pad74[4]; Int width,height;
    __forceinline Bool isMarked(const Coord3D *p) const {
        Int x=clipCellRound(clipCellFloor((p->x+0.5f)/10.0f));
        Int y=clipCellRound(clipCellFloor((p->y+0.5f)/10.0f));
        if(x<0 || x>=width || y<0 || y>=height)return false;
        return cells[x][y].count>0;
    }
};
static Int groundDx[8]={1,0,-1,0,1,-1,-1,1};
static Int groundDy[8]={0,1,0,-1,1,1,-1,-1};

inline __declspec(noinline) Int Pathfinder::iterateCellsAlongLine( const ICoord2D *startCell,
	const ICoord2D *destinationCell, PathfindLayerEnum layer,
	Rva002F4491Info *callbackInfo )
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


// ZH/BFME1 findGroundPath semantic donor. Native 2F95F6..2F9DBA and WB
// D337F0 identify the target's Object-aware four-argument ground search.
// Target adds hierarchy metadata, movement query, CalcExtraCosts and trigger
// grid penalty; every field, direction table and coefficient is decoded there.
Path *Pathfinder::FindGroundPath(Object *obj,const Coord3D *from,const Coord3D *rawTo,Int diameter)
{
    m_zoneManager.rva005312BE();
    m_srcMineshaft=0;m_destMineshaft=0;{ _STL::vector<Gen_p12pod> *hops=reinterpret_cast<_STL::vector<Gen_p12pod> *>(&m_1C1CC);hops->erase(hops->begin(),hops->end()); };
    Coord3D hierarchicalTarget;
    if(!internal_findHierarchicalPath(true,1,obj,from,rawTo,false,false,&hierarchicalTarget))m_zoneManager.rva00531300();
    if((rawTo->x==0 && rawTo->y==0) || !m_isMapReady)return 0;
    Coord3D adjusted;copyCoord3D(&adjusted,rawTo);
    Coord3D clipped;copyCoord3D(&clipped,from);
    clip(&clipped,&adjusted);m_isTunneling=false;
    PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,&adjusted);
    ICoord2D cell;Rva002E7875WorldToCell(&cell,true,&adjusted);
    if(diameter!=rva002E7749(0,cell.x,cell.y,layer,diameter,true)){
        Int offset=1;ICoord2D previous;
        while(offset<8){
            previous=cell;
            cell.x+=offset;
            if(rva002E7749(0,cell.x,cell.y,layer,diameter,true)==diameter)break;
            cell.y+=offset;
            if(rva002E7749(0,cell.x,cell.y,layer,diameter,true)==diameter)break;
            cell.x-=offset;
            if(rva002E7749(0,cell.x,cell.y,layer,diameter,true)==diameter)break;
            cell.x-=offset;
            if(rva002E7749(0,cell.x,cell.y,layer,diameter,true)==diameter)break;
            cell.y-=offset;
            if(rva002E7749(0,cell.x,cell.y,layer,diameter,true)==diameter)break;
            cell.y-=offset;
            if(rva002E7749(0,cell.x,cell.y,layer,diameter,true)==diameter)break;
            cell.x+=offset;
            if(rva002E7749(0,cell.x,cell.y,layer,diameter,true)==diameter)break;
            cell.x+=offset;
            if(rva002E7749(0,cell.x,cell.y,layer,diameter,true)==diameter)break;
            ++offset;cell=previous;
        }
        if(offset>=8)return 0;
    }
    PathfindCell *goal=getCell(layer,cell.x,cell.y);
    if(!goal)return 0;
    goal->allocateInfo((In002E6BA1 *)&cell);
    PathfindCell *parent;PathfindLayerEnum startLayer=TheTerrainLogic->getLayerForDestination(obj,from);parent=rva002E8BF8(startLayer,&clipped);
    if(!parent)return 0;
    if(parent!=goal){
        ICoord2D start;ICoord2D *coordinate=Rva002E7875WorldToCell(&start,true,&clipped);
        parent->allocateInfo((In002E6BA1 *)coordinate);
    }
    Int priority=obj->m_template->priority;
    Bool flag=obj->m_template->flag;

    HSO query(1,!flag,priority-1,obj->rva0028AFBB(),obj->rva0028AC62());
    Int zone1=((Rva002E99F9Sub460 *)&m_zoneManager)->rva0053241F(&query,parent->quickZone());
    Int zone2=((Rva002E99F9Sub460 *)&m_zoneManager)->rva0053241F(&query,goal->quickZone());
    if(zone1!=zone2){goal->ReleaseInfo();parent->ReleaseInfo();return 0;}
    parent->StartPathfind((Int)goal);
    parent->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parent,goal);
    AddToOpenList(parent);
    while((parent=rva002F36E5())!=0){
        if(parent==goal){
            m_isTunneling=false;
            Path *path=BuildGroundPath(from,goal,false,diameter);
            rva002F40E7();parent->ReleaseInfo();return path;
        }
        parent->PutOnClosedList(&m_closedList);CheckChangeLayers(parent,0);
        {
        ICoord2D start,end;start.x=parent->getXIndex();start.y=parent->getYIndex();end.x=goal->getXIndex();end.y=goal->getYIndex();
        Rva002F4491Info info;info.pathfinder=this;info.center=false;info.goal=goal;info.diameter=diameter;
        iterateCellsAlongLine(&start,&end,(PathfindLayerEnum)parent->getLayer(),&info); }
        ICoord2D newCellCoord;
        PathfindCell *newCell;
        const Int adjacent[5]={0,1,2,3,0};
        Bool neighborFlags[8]={false,false,false,false,false,false,false};
        unsigned int newCostSoFar;
        for(Int i=0;i<8;++i){
            neighborFlags[i]=false;
            newCellCoord.x=parent->getXIndex()+groundDx[i];
            newCellCoord.y=parent->getYIndex()+groundDy[i];
            newCell=getCell((PathfindLayerEnum)parent->getLayer(),newCellCoord.x,newCellCoord.y);
            if(!newCell)continue;
            if(newCell->getLayer()==1 && !m_zoneManager.IsPassable(newCellCoord.x,newCellCoord.y)){
                Bool passable=false;
                if(m_zoneManager.IsPassable(newCellCoord.x+3,newCellCoord.y+3))passable=true;
                if(m_zoneManager.IsPassable(newCellCoord.x-3,newCellCoord.y+3))passable=true;
                if(m_zoneManager.IsPassable(newCellCoord.x+3,newCellCoord.y-3))passable=true;
                if(m_zoneManager.IsPassable(newCellCoord.x-3,newCellCoord.y-3))passable=true;
                if(!passable)continue;
            }
            if((unsigned char)((Rva002E6AF3 *)newCell)->get())continue;
            if((unsigned char)((Rva002E6B06 *)newCell)->rva002E6B06())continue;
            if(newCell!=goal){
                if(i>=4){
                    if(!neighborFlags[adjacent[i-4]] && !neighborFlags[adjacent[i-3]])continue;
                }
                if(newCell->getType()!=PathfindCell::CELL_CLEAR)continue;
                if((unsigned char)(newCell->m_info>>16)&1)continue;
                neighborFlags[i]=true;
                newCell->allocateInfo((In002E6BA1 *)&newCellCoord);
            }
            Int clearDiameter=rva002E7749(0,newCellCoord.x,newCellCoord.y,newCell->getLayer(),diameter,false);
            newCostSoFar=newCell->CalcCostSoFar((const Rva002E6C79 *)parent);
            newCostSoFar+=CalcExtraCosts(obj,parent,(Rva002EBC7FPair *)&newCellCoord,diameter,diameter,true);
            if(clearDiameter<diameter){
                int delta=diameter-clearDiameter;
                newCostSoFar+=0.6f*(delta*10);
            }
            Coord3D pos;pos.x=(float)(newCellCoord.x*10);pos.y=(float)(newCellCoord.y*10);
            if(((GroundTriggerGrid *)TheTriggerManager)->isMarked(&pos))newCostSoFar+=10;
            newCell->m_pathInfo->flags&=~1U;
            Int costRemaining=rva002F0A72(newCell,goal);
            newCell->m_pathInfo->costSoFar=(unsigned short)newCostSoFar;
            newCell->SetParentCell((Int *)parent);
            newCell->m_pathInfo->totalCost=(unsigned short)(newCell->m_pathInfo->costSoFar+costRemaining);
            AddToOpenList(newCell);
        }
    }
    m_isTunneling=false;rva002F40E7();goal->ReleaseInfo();return 0;
}

struct PathfinderAttackNode{PathfinderAttackNode*next,*previous,*optimized;};
struct PathfinderAttackPathView{void*vptr;PathfinderAttackNode*first;};
struct AttackLimitView{char gap[0x9b8];Int debugAI;char pad[0x1214-0x9bc];unsigned int attackLimit;};
__declspec(noinline) inline void Coord3D::normalize(){float len=length();if(len!=0.0f){float s=1.0f/len;x*=s;y*=s;z*=s;}}
struct Rva002E8BCFSrc{char pad[0x10];Int m10;char m14;Bool m15;};
__declspec(noinline) Rva002E8BCF::Rva002E8BCF(const Rva002E8BCFSrc*src,Bool lhs,Int rhs,Bool pathCell){surfaces=src->m10;field4=lhs;field5=pathCell;maxLayer=rhs;fieldC=src->m15;}
struct PathfinderAttackCoord : Coord3D {
    __forceinline PathfinderAttackCoord() {}
    __forceinline PathfinderAttackCoord(const Coord3D &v) { x=v.x;y=v.y;z=v.z; }
    __forceinline PathfinderAttackCoord(const PathfinderAttackCoord &pathfinderAttackCoord) { x=pathfinderAttackCoord.x;y=pathfinderAttackCoord.y;z=pathfinderAttackCoord.z; }
    __forceinline ~PathfinderAttackCoord(){}
    void set(float xx,float yy,float zz){x=xx;y=yy;z=zz;}
    void sub(const Coord3D&p){x-=p.x;y-=p.y;z-=p.z;}
    void scale(float f){x*=f;y*=f;z*=f;}
    void add(const Coord3D&p){x+=p.x;y+=p.y;z+=p.z;}
};

inline __declspec(noinline) PathNode::PathNode(const Coord3D *p,PathfindLayerEnum l) throw() {
 next=0;previous=0;nextOptimized=0;copyCoord3D(&position,p);layer=l;canOptimize=false;portalID=0x7fffffff;
}

class Rva0026E4A0 {public:Rva0026E4A0 &set(Rva0026E4A0 *) throw();};
extern Rva00065964ObjectPool g_pathNodePool;
inline __declspec(noinline) void Path::prependNode(const Coord3D *pos,PathfindLayerEnum layer,int id) {
 void *mem=g_pathNodePool.rva002635C2();
 PathNode *node=mem ? new(mem) PathNode(pos,layer):0;
 node->portalID=id;
 firstNode=(PathNode *)&((Rva0026E4A0 *)node)->set((Rva0026E4A0 *)firstNode);
 if(lastNode==0)lastNode=node;
 wordC=false;
}

Path *Pathfinder::FindAttackPath(Object *obj,const LocomotorSet &locos,const Coord3D *from,
 Object *victim,const Coord3D *victimPos,Rva002C9B80Owner *weapon,Bool skipQuick,Bool *partial)
{
    if (!m_isMapReady) return 0;
    if (partial) *partial=false;
    m_srcMineshaft=0; m_destMineshaft=0;
    Bool crusher=obj->rva00294815()>0;
    Int radius; Bool center;
    Rva002EBCA7Split(obj,&radius,(unsigned char *)&center);
    Int priority=obj->m_template->priority;
    Bool flag=obj->m_template->flag;
    Rva002E8BCF movement((const Rva002E8BCFSrc *)&locos,!flag,priority-1,obj->rva0028AFBB());
    Bool human=true;
    if(obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType==1) human=false;
    if(!skipQuick){
        PathfinderAttackCoord curPos(*(const Coord3D *)obj->position);
        PathfinderAttackCoord quickGoal(victim?*(const Coord3D *)victim->position:*victimPos);
        PathfinderAttackCoord delta;
        delta.set(quickGoal.x-curPos.x,quickGoal.y-curPos.y,0);
        delta.normalize();
        delta.x*=10.0f;
        delta.y*=10.0f;
        Int i;
        for(i=1;i<10;++i){
            PathfinderAttackCoord test(curPos);
            test.x+=delta.x*i*0.5f;test.y+=delta.y*i*0.5f;
            ICoord2D index;Rva002E7875WorldToCell(&index,true,&test);
            if(human && (index.x<m_extentLowX || index.y<m_extentLowY || index.x>m_extentHighX || index.y>m_extentHighY))break;
            PathfindCell *cell=getCell((PathfindLayerEnum)obj->rva0028B511(),index.x,index.y);
            if(!cell || !((Rva002E6DC4 *)this)->rva002E6DC4(&movement,cell))break;
            if(!bfmeWrapE6E90(obj,(void *)index.x,(void *)index.y,(void *)obj->rva0028B511(),(void *)radius,*(void **)&center))break;
            if(((Weapon*)weapon)->isWithinAttackRange(obj,&test,victim,victimPos,10.0f,true) &&
               !isAttackViewBlockedByObstacle(obj,test,victim,*victimPos)){
                Path *path=new Path;
                path->prependNode(&test,(PathfindLayerEnum)obj->rva0028B511(),0x7fffffff);
                path->prependNode(&curPos,(PathfindLayerEnum)obj->rva0028B511(),0x7fffffff);
                PathfinderAttackNode *first=((PathfinderAttackPathView *)path)->first;
                first->optimized=first->next;
                if(((AttackLimitView*)TheWritableGlobalData)->debugAI==1)SetDebugPath((Rva002EDEABArg *)path);
                return path;
            }
        }
    }
    PathfinderAttackCoord goal(*victimPos);
    if(victim){
        if(victim->m_template->hasKind(150))victim->rva0028C2DD(&goal);
        if(!weapon->m_04->get()){
            PathfinderAttackCoord delta(*(Coord3D*)obj->position);delta.sub(*(Coord3D*)victim->position);delta.z=0;
            delta.Normalize();
            delta.scale(victim->getAttackGeometry().getRadial()+10.0f);goal.add(delta);
        }
    }
    reinterpret_cast<_STL::vector<Gen_p12pod> &>(m_1C1CC).clear();
    m_zoneManager.rva005312BE();
    PathfinderAttackHandle hierarchical(FindClosestHierarchicalPath(human,locos,obj,from,&goal,crusher,&goal));
    if(!hierarchical.path)m_zoneManager.rva00531300();
    unsigned int count=0;
    Int attackDistance=(Int)((Weapon *)weapon)->getAttackDistance(obj,victim,victimPos)+30;
    PathfinderAttackCoord objectPos(*(const Coord3D *)obj->position);
    if(center){objectPos.x+=5.0f;objectPos.y+=5.0f;}
    ICoord2D startIndex;
    { ICoord2D scratch; startIndex=*Rva002E7875WorldToCell(&scratch,true,&objectPos); }
    PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(),&objectPos);
    if(!parent)return 0;
    if(!obj->getAI())return 0;
    const PathfindCell *start=parent;
    parent->allocateInfo((In002E6BA1 *)&startIndex);
    parent->StartPathfind(0);
    ICoord2D victimIndex;
    Rva002E7875WorldToCell(&victimIndex,true,victim?(const Coord3D *)victim->position:victimPos);
    PathfindCell *goalCell=getCell(PATHFIND_LAYER_GROUND,victimIndex.x,victimIndex.y);
    if(!goalCell)return 0;
    goalCell->allocateInfo((In002E6BA1 *)&victimIndex);
    AddToOpenList(parent);
    PathfindCell *acceptable=0,*closest=0;
    Int destinationDistance;
    Int acceptableDistance=9999999;
    Int closestOrder=0;
    Int dx=goalCell->getXIndex()-parent->getXIndex();
    Int dy=goalCell->getYIndex()-parent->getYIndex();
    float closestDistance=(float)(dx*dx+dy*dy)*0.9f;
    Bool checkLOS=false;
    if(!victim)checkLOS=true;
    if(victim && !victim->isSignificantlyAboveTerrain())checkLOS=true;
    PathfinderSearchCellsVisited=0;
    while((parent=rva002F36E5())!=0){
        PathfinderCellPoint cellCenter=Rva002E8C23Call(center,parent);
        if(hierarchical.path){
            Int order=((HierarchicalPath *)hierarchical.path)->lookUpPositionOnPath((const Coord3D *)parent->m_pathInfo);
            Int dx=goalCell->getXIndex()-parent->getXIndex(),dy=goalCell->getYIndex()-parent->getYIndex();
            float distance=(float)(dx*dx+dy*dy);
            if(order>closestOrder || (order==closestOrder && distance<closestDistance)){
                closest=parent;closestOrder=order;closestDistance=distance;
            }
        }
        Int cellState=parent->m_pathInfo?(Int)parent->m_pathInfo->parentWaypoint:0;
        if(!cellState && ((Weapon*)weapon)->isWithinAttackRange(obj,&cellCenter,victim,victimPos,0.0f,true)){
            if(CheckDestination(obj,parent->getXIndex(),parent->getYIndex(),(PathfindLayerEnum)parent->getLayer(),radius,center,&destinationDistance,false)){
                Bool blocked=checkLOS?isAttackViewBlockedByObstacle(obj,cellCenter,victim,*victimPos):false;
                if(start==parent)blocked=true;
                else {
                    PathfinderCellPoint pos=Rva002E8C23Call(center,parent);
                    float dx=pos.x-objectPos.x,dy=pos.y-objectPos.y;
                    if(dx*dx+dy*dy<25.0f)blocked=true;
                }
                if(!blocked && destinationDistance>1){
                    blocked=true;
                    if(destinationDistance<acceptableDistance){acceptable=parent;acceptableDistance=destinationDistance;partial=0;}
                }
                if(!blocked){
                    parent->PutOnClosedList(&m_closedList);
                    Path *path=BuildActualPath(obj,locos.getValidSurfaces(),(const Coord3D *)obj->position,parent,center,false,true);
                    if(goalCell->m_pathInfo && !static_cast<unsigned char>(((Rva002E6B06 *)goalCell)->rva002E6B06()) && !static_cast<unsigned char>(((const Rva002E6AF3 *)goalCell)->get()))goalCell->ReleaseInfo();
                    rva002F40E7();return path;
                }
            }
        }
        parent->PutOnClosedList(&m_closedList);
        if(count<((AttackLimitView*)TheWritableGlobalData)->attackLimit){
            if(!skipQuick)CheckChangeLayers(parent,obj);
            count+=rva002F83F5(parent,goalCell,locos,human,center,radius,&startIndex,obj,attackDistance);
        }
    }
    if(acceptable){
        Path *path=BuildActualPath(obj,locos.getValidSurfaces(),(const Coord3D *)obj->position,acceptable,center,false,true);
        rva002F40E7();return path;
    }
    if(closest){
        if(partial)*partial=true;
        Path *path=BuildActualPath(obj,locos.getValidSurfaces(),(const Coord3D *)obj->position,closest,center,false,true);
        rva002F40E7();return path;
    }
    rva002F40E7();m_isTunneling=false;goalCell->ReleaseInfo();return 0;
}


// Native 0x002F4115..0x002F436F (602 B, RET 16, EH): waypoint-zone
// reachability. WorldBuilder D5F260 supplies the unoptimised algorithm;
// the native calls, object/template/waypoint offsets and effective-zone query
// establish this target ABI. The address-derived spelling does not claim an
// original source name. STLport storage adapters retain the prior bank's
// existing folded provider spellings; no new pin or symbol alias is added.
// The queue uses the real deque destructor (including its iterator-by-value
// _Destroy), and each locomotor arm loads the surfaces value. With the current
// home unit both produce the native register allocation and unwind sequence.
// Full provenance and controls: reverse/attempt_support/waypoint-zone-2f4115-recovery-20261020.md.
#include <map>
#include <set>
#include <deque>
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@H@_STL@@U12@V?$allocator@U?$_Rb_tree_no:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _STLP_alloc_proxy<_Rb_tree_node<int> *,_Rb_tree_node<int>,allocator<_Rb_tree_node<int> > >::deallocate(_Rb_tree_node<int> *,unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@H@_STL@@@_STL@@QBEXPAU?$_Rb_tree_node@H@2@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<_Rb_tree_node<int> >::deallocate(_Rb_tree_node<int> *,unsigned int) const; }
// Keep less<int>::operator() inlined without emitting an optimised out-of-line
// copy that would shadow the retail-proven one other units supply.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(const int &__x, const int &__y) const { return __x < __y; } }
// stlport_deque_ptr_o1.cpp supplies the rowed map-reservation helper.
namespace _STL { template <> void deque<void *>::_M_reserve_map_at_back(size_t); }
// Suppress this TU's non-retail copy of ??$copy_backward@PAPAPAXPAPAPAX@_STL@@YAPAPAPAXPAPAPAX00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * * * copy_backward<void * * *,void * * *>(void * * *,void * * *,void * * *); }
// Folded element spellings of the rowed STLport members.
struct Rva002F307AElement {
	Rva002F307AElement(); Rva002F307AElement(const Rva002F307AElement &);
	Rva002F307AElement &operator=(const Rva002F307AElement &);
	char bytes[8];
};
bool operator<(const Rva002F307AElement &, const Rva002F307AElement &);
struct Rva002F0BB5Element { char bytes[1]; bool operator<(const Rva002F0BB5Element &) const; bool operator==(const Rva002F0BB5Element &) const; };
struct Rva002F0B8AElement { char bytes[1]; bool operator<(const Rva002F0B8AElement &) const; bool operator==(const Rva002F0B8AElement &) const; };
struct Rva002F1DA1Mapped { int a; };
struct Rva002F3759Compare { bool operator()(unsigned int a, unsigned int b) const { return a < b; } };
struct BfmeWordValue4
{
	unsigned int bits;
	BfmeWordValue4() {}
	~BfmeWordValue4() {}
};

template<class T> class Rva002F0C32Allocator : public _STL::allocator<T>
{
public:
 template<class U> struct rebind {typedef Rva002F0C32Allocator<U> other;};
 Rva002F0C32Allocator() throw() {}
 Rva002F0C32Allocator(const Rva002F0C32Allocator&) throw() {}
 template<class U> Rva002F0C32Allocator(const Rva002F0C32Allocator<U>&) throw() {}
};

typedef _STL::multiset<int, _STL::less<int>, Rva002F0C32Allocator<int> > FoldZoneTreeCtor;                         // 0x002F3039
typedef _STL::map<int, Rva002F0B8AElement> FoldZoneTreeDtorMap;       // 0x002F0B8A
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva002F0B8AElement >, _STL::_Select1st<_STL::pair<const int, Rva002F0B8AElement > >, _STL::less<int >, _STL::allocator<_STL::pair<const int, Rva002F0B8AElement > > > FoldZoneTreeDtor;
typedef _STL::multimap<int, Rva002F1DA1Mapped> FoldZoneInsertMap;     // 0x002F1DA1
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva002F1DA1Mapped >, _STL::_Select1st<_STL::pair<const int, Rva002F1DA1Mapped > >, _STL::less<int >, _STL::allocator<_STL::pair<const int, Rva002F1DA1Mapped > > > FoldZoneInsert;
// The pool-backed node factory is rowed in Rva002EF239CreateNode.cpp.
namespace _STL {
template <> FoldZoneInsert::_Link_type FoldZoneInsert::_M_create_node(const FoldZoneInsert::value_type &);
}
typedef _STL::multimap<int, int> FoldZoneRangeMap;                    // 0x002F1C89
typedef _STL::_Rb_tree<int, _STL::pair<const int, int >, _STL::_Select1st<_STL::pair<const int, int > >, _STL::less<int >, _STL::allocator<_STL::pair<const int, int > > > FoldZoneRange;
typedef _STL::set<Rva002F307AElement> FoldWayTreeCtor;                // 0x002F307A
// The rowed constructor owns its element cleanup dependencies.
namespace _STL { template <> FoldWayTreeCtor::set(); }
typedef _STL::map<int, Rva002F0BB5Element> FoldWayTreeDtorMap;        // 0x002F0BB5
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva002F0BB5Element >, _STL::_Select1st<_STL::pair<const int, Rva002F0BB5Element > >, _STL::less<int >, _STL::allocator<_STL::pair<const int, Rva002F0BB5Element > > > FoldWayTreeDtor;
// Both folded tree teardowns are rowed (StlSweepW4Rva002F0B8A.cpp / StlSweepW4Rva002F0BB5.cpp);
// the map wrappers below only call them.
namespace _STL {
template <> FoldZoneTreeDtor::~_Rb_tree();
template <> FoldWayTreeDtor::~_Rb_tree();
}
typedef _STL::map<unsigned int, unsigned int, Rva002F3759Compare> FoldWayIndex; // 0x002F3759
typedef _STL::map<unsigned int, void *> FoldWayFindMap;               // 0x00357180
typedef _STL::_Rb_tree<unsigned int, _STL::pair<const unsigned int, void * >, _STL::_Select1st<_STL::pair<const unsigned int, void * > >, _STL::less<unsigned int >, _STL::allocator<_STL::pair<const unsigned int, void * > > > FoldWayFind;
typedef _STL::map<unsigned char, short> FoldVisitedCtor;              // 0x000D3A71
// Its teardown is rowed elsewhere (retail ~_Rb_tree 0x38323E frees through the
// game allocator); this unit only references it from the ctor's unwind path.
namespace _STL {
template <> _Rb_tree<unsigned char, pair<const unsigned char, short>, _Select1st<pair<const unsigned char, short> >, less<unsigned char>, allocator<pair<const unsigned char, short> > >::~_Rb_tree();
template <> _Rb_tree_base<pair<const unsigned char, short>, allocator<pair<const unsigned char, short> > >::~_Rb_tree_base();
}
typedef _STL::set<int> FoldVisited;                                   // 0x000BC15D 0x00388F63
typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > FoldVisitedTree;
typedef _STL::_Deque_base<BfmeWordValue4, _STL::allocator<BfmeWordValue4> > FoldQueueCtor; // 0x00605464
// StlportNestedWordDeque.cpp supplies the retail map initializer and node allocator.
namespace _STL { template <> void FoldQueueCtor::_M_initialize_map(size_t); }
typedef _STL::deque<void *> FoldQueue;                                // 0x00423BD8 0x002EE9A0
typedef _STL::_Deque_base<void *, _STL::allocator<void *> > FoldQueueDtor; // 0x0054FAAC

class Rva00072FE6
{
public:
	~Rva00072FE6();
};

namespace _STL {
template <> FoldQueueDtor::~_Deque_base();
}

struct ZoneWaypointMap
{
	ZoneWaypointMap() { reinterpret_cast<FoldZoneTreeCtor *>(this)->FoldZoneTreeCtor::multiset(); }
	~ZoneWaypointMap() { reinterpret_cast<FoldZoneTreeDtor *>(this)->~FoldZoneTreeDtor(); }
	FoldZoneInsertMap &tree() { return *reinterpret_cast<FoldZoneInsertMap *>(this); }
	char m_storage[sizeof(FoldZoneInsertMap)];
};

struct WaypointZoneMap
{
	WaypointZoneMap() { reinterpret_cast<FoldWayTreeCtor *>(this)->FoldWayTreeCtor::set(); }
	~WaypointZoneMap() { reinterpret_cast<FoldWayTreeDtor *>(this)->~FoldWayTreeDtor(); }
	char m_storage[sizeof(FoldWayIndex)];
};

struct ZoneQueue
{
	ZoneQueue() { reinterpret_cast<FoldQueueCtor *>(this)->FoldQueueCtor::_Deque_base(_STL::allocator<BfmeWordValue4>(), 0); }
	~ZoneQueue() { reinterpret_cast<FoldQueue *>(this)->~FoldQueue(); }
	FoldQueue &q() { return *reinterpret_cast<FoldQueue *>(this); }
	char m_storage[sizeof(FoldQueue)];
};

struct VisitedZones
{
	VisitedZones() { reinterpret_cast<FoldVisitedCtor *>(this)->FoldVisitedCtor::map(); }
	~VisitedZones() { reinterpret_cast<Rva00072FE6 *>(this)->~Rva00072FE6(); }
	FoldVisited &s() { return *reinterpret_cast<FoldVisited *>(this); }
	char m_storage[sizeof(FoldVisited)];
};


struct ZoneQuery { Int m_surfaces; Bool m_04,m_05; Int m_08; Bool m_0C; };
Bool Pathfinder::rva002F4115(Object *obj, Int startZone, Int goalZone, LocomotorSet *locoSet)
{
	if (reinterpret_cast<Rva0028B984ByteField *>(obj)->get())
		return false;
	AIUpdateInterface *ai = obj->getAI();
	if (ai == 0 && locoSet == 0)
		return false;
	Int surfaces = locoSet ? locoSet->getValidSurfaces() : ((const LocomotorSet *)((const char *)ai+0x1cc))->getValidSurfaces();
	Int crusherLevel = obj->m_template->priority;
	Bool b634 = obj->m_template->flag;
	Bool flagA = obj->rva0028AC62();
	Bool flagB = obj->rva0028AFBB();
	ZoneQuery query;
	query.m_04 = !b634;
	query.m_05 = flagB;
	query.m_surfaces = surfaces;
	query.m_08 = crusherLevel - 1;
	query.m_0C = flagA;

	ZoneWaypointMap zoneWaypoints;
	WaypointZoneMap waypointZones;
	for (Waypoint *wp = ((HierarchyTerrain *)TheTerrainLogic)->getFirstWaypoint(); wp; wp = wp->next) {
		if (!(unsigned char)reinterpret_cast<Rva002E6ECA *>(wp)->get())
			continue;
		if (!wp->isValidUnitType(obj))
			continue;
		PathfindCell *cell = (PathfindCell *)rva001E3647Pos(
			TheTerrainLogic->getLayerForDestination(0, &wp->location), &wp->location);
		if (!cell)
			continue;
		Int zone = ((Rva002E99F9Sub460 *)&m_zoneManager)->rva0053241F(&query, cell->quickZone());
		Rva002F1DA1Mapped mapped;
		mapped.a = (int)wp;
		zoneWaypoints.tree().insert(FoldZoneInsertMap::value_type(zone, mapped));
		(*reinterpret_cast<FoldWayIndex *>(&waypointZones))[reinterpret_cast<const unsigned int &>(wp)] = zone;
	}

	ZoneQueue queue;
	VisitedZones visited;
	queue.q().push_back((void *const &)startZone);
	visited.s().insert(startZone);
	while (!queue.q().empty()) {
		Int zone = (Int)queue.q().front();
		queue.q().pop_front();
		if (zone == goalZone)
			return true;
		_STL::pair<FoldZoneRangeMap::iterator, FoldZoneRangeMap::iterator> range =
			reinterpret_cast<FoldZoneRangeMap *>(&zoneWaypoints)->equal_range(zone);
		// Walk the range as the map's own iterator (pair<const int, Rva002F1DA1Mapped>):
		// stepping it as the <int,int> spelling would emit this /O1 unit's copy of
		// that iterator's operator++, rowed as an /O2 body in stlport_map_int_int.cpp.
		FoldZoneInsertMap::iterator last = reinterpret_cast<FoldZoneInsertMap::iterator &>(range.second);
		for (FoldZoneInsertMap::iterator it = reinterpret_cast<FoldZoneInsertMap::iterator &>(range.first); it != last; ) {
			Waypoint *wp = (Waypoint *)(*it).second.a;
			++it;
			for (Int i = 0; i < wp->linkCount; ++i) {
				Waypoint *link = wp->getLink(i);
				unsigned int key = (unsigned int)link;
				FoldWayFindMap::iterator found = reinterpret_cast<FoldWayFindMap *>(&waypointZones)->find(key);
				if (found != reinterpret_cast<FoldWayFindMap *>(&waypointZones)->end()) {
					zone = (Int)(*found).second;
					if (visited.s().find(zone) == visited.s().end()) {
						visited.s().insert(zone);
						queue.q().push_back((void *const &)zone);
					}
				}
			}
		}
	}
	return false;
}

// FindPath's retreat step uses the native component subtraction and scale.
static __forceinline void subCoord3D(Coord3D *dst, const Coord3D *a)
{
	dst->x -= a->x;
	dst->y -= a->y;
	dst->z -= a->z;
}
static __forceinline void scaleCoord3D(Coord3D *dst, float scale)
{
	dst->x *= scale;
	dst->y *= scale;
	dst->z *= scale;
}

struct PathfinderSearchHandle {
	HierarchicalPath *path;
	__forceinline PathfinderSearchHandle(HierarchicalPath *p) : path(p) {}
	__forceinline ~PathfinderSearchHandle() { ((Rva002EAD62 *)this)->rva002EAD62(); }
};

// WB 0x00D48230 names FindPath and its five arguments. Native 0x002FD344,
// 781B RET20, confirms the logging, quick-path backoff, hierarchy and direct
// search sequence. Both name members have the canonical four-byte string
// representation: template +0x64 and locomotor set +0x18. Keeping those real
// string objects, rather than char-pointer views, also recovers the native
// y/x/z latch reload order. Their getters do not construct or copy strings.
Path *Pathfinder::FindPath(Object *obj, const LocomotorSet &locos, const Coord3D *from,
	const Coord3D *rawTo, Bool *destinationAdjusted)
{
	if (g_00E03745) {
		if (theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile, "CritterDesync:    Pathfinder::FindPath() called");
		if (theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile,"    obj=%s, locomotorSet=%s, from=%g,%g,%g, to=%g,%g,%g",obj->getTemplate()->name(),locos.name(),from->x,from->y,from->z,rawTo->x,rawTo->y,rawTo->z);
	}
	*destinationAdjusted = false;
	Bool human = true;
	if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1) {
		if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile, "CritterDesync:    isHuman set to FALSE");
		human = false;
	}
	Coord3D adjusted; copyCoord3D(&adjusted, rawTo);
	if (!QuickDoesPathExist(obj, from, &adjusted, 0)) {
		*destinationAdjusted = true;
		Coord3D delta; copyCoord3D(&delta, &adjusted);
		subCoord3D(&delta, from);
		delta.z = 0;
		Int steps = (Int)(delta.length() / 30.0f) - 1;
		if (steps > 5) steps = 5;
		delta.Normalize();
		scaleCoord3D(&delta, 30.0f);
		for (Int i = 0; i < steps; i++) {
			subCoord3D(&adjusted, &delta);
			if (QuickDoesPathExist(obj, from, &adjusted, 0)) break;
		}
	}
	{
		_STL::vector<Gen_p12pod> *hops = reinterpret_cast<_STL::vector<Gen_p12pod> *>(&m_1C1CC);
		hops->erase(hops->begin(), hops->end());
	} m_zoneManager.rva005312BE();
	m_srcMineshaft = 0; m_destMineshaft = 0;
	{
	Coord3D destination; copyCoord3D(&destination, &adjusted);
	PathfinderSearchHandle hierarchical((HierarchicalPath *)FindClosestHierarchicalPath(human, locos, obj, from, &adjusted, false, &destination));
	if (!hierarchical.path) {
		if (g_00E03745 && theLogicRandomLogFile) fprintf((FILE *)theLogicRandomLogFile, "CritterDesync:    FindHierarchicalPath fails");
		m_zoneManager.rva00531300();
	} else if (destination.x != adjusted.x || destination.y != adjusted.y) *destinationAdjusted = true;
	return InternalFindPath(obj, locos, from, &destination, hierarchical.path, destinationAdjusted);
	}
}
