// Disp8 byte setters: ten-byte __thiscall members with one shape:
//
//     mov al,[esp+4] / mov [ecx+<DISP>],al / ret 4
//
// One byte is taken from the stack argument slot and stored at a fixed
// displacement from `this`. Same macro as DispByteFieldSetters.cpp; every
// displacement here fits disp8 (MSVC 7.1 uses disp8 whenever the offset
// fits, so every offset is below 0x80).
// Identity is not recovered: every name is derived from its address,
// following DispByteFieldSetters.cpp.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_DISP8_BYTE_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(unsigned char value); \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	void NAME::set(unsigned char value) \
	{ \
		m_value = value; \
	}

BFME_DISP8_BYTE_SETTER(Rva00318D14ByteSlot, 0x58)
