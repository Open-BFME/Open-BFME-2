// Disp8 byte-chase getters with wide inner displacement (twin-free TU).
//
// Same two shapes as Disp8ByteChaseGetters.cpp:
//
//     mov eax,[ecx+<DISP1>] / mov al,[eax+<DISP2>] / ret
//
// but the inner displacement does not fit the sign-byte form, so MSVC 7.1
// emits `8A 80 <DISP32>` instead of `8A 40 XX`, for ten bytes total. The
// macros are verbatim copies (the compiler picks disp8 vs disp32 from the
// INNER value); the opcode itself is why this family is kept in a separate
// translation unit. Identity is not recovered: every name is derived from
// its address.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_DISP8_WIDE_BYTECHASE_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return *(unsigned char *)((char *)m_ptr + DISP2); \
	}

#define BFME_DISP8_WIDE_BYTECHASE_BEFORE_GETTER(NAME, BACK, INNER) \
	class Inner##NAME \
	{ \
	public: \
		char m_lead[INNER]; \
		unsigned char m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this - (BACK)))->m_holder->m_value; \
	}

BFME_DISP8_WIDE_BYTECHASE_GETTER(Rva0028AA21ByteChaseField, 0x04, 0x118)
BFME_DISP8_WIDE_BYTECHASE_GETTER(Rva002C8F24ByteChaseField, 0x04, 0x16C)
BFME_DISP8_WIDE_BYTECHASE_GETTER(Rva0033F8C0ByteChaseField, 0x04, 0x100)
BFME_DISP8_WIDE_BYTECHASE_GETTER(Rva0045B12AByteChaseField, 0x04, 0x156)
BFME_DISP8_WIDE_BYTECHASE_BEFORE_GETTER(Rva00460AE2ByteChaseField, 0x0C, 0x116)
BFME_DISP8_WIDE_BYTECHASE_BEFORE_GETTER(Rva0047840CByteChaseField, 0x1C, 0xA1)
BFME_DISP8_WIDE_BYTECHASE_BEFORE_GETTER(Rva004827F9ByteChaseField, 0x1C, 0x115)
