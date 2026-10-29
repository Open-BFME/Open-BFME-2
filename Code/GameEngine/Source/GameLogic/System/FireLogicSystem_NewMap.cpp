// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include /ICode/GameEngine/Source/Common /Ireference/shims/moduledata/Common
// ?NewMap@FireLogicSystem@@QAEXXZ
//
// FireLogicSystem's registration of a placed object (0x00286373): the id is
// filed in the grid cell under its world position and the cell takes the
// template's flammability through ChangeCellToObjectFlammability
// (0x00285F43, WorldBuilder's Map/FireLogicSystem.cpp name). Removing an id
// (0x0028641F, name unknown) unlinks its node and, once the cell holds no
// objects, restores the terrain material's flammability through
// ResetCellToOriginalFlammability (0x00285778, WorldBuilder name; asserts at
// lines 1361..1367). The material table is four 24-byte entries at +0x10
// indexed by TheTerrainLogic's slot 0x60 material lookup. ChangeBurnRate
// (0x00286926, WorldBuilder name; assert line 947) adds a burn delta to one
// row span of cells, zeroing cells TheTerrainLogic reports underwater
// (isUnderwater, slot 0x4C); a cell burnt out that was not newly lit leaves
// the m_cellsOnFire set (+0x84) through its find (0x00286214) and erase
// (0x002860CF). Its Coord3D overload (0x00286AB4, WorldBuilder name) touches
// only the cells of the span whose offset from the origin projects onto the
// direction at or past the threshold. ChangeBurnRateInArea (0x002871A4
// and its directional overload 0x002873DF, WorldBuilder names; assert
// lines 775 and 827) walks a disc of cells row span by row span with the
// midpoint circle loop ChangeFuelInArea uses. 0x002872BA (WorldBuilder
// body unnamed) burns every cell of an area's bounds whose centre lies in
// the area's shape; the centre test 0x00285B66 is defined here, and only
// with its body in this unit does the compiler keep the centre's x store
// out of the inner loop as retail does. The constructor (0x00286EC8) and
// destructor (0x00286F8F) need /GX for their unwind states; between them
// sit the grid teardown 0x00286CC4 and the use-counted registration of the
// system's block parse at VA 0x00DBB750.
//
// Target facts: the fire grid is the 20-byte cell rows at +0x70 with the row
// and column counts at +0x78/+0x7C (as Rva00285DC5Paint.cpp reads them); a
// cell keeps a singly linked list of 8-byte id nodes at +0x10, allocated from
// the pool at VA 0x00DFECA8 (freed by Rva00286136Free). The position is
// scaled by the 0.1f and 0.5 literals, floored and rounded through x87 fistp
// as ChangeFuelInArea does. Both callers (the record xfer at 0x0028002F and
// 0x00283839) pass a ThingTemplate, and the other callers of 0x00285F43 pass
// Thing+0x04 under a template flag test.
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include "Lib/Coord3D.h"

typedef int Int;

#include <math.h>


__forceinline long FloatToLong(float floatValue)
{
	long i;
	__asm {
		fld [floatValue]
		fistp [i]
	}
	return i;
}

struct Rva00065964ObjectPool
{
	void *rva00285A3B();
	void *rva00285AC4();
};
extern Rva00065964ObjectPool g_pool00286136;
extern Rva00065964ObjectPool g_pool00286116;
void Rva00286116Free(void *node);

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class ThingTemplate;

// The flammability a template gives its cell (WB reads it at +0x314).
struct FlammabilityData
{
	unsigned short m_fuel;	// +0x314
	Int m_field18;		// +0x318, 12-bit cell field
	Int m_flammability;	// +0x31C, 10-bit cell field
	Int m_field10;		// +0x320, 8-bit cell field
};

// A burning cell's key in m_cellsOnFire: the cell's world-centre
// coordinates (constructed at 0x00285B91, destroyed at 0x00285BEC).
#include "../../Common/Rva00285BEC.h"

// m_cellsOnFire's tree find (0x00286214) and erase (0x002860CF).
class Rva00285672;
struct Rva00286214Node;
struct Rva002860CFIterator
{
	Rva00286214Node *m_node;
	Rva002860CFIterator(Rva00286214Node *node) : m_node(node) {}
	Rva002860CFIterator(const Rva002860CFIterator &that) : m_node(that.m_node) {}
};
class Rva002860CFHost
{
public:
	void rva002860CF(Rva002860CFIterator it);
};
class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);
	void erase(Rva002860CFIterator pos) { ((Rva002860CFHost *)this)->rva002860CF(pos); }
	Rva00286214();	// the map's default ctor 0x00242F01
	~Rva00286214();	// the tree teardown 0x0028681A
	Rva00286214Node *m_header;
	char m_pad04[8];
};


// Coord3D's sub and dot as WorldBuilder calls them out of line (WB 0x40b88e
// and 0x40b7d0); retail inlines both and the canonical header lacks them.
struct FireCoord3D : public Coord3D
{
	void sub(const Coord3D *o) { x -= o->x; y -= o->y; z -= o->z; }
	float dot(const Coord3D *other) const { return x * other->x + y * other->y + z * other->z; }
};
// The area's shape (PolygonTrigger +8): its bounds come back through
// 0x0030B6E3 and 0x00285B66 tests a cell centre against it.
#include "../../../../Libraries/Include/Lib/Region2D.h"
class Rva0030B719Shape
{
public:
	Region2D rva0030B6E3();
};
bool __cdecl rva00285B66(const void *point, const void *region);
struct FireCellCentre
{
	Int x;
	Int y;
};
class PolygonTrigger;

// The subsystem base (ctor 0x001B4E63, dtor 0x001B4E74) and Snapshot at
// +0x0C, the second base whose vtable 0x00BBB554 the destructor restores.
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "Snapshot.h"

// A material entry (0x18 bytes): the array constructor zeroes all six
// dwords (0x00286297) and the destructor releases the string at +4
// (0x0029D7C2, folded with CameraMarker's).
struct Rva00286297
{
	Rva00286297();
	~Rva00286297();
	Int unknown00, unknown04;
	Int fuel;
	unsigned int field18, field00, field10;
};

// The FireLogicSystem block-parse registration (VA 0x00DBB750: vtable
// 0x00BFB730 and a use count at +4). The first live system registers it
// through 0x0020DFFB and the last
// one out removes it through 0x0020DAE0; only these two bodies touch it.
class ModuleData;
void __cdecl Rva0020DFFBRegister(const ModuleData *);
void __cdecl Rva0020DAE0(void *);
#include "../Map/FireLogicSystemParseRegistration.h"


class FireLogicSystem : public SubsystemInterface, public Snapshot
{
public:
	FireLogicSystem();
	virtual ~FireLogicSystem();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	void ChangeBurnRate(Int x0, Int x1, Int y, Int delta, bool onlyBurning);
	void ChangeBurnRate(const Coord3D *origin, const Coord3D *dir, float threshold, Int x0, Int x1, Int y, Int delta, bool onlyBurning);
	void ChangeBurnRateInArea(const Coord3D *pos, float radius, Int delta, bool onlyBurning);
	void ChangeBurnRateInArea(const Coord3D *pos, float radius, const Coord3D *dir, float threshold, Int delta, bool onlyBurning);
	void rva002872BA(const PolygonTrigger *area, Int delta, bool onlyBurning);
	void ChangeCellToObjectFlammability(Int x, Int y, const ThingTemplate *tmpl);
    void rva0028641F(unsigned int id, const Coord3D *pos);
    void ResetCellToOriginalFlammability(Int x, Int y);
	void rva00286373(Int id, const Coord3D *pos, const ThingTemplate *tmpl);
	void *rva00286D4E(ObjectID id, Int x, Int y, bool add);
	bool rva00286772(const PolygonTrigger *area, Int minBurn);
	void rva00286CC4();
	void NewMap();
private:
	// A cell's watcher list (16-byte nodes from the 0xDFEC94 pool).
	struct WatcherNode
	{
		WatcherNode *m_next;
		Int m_04;
		ObjectID m_id;
		short m_x;
		short m_y;
	};
	struct ObjectNode
	{
		Int m_id;
		ObjectNode *m_next;
	};
	struct Cell
	{
		Int m_type;
		unsigned short m_fuel;
		unsigned short m_check;
		unsigned int m_flammability : 10;
        unsigned int m_field10 : 8;
        unsigned int m_field18 : 12;
        unsigned int m_field30 : 1;
        unsigned int m_field31 : 1;
		WatcherNode *m_0C;
		ObjectNode *m_objects; // +0x10
	};
	typedef Rva00286297 Material;
    Material m_materials[4];	// +0x10
	Cell **m_cells;
	Cell *m_storage;	// +0x74, the rows' shared cell block
	Int m_numRows;
	Int m_numCols;
	Int m_80;
	Rva00286214 m_cellsOnFire;
	Int m_90;
	Int m_94;
	Int m_98;
	Int m_9C;
};

void Rva00286136Free(void *node);

class TerrainLogic {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void getExtent(struct Rva00287015Extent *extent) const;	// slot 0x30
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual bool isUnderwater(float x, float y, float *waterZ = 0, float *terrainZ = 0, Int unused = 0);	// slot 0x4C
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual unsigned char materialAt(float x, float y);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva0030B7C2Point { float x, y; };
bool rva0030B7C2(const Rva0030B7C2Point *point, Rva0030B719Shape *shape);
// m_cellsOnFire's in-order walk (STLport's shared increment, 0x00024250) and
// the grid's burn query at a world point (0x00285860, rowed under its
// structural view in Rva002E6EFFCellQuery.cpp).
namespace _STL
{
	struct _Rb_tree_node_base;
	template <class _Dummy> struct _Rb_global
	{
		static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
	};
}
struct Rva00286214Node
{
	char m_pad00[8];
	Rva00286214Node *m_left;		// +0x08
	char m_pad0C[0x18 - 0x0C];
	FireCellCentre m_key;			// +0x18, the cell's centre
};
struct Rva002E6EFFPosition;
class Rva002E6EFFGrid
{
public:
	unsigned int rva00285860(const Rva002E6EFFPosition *position);
};

#include <new>

// m_cellsOnFire's clear (0x0028662D).
class Rva0028614C
{
public:
	void rva0028662D();
};

// The terrain extent TheTerrainLogic's slot 0x30 fills (lo, hi).
struct Rva00287015Extent
{
	Coord3D lo;
	Coord3D hi;
};

// ?NewMap@FireLogicSystem@@QAEXXZ @0x00287015
// Rebuilds the grid over the terrain extent (one cell per 10 units) and
// seeds each cell from the material TheTerrainLogic reports at its centre.
// WorldBuilder FireLogicSystem::NewMap, WB VA 0x00C382E0 (align lead, score 2).
void FireLogicSystem::NewMap()
{
	rva00286CC4();
	Rva00287015Extent extent;
	TheTerrainLogic->getExtent(&extent);
	m_numRows = FloatToLong((float)floor(extent.hi.x * 0.1f)) + 1;
	m_numCols = FloatToLong((float)floor(extent.hi.y * 0.1f)) + 1;
	m_storage = new Cell[m_numRows * m_numCols];
	m_cells = new Cell *[m_numRows];
	for (Int x = 0; x < m_numRows; ++x)
	{
		m_cells[x] = &m_storage[m_numCols * x];
		for (Int y = 0; y < m_numCols; ++y)
		{
			Cell *cell = &m_cells[x][y];
			cell->m_type = 0;
			cell->m_fuel = 0;
			cell->m_check = 0;
			((unsigned int *)cell)[2] = 0;
			cell->m_0C = 0;
			cell->m_objects = 0;
			int type = TheTerrainLogic->materialAt((x + 0.5) * 10.0, (y + 0.5) * 10.0);
			if (type != 0 && type < 4)
			{
				Material *material = &m_materials[type];
				cell->m_fuel = (unsigned short)material->fuel;
				cell->m_field18 = material->field18;
				cell->m_flammability = material->field00;
				cell->m_field10 = material->field10;
			}
		}
	}
}
