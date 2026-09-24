// Disp8 add-imm32 dword getters: nine-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / add eax,<IMM32> / ret
//
// One dword is read at a fixed displacement from `this`, a 32-bit immediate
// too large for the sign-byte form is added, and the result is returned.
// MSVC 7.1 emits the disp8 load `8B 41 XX` plus `05 IMM32`, plus `ret`, for
// nine bytes total. This is the imm32 sibling of the Disp8AddDwordFieldGetters
// family; the opcode itself is why the two families are kept in separate
// translation units. Identity is not recovered: every name is derived from
// its address.
// No // cl: line (defaults match the frameless nine-byte shape).
// Backward variant: the field sits at a NEGATIVE displacement from `this`.
// Spelled as an explicit backward read, which MSVC folds to
// `mov eax,[ecx-BACK]`.
#define BFME_DISP8_ADD_IMM32_BEFORE_DWORD_GETTER(NAME, BACK, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(const int *)((const char *)this - (BACK)) + (IMM); \
	}
#define BFME_DISP8_ADD_IMM32_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value + IMM; \
	}

BFME_DISP8_ADD_IMM32_DWORD_GETTER(Rva002D371DAddImm32Field, 0x10, 0xF8)
BFME_DISP8_ADD_IMM32_DWORD_GETTER(Rva0044E642AddImm32Field, 0x04, 0xC0)
BFME_DISP8_ADD_IMM32_BEFORE_DWORD_GETTER(Rva00483D9BAddImm32Field, 0x4C, 0x190)
BFME_DISP8_ADD_IMM32_BEFORE_DWORD_GETTER(Rva004A39BEAddImm32Field, 0x1C, 0x1D4)
BFME_DISP8_ADD_IMM32_BEFORE_DWORD_GETTER(Rva004A39C7AddImm32Field, 0x1C, 0x1D8)
BFME_DISP8_ADD_IMM32_BEFORE_DWORD_GETTER(Rva004ABAAAAddImm32Field, 0x1C, 0x10C)
BFME_DISP8_ADD_IMM32_BEFORE_DWORD_GETTER(Rva004ABAB3AddImm32Field, 0x1C, 0x94)
BFME_DISP8_ADD_IMM32_DWORD_GETTER(Rva004DE9F9AddImm32Field, 0x04, 0xC8)
BFME_DISP8_ADD_IMM32_DWORD_GETTER(Rva00528C5CAddImm32Field, 0x04, 0x118)
BFME_DISP8_ADD_IMM32_DWORD_GETTER(Rva005B265DAddImm32Field, 0x04, 0x27C)
