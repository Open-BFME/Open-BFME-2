// cl: /MD /DNDEBUG
//
// ?getCell@PathfindLayer@@QAEPAVPathfindCell@@HH@Z
// retail 0x00366626, 69 bytes (Ghidra FUN_00766626).
//
// Donor: GeneralsMD AIPathfind.cpp PathfindLayer::getCell, unchanged in
// BFME 2. Target layout read from the body: cells (column pointers) +4,
// width +8, height +0xC, origin +0x10/+0x14; 16-byte cells whose type is the
// low nibble at +0xC, type 5 (CELL_BRIDGE_IMPASSABLE in the header).

typedef int Int;

#include "../../../Include/GameLogic/PathfindCell.h"
#include "../../../Include/GameLogic/PathfindLayer.h"

PathfindCell *PathfindLayer::getCell(Int x, Int y)
{
	if (m_layerCells == 0) {
		return 0;
	}
	x -= m_xOrigin;
	y -= m_yOrigin;
	if (x < 0 || x >= m_width) return 0;
	if (y < 0 || y >= m_height) return 0;
	PathfindCell *cell = &m_layerCells[x][y];
	if (cell->getType() == PathfindCell::CELL_BRIDGE_IMPASSABLE) {
		return 0; // Impassable cells are ignored.
	}
	return cell;
}
