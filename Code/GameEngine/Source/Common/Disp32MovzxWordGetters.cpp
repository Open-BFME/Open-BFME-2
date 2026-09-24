// Disp32 movzx word getters: eight-byte __thiscall members with one shape:
//
//     movzx eax,word [ecx+<DISP>] / ret
//
// One word is read at a fixed 32-bit displacement from `this`, zero-extended,
// and returned. The offset does not fit the sign-byte form, so MSVC 7.1 emits
// `0F B7 81 DISP32`, plus `ret`, for eight bytes total. Identity is not
// recovered: every name is derived from its address. This is the disp32-word
// sibling of the disp8 Disp8MovzxFieldGetters word family and the disp32-byte
// Disp32MovzxByteGetters family.
// No // cl: line (defaults match the frameless eight-byte shape).
#define BFME_DISP32_MOVZX_WORD_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned int get() const; \
		char m_lead[DISP]; \
		unsigned short m_value; \
	}; \
	unsigned int NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP32_MOVZX_WORD_GETTER(Rva0039160CMovzxWordField, 0x5E0)
