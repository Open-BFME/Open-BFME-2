// cl: /MD /DNDEBUG
//
// ?getCell@PathfindLayer@@QAEPAVPathfindCell@@HH@Z
// retail 0x00366626, 69 bytes (Ghidra FUN_00766626).
//
// Donor: GeneralsMD AIPathfind.cpp PathfindLayer::getCell, unchanged in
// BFME 2. Target layout read from the body: cells (column pointers) +4,
// width +8, height +0xC, origin +0x10/+0x14; 16-byte cells whose type is the
// low nibble at +0xC, CELL_IMPASSABLE = 5.

typedef int Int;

class PathfindCell
{
public:
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_IMPASSABLE = 5
	};

	// Keep the native four-bit access inline without a competing getter copy.
	__declspec(dllimport) __forceinline CellType getType() const { return (CellType)m_type; }

private:
	char m_pad00[0x0C];
	unsigned char m_type : 4;
	unsigned char m_flags : 4;
	char m_pad0D[0x10 - 0x0D];
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);

private:
	void *m_unknown00;
	PathfindCell **m_layerCells;
	Int m_width;
	Int m_height;
	Int m_xOrigin;
	Int m_yOrigin;
};

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
	if (cell->getType() == PathfindCell::CELL_IMPASSABLE) {
		return 0; // Impassable cells are ignored.
	}
	return cell;
}
