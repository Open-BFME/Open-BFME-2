// Disp8 shl dword getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / shl eax,<IMM8> / ret
//
// One dword is read at a fixed displacement from `this`, shifted left, and
// the result is returned. MSVC 7.1 emits the disp8 load `8B 41 XX` plus
// `C1 E0 XX`, plus `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless eight-byte shape).
#define BFME_DISP8_SHL_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value << IMM; \
	}

BFME_DISP8_SHL_DWORD_GETTER(Rva00169650ShlDwordField, 0x10, 0x04)
