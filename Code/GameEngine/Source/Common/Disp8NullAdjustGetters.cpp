// Disp8 null-adjust getters: __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / test eax,eax / je <ELSE> / add eax,<IMM> / ret
//     <ELSE>: xor eax,eax / ret  OR  mov eax,<GLOBAL> / ret
//
// A dword at a fixed displacement from `this` is null-tested; when nonzero
// it is adjusted by a small immediate, otherwise a default (null or a shared
// global address) is returned. The xor-else form is fourteen bytes, the
// mov-global-else form seventeen. Identity is not recovered: every name is
// derived from its address.
// No // cl: line (defaults match the shape).
#define BFME_DISP8_NULL_ADJUST_GETTER(NAME, DISP, ADJ) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return m_ptr ? m_ptr + ADJ : 0; \
	}

struct BfmeNullAdjustDefault;
extern BfmeNullAdjustDefault g_bfmeNullAdjustBBAC1C;
extern BfmeNullAdjustDefault g_bfmeNullAdjustDE0878;

#define BFME_DISP8_NULL_ADJUST_GLOBAL_GETTER(NAME, DISP, ADJ, GLOBAL) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_ptr; \
	}; \
	int NAME::get() const \
	{ \
		return m_ptr ? m_ptr + ADJ : (int)&GLOBAL; \
	}

BFME_DISP8_NULL_ADJUST_GETTER(Rva002B2252NullAdjustField, 0x08, 0x2C)
BFME_DISP8_NULL_ADJUST_GETTER(Rva002C5FCBNullAdjustField, 0x0C, 8)
BFME_DISP8_NULL_ADJUST_GETTER(Rva002D2548NullAdjustField, 0x08, -4)
BFME_DISP8_NULL_ADJUST_GETTER(Rva002D25ACNullAdjustField, 0x04, -4)
BFME_DISP8_NULL_ADJUST_GLOBAL_GETTER(Rva00136164NullAdjustGlobalField, 0x14, 8, g_bfmeNullAdjustBBAC1C)
