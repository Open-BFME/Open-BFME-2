// Sign-extending byte-field getters: eight-byte __thiscall members with one
// shape:
//
//     movsx eax,byte ptr [ecx+<DISP>] / ret
//
// One byte is read at a fixed displacement from `this`, sign-extended into
// eax and returned as an int. Members before the accessed one are spelled
// as a lead array because their types are not witnessed here, only their
// total size. Identity is not recovered: every name is derived from its
// address. This is the disp32 sibling of the Disp8 movsx family (MSVC 7.1
// uses disp8 whenever the offset fits, so every offset here is large).
// No // cl: line (defaults match the frameless 8-byte shape).
#define BFME_MOVSX_BYTE_FIELD_GETTER(NAME, OFFSET) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[OFFSET]; \
		signed char m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

BFME_MOVSX_BYTE_FIELD_GETTER(Rva0028A87BMovsxByteField, 0x5F0)
BFME_MOVSX_BYTE_FIELD_GETTER(Rva0028A883MovsxByteField, 0x5F1)
