// Trivial int-zero getters: three-byte __thiscall members with one shape:
//
//     xor eax,eax / ret      (33 C0 C3)
//
// The constant zero is returned with no member access. Identity is not
// recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless three-byte shape).
#define BFME_INT_ZERO_GETTER(NAME) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return 0; \
	}

BFME_INT_ZERO_GETTER(Rva0008550CZeroGetter)
BFME_INT_ZERO_GETTER(Rva000CB0FCZeroGetter)
