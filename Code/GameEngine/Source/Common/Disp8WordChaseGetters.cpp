// Disp8 word-chase getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / movsx eax,word [eax+<DISP2>] / ret
//
// A pointer is read at a fixed displacement from `this`, then a signed word
// is read at a second displacement from that pointer, sign-extended, and
// returned. MSVC 7.1 emits the disp8 loads `8B 41 XX` + `0F BF XX`, plus
// `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP8_WORDCHASE_ZERO_GETTER(NAME, DISP1) \
	class Inner##NAME \
	{ \
	public: \
		short m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this + (DISP1)))->m_holder->m_value; \
	}

BFME_DISP8_WORDCHASE_ZERO_GETTER(Rva0023DB58WordChaseField, 0x0C)
