// ?rva0028641F@FireLogicSystem@@QAEXIPBUCoord3D@@@Z
// partial score=0.99 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include
//
// FireLogicSystem's registration of a placed object (0x00286373): the id is
// filed in the grid cell under its world position and the cell takes the
// template's flammability through ChangeCellToObjectFlammability
// (0x00285F43, WorldBuilder's Map/FireLogicSystem.cpp name; pinned, its
// register allocation is banked in reverse/attempts/0x00285f43.cpp).
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

class FireLogicSystem
{
public:
	void ChangeCellToObjectFlammability(Int x, Int y, const ThingTemplate *tmpl);
    void rva0028641F(unsigned int id, const Coord3D *pos);
    void rva00285778(Int x, Int y);
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
		unsigned int m_flammability; // +0x08, 10/8/12-bit fields
		Int m_0C;
		ObjectNode *m_objects; // +0x10
	};
	char m_pad[0x70];
	Cell **m_cells;
	Int m_pad74;
	Int m_numRows;
	Int m_numCols;
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
                    rva00285778(x, y);
                break;
            }
            cursor = &(*cursor)->m_next;
        }
    }
}
