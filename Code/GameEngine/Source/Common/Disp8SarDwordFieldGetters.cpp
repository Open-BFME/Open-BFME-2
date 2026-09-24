// Disp8 sar dword getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / sar eax,<IMM8> / ret
//
// One dword is read at a fixed displacement from `this`, arithmetically
// shifted right, and the result is returned. MSVC 7.1 emits the disp8 load
// `8B 41 XX` plus `C1 F8 XX`, plus `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless eight-byte shape).
#define BFME_DISP8_SAR_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value >> IMM; \
	}

BFME_DISP8_SAR_DWORD_GETTER(Rva006DBB30SarDwordField, 0x04, 0x19)
