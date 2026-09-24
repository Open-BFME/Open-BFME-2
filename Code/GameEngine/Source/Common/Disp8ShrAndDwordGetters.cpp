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

BFME_DISP8_SHR_AND_DWORD_GETTER(Rva00091A29ShrAndField, 0x44)
BFME_DISP8_SHR_AND_DWORD_GETTER(Rva00179120ShrAndField, 0x30)
