// cl: /O1 /DNDEBUG /MD

// ?FillFourSlots@Rva0011216CSlotQuartet@@QAEXXZ, retail 0x0011216C, 43 bytes.
// Four-slot level filler: marks the quartet ready, then fills each slot's
// per-level surfaces in the retail order (+0x38, +0x34, +0x40, +0x3C, the
// last via tail-jump). The holder's true class is unknown, so it carries an
// address-derived name; each 4-byte slot is a CursorTextureSlot (the level
// filler row proves the call shape).

class W3DRadarResetSurface
{
	void *m_surface;
};

struct CursorTextureSlot
{
	void *Ptr;

	W3DRadarResetSurface Get_Surface_Level(int level);
	void FillLevelSurfaces(void);
};

struct Rva00112153Elem
{
	char m_00;
};

void __cdecl operator delete[](void *p);

struct Rva0011216CSlotQuartet
{
	char m_pad00[0x34];
	CursorTextureSlot m_slot34;
	CursorTextureSlot m_slot38;
	CursorTextureSlot m_slot3C;
	CursorTextureSlot m_slot40;
	char m_pad44[0x84 - 0x44];
	bool m_ready84;
	char m_pad85[0xD0 - 0x85];
	Rva00112153Elem *m_ptrD0; // +0xD0 array cleaned by 0x00112153 via delete[]

	void FillFourSlots(void);
	void rva00112153(void); // @0x00112153 25B abutting FillFourSlots
};

// ?FillFourSlots@Rva0011216CSlotQuartet@@QAEXXZ
void Rva0011216CSlotQuartet::FillFourSlots(void)
{
	m_ready84 = true;
	m_slot38.FillLevelSurfaces();
	m_slot34.FillLevelSurfaces();
	m_slot40.FillLevelSurfaces();
	m_slot3C.FillLevelSurfaces();
}

// ?rva00112153@Rva0011216CSlotQuartet@@QAEXXZ @0x00112153 25B: array cleanup
// abutting FillFourSlots (0x112153+25=0x11216C). Retail: if (m_ptrD0)
// delete[] m_ptrD0 via rowed ??_V@YAXPAX@Z 0x0002FD80; clear m_ptrD0.
void Rva0011216CSlotQuartet::rva00112153(void)
{
	if (m_ptrD0) {
		::operator delete[](m_ptrD0);
		m_ptrD0 = 0;
	}
}
