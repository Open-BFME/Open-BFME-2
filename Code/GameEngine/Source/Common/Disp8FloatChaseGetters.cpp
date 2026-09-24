// Disp8 float-chase getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / fld dword [eax+<DISP2>] / ret
//
// A pointer is read at a fixed displacement from `this`, then a float is read
// at a second displacement from that pointer and returned in ST0. MSVC 7.1
// emits the disp8 loads `8B 41 XX` + `D9 40 XX`, plus `ret`, for seven bytes.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP8_FLOATCHASE_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	float NAME::get() const \
	{ \
		return *(float *)((char *)m_ptr + DISP2); \
	}

// Backward variant: the holder sits at a NEGATIVE displacement from `this`.
// Spelled as an explicit backward cast, which MSVC folds to
// `mov eax,[ecx-BACK]`; same reading as the dword/byte chase families.
#define BFME_DISP8_FLOATCHASE_BEFORE_GETTER(NAME, BACK, INNER) \
	class Inner##NAME \
	{ \
	public: \
		char m_lead[INNER]; \
		float m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		float get() const; \
	}; \
	float NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this - (BACK)))->m_holder->m_value; \
	}

BFME_DISP8_FLOATCHASE_GETTER(Rva0007E066FloatChaseField, 0x0C, 0x28)
BFME_DISP8_FLOATCHASE_GETTER(Rva0007E0F1FloatChaseField, 0x40, 0x5C)
BFME_DISP8_FLOATCHASE_GETTER(Rva000910C0FloatChaseField, 0x2C, 0x20)
BFME_DISP8_FLOATCHASE_GETTER(Rva001E3F27FloatChaseField, 0x04, 0x38)
BFME_DISP8_FLOATCHASE_GETTER(Rva002C7229FloatChaseField, 0x04, 0x2C)
BFME_DISP8_FLOATCHASE_GETTER(Rva0033F981FloatChaseField, 0x04, 0x20)
BFME_DISP8_FLOATCHASE_GETTER(Rva0033F9BBFloatChaseField, 0x04, 0x30)
BFME_DISP8_FLOATCHASE_GETTER(Rva003638ACFloatChaseField, 0x04, 0x40)
BFME_DISP8_FLOATCHASE_GETTER(Rva00373CAAFloatChaseField, 0x04, 0x34)
BFME_DISP8_FLOATCHASE_GETTER(Rva00373D45FloatChaseField, 0x04, 0x24)
BFME_DISP8_FLOATCHASE_GETTER(Rva0039ABEBFloatChaseField, 0x2C, 0x08)
BFME_DISP8_FLOATCHASE_GETTER(Rva0044E6A7FloatChaseField, 0x04, 0x4C)
BFME_DISP8_FLOATCHASE_GETTER(Rva0045523AFloatChaseField, 0x04, 0x08)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7C57FloatChaseField, 0x08, 0x44)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7C65FloatChaseField, 0x08, 0x08)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7C6CFloatChaseField, 0x08, 0x04)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7C73FloatChaseField, 0x08, 0x40)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7C7AFloatChaseField, 0x08, 0x48)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7C81FloatChaseField, 0x08, 0x0C)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7C88FloatChaseField, 0x08, 0x50)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7C8FFloatChaseField, 0x08, 0x54)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7CABFloatChaseField, 0x08, 0x68)
BFME_DISP8_FLOATCHASE_GETTER(Rva004D7CB2FloatChaseField, 0x08, 0x6C)
BFME_DISP8_FLOATCHASE_GETTER(Rva005D48FEFloatChaseField, 0x14, 0x18)
BFME_DISP8_FLOATCHASE_GETTER(Rva005D4905FloatChaseField, 0x14, 0x1C)
BFME_DISP8_FLOATCHASE_GETTER(Rva005D490CFloatChaseField, 0x14, 0x20)
BFME_DISP8_FLOATCHASE_GETTER(Rva005E0D8DFloatChaseField, 0x08, 0x3C)
BFME_DISP8_FLOATCHASE_BEFORE_GETTER(Rva004BDC41FloatChaseField, 0x0C, 0x18)
BFME_DISP8_FLOATCHASE_BEFORE_GETTER(Rva004BDC4FFloatChaseField, 0x0C, 0x3C)
