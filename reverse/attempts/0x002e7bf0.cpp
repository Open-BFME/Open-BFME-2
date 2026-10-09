// ?rva002E7BF0@Rva002EC3CEProbes@@QAE_NHH_NHHHPAX0@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?rva002E7BF0@Rva002EC3CEProbes@@QAE_NHH_NHHHPAX0@Z, retail 0x002E7BF0..
// 0x002E7C99 (169 bytes, RET 32): the pathfinder cell probe the rowed
// 0x002EC3CE calls twice (the spelling it pinned). The cell at (x, y) on the
// layer (rowed Pathfinder::getCell) must exist, sit on that layer (flags
// bits 4..9) and not be of type 4 or 5 (bits 0..3); a cell flagged at bit 18
// is refused to a locomotor whose +0x05 byte is set. The cell's zone (+0x08)
// is mapped for the locomotor through the +0x460 zone manager (rowed
// 0x0053241F, and 0x00531FD4 when the last flag asks for it) and must equal
// the wanted zone; then the cell's centre (pinned static 0x002E79A8, which
// returns its result's address) is copied out and the probe succeeds.

#include "Coord3D.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class PathfindCell
{
public:
	unsigned char m_pad00[0x08];
	unsigned short m_zone08;				// +0x08
	unsigned char m_pad0A[0x0C - 0x0A];
	unsigned int m_type : 4;				// +0x0C bits 0..3
	unsigned int m_layer : 6;				// bits 4..9
	unsigned int m_bits10 : 8;				// bits 10..17
	unsigned int m_flag18 : 1;				// bit 18
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
};

class Rva002E99F9Sub460
{
public:
	unsigned short rva0053241F(void *locomotor, unsigned short zone);
	unsigned short rva00531FD4(void *locomotor, unsigned short zone);
};

int rva002E79A8_ret(int result, unsigned char flag, int x, int y, int layer);

struct Rva002E7BF0Locomotor
{
	unsigned char m_pad00[0x05];
	bool m_05;								// +0x05
};

class Rva002EC3CEProbes
{
public:
	bool rva002E7BF0(int locomotor, int zone, bool flag, int x, int y, int layer, void *out, bool remap);
private:
	unsigned char m_pad000[0x460];
	Rva002E99F9Sub460 m_zones460;			// +0x460
};

bool Rva002EC3CEProbes::rva002E7BF0(int locomotor, int zone, bool flag, int x, int y, int layer, void *out, bool remap)
{
	PathfindCell *cell = reinterpret_cast<Pathfinder *>(this)->getCell((PathfindLayerEnum)layer, x, y);
	if (!cell || cell->m_layer != layer || cell->m_type == 4 || cell->m_type == 5)
		return false;
	if (cell->m_flag18 && ((Rva002E7BF0Locomotor *)locomotor)->m_05)
		return false;
	int z = m_zones460.rva0053241F((void *)locomotor, cell->m_zone08);
	if (remap)
		z = m_zones460.rva00531FD4((void *)locomotor, z);
	if (zone != z)
		return false;
	Coord3D centre;
	*(Coord3D *)out = *(Coord3D *)rva002E79A8_ret((int)&centre, flag, x, y, layer);
	return true;
}
