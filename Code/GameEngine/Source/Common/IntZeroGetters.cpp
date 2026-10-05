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
BFME_INT_ZERO_GETTER(Rva0008BBDDZeroGetter)
BFME_INT_ZERO_GETTER(Rva000B19F8ZeroGetter)
BFME_INT_ZERO_GETTER(Rva000B3809ZeroGetter)
BFME_INT_ZERO_GETTER(Rva000CB0FCZeroGetter)
BFME_INT_ZERO_GETTER(Rva001499A5ZeroGetter)
BFME_INT_ZERO_GETTER(Rva00149A6CZeroGetter)
BFME_INT_ZERO_GETTER(Rva00149A8CZeroGetter)
BFME_INT_ZERO_GETTER(Rva0014A07FZeroGetter)
BFME_INT_ZERO_GETTER(Rva0065E7CAZeroGetter)
BFME_INT_ZERO_GETTER(Rva0065EC9AZeroGetter)
BFME_INT_ZERO_GETTER(Rva0010615FZeroGetter)
BFME_INT_ZERO_GETTER(Rva002632C4ZeroGetter)
BFME_INT_ZERO_GETTER(Rva002632DEZeroGetter)
