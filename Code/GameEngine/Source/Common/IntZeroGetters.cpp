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

BFME_INT_ZERO_GETTER(Rva00021736ZeroGetter)
BFME_INT_ZERO_GETTER(Rva000310EBZeroGetter)
BFME_INT_ZERO_GETTER(Rva00042FF5ZeroGetter)
BFME_INT_ZERO_GETTER(Rva00050D50ZeroGetter)
BFME_INT_ZERO_GETTER(Rva00050D5DZeroGetter)
BFME_INT_ZERO_GETTER(Rva00050DEDZeroGetter)
BFME_INT_ZERO_GETTER(Rva0006CEEBZeroGetter)
BFME_INT_ZERO_GETTER(Rva00075692ZeroGetter)
BFME_INT_ZERO_GETTER(Rva0007B716ZeroGetter)
BFME_INT_ZERO_GETTER(Rva0008550CZeroGetter)
