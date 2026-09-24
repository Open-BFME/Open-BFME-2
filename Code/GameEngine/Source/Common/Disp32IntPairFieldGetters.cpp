// Disp32 int-pair field getters: twenty-four-byte __thiscall members with one shape:
//
//     mov edx,[ecx+<DISP>] / mov eax,[esp+4] / mov [eax],edx
//       / mov ecx,[ecx+<DISP+4>] / mov [eax+4],ecx / ret 4
//
// Two adjacent dwords at a fixed 32-bit displacement from `this` are copied
// as a unit into the caller's out-parameter. The pair is modelled as a small
// two-int struct so the whole copy is one assignment; MSVC 7.1 loads the
// first member into edx, fetches the out pointer, stores, then loads the
// second member, which reproduces the retail register order exactly.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless twenty-four-byte shape).
struct Disp32IntPair
{
	int m_firstValue;
	int m_secondValue;
};

#define BFME_DISP32_INT_PAIR_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void get(Disp32IntPair &result); \
		char m_leadingPadding[DISP]; \
		Disp32IntPair m_pairValue; \
	}; \
	void NAME::get(Disp32IntPair &result) \
	{ \
		result = m_pairValue; \
	}

BFME_DISP32_INT_PAIR_GETTER(Rva002620DBIntPairField, 0x414)
