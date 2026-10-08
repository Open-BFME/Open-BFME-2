// ?update@FireLogicSystem@@UAEXXZ
// partial score=0.85 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
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
#include <map>
#include <vector>
#include "Lib/Coord3D.h"

typedef int Int;

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

__forceinline long FloatToLong(float f)
{
	long i;
	__asm {
		fld [f]
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

#include "../../Common/GameLogicObjectLookupView.h"
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
class Rva00285BECBase
{
public:
	virtual ~Rva00285BECBase();
};
class Rva00285BECSnapshotBase
{
public:
	virtual ~Rva00285BECSnapshotBase();
};
class Rva00285BEC : public Rva00285BECBase, public Rva00285BECSnapshotBase
{
public:
	Rva00285BEC(int a, int b);
	virtual ~Rva00285BEC();
	int m_08;
	int m_0C;
	int m_10;
};

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
struct Rva00287B2AResult
{
	Rva00287B2AResult(Rva00286214Node *node, bool inserted) : m_node(node), m_inserted(inserted) {}
	Rva00286214Node *m_node;
	bool m_inserted;
};
class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);
	void erase(Rva002860CFIterator pos) { ((Rva002860CFHost *)this)->rva002860CF(pos); }
	Rva00286214();	// the map's default ctor 0x00242F01
	~Rva00286214();	// the tree teardown 0x0028681A
	Rva00287B2AResult rva00287B2A(const Rva00285672 *key);	// insert 0x00287B2A
	Rva00286214Node *m_header;
	unsigned int m_size;	// +0x04
	char m_pad08[4];
};


// Coord3D's sub and dot as WorldBuilder calls them out of line (WB 0x40b88e
// and 0x40b7d0); retail inlines both and the canonical header lacks them.
struct FireCoord3D : public Coord3D
{
	void sub(const Coord3D *o) { x -= o->x; y -= o->y; z -= o->z; }
	float dot(const Coord3D *o) const { return x * o->x + y * o->y + z * o->z; }
};
// The area's shape (PolygonTrigger +8): its bounds come back through
// 0x0030B6E3 and 0x00285B66 tests a cell centre against it.
struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};
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
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();
	virtual void draw();

private:
	char m_pad[8];
};
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

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
// 0x00BFB730, a use count at +4, the field table theFireLogicSystemBlockParse
// at +8). The first live system registers it through 0x0020DFFB and the last
// one out removes it through 0x0020DAE0; only these two bodies touch it.
class ModuleData;
void __cdecl Rva0020DFFBRegister(const ModuleData *);
void __cdecl Rva0020DAE0(void *);
struct FireLogicSystemParseRegistration
{
	void *m_vtable;
	unsigned int m_useCount;
};
extern FireLogicSystemParseRegistration theFireLogicSystemParseRegistration;

class FireLogicSystem : public SubsystemInterface, public Snapshot
{
public:
	FireLogicSystem();
	virtual ~FireLogicSystem();
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
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
	virtual void update();
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
	void (__cdecl *m_9C)(Int x, Int y);	// a cell's burn state changed
};

// ?rva00286373@FireLogicSystem@@QAEXHPBUCoord3D@@PBVThingTemplate@@@Z @0x00286373
void FireLogicSystem::rva00286373(Int id, const Coord3D *pos, const ThingTemplate *tmpl)
{
	float fx = (float)floor(pos->x * 0.1f + 0.5);
	Int x = FloatToLong(fx);
	float fy = (float)floor(pos->y * 0.1f + 0.5);
	Int y = FloatToLong(fy);
	if (x >= 0 && x < m_numRows && y >= 0 && y < m_numCols)
	{
		ObjectNode *node = (ObjectNode *)g_pool00286136.rva00285AC4();
		node->m_id = id;
		node->m_next = m_cells[x][y].m_objects;
		m_cells[x][y].m_objects = node;
		ChangeCellToObjectFlammability(x, y, tmpl);
	}
}

void Rva00286136Free(void *node);

void FireLogicSystem::rva0028641F(unsigned int id, const Coord3D *pos)
{
    float fx = (float)floor(pos->x * 0.1f + 0.5);
    Int x = FloatToLong(fx);
    float fy = (float)floor(pos->y * 0.1f + 0.5);
    Int y = FloatToLong(fy);
    if (x >= 0 && x < m_numRows && y >= 0 && y < m_numCols)
    {
        Cell *cell = &m_cells[x][y];
        ObjectNode **cursor = &cell->m_objects;
        while (*cursor)
        {
            if ((unsigned int)(*cursor)->m_id == id)
            {
                ObjectNode *next = (*cursor)->m_next;
                Rva00286136Free(*cursor);
                *cursor = next;
                if (cell->m_0C == 0 && cell->m_objects == 0)
                    ResetCellToOriginalFlammability(x, y);
                break;
            }
            cursor = &(*cursor)->m_next;
        }
    }
}

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
 virtual void slot12();
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

void FireLogicSystem::ResetCellToOriginalFlammability(Int x, Int y)
{
    Cell *cell = &m_cells[x][y];
    float fx = (x + 0.5) * 10.0;
    float fy = (y + 0.5) * 10.0;
    int type = TheTerrainLogic->materialAt(fx, fy);
    if (type != 0)
    {
        Material *material = &m_materials[type];
        if (material->fuel < cell->m_fuel) cell->m_fuel = (unsigned short)material->fuel;
        if (material->field18 < cell->m_field18) cell->m_field18 = material->field18;
        if (material->field00 > cell->m_flammability) cell->m_flammability = material->field00;
        if (material->field10 > cell->m_field10) cell->m_field10 = material->field10;
    }
    else
    {
        cell->m_fuel = 0;
        cell->m_flammability = 0;
        cell->m_field10 = 0;
        cell->m_field18 = 0;
    }
    cell->m_field31 = 0;
}

void FireLogicSystem::ChangeCellToObjectFlammability(Int x, Int y, const ThingTemplate *tmpl)
{
	const FlammabilityData *data = (const FlammabilityData *)((const char *)tmpl + 0x314);
	Cell *cell = &m_cells[x][y];
	cell->m_fuel = data->m_fuel;
	cell->m_flammability = data->m_flammability;
	cell->m_field18 = data->m_field18;
	cell->m_field10 = data->m_field10;
}

void FireLogicSystem::ChangeBurnRate(Int x0, Int x1, Int y, Int delta, bool onlyBurning)
{
	if (y < 0 || y >= m_numCols)
		return;
	if (x0 >= m_numRows || x1 < 0)
		return;
	if (x0 < 0)
		x0 = 0;
	if (x1 >= m_numRows)
		x1 = m_numRows - 1;
	while (x0 <= x1)
	{
		Cell *cell = &m_cells[x0][y];
		if (onlyBurning && cell->m_check < 1)
		{
			++x0;
			continue;
		}
		if (TheTerrainLogic->isUnderwater((x0 + 0.5) * 10.0, (y + 0.5) * 10.0))
		{
			cell->m_check = 0;
		}
		else if (delta > 0)
		{
			if (cell->m_check == 0)
				cell->m_field30 = 1;
			Int burn = cell->m_check + delta;
			if (burn > 0xffff)
				burn = 0xffff;
			cell->m_check = (unsigned short)burn;
		}
		else if (cell->m_check > 0)
		{
			if (cell->m_check <= -delta)
			{
				if (!cell->m_field30)
				{
					Rva00285BEC key(x0 * 10 + 5, y * 10 + 5);
					Rva002860CFIterator i = m_cellsOnFire.rva00286214((const Rva00285672 *)&key);
					if (i.m_node != m_cellsOnFire.m_header)
						m_cellsOnFire.erase(i);
				}
				cell->m_field30 = 0;
				cell->m_check = 0;
			}
			else
				cell->m_check = (unsigned short)(cell->m_check + delta);
		}
		++x0;
	}
}

void FireLogicSystem::ChangeBurnRate(const Coord3D *origin, const Coord3D *dir, float threshold, Int x0, Int x1, Int y, Int delta, bool onlyBurning)
{
	if (y < 0 || y >= m_numCols || x0 >= m_numRows || x1 < 0)
		return;
	if (x0 < 0)
		x0 = 0;
	if (x1 >= m_numRows)
		x1 = m_numRows - 1;
	FireCoord3D offset;
	offset.x = (x0 + 0.5) * 10.0;
	offset.y = (y + 0.5) * 10.0;
	offset.z = 0.0f;
	offset.sub(origin);
	for (; x0 <= x1; ++x0, offset.x += 10.0f)
	{
		Cell *cell = &m_cells[x0][y];
		if (onlyBurning && cell->m_check < 1)
			continue;
		if (offset.dot(dir) < threshold)
			continue;
		if (TheTerrainLogic->isUnderwater((x0 + 0.5) * 10.0, (y + 0.5) * 10.0))
		{
			cell->m_check = 0;
		}
		else if (delta > 0)
		{
			if (cell->m_check == 0)
				cell->m_field30 = 1;
			Int burn = cell->m_check + delta;
			if (burn > 0xffff)
				burn = 0xffff;
			cell->m_check = (unsigned short)burn;
		}
		else if (cell->m_check > 0)
		{
			if (cell->m_check <= -delta)
			{
				if (!cell->m_field30)
				{
					Rva00285BEC key(x0 * 10 + 5, y * 10 + 5);
					Rva002860CFIterator i = m_cellsOnFire.rva00286214((const Rva00285672 *)&key);
					if (i.m_node != m_cellsOnFire.m_header)
						m_cellsOnFire.erase(i);
				}
				cell->m_field30 = 0;
				cell->m_check = 0;
			}
			else
				cell->m_check = (unsigned short)(cell->m_check + delta);
		}
	}
}

void FireLogicSystem::ChangeBurnRateInArea(const Coord3D *pos, float radius, Int delta, bool onlyBurning)
{
	if (radius <= 0.0f)
		return;
	if (delta == 0)
		return;
	float fx = (float)floor(pos->x * 0.1f + 0.5);
	Int cx = FloatToLong(fx);
	float fy = (float)floor(pos->y * 0.1f + 0.5);
	Int cy = FloatToLong(fy);
	float fr = (float)ceil(radius * 0.1f);
	Int rad = FloatToLong(fr);
	Int y = rad;
	Int d = 0;
	Int err = 2 - 2 * rad;
	Int bot = cx;
	Int top = cx;
	while (true) {
		if (err + y > 0) {
			if (y == 0) {
				if (rad == 1) {
					d++;
					bot++;
					top--;
				}
			}
			ChangeBurnRate(top, bot, cy + y, delta, onlyBurning);
			if (y == 0)
				break;
			ChangeBurnRate(top, bot, cy - y, delta, onlyBurning);
			y--;
			err += 1 - 2 * y;
		}
		if (d <= err)
			continue;
		d++;
		bot++;
		top--;
		err += 2 * d + 1;
	}
}

void FireLogicSystem::ChangeBurnRateInArea(const Coord3D *pos, float radius, const Coord3D *dir, float threshold, Int delta, bool onlyBurning)
{
	if (radius <= 0.0f)
		return;
	if (delta == 0)
		return;
	float fx = (float)floor(pos->x * 0.1f + 0.5);
	Int cx = FloatToLong(fx);
	float fy = (float)floor(pos->y * 0.1f + 0.5);
	Int cy = FloatToLong(fy);
	float fr = (float)ceil(radius * 0.1f);
	Int rad = FloatToLong(fr);
	Int y = rad;
	Int d = 0;
	Int err = 2 - 2 * rad;
	Int bot = cx;
	Int top = cx;
	while (true) {
		if (err + y > 0) {
			if (y == 0) {
				if (rad == 1) {
					d++;
					bot++;
					top--;
				}
			}
			ChangeBurnRate(pos, dir, threshold, top, bot, cy + y, delta, onlyBurning);
			if (y == 0)
				break;
			ChangeBurnRate(pos, dir, threshold, top, bot, cy - y, delta, onlyBurning);
			y--;
			err += 1 - 2 * y;
		}
		if (d <= err)
			continue;
		d++;
		bot++;
		top--;
		err += 2 * d + 1;
	}
}

struct Rva0030B7C2Point { float x, y; };
bool rva0030B7C2(const Rva0030B7C2Point *point, Rva0030B719Shape *shape);
bool __cdecl rva00285B66(const void *point, const void *region)
{
	Rva0030B7C2Point f;
	f.x = (float)((const int *)point)[0];
	f.y = (float)((const int *)point)[1];
	return rva0030B7C2(&f, (Rva0030B719Shape *)region);
}

void FireLogicSystem::rva002872BA(const PolygonTrigger *area, Int delta, bool onlyBurning)
{
	if (delta == 0)
		return;
	Rva0030B719Shape *shape = (Rva0030B719Shape *)((char *)area + 8);
	Region2D bounds = shape->rva0030B6E3();
	float f = (float)floor(bounds.x_min * 0.1f + 0.5);
	Int x0 = FloatToLong(f);
	f = (float)floor(bounds.x_max * 0.1f + 0.5);
	Int x1 = FloatToLong(f);
	f = (float)floor(bounds.y_min * 0.1f + 0.5);
	Int y0 = FloatToLong(f);
	f = (float)floor(bounds.y_max * 0.1f + 0.5);
	Int y1 = FloatToLong(f);
	for (Int x = x0; x <= x1; ++x)
	{
		for (Int y = y0; y <= y1; ++y)
		{
			FireCellCentre centre;
			centre.x = x * 10 + 5;
			centre.y = y * 10 + 5;
			if (rva00285B66(&centre, shape))
				ChangeBurnRate(x, x, y, delta, onlyBurning);
		}
	}
}

// ?rva00286D4E@FireLogicSystem@@QAEPAXW4ObjectID@@HH_N@Z @0x00286D4E
// Adds (or removes) a watcher id on cell (x, y); the added node comes back,
// and a cell left with no watchers and no objects regains its terrain
// flammability unless the object still there is of kind bit 2.
void *FireLogicSystem::rva00286D4E(ObjectID id, Int x, Int y, bool add)
{
	if (x < 0 || y < 0 || x >= m_numRows || y >= m_numCols)
		return 0;
	Cell *cell = &m_cells[x][y];
	if (add)
	{
		for (WatcherNode *n = cell->m_0C; n; n = n->m_next)
			if (n->m_id == id)
				return 0;
		WatcherNode *node = (WatcherNode *)g_pool00286116.rva00285A3B();
		node->m_next = cell->m_0C;
		node->m_04 = 0;
		node->m_x = (short)x;
		node->m_y = (short)y;
		node->m_id = id;
		cell->m_0C = node;
		return node;
	}
	for (WatcherNode **cursor = &cell->m_0C; *cursor; cursor = &(*cursor)->m_next)
	{
		if ((*cursor)->m_id == id)
		{
			WatcherNode *next = (*cursor)->m_next;
			Rva00286116Free(*cursor);
			*cursor = next;
			if (cell->m_0C == 0 && cell->m_objects == 0)
			{
				Object *obj = TheGameLogic->findObjectByID(id);
				if (!obj || (*(*(const unsigned char **)((const char *)obj + 4) + 0x108) & 4))
					ResetCellToOriginalFlammability(x, y);
			}
			break;
		}
	}
	return 0;
}

// m_cellsOnFire's in-order walk (STLport's shared increment, 0x00024250) and
// the grid's burn query at a world point (0x00285860, rowed under its
// structural view in Rva002E6EFFCellQuery.cpp).
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

// ?rva00286772@FireLogicSystem@@QAE_NPBVPolygonTrigger@@H@Z @0x00286772
// True when a burning cell inside the area's bounds and shape burns at
// least minBurn.
bool FireLogicSystem::rva00286772(const PolygonTrigger *area, Int minBurn)
{
	Rva0030B719Shape *shape = (Rva0030B719Shape *)((char *)area + 8);
	Region2D bounds = shape->rva0030B6E3();
	for (Rva00286214Node *node = m_cellsOnFire.m_header->m_left; node != m_cellsOnFire.m_header;
		node = (Rva00286214Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)node))
	{
		float x = (float)node->m_key.x;
		if (bounds.x_min > x || x > bounds.x_max)
			continue;
		float y = (float)node->m_key.y;
		if (bounds.y_min > y || y > bounds.y_max)
			continue;
		Coord3D pos;
		pos.x = x;
		pos.y = y;
		pos.z = 0.0f;
		if ((Int)((Rva002E6EFFGrid *)this)->rva00285860((const Rva002E6EFFPosition *)&pos) >= minBurn
			&& rva00285B66(&node->m_key, shape))
			return true;
	}
	return false;
}

void operator delete[](void *p);

// m_cellsOnFire's clear (0x0028662D).
class Rva0028614C
{
public:
	void rva0028662D();
};

// ?rva00286CC4@FireLogicSystem@@QAEXXZ @0x00286CC4
// Frees every cell's watcher and object lists, the grid and the burning set.
void FireLogicSystem::rva00286CC4()
{
	if (m_storage)
	{
		Cell *cell = m_storage + m_numRows * m_numCols;
		while (cell != m_storage)
		{
			--cell;
			WatcherNode *w = cell->m_0C;
			while (w)
			{
				WatcherNode *next = w->m_next;
				Rva00286116Free(w);
				w = next;
			}
			ObjectNode *o = cell->m_objects;
			while (o)
			{
				ObjectNode *next = o->m_next;
				Rva00286136Free(o);
				o = next;
			}
		}
		delete[] m_cells;
		delete[] m_storage;
		m_cells = 0;
		m_storage = 0;
		m_numCols = 0;
		m_numRows = 0;
		m_80 = 0;
		((Rva0028614C *)&m_cellsOnFire)->rva0028662D();
	}
}

// ??0FireLogicSystem@@QAE@XZ @0x00286EC8
FireLogicSystem::FireLogicSystem()
	: m_cells(0), m_storage(0), m_numRows(0), m_numCols(0), m_80(0),
	  m_90(0x7FFFFFFF), m_94(1), m_98(0), m_9C(0)
{
	if (theFireLogicSystemParseRegistration.m_useCount == 0)
		Rva0020DFFBRegister((const ModuleData *)&theFireLogicSystemParseRegistration);
	++theFireLogicSystemParseRegistration.m_useCount;
}

// ??1FireLogicSystem@@UAE@XZ @0x00286F8F
FireLogicSystem::~FireLogicSystem()
{
	rva00286CC4();
	if (--theFireLogicSystemParseRegistration.m_useCount == 0)
		Rva0020DAE0(&theFireLogicSystemParseRegistration);
}

// The per-object fire damage (DamageInfo ctor 0x00263895; 0x7C bytes) and
// the Object calls update makes with it.
class DamageInfo
{
public:
	DamageInfo();
	char m_pad00[0x10];
	Int m_10;		// +0x10, damage type
	char m_pad14[0x1C - 0x14];
	Int m_1C;		// +0x1C, death type
	float m_amount;		// +0x20
	char m_pad24[0x7C - 0x24];
};
class Object
{
public:
	bool isSignificantlyAboveTerrain() const;	// 0x0030ADDC
	void attemptDamage(DamageInfo *info);		// 0x0029848E
};
// An object's burn share in a cell (0x0027F09F through TheTerrainLogic) and
// the per-key tick of a burning cell (0x002856CF).
class Rva0027F09F
{
public:
	void rva0027F09F(Int id, Int amount);
};
class Rva002856CFHost
{
public:
	void rva002856CF();
};
// The pending heat of one cell, applied after the spread pass (push_back
// 0x00287F76); the static list itself is the BfmePod8 vector whose clear
// is 0x003FA4DB.
struct BfmePod8 { int a[2]; };
static inline Rva00287B2AResult insertCell(Rva00286214 &set, const Rva00285BEC &key)
{
	return set.rva00287B2A((const Rva00285672 *)&key);
}
struct Rva00287F76Element
{
	void *m_cell;
	unsigned short m_value;
};

// ?update@FireLogicSystem@@UAEXXZ @0x00287FAD
// Burns a tenth of the grid's rows a frame, damages the objects watching a
// burning cell, regrows burnt fuel and spreads heat to neighbours.
void FireLogicSystem::update()
{
	if (!m_storage || m_numRows < 1 || m_numCols < 1)
		return;
	Int startRow = m_80 * m_numRows / 10;
	Int endRow = (m_80 + 1) * m_numRows / 10;
	Int row;
	for (row = startRow; row < endRow; ++row)
	{
		Int worldX = row * 10 + 5;
		Cell *cell = m_cells[row] + m_numCols;
		while (cell != m_cells[row])
		{
			--cell;
			if (cell->m_check == 0)
				continue;
			Int worldY = (cell - m_cells[row]) * 10 + 5;
			if (cell->m_check <= cell->m_flammability + m_98)
			{
				if (!cell->m_field30)
				{
					Rva00285BEC key(worldX, worldY);
					Rva002860CFIterator i = m_cellsOnFire.rva00286214((const Rva00285672 *)&key);
					if (i.m_node != m_cellsOnFire.m_header)
						m_cellsOnFire.erase(i);
				}
				cell->m_field30 = 0;
				cell->m_check = 0;
				if ((float)cell->m_fuel > 0.0f)
				{
					cell->m_type = 2;
					m_9C(worldX, worldY);
				}
			}
			else
			{
				if (cell->m_field30)
				{
					cell->m_field30 = 0;
					if (m_cellsOnFire.m_size >= (unsigned int)m_90)
					{
						cell->m_check = 0;
						continue;
					}
					Rva00287B2AResult added = insertCell(m_cellsOnFire, Rva00285BEC(worldX, worldY));
				}
				cell->m_check -= (unsigned short)(cell->m_flammability + m_98);
				Int consumed;
				if (cell->m_fuel <= cell->m_check)
				{
					consumed = cell->m_fuel;
					Rva00285BEC key(worldX, worldY);
					Rva002860CFIterator i = m_cellsOnFire.rva00286214((const Rva00285672 *)&key);
					if (i.m_node != m_cellsOnFire.m_header)
						m_cellsOnFire.erase(i);
					cell->m_check = 0;
					cell->m_field31 = 1;
					if ((float)cell->m_fuel > 0.0f)
					{
						cell->m_type = 2;
						m_9C(worldX, worldY);
					}
				}
				else
				{
					consumed = cell->m_check;
					cell->m_type = 1;
					m_9C(worldX, worldY);
				}
				cell->m_fuel -= (unsigned short)consumed;
				ObjectNode *node = cell->m_objects;
				while (node)
				{
					ObjectNode *next = node->m_next;
					if (TheTerrainLogic)
						((Rva0027F09F *)TheTerrainLogic)->rva0027F09F(node->m_id, consumed);
					node = next;
				}
			}
		}
	}

	_STL::map<Int, void *> damageMap;
	_STL::map<Int, Int> &damage = (_STL::map<Int, Int> &)damageMap;
	Rva00286214 *onFire = &m_cellsOnFire;
	for (Rva00286214Node *n = onFire->m_header->m_left; n != onFire->m_header;
		n = (Rva00286214Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
	{
		Cell *cell = &m_cells[n->m_key.x / 10][n->m_key.y / 10];
		if (cell->m_check)
			for (WatcherNode *w = cell->m_0C; w; w = w->m_next)
				damage[*(Int *)&w->m_id] += cell->m_check;
	}

	DamageInfo info;
	info.m_10 = 0x17;
	info.m_1C = 3;
	for (_STL::map<Int, Int>::iterator it = damage.begin(); it != damage.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)(*it).first);
		if (obj && !obj->isSignificantlyAboveTerrain())
		{
			info.m_amount = (float)(*it).second;
			obj->attemptDamage(&info);
		}
	}

	if (startRow > 0)
		--startRow;
	if (endRow + 1 < m_numRows)
		--endRow;
	static _STL::vector<BfmePod8> s_pending;
	s_pending.clear();
	_STL::vector<Rva00287F76Element> &pending = (_STL::vector<Rva00287F76Element> &)s_pending;
	for (row = startRow; row < endRow; ++row)
	{
		for (Int col = 0; col < m_numCols; ++col)
		{
			Cell *cell = &m_cells[row][col];
			if (cell->m_fuel == 0)
			{
				if (cell->m_field31)
				{
					Int index = TheTerrainLogic->materialAt((float)((row + 0.5) * 10.0), (float)((col + 0.5) * 10.0));
					if (index)
					{
						Material *material = &m_materials[index];
						if (cell->m_fuel < material->fuel)
						{
							cell->m_fuel += (unsigned short)m_94;
							if (cell->m_fuel >= material->fuel)
								cell->m_fuel = (unsigned short)material->fuel;
						}
						if (cell->m_fuel >= material->fuel)
							cell->m_field31 = 0;
					}
					else
						cell->m_field31 = 0;
				}
			}
			else
			{
				Int threshold = cell->m_field10;
				Int heat = 0;
				if (row > 0)
				{
					Int n = m_cells[row - 1][col].m_check;
					if (n > threshold)
						heat += n - threshold;
				}
				if (row + 1 < m_numRows)
				{
					Int n = m_cells[row + 1][col].m_check;
					if (n > threshold)
						heat += n - threshold;
				}
				if (col > 0)
				{
					Int n = cell[-1].m_check;
					if (n > threshold)
						heat += n - threshold;
				}
				if (col + 1 < m_numCols)
				{
					Int n = cell[1].m_check;
					if (n > threshold)
						heat += n - threshold;
				}
				if (heat > 0)
				{
					if (cell->m_check == 0)
					{
						if (m_cellsOnFire.m_size >= (unsigned int)m_90)
							continue;
						cell->m_field30 = 0;
						Rva00287B2AResult added = insertCell(m_cellsOnFire, Rva00285BEC(row * 10 + 5, col * 10 + 5));
					}
					unsigned int value = cell->m_check + heat;
					if (value > cell->m_field18)
						value = cell->m_field18;
					Rva00287F76Element e;
					e.m_cell = cell;
					e.m_value = (unsigned short)value;
					pending.push_back(e);
				}
			}
		}
	}
	for (Rva00287F76Element *p = pending.begin(); p != pending.end(); ++p)
		((Cell *)p->m_cell)->m_check = p->m_value;

	if (++m_80 >= 10)
	{
		m_80 = 0;
		Rva00286214Node *header = onFire->m_header;
		for (Rva00286214Node *n = header->m_left; n != header;
			n = (Rva00286214Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
			((Rva002856CFHost *)&n->m_pad0C[4])->rva002856CF();
	}
}
