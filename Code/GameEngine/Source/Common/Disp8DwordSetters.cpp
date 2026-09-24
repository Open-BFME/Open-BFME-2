// Disp8 dword setters: eight-byte __thiscall members with one shape:
//
//     mov dword [ecx+<DISP>],<IMM32> / ret
//
// One dword at a fixed displacement from `this` is overwritten with zero
// (the only constant in this family) and nothing is read back. MSVC 7.1
// emits `C7 41 XX IMM32`, plus `ret`, for eight bytes total. Identity is
// not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless eight-byte shape).
#define BFME_DISP8_DWORD_SETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		void disable(); \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	void NAME::disable() \
	{ \
		m_value = IMM; \
	}
BFME_DISP8_DWORD_SETTER(Rva00118CB0DwordSetter, 0x8, 0x0)
BFME_DISP8_DWORD_SETTER(Rva00660050DwordSetter, 0x58, 0x0)
BFME_DISP8_DWORD_SETTER(Rva006F1350DwordSetter, 0x20, 0x0)
