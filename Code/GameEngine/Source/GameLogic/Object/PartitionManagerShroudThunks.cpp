// cl: /DNDEBUG /MD
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

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Region3D;

class BfmeThingYQ;

class Gen009F5040
{
public:
	void bfmeDropYQ(BfmeThingYQ *t);
};

class BfmeP1050
{
public:
	void bfmeFwd1050(int a, int b, int c, int d, int e);
};

class ShroudManager
{
public:
	void revealMapForPlayerPermanently(int playerIndex);
	void undoRevealMapForPlayerPermanently(int playerIndex);
	void updatePlayerCells450_Rva0073D860(int playerIndex);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
	void setRegion(const Region3D *region, float cellSize);
	// Opaque ShroudManager methods behind the 0x625300/10/20 run (targets
	// 0x6276E0/0x627E40/0x627810); identities unproven, signatures read
	// from the thunk call sites (region address / int / address).
	void Rva006276E0(const Region3D *region);
	void Rva00627E40(int value);
	void Rva00627810(void *ptr);
};

class CDEProvider;

class ShroudManagerImpl
{
public:
	void setEnabled_Rva0073B460(bool value);
	void rva008F8C70(CDEProvider *first, CDEProvider *second);
	void RevealMapForPlayer(int value);
	void notify();
	int GetLookerCount(int playerIndex, const Coord3D *pos) const;
	ObjectShroudStatus GetPropShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
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
	void rva00625330(void *ptr);
	void rva00625340(int a, int b, int c);
	// Retail 0x007397A0 forwards to ShroudManagerImpl::setEnabled_Rva0073B460
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

void PartitionManager::rva00625330(void *ptr)
{
	((Gen009F5040 *)m_shroudManager)->bfmeDropYQ((BfmeThingYQ *)ptr);
}

void PartitionManager::rva00625340(int a, int b, int c)
{
	((BfmeP1050 *)m_shroudManager)->bfmeFwd1050(a, b, 0, c, 0);
}

// ?rva007397A0@PartitionManager@@QAEX_N@Z
void PartitionManager::rva007397A0(bool value)
{
	reinterpret_cast<ShroudManagerImpl *>(m_shroudManager)->setEnabled_Rva0073B460(value);
}

//
// ?rva00739830@Rva00739830@@QBEHPBUBfmePointFD@@HI@Z retail 0x00739830 8B.
// Cell-sum thunk via +0x10 pointer tail-jumping to rowed 0x0073BD70.
// Evidence: retail mov ecx [ecx+0x10] jmp; callers 0x004B0F6D 0x004B1438 0x004B1954 0x004D942B.
struct BfmePointFD;
class Gen_008F7CD0
{
public:
	int bfmeCellSum(const BfmePointFD *pt, int a, unsigned int b) const;
};
class Rva00739830
{
public:
	int rva00739830(const BfmePointFD *pt, int a, unsigned int b) const;
private:
	char m_pad[0x10];
	Gen_008F7CD0 *m_cell; // +0x10
};

int Rva00739830::rva00739830(const BfmePointFD *pt, int a, unsigned int b) const
{
	return m_cell->bfmeCellSum(pt, a, b);
}

//
// ?rva00739730@Rva00739730@@QAEXHH@Z retail 0x00739730 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0073B280.
// Evidence: retail mov ecx [ecx+0x10] jmp; callers 0x002A7B73 0x002A84D2 with two int pushes; next row 0x00739740 in same TU.
class Rva008F8C30
{
public:
	void set(int a, int b);
};
class Rva00739730
{
public:
	void rva00739730(int a, int b);
private:
	char m_pad[0x10];
	Rva008F8C30 *m_cell; // +0x10
};

void Rva00739730::rva00739730(int a, int b)
{
	m_cell->set(a, b);
}

//
// ?rva00739750@Rva00739750@@QAEXPAX@Z retail 0x00739750 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0073D440.
// Evidence: retail mov ecx [ecx+0x10] jmp; gap between 0x00739740 and 0x00739790 in same TU.
class BfmeOwnerCDE
{
public:
	void rva008fa850(void *ptr);
	void bfmeOneCDE(void *ptr);
};
class Rva00739750
{
public:
	void rva00739750(void *ptr);
private:
	char m_pad[0x10];
	BfmeOwnerCDE *m_cell; // +0x10
};

void Rva00739750::rva00739750(void *ptr)
{
	m_cell->rva008fa850(ptr);
}

//
// ?rva00739760@Rva00739760@@QAEXPAVCDEProvider@@0@Z retail 0x00739760 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0073B2C0.
// Evidence: retail mov ecx [ecx+0x10] jmp; gap between 0x00739750 and 0x00739790 in same TU.
class Rva00739760
{
public:
	void rva00739760(CDEProvider *first, CDEProvider *second);
private:
	char m_pad[0x10];
	ShroudManagerImpl *m_cell; // +0x10
};

void Rva00739760::rva00739760(CDEProvider *first, CDEProvider *second)
{
	m_cell->rva008F8C70(first, second);
}

//
// ?rva00739770@Rva00739770@@QAEXPAX@Z retail 0x00739770 8B.
// Thunk via +0x10 pointer tail-jumping to pinned 0x0073B350.
// Evidence: retail mov ecx [ecx+0x10] jmp; caller 0x00299E40 pushes one ptr; pin bfmeOneCDE same body as rowed bfmeReleaseABI.
class Rva00739770
{
public:
	void rva00739770(void *ptr);
private:
	char m_pad[0x10];
	BfmeOwnerCDE *m_cell; // +0x10
};

void Rva00739770::rva00739770(void *ptr)
{
	m_cell->bfmeOneCDE(ptr);
}

//
// ?rva00739780@Rva00739780@@QAEXH@Z retail 0x00739780 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0073B3B0.
// Evidence: retail mov ecx [ecx+0x10] jmp; gap between 0x00739770 and 0x00739790 in same TU.
class Rva00739780
{
public:
	void rva00739780(int value);
private:
	char m_pad[0x10];
	ShroudManagerImpl *m_cell; // +0x10
};

void Rva00739780::rva00739780(int value)
{
	m_cell->RevealMapForPlayer(value);
}

//
// ?rva007397D0@Rva007397D0@@QAEXXZ retail 0x007397D0 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0073B7E0.
// Evidence: retail mov ecx [ecx+0x10] jmp; gap between 0x007397B0 and 0x007397F0 in same TU.
class Rva007397D0
{
public:
	void rva007397D0();
private:
	char m_pad[0x10];
	ShroudManagerImpl *m_cell; // +0x10
};

void Rva007397D0::rva007397D0()
{
	m_cell->notify();
}

//
// ?rva007397E0@Rva007397E0@@QBEHHPBUCoord3D@@@Z retail 0x007397E0 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0073B890.
// Evidence: retail mov ecx [ecx+0x10] jmp; gap between 0x007397D0 and 0x007397F0 in same TU.
class Rva007397E0
{
public:
	int rva007397E0(int playerIndex, const Coord3D *pos) const;
private:
	char m_pad[0x10];
	ShroudManagerImpl *m_cell; // +0x10
};

int Rva007397E0::rva007397E0(int playerIndex, const Coord3D *pos) const
{
	return m_cell->GetLookerCount(playerIndex, pos);
}

//
// ?rva00739800@Rva00739800@@QBE?AW4ObjectShroudStatus@@HPBUCoord3D@@@Z retail 0x00739800 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0073B990.
// Evidence: retail mov ecx [ecx+0x10] jmp; gap between 0x007397F0 and 0x00739830 in same TU.
class Rva00739800
{
public:
	ObjectShroudStatus rva00739800(int playerIndex, const Coord3D *pos) const;
private:
	char m_pad[0x10];
	ShroudManagerImpl *m_cell; // +0x10
};

ObjectShroudStatus Rva00739800::rva00739800(int playerIndex, const Coord3D *pos) const
{
	return m_cell->GetPropShroudStatusForPlayer(playerIndex, pos);
}

//
// ?rva00739720@Rva00739720@@QAEXH@Z retail 0x00739720 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0066C940.
// Evidence: retail mov ecx [ecx+0x10] jmp; prev gap before 0x00739730 in same TU.
class NodeCompressedMotionStruct
{
public:
	void SetFlavor(int flavor);
};
class Rva00739720
{
public:
	void rva00739720(int flavor);
private:
	char m_pad[0x10];
	NodeCompressedMotionStruct *m_cell; // +0x10
};

void Rva00739720::rva00739720(int flavor)
{
	m_cell->SetFlavor(flavor);
}

//
// ?rva007397C0@Rva007397C0@@QAEXH@Z retail 0x007397C0 8B.
// Thunk via +0x10 pointer tail-jumping to rowed 0x0073D860.
// Evidence: retail mov ecx [ecx+0x10] jmp; chain from 0x0073D860 same TU family as 0x00739780.
class Rva007397C0
{
public:
	void rva007397C0(int playerIndex);
private:
	char m_pad[0x10];
	ShroudManager *m_cell; // +0x10
};

void Rva007397C0::rva007397C0(int playerIndex)
{
	m_cell->updatePlayerCells450_Rva0073D860(playerIndex);
}
