// Disp8 mov-lea-neg-sbb getters: twelve-byte __thiscall members with one shape:
//
//     mov eax,ecx / lea ecx,[eax+<ADDIMM>] / neg eax / sbb eax,eax / and eax,ecx / ret
//
// The mirror image of the lea-neg-sbb family: here the null-tested base is
// `this` itself, copied to eax, while the selected field is derived from the
// base so it compiles to a lea into ecx. neg sets carry exactly when the base
// is nonzero and sbb spreads it to a full mask selecting the field or null.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the shape).
#define BFME_DISP8_MOV_LEA_NEG_SBB_GETTER(NAME, ADDIMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		const void *base = this; \
		const char *field = (const char *)base + ADDIMM; \
		return base ? (int)field : 0; \
	}

BFME_DISP8_MOV_LEA_NEG_SBB_GETTER(Rva000CA841MovLeaNegSbbField, 0x0C)
