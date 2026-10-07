// Disp8 sub dword getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / sub eax,<IMM8> / ret
//
// One dword is read at a fixed displacement from `this`, a small immediate
// is subtracted, and the result is returned. The immediate fits in a signed
// byte, so MSVC 7.1 emits the `83 E8 XX` form (three bytes) after the disp8
// load `8B 41 XX`, plus `ret`, for seven bytes total. This is the sub
// sibling of the masked Disp8MaskedDwordFieldGetters family (and-imm8);
// the opcode itself is why the two families are kept in separate
// translation units. Identity is not recovered: every name is derived from
// its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP8_SUB_DWORD_GETTER(NAME, DISP, IMM) \
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

BFME_DISP8_SUB_DWORD_GETTER(Rva0007E96ASubDwordField, 0x04, 0x2C)
BFME_DISP8_SUB_DWORD_GETTER(Rva000B6371SubDwordField, 0x04, 0x18)
BFME_DISP8_SUB_DWORD_GETTER(Rva00151DB8SubDwordField, 0x04, 0x24)
BFME_DISP8_SUB_DWORD_GETTER(Rva00217490SubDwordField, 0x04, 0x10)
BFME_DISP8_SUB_DWORD_GETTER(Rva00219823SubDwordField, 0x04, 0x20)
BFME_DISP8_SUB_DWORD_GETTER(Rva0033167BSubDwordField, 0x04, 0x0C)
BFME_DISP8_SUB_DWORD_GETTER(Rva003B8B3DSubDwordField, 0x04, 0x68)
BFME_DISP8_SUB_DWORD_GETTER(Rva0040CAC5SubDwordField, 0x04, 0x08)
BFME_DISP8_SUB_DWORD_GETTER(Rva0040CACCSubDwordField, 0x04, 0x04)
BFME_DISP8_SUB_DWORD_GETTER(Rva00414325SubDwordField, 0x04, 0x30)
BFME_DISP8_SUB_DWORD_GETTER(Rva0051E3F1SubDwordField, 0x04, 0x50)
BFME_DISP8_SUB_DWORD_GETTER(Rva00625BA0SubDwordField, 0x04, 0x08)
BFME_DISP8_SUB_DWORD_GETTER(Rva006BD4C0SubDwordField, 0x04, 0x24)
