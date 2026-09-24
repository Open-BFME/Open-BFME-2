// Disp8 sub-imm32 dword getters: nine-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / sub eax,<IMM32> / ret
//
// One dword is read at a fixed displacement from `this`, a 32-bit immediate
// too large for the sign-byte form is subtracted, and the result is returned.
// MSVC 7.1 emits the disp8 load `8B 41 XX` plus `2D IMM32`, plus `ret`, for
// nine bytes total. This is the imm32 sibling of the Disp8SubDwordFieldGetters
// family; the opcode itself is why the two families are kept in separate
// translation units. Identity is not recovered: every name is derived from
// its address.
// No // cl: line (defaults match the frameless nine-byte shape).
#define BFME_DISP8_SUB_IMM32_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value - IMM; \
	}

BFME_DISP8_SUB_IMM32_DWORD_GETTER(Rva000519D6SubImm32Field, 0x04, 0x90)
BFME_DISP8_SUB_IMM32_DWORD_GETTER(Rva001EAEA6SubImm32Field, 0x04, 0xAC)
BFME_DISP8_SUB_IMM32_DWORD_GETTER(Rva0021981ASubImm32Field, 0x04, 0xD8)
BFME_DISP8_SUB_IMM32_DWORD_GETTER(Rva004D9645SubImm32Field, 0x04, 0x154)
BFME_DISP8_SUB_IMM32_DWORD_GETTER(Rva005429F4SubImm32Field, 0x04, 0x104)
