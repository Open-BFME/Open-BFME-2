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

// Disp32-back chase getters: the FIRST displacement is a negative disp32
// (the pointer lives below `this`, so MSVC 7.1 emits `8B 81 <neg-disp32>`).
// A plain lead array cannot model a negative offset, so the outer load is
// spelled as pointer arithmetic off `(char *)this - BACK`, which folds to
// the same disp32-neg addressing (lea-BEFORE precedent).
#define BFME_DISP32_BACK_PTRCHASE_GETTER(NAME, BACK, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(int *)((char *)*(void *const *)((char *)this - (BACK)) + (DISP2)); \
	}

#define BFME_DISP32_BACK_BYTECHASE_GETTER(NAME, BACK, DISP2) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return *(unsigned char *)((char *)*(void *const *)((char *)this - (BACK)) + (DISP2)); \
	}

#define BFME_DISP32_BACK_FLOATCHASE_GETTER(NAME, BACK, DISP2) \
	class NAME \
	{ \
	public: \
		float get() const; \
	}; \
	float NAME::get() const \
	{ \
		return *(float *)((char *)*(void *const *)((char *)this - (BACK)) + (DISP2)); \
	}

BFME_DISP32_BACK_PTRCHASE_GETTER(Rva004A6E29PtrChaseField, 0x3E0, 0x64)
BFME_DISP32_BACK_PTRCHASE_GETTER(Rva004A6FF9PtrChaseField, 0x3E0, 0x7C)
BFME_DISP32_BACK_PTRCHASE_GETTER(Rva004A9B85PtrChaseField, 0x3E4, 0x64)
BFME_DISP32_BACK_BYTECHASE_GETTER(Rva0047EC5FByteChaseField, 0x3E0, 0x7C)
BFME_DISP32_BACK_BYTECHASE_GETTER(Rva004A6FE5ByteChaseField, 0x3E0, 0x74)
BFME_DISP32_BACK_FLOATCHASE_GETTER(Rva00488C34FloatChaseField, 0x3E0, 0x64)
BFME_DISP32_BACK_FLOATCHASE_GETTER(Rva00488C3EFloatChaseField, 0x3E0, 0x68)
BFME_DISP32_BACK_FLOATCHASE_GETTER(Rva004A6FEFFloatChaseField, 0x3E0, 0x78)
BFME_DISP32_BACK_FLOATCHASE_GETTER(Rva004A964CFloatChaseField, 0x3E0, 0x6C)
BFME_DISP32_BACK_FLOATCHASE_GETTER(Rva004A9656FloatChaseField, 0x3E0, 0x70)
BFME_DISP32_FIRST_WORDCHASE_ZERO_GETTER(Rva0023DB89WordChaseField, 0xF50)
