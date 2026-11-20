// cl: /MD
//
// ?cellCallback@Rva002F1BD5Info@@QAEHPAVPathfindCell@@0HH@Z, retail 0x002F1BD5, 80 bytes.
// Cell-line walk callback (previous cell, current cell, x, y) of the walker
// 0x002F203F in PathfinderCellLineWalks.cpp, which calls it by this pinned name.
// Evidence: caller 0x002F203F; callee findObjectByID rowed 0x00049DC5 via global
// TheGameLogic 0x009FE78C; arg tag at +0xC low nibble 4 with payload ptr at +0
// and ObjectID at +0x28; Object +4 -> flag byte at +0x110 bit 2 and +0x74 vs this+4.
#include "../GameLogicObjectLookupView.h"


class PathfindCell;




extern class GameLogic *TheGameLogic;

struct Rva002F1BD5Data
{
	char m_pad[0x28];
	int m_objectID;
};

struct Rva002F1BD5Arg
{
	Rva002F1BD5Data *m_00;
	char m_04[8];
	int m_flags;
};

struct Rva002F1BD5Mid
{
	unsigned char m_pad[0x110];
	unsigned char m_110;
};

class Object
{
public:
	char m_00[4];
	Rva002F1BD5Mid *m_04;
	char m_08[0x6C];
	int m_74;
};

class Rva002F1BD5Info
{
	Object *m_00;
	int m_04;

public:
	int cellCallback(PathfindCell *previous, PathfindCell *current, int cellX, int cellY);
};

int Rva002F1BD5Info::cellCallback(PathfindCell *previous, PathfindCell *current, int cellX, int cellY)
{
	Rva002F1BD5Arg *cell = (Rva002F1BD5Arg *)current;
	if ((cell->m_flags & 15) != 4)
		return 0;
	Rva002F1BD5Data *cellData = cell->m_00;
	int id = cellData ? cellData->m_objectID : 0;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj == 0)
		return 0;
	if ((obj->m_04->m_110 & 4) == 0)
		return 0;
	if (obj->m_74 != m_04) {
		m_00 = obj;
		return 1;
	}
	return 0;
}
