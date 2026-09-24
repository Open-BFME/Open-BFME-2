// Disp8 lea-neg-sbb getters: thirteen-byte __thiscall members with one shape:
//
//     lea eax,[ecx-<LEADISP>] / add ecx,<ADDIMM> / neg eax / sbb eax,eax / and eax,ecx / ret
//
// A pointer derived from `this` is null-tested branchlessly: neg sets carry
// exactly when the derived base is nonzero and sbb spreads it to a full mask
// that selects the adjusted `this` or null. Deriving the base from a live
// field-local keeps `this` in ecx so the adjustment compiles to an in-place
// add instead of a lea into a scratch register. Identity is not recovered:
// every name is derived from its address.
// No // cl: line (defaults match the shape).
#define BFME_DISP8_LEA_NEG_SBB_GETTER(NAME, LEADISP, ADDIMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		const char *field = (const char *)this; \
		const void *base = field - LEADISP; \
		field += ADDIMM; \
		return base ? (int)field : 0; \
	}

BFME_DISP8_LEA_NEG_SBB_GETTER(Rva003730FCLeaNegSbbField, 12, 0x18)
BFME_DISP8_LEA_NEG_SBB_GETTER(Rva0039852BLeaNegSbbField, 12, 0x24)
BFME_DISP8_LEA_NEG_SBB_GETTER(Rva004523A9LeaNegSbbField, 12, 0x1C)
