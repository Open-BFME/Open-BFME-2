// cl: /O1
// Disp8 div-avg dword getters: thirteen-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / sub eax,[ecx+<DISP2>] / push <DIV> / cdq
//     pop ecx / idiv ecx / ret
//
// The difference of two dwords at fixed displacements from `this` is divided
// by a small constant. MSVC 7.1 under /O1 materializes the divisor through
// the stack (`push imm` + `pop ecx`, three bytes) instead of `mov ecx,imm`
// (five bytes); `cdq` sign-extends for the signed `idiv`. Thirteen bytes
// total. Identity is not recovered: every name is derived from its address.
#define BFME_DISP8_DIV_AVG_DWORD_GETTER(NAME, DISP1, DISP2, DIVISOR) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		int m_first; \
	}; \
	int NAME::get() const \
	{ \
		return (m_first - *(int *)((char *)this + DISP2)) / DIVISOR; \
	}

BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0007E5E1DivAvgField, 0x18, 0x14, 12)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0014F3ABDivAvgField, 0x08, 0x04, 76)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0020E41FDivAvgField, 0x1C, 0x18, 28)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva002638F2DivAvgField, 0x40, 0x3C, 12)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0028628ADivAvgField, 0x30, 0x2C, 36)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0040A82DDivAvgField, 0x10, 0x0C, 40)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0040A85FDivAvgField, 0x1C, 0x18, 104)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva005C83C0DivAvgField, 0x0C, 0x08, 72)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva005EC17EDivAvgField, 0x08, 0x04, 24)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva005FDE74DivAvgField, 0x2C, 0x28, 12)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva005EC156DivAvgField, 0x04, 0x00, 24)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva000454E1DivAvgField, 0x04, 0x00, 0x5C)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0007E19ADivAvgField, 0x04, 0x00, 0x2C)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0007E358DivAvgField, 0x08, 0x00, 0x2C)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva000AD6E8DivAvgField, 0x04, 0x00, 0x24)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva000B4272DivAvgField, 0x08, 0x00, 0x3C)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0014DB51DivAvgField, 0x04, 0x00, 0x30)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva00151DBFDivAvgField, 0x08, 0x00, 0x24)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva00152FCEDivAvgField, 0x04, 0x00, 0x44)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva001DD101DivAvgField, 0x08, 0x00, 0x30)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva002B2F3DDivAvgField, 0x04, 0x00, 0x34)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva002CF006DivAvgField, 0x08, 0x00, 0x5C)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva002E07EEDivAvgField, 0x04, 0x00, 0x58)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva003F413ADivAvgField, 0x08, 0x00, 0x68)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0040A65BDivAvgField, 0x04, 0x00, 0x68)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0047A6B4DivAvgField, 0x08, 0x00, 0x18)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0051E3D9DivAvgField, 0x04, 0x00, 0x50)
BFME_DISP8_DIV_AVG_DWORD_GETTER(Rva0051E42BDivAvgField, 0x08, 0x00, 0x50)
