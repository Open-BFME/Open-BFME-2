// Disp8 masked dword getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / and eax,<MASK> / ret
//
// One dword is read at a fixed displacement from `this`, masked with a small
// immediate, and returned. The mask fits in a signed byte, so MSVC 7.1 emits
// the `83 E0 XX` form (three bytes) after the disp8 load `8B 41 XX`, plus
// `ret`, for seven bytes total. This is the masked sibling of the plain
// Disp8DwordFieldGetters family (four bytes per body); the extra `and`
// is why the two families are kept in separate translation units. Identity
// is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP8_MASKED_DWORD_GETTER(NAME, DISP, MASK) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value & MASK; \
	}

BFME_DISP8_MASKED_DWORD_GETTER(Rva001E35B6MaskedDwordField, 0x0C, 0x0F)
BFME_DISP8_MASKED_DWORD_GETTER(Rva00030CB0MaskedDwordField, 0x04, 0x01)
BFME_DISP8_MASKED_DWORD_GETTER(Rva00203502MaskedDwordField, 0x18, 0x01)
BFME_DISP8_MASKED_DWORD_GETTER(Rva0045D397MaskedDwordField, 0x3C, 0x01)
BFME_DISP8_MASKED_DWORD_GETTER(Rva00030D00MaskedDwordField, 0x04, 0xFFFFFFFE)
BFME_DISP8_MASKED_DWORD_GETTER(Rva00742EC0MaskedDwordField, 0x40, 0x02)
BFME_DISP8_MASKED_DWORD_GETTER(Rva0043315CMaskedDwordField, 0xC4, 0x01)
