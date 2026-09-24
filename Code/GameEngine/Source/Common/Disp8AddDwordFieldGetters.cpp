// Disp8 add dword getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / add eax,<IMM8> / ret
//
// One dword is read at a fixed displacement from `this`, a small immediate
// is added, and the result is returned. The immediate fits in a signed
// byte, so MSVC 7.1 emits the `83 C0 XX` form (three bytes) after the disp8
// load `8B 41 XX`, plus `ret`, for seven bytes total. This is the add
// sibling of the sub Disp8SubDwordFieldGetters family; the opcode itself
// is why the two families are kept in separate translation units. Identity
// is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
// Backward variant: the field sits at a NEGATIVE displacement from `this`.
// Spelled as an explicit backward read, which MSVC folds to
// `mov eax,[ecx-BACK]`; same reading as the chase-family backward cast.
#define BFME_DISP8_ADD_BEFORE_DWORD_GETTER(NAME, BACK, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(const int *)((const char *)this - (BACK)) + (IMM); \
	}
#define BFME_DISP8_ADD_DWORD_GETTER(NAME, DISP, IMM) \
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

BFME_DISP8_ADD_DWORD_GETTER(Rva000B28C8AddDwordField, 0x30, 0x24)
BFME_DISP8_ADD_DWORD_GETTER(Rva002B236EAddDwordField, 0x40, 0x04)
BFME_DISP8_ADD_DWORD_GETTER(Rva0033F272AddDwordField, 0x18, 0x24)
BFME_DISP8_ADD_DWORD_GETTER(Rva0033F94DAddDwordField, 0x30, 0x3C)
BFME_DISP8_ADD_DWORD_GETTER(Rva0048E84BAddDwordField, 0x04, 0x70)
BFME_DISP8_ADD_DWORD_GETTER(Rva004989EEAddDwordField, 0x0C, 0x38)
BFME_DISP8_ADD_DWORD_GETTER(Rva00574AA5AddDwordField, 0x04, 0x5C)
BFME_DISP8_ADD_DWORD_GETTER(Rva00574AACAddDwordField, 0x04, 0x48)
BFME_DISP8_ADD_DWORD_GETTER(Rva0059E81FAddDwordField, 0x04, 0x08)
BFME_DISP8_ADD_DWORD_GETTER(Rva005CCB30AddDwordField, 0x08, 0x08)
BFME_DISP8_ADD_DWORD_GETTER(Rva005ED28AAddDwordField, 0x04, 0x28)
BFME_DISP8_ADD_DWORD_GETTER(Rva005F17A3AddDwordField, 0x04, 0x20)
BFME_DISP8_ADD_DWORD_GETTER(Rva005F17AAAddDwordField, 0x04, 0x24)
BFME_DISP8_ADD_DWORD_GETTER(Rva005FC75BAddDwordField, 0x18, 0x0C)
BFME_DISP8_ADD_DWORD_GETTER(Rva00709BD0AddDwordField, 0x30, 0x18)
BFME_DISP8_ADD_DWORD_GETTER(Rva00709D10AddDwordField, 0x30, 0x1C)
BFME_DISP8_ADD_BEFORE_DWORD_GETTER(Rva004A3904AddDwordField, 0x1C, 0x08)
BFME_DISP8_ADD_BEFORE_DWORD_GETTER(Rva004ABAC4AddDwordField, 0x20, 0x08)
BFME_DISP8_ADD_BEFORE_DWORD_GETTER(Rva00464829AddDwordField, 0x18, 0x38)
