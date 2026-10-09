// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?getCellClaimant@TerrainResourceManager@@QAEHHHH@Z, retail 0x00359902..0x0035997F (125 bytes, ret 0xC).
// WorldBuilder twin 0x00E608E0 is TerrainResourceManager::getCellClaimant (TerrainResourceManager.cpp
// 414..453; its decompiled switch is this body, with the initialisation assert compiled out).
// Same owner layout as tryToClaimCell (TerrainResourceManagerRva0035AA43.cpp): width +0x34, height +0x38
// and the 16-byte cell array at +0x40, a cell being the claimant records (8 bytes: key, player) plus a state.
//
// The player claiming the cell at (x, y): state 2 (shared) looks the key up among the records (a key of -1
// finds none), state 3 (exclusive) answers the single record's player, resetting a state-3 cell that
// has lost it; any other state, or an out-of-range cell, answers 0.
struct TerrainClaimRecord
{
	int m_key;
	int m_player;
};

struct TerrainClaimCell
{
	TerrainClaimRecord *m_begin;
	TerrainClaimRecord *m_end;
	void *m_capacity;
	int m_state;			// +0x0C
};

class TerrainResourceManager
{
public:
	int getCellClaimant(int x, int y, int key);

private:
	void *m_vtable00;
	unsigned char m_opaque04[0x30];
	int m_width;			// +0x34
	int m_height;			// +0x38
	float m_value3C;
	TerrainClaimCell *m_cells;	// +0x40
};

int TerrainResourceManager::getCellClaimant(int x, int y, int key)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height && m_cells != 0) {
		TerrainClaimCell *cell = &m_cells[y * m_width + x];
		int state = cell->m_state;
		if (state >= 0 && state > 1) {
			if (state != 2) {
				if (state == 3) {
					if ((unsigned int)(cell->m_end - cell->m_begin) >= 1)
						return cell->m_begin->m_player;
					cell->m_state = 0;
				}
			} else {
				if (key != -1) {
					for (TerrainClaimRecord *record = cell->m_begin; record != cell->m_end; ++record) {
						if (record->m_key == key)
							return record->m_player;
					}
				}
			}
		}
	}
	return 0;
}
