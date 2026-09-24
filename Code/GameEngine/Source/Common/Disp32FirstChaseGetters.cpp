// Disp32-first chase getters (twin-free TU).
//
// Two ten-byte __thiscall members whose FIRST displacement needs disp32:
//
//     mov eax,[ecx+<DISP32>] / mov eax,[eax+<DISP>] / ret          (dword)
//     mov eax,[ecx+<DISP32>] / movsx eax,word [eax] / ret          (word)
//
// MSVC 7.1 emits `8B 81 <DISP32>` for the wide first load; the second load
// keeps its disp8/zero form. Members before the accessed ones are spelled
// as lead arrays because their types are not witnessed here, only their
// total size. Identity is not recovered: every name is derived from its
// address.
// No // cl: line (defaults match the frameless ten-byte shapes).
#define BFME_DISP32_FIRST_PTRCHASE_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return *(int *)((char *)m_ptr + DISP2); \
	}

#define BFME_DISP32_FIRST_WORDCHASE_ZERO_GETTER(NAME, DISP1) \
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

BFME_DISP32_FIRST_PTRCHASE_GETTER(Rva00149960PtrChaseField, 0xC4, 0x20)
BFME_DISP32_FIRST_WORDCHASE_ZERO_GETTER(Rva002AAE4FWordChaseField, 0xF6C)
