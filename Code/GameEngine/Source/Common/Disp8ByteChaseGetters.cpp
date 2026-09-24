// Disp8 byte-chase getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / mov al,[eax+<DISP2>] / ret
//
// A pointer is read at a fixed displacement from `this`, then a byte is read
// at a second displacement from that pointer and returned in `al` (only the
// low byte is defined; the caller uses `al`). MSVC 7.1 emits the disp8 loads
// `8B 41 XX` + `8A 40 XX`, plus `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP8_BYTECHASE_GETTER(NAME, DISP1, DISP2) \
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

// Backward variant: the holder sits at a NEGATIVE displacement from `this`
// (a sub-object `this` pointing into a larger object). Spelled as an explicit
// backward cast, which MSVC folds to `mov eax,[ecx-BACK]`; same shape and
// reading as BFME1's ChainedFieldGetters.
#define BFME_DISP8_BYTECHASE_BEFORE_GETTER(NAME, BACK, INNER) \
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

BFME_DISP8_BYTECHASE_GETTER(Rva0007E05FByteChaseField, 0x0C, 0x2C)
BFME_DISP8_BYTECHASE_GETTER(Rva0033F988ByteChaseField, 0x04, 0x24)
BFME_DISP8_BYTECHASE_GETTER(Rva00373CA3ByteChaseField, 0x04, 0x30)
BFME_DISP8_BYTECHASE_GETTER(Rva004551ACByteChaseField, 0x04, 0x74)
BFME_DISP8_BYTECHASE_GETTER(Rva0048E836ByteChaseField, 0x04, 0x6D)
BFME_DISP8_BYTECHASE_GETTER(Rva0048E83DByteChaseField, 0x04, 0x6E)
BFME_DISP8_BYTECHASE_GETTER(Rva0048E844ByteChaseField, 0x04, 0x6F)
BFME_DISP8_BYTECHASE_GETTER(Rva004D7C5EByteChaseField, 0x08, 0x66)
BFME_DISP8_BYTECHASE_GETTER(Rva004E0605ByteChaseField, 0x28, 0x08)
BFME_DISP8_BYTECHASE_GETTER(Rva0057C22FByteChaseField, 0x04, 0x18)
BFME_DISP8_BYTECHASE_GETTER(Rva005C7917ByteChaseField, 0x04, 0x54)
BFME_DISP8_BYTECHASE_GETTER(Rva005C791EByteChaseField, 0x04, 0x55)
BFME_DISP8_BYTECHASE_GETTER(Rva005CCB3EByteChaseField, 0x08, 0x21)
BFME_DISP8_BYTECHASE_GETTER(Rva005CCB45ByteChaseField, 0x08, 0x22)
BFME_DISP8_BYTECHASE_GETTER(Rva005D48F0ByteChaseField, 0x14, 0x24)
BFME_DISP8_BYTECHASE_GETTER(Rva005D48F7ByteChaseField, 0x14, 0x25)
BFME_DISP8_BYTECHASE_GETTER(Rva005E0D71ByteChaseField, 0x08, 0x41)
BFME_DISP8_BYTECHASE_GETTER(Rva005E0D78ByteChaseField, 0x08, 0x42)
BFME_DISP8_BYTECHASE_GETTER(Rva005E0D86ByteChaseField, 0x08, 0x43)
BFME_DISP8_BYTECHASE_GETTER(Rva005F05F6ByteChaseField, 0x04, 0x4C)
BFME_DISP8_BYTECHASE_GETTER(Rva005F05FDByteChaseField, 0x04, 0x4D)
BFME_DISP8_BYTECHASE_GETTER(Rva005F3F3AByteChaseField, 0x08, 0x14)
BFME_DISP8_BYTECHASE_GETTER(Rva005F3F64ByteChaseField, 0x08, 0x15)
BFME_DISP8_BYTECHASE_GETTER(Rva005F601BByteChaseField, 0x08, 0x34)
BFME_DISP8_BYTECHASE_GETTER(Rva005F6022ByteChaseField, 0x08, 0x35)
BFME_DISP8_BYTECHASE_GETTER(Rva005F6037ByteChaseField, 0x08, 0x36)
BFME_DISP8_BYTECHASE_GETTER(Rva005F6045ByteChaseField, 0x08, 0x37)
BFME_DISP8_BYTECHASE_GETTER(Rva005F6B20ByteChaseField, 0x04, 0x64)
BFME_DISP8_BYTECHASE_GETTER(Rva005F6B27ByteChaseField, 0x04, 0x65)
BFME_DISP8_BYTECHASE_GETTER(Rva005F6B2EByteChaseField, 0x04, 0x66)
BFME_DISP8_BYTECHASE_GETTER(Rva005F6B35ByteChaseField, 0x04, 0x67)
BFME_DISP8_BYTECHASE_GETTER(Rva005FD4F0ByteChaseField, 0x04, 0x4E)
BFME_DISP8_BYTECHASE_GETTER(Rva005FF1EAByteChaseField, 0x04, 0x3C)
BFME_DISP8_BYTECHASE_GETTER(Rva005FF1F1ByteChaseField, 0x04, 0x3D)
BFME_DISP8_BYTECHASE_BEFORE_GETTER(Rva004932D5ByteChaseField, 0x0C, 0x0D)
BFME_DISP8_BYTECHASE_BEFORE_GETTER(Rva00495DCDByteChaseField, 0x1C, 0x21)
BFME_DISP8_BYTECHASE_BEFORE_GETTER(Rva004A0107ByteChaseField, 0x1C, 0x31)
BFME_DISP8_BYTECHASE_BEFORE_GETTER(Rva004A1949ByteChaseField, 0x1C, 0x55)
