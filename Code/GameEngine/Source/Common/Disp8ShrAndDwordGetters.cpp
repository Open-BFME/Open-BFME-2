// Disp8 shr-and dword getters: nine-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / shr eax,1 / and eax,1 / ret
//
// A dword is read at a fixed displacement from `this`, shifted right by one,
// masked to the low bit, and returned. This is the bit-1 test idiom
// `(m_value >> 1) & 1`. MSVC 7.1 emits the disp8 load `8B 41 XX`, plus
// `D1 E8`, plus the `83 E0 01` and-mask, plus `ret`, for nine bytes total
// (twelve with a disp32 load, which the same macro auto-encodes).
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless shape).
#define BFME_DISP8_SHR_AND_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		unsigned int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (m_value >> 1) & 1; \
	}

// Shift-by-three variant: `C1 E8 03` instead of `D1 E8` (bit-3 test idiom).
#define BFME_DISP8_SHR3_AND_DWORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		unsigned int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (m_value >> 3) & 1; \
	}

// General shift-count variant: `C1 E8 <COUNT>` for any bit-N test idiom.
#define BFME_DISP8_SHRN_AND_DWORD_GETTER(NAME, DISP, COUNT) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		unsigned int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (m_value >> COUNT) & 1; \
	}

BFME_DISP8_SHR_AND_DWORD_GETTER(Rva00091A29ShrAndField, 0x44)
BFME_DISP8_SHR_AND_DWORD_GETTER(Rva00179120ShrAndField, 0x30)
BFME_DISP8_SHR_AND_DWORD_GETTER(Rva006DBB40ShrAndField, 0x04)
BFME_DISP8_SHR_AND_DWORD_GETTER(Rva00433166ShrAnd32Field, 0xC4)
BFME_DISP8_SHR3_AND_DWORD_GETTER(Rva00091A32Shr3AndField, 0x44)
BFME_DISP8_SHR3_AND_DWORD_GETTER(Rva00433172Shr3And32Field, 0xC4)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva002638DAShrNAndField, 0x44, 6)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva0027C1FEShrNAndField, 0x44, 2)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva002E6B46ShrNAndField, 0x0C, 17)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva002E6B50ShrNAndField, 0x0C, 22)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva002E6B5AShrNAndField, 0x0C, 18)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva002E6B64ShrNAndField, 0x0C, 21)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva002E6B78ShrNAndField, 0x0C, 23)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva0030D37BShrNAndField, 0x44, 5)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva0030D385ShrNAndField, 0x44, 4)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva001E448DShrNAnd32Field, 0x4B8, 7)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva0028C8B0ShrNAnd32Field, 0x94, 6)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva003685B4ShrNAnd32Field, 0x4B8, 8)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva0043317FShrNAnd32Field, 0xC4, 4)
BFME_DISP8_SHRN_AND_DWORD_GETTER(Rva0043318CShrNAnd32Field, 0xC4, 5)
