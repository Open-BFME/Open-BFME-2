// cl: /O2 /DNDEBUG /MD
//
// PartitionManager shroud thunks, retail 0x00739740 (8 bytes),
// 0x00739790 (8 bytes), 0x007397B0 (8 bytes) and 0x007397F0 (8 bytes).
// Dedicated TU: the caller (doBorderSwitch, and setActiveBoundary once it
// lands) lives elsewhere, so the bodies live here (a TU holding a row must
// not define that row's callees).
//
// Each body forwards to the shroud manager at +0x10, tail-jumping to the
// ShroudManager method (same semantics, adjusted this). The setRegion
// target resolves to the landed ShroudManager::setRegion row.

enum CellShroudStatus
{
	SHROUD_CLEAR = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Region3D;

class ShroudManager
{
public:
	void revealMapForPlayerPermanently(int playerIndex);
	void undoRevealMapForPlayerPermanently(int playerIndex);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
	void setRegion(const Region3D *region, float cellSize);
	// Opaque ShroudManager methods behind the 0x625300/10/20 run (targets
	// 0x6276E0/0x627E40/0x627810); identities unproven, signatures read
	// from the thunk call sites (region address / int / address).
	void Rva006276E0(const Region3D *region);
	void Rva00627E40(int value);
	void Rva00627810(void *ptr);
};

class ShroudManagerImpl008FBA40
{
public:
	void setEnabled_Rva0073B460(bool value);
};

class PartitionManager
{
public:
	void revealMapForPlayerPermanently(int playerIndex);
	void undoRevealMapForPlayerPermanently(int playerIndex);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
	void setRegion(const Region3D *region, float cellSize);
	// Opaque thunks of the 0x625300/10/20 run (PartitionManager facade
	// over the +0x10 shroud manager, same shape as the shroud thunks).
	// 0x625300 upgrades banked pin 1720 to a row.
	void rva00625300(const Region3D *region);
	void rva00625310(int value);
	void rva00625320(void *ptr);
	// Retail 0x007397A0 forwards to ShroudManagerImpl008FBA40::setEnabled_Rva0073B460
	// (single-byte enabled flag at +0x68). Identity unproven, honest address name.
	void rva007397A0(bool value);

private:
	char m_pad[0x10];
	ShroudManager *m_shroudManager; // +0x10
};

// ?revealMapForPlayerPermanently@PartitionManager@@QAEXH@Z
void PartitionManager::revealMapForPlayerPermanently(int playerIndex)
{
	m_shroudManager->revealMapForPlayerPermanently(playerIndex);
}

// ?undoRevealMapForPlayerPermanently@PartitionManager@@QAEXH@Z
void PartitionManager::undoRevealMapForPlayerPermanently(int playerIndex)
{
	m_shroudManager->undoRevealMapForPlayerPermanently(playerIndex);
}

// ?getShroudStatusForPlayer@PartitionManager@@QBE?AW4CellShroudStatus@@HPBUCoord3D@@@Z
CellShroudStatus PartitionManager::getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const
{
	return m_shroudManager->getShroudStatusForPlayer(playerIndex, pos);
}

// ?setRegion@PartitionManager@@QAEXPBURegion3D@@M@Z
void PartitionManager::setRegion(const Region3D *region, float cellSize)
{
	m_shroudManager->setRegion(region, cellSize);
}

// ?rva00625300@PartitionManager@@QAEXPBURegion3D@@@Z
void PartitionManager::rva00625300(const Region3D *region)
{
	m_shroudManager->Rva006276E0(region);
}

// ?rva00625310@PartitionManager@@QAEXH@Z
void PartitionManager::rva00625310(int value)
{
	m_shroudManager->Rva00627E40(value);
}

// ?rva00625320@PartitionManager@@QAEXPAX@Z
void PartitionManager::rva00625320(void *ptr)
{
	m_shroudManager->Rva00627810(ptr);
}

// ?rva007397A0@PartitionManager@@QAEX_N@Z
void PartitionManager::rva007397A0(bool value)
{
	reinterpret_cast<ShroudManagerImpl008FBA40 *>(m_shroudManager)->setEnabled_Rva0073B460(value);
}
