// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include
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
// direction at or past the threshold.
//
// Target facts: the fire grid is the 20-byte cell rows at +0x70 with the row
// and column counts at +0x78/+0x7C (as Rva00285DC5Paint.cpp reads them); a
// cell keeps a singly linked list of 8-byte id nodes at +0x10, allocated from
// the pool at VA 0x00DFECA8 (freed by Rva00286136Free). The position is
// scaled by the 0.1f and 0.5 literals, floored and rounded through x87 fistp
// as ChangeFuelInArea does. Both callers (the record xfer at 0x0028002F and
// 0x00283839) pass a ThingTemplate, and the other callers of 0x00285F43 pass
// Thing+0x04 under a template flag test.
#include "Lib/Coord3D.h"

typedef int Int;

extern "C" __declspec(dllimport) double __cdecl floor(double);

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
	void *rva00285AC4();
};
extern Rva00065964ObjectPool g_pool00286136;

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
private:
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
class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);
	void erase(Rva002860CFIterator pos) { ((Rva002860CFHost *)this)->rva002860CF(pos); }
	Rva00286214Node *m_header;
};


// Coord3D's sub and dot as WorldBuilder calls them out of line (WB 0x40b88e
// and 0x40b7d0); retail inlines both and the canonical header lacks them.
struct FireCoord3D : public Coord3D
{
	void sub(const Coord3D *o) { x -= o->x; y -= o->y; z -= o->z; }
	float dot(const Coord3D *o) const { return x * o->x + y * o->y + z * o->z; }
};
class FireLogicSystem
{
public:
	void ChangeBurnRate(Int x0, Int x1, Int y, Int delta, bool onlyBurning);
	void ChangeBurnRate(const Coord3D *origin, const Coord3D *dir, float threshold, Int x0, Int x1, Int y, Int delta, bool onlyBurning);
	void ChangeCellToObjectFlammability(Int x, Int y, const ThingTemplate *tmpl);
    void rva0028641F(unsigned int id, const Coord3D *pos);
    void ResetCellToOriginalFlammability(Int x, Int y);
	void rva00286373(Int id, const Coord3D *pos, const ThingTemplate *tmpl);
private:
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
		Int m_0C;
		ObjectNode *m_objects; // +0x10
	};
	struct Material { Int unknown00, unknown04; Int fuel; unsigned int field18, field00, field10; };
    char m_pad[0x10];
    Material m_materials[4];
	Cell **m_cells;
	Int m_pad74;
	Int m_numRows;
	Int m_numCols;
	char m_pad80[0x84 - 0x80];
	Rva00286214 m_cellsOnFire;
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
