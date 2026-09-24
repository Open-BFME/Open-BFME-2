// Disp8 masked-chase dword getters: ten-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / mov eax,[eax+<DISP2>] / and eax,<MASK> / ret
//
// A pointer is read at a fixed displacement from `this`, then a dword is read
// at a second displacement from that pointer, masked with a small immediate,
// and returned. MSVC 7.1 emits the disp8 loads `8B 41 XX` + `8B 40 XX`, plus
// the `83 E0 XX` and-mask, plus `ret`, for ten bytes total. This is the masked
// sibling of the plain Disp8PtrChaseDwordFieldGetters family; the extra `and`
// is why the two families are kept in separate translation units. Identity
// is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_DISP8_MASKED_CHASE_DWORD_GETTER(NAME, DISP1, DISP2, MASK) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return *(int *)((char *)m_ptr + DISP2) & MASK; \
	}

BFME_DISP8_MASKED_CHASE_DWORD_GETTER(Rva00072756MaskedChaseField, 0x40, 0x10, 0x02)
