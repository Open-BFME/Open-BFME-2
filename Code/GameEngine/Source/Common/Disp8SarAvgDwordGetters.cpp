// Disp8 sar-avg dword getters: eight-to-ten-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / sub eax,[ecx+<DISP2>] / sar eax,<IMM8> / ret
//
// The difference of two dwords at fixed displacements from `this` is
// arithmetically shifted right. MSVC 7.1 emits the disp8 loads `8B 41 XX`
// plus `2B 41 XX`, plus `C1 F8 XX` (or `D1 F8` for shift-by-1), plus `ret`.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless shape).
#define BFME_DISP8_SAR_AVG_DWORD_GETTER(NAME, DISP1, DISP2, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		int m_first; \
	}; \
	int NAME::get() const \
	{ \
		return (m_first - *(int *)((char *)this + DISP2)) >> IMM; \
	}

BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0004582DSarAvgField, 0x18, 0x14, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0007E1A6SarAvgField, 0x04, 0x00, 1)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0007E6DASarAvgField, 0x0C, 0x08, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0007EB32SarAvgField, 0x18, 0x14, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva000B3F52SarAvgField, 0x04, 0x00, 6)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva000B4269SarAvgField, 0x08, 0x00, 6)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva00210F8CSarAvgField, 0x44, 0x40, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva00219695SarAvgField, 0x34, 0x30, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0021969FSarAvgField, 0x40, 0x3C, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0023D6F0SarAvgField, 0x5C, 0x58, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0029B1D8SarAvgField, 0x04, 0x00, 5)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva002D34F4SarAvgField, 0x08, 0x04, 3)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva00329DB4SarAvgField, 0x08, 0x00, 7)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva003B0FC6SarAvgField, 0x10, 0x0C, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva0040A7CBSarAvgField, 0x14, 0x10, 2)
BFME_DISP8_SAR_AVG_DWORD_GETTER(Rva00421876SarAvgField, 0x08, 0x00, 5)
