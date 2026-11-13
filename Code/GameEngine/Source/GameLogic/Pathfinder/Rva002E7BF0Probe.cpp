// cl: /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?rva002E7BF0@Rva002EC3CEProbes@@QAE_NHH_NHHHPAX0@Z, retail 0x002E7BF0..
// 0x002E7C99 (169 bytes, RET 32): the pathfinder cell probe the rowed
// 0x002EC3CE calls twice (the spelling it pinned). The cell at (x, y) on the
// layer (rowed Pathfinder::getCell) must exist, sit on that layer (flags
// bits 4..9) and not be of type 4 or 5 (bits 0..3); a cell flagged at bit 18
// is refused to a locomotor whose +0x05 byte is set. The cell's zone (+0x08)
// is mapped for the locomotor through the +0x460 zone manager (rowed
// 0x0053241F, and 0x00531FD4 when the last flag asks for it) and must equal
// the wanted zone; then the cell's centre (pathfinder.cpp's rowed 0x002E79A8, returned
// by value) is copied out and the probe succeeds.
//
// WorldBuilder's unoptimized twin (0x00D59AA0) gives the statement shape
// retail needs: one early return per check, the bit-18 flag converted to
// bool before the locomotor test, and the success path nested under the
// zone comparison with a single trailing return false. With them cl pushes
// EDI only after the early checks, as retail does.

#include "Coord3D.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

#include "../../../Include/GameLogic/PathfindCell.h"

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/Rva002E99F9Sub460.h"

// pathfinder.cpp's cell-centre helper 0x002E79A8: it returns the centre by
// value through the caller's temporary (whose address comes back in EAX).
#include "../../../Include/Common/PathfinderCellPoint.h"
PathfinderCellPoint rva002E79A8(bool centerInCell, int cellX, int cellY, PathfindLayerEnum layer);

struct Rva002E7BF0Locomotor
{
	unsigned char m_pad00[0x05];
	bool m_05;								// +0x05
};

class Rva002EC3CEProbes
{
public:
	bool rva002E7BF0(int locomotor, int zone, bool flag, int cellX, int cellY, int layer, void *out, bool remap);
private:
	unsigned char m_pad000[0x460];
	Rva002E99F9Sub460 m_zones460;			// +0x460
};

bool Rva002EC3CEProbes::rva002E7BF0(int locomotor, int zone, bool flag, int cellX, int cellY, int layer, void *out, bool remap)
{
	PathfindCell *cell = reinterpret_cast<Pathfinder *>(this)->getCell((PathfindLayerEnum)layer, cellX, cellY);
	if (!cell)
		return false;
	if (cell->getLayer() != layer)
		return false;
	if (cell->getType() == PathfindCell::CELL_OBSTACLE)
		return false;
	if (cell->getType() == PathfindCell::CELL_BRIDGE_IMPASSABLE)
		return false;
	if ((bool)((cell->m_0C >> 18) & 1) && ((Rva002E7BF0Locomotor *)locomotor)->m_05)
		return false;
	int mappedZone = m_zones460.rva0053241F((void *)locomotor, cell->getZone());
	if (remap)
		mappedZone = m_zones460.rva00531FD4((void *)locomotor, mappedZone);
	if (zone == mappedZone) {
		*(Coord3D *)out = rva002E79A8(flag, cellX, cellY, (PathfindLayerEnum)layer);
		return true;
	}
	return false;
}
