// cl: /MD
// Dump lane range 13: ?rva002E99F9 @0x002E99F9 211B. Two-position cell
// resolution (TerrainLogic layers, then Pathfinder cells) feeding the
// union-find subobject at +0x460 through the pinned 0x0053241F/0x00531FD4
// thunks. Param a2 is overwritten with a ushort result (dead after the
// ret 0xc pop); the function returns 0. Identities unproven.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;
class PathfindCell
{
public:
	char m_pad0[8];
	unsigned short m_8;
};
class Rva002E99F9Sub460
{
public:
	unsigned short rva0053241F(void *s, unsigned short w);
	unsigned short rva00531FD4(void *s, unsigned short w);
};
struct Rva002E99F9Arg1
{
	char m_pad0[0x10];
	int m_10;
	char m_pad14;
	unsigned char m_15;
};
struct Rva002E99F9Query
{
	int m_0;
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	int m_8;
	unsigned char m_C;
};
class Pathfinder
{
public:
	PathfindCell *rva002E8BF8(PathfindLayerEnum layer, const Coord3D *pos);
	int rva002E99F9(Rva002E99F9Arg1 *a1, const Coord3D * volatile a2, const Coord3D *a3);
private:
	char m_pad0[0x460];
	Rva002E99F9Sub460 m_sub460;
};
// ?rva002E99F9@Pathfinder@@QAEHPAURva002E99F9Arg1@@RBUCoord3D@@PBU3@@Z
// @0x002E99F9 211B. a2 is top-level volatile: retail observably writes the
// dead param slot (mov [ebp+0xc]) after the fifth sub-call, and the
// qualifier keeps that store. Flags /O1 /MD /G7: /G7 lowers the ushort
// cell-field loads as plain 16-bit mov (no movzx) like the rowed
// Rva00531A44 find in the same family.
int Pathfinder::rva002E99F9(Rva002E99F9Arg1 *a1, const Coord3D * volatile a2, const Coord3D *a3)
{
	PathfindLayerEnum layerA3 = TheTerrainLogic->getLayerForDestination(0, a3);
	PathfindLayerEnum layerA2 = TheTerrainLogic->getLayerForDestination(0, a2);
	PathfindCell *cellA2 = rva002E8BF8(layerA2, a2);
	PathfindCell *cellA3 = rva002E8BF8(layerA3, a3);
	Rva002E99F9Query q;
	q.m_8 |= -1;
	q.m_0 = a1->m_10;
	q.m_C = a1->m_15;
	q.m_4 = 0;
	q.m_5 = 0;
	unsigned short wB;
	unsigned short wA;
	wB = cellA2->m_8;
	unsigned int r1 = m_sub460.rva0053241F(&q, wB);
	wA = cellA3->m_8;
	unsigned int r2 = m_sub460.rva0053241F(&q, wA);
	unsigned int r3 = m_sub460.rva00531FD4(&q, r1);
	unsigned int r4 = m_sub460.rva00531FD4(&q, r2);
	unsigned int r5 = m_sub460.rva0053241F(&q, r3);
	a2 = (const Coord3D *)r5;
	m_sub460.rva0053241F(&q, r4);
	return 0;
}
