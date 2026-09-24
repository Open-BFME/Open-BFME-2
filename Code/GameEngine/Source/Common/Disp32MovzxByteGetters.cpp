// Disp32 movzx byte getters: eight-byte __thiscall members with one shape:
//
//     movzx eax,byte [ecx+<DISP>] / ret
//
// One byte is read at a fixed 32-bit displacement from `this`, zero-extended,
// and returned. The offset does not fit the sign-byte form, so MSVC 7.1 emits
// `0F B6 81 DISP32`, plus `ret`, for eight bytes total. Identity is not
// recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless eight-byte shape).
#define BFME_DISP32_MOVZX_BYTE_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned int get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	unsigned int NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP32_MOVZX_BYTE_GETTER(Rva00167EAAMovzxByteField, 0x104)
BFME_DISP32_MOVZX_BYTE_GETTER(Rva003889CAMovzxByteField, 0x4A8)
BFME_DISP32_MOVZX_BYTE_GETTER(Rva00507921MovzxByteField, 0x141)
