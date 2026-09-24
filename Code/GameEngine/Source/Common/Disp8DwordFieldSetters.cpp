// Disp8 dword setters: ten-byte __thiscall members with one shape:
//
//     mov eax,[esp+4] / mov [ecx+<DISP>],eax / ret 4
//
// One dword is taken from the stack argument slot and stored at a fixed
// displacement from `this`. Same macro as DispDwordFieldSetters.cpp; every
// displacement here fits disp8 (MSVC 7.1 uses disp8 whenever the offset
// fits, so every offset is below 0x80).
// Identity is not recovered: every name is derived from its address,
// following DispDwordFieldSetters.cpp.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_DISP8_DWORD_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(int value); \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	void NAME::set(int value) \
	{ \
		m_value = value; \
	}

BFME_DISP8_DWORD_SETTER(Rva002D94FEDwordSlot, 0x74)
