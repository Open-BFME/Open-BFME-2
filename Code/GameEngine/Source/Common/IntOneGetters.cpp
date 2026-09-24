// Trivial int-one getters: four-byte __thiscall members with one shape:
//
//     xor eax,eax / inc eax / ret      (33 C0 40 C3)
//
// The constant one is returned with no member access. MSVC 7.1 emits the
// xor-plus-inc form under /O1; at defaults it uses a five-byte mov instead.
// Several sit immediately after a conditional predecessor whose taken arm
// jumps into them as a shared true-tail, so they double as standalone
// entries and as tails. Identity is not recovered: every name is derived
// from its address.
// cl: /O1
#define BFME_INT_ONE_GETTER(NAME) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return 1; \
	}

BFME_INT_ONE_GETTER(Rva0004CACDOneGetter)
BFME_INT_ONE_GETTER(Rva0007246EOneGetter)
BFME_INT_ONE_GETTER(Rva000782DDOneGetter)
BFME_INT_ONE_GETTER(Rva000B22C7OneGetter)
BFME_INT_ONE_GETTER(Rva00262126OneGetter)
BFME_INT_ONE_GETTER(Rva000B2BDDOneGetter)
BFME_INT_ONE_GETTER(Rva000B4975OneGetter)
BFME_INT_ONE_GETTER(Rva0027000AOneGetter)
