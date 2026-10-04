// Trivial int-one getters: four-byte __thiscall members with one shape:
//
//     xor eax,eax / inc eax / ret      (33 C0 40 C3)
//
// The constant one is returned with no member access. MSVC 7.1 emits the
// xor-plus-inc form under /O1; at defaults it uses a five-byte mov instead.
// Some historical row notes call conditional arms shared true-tails.
// Each standalone entry needs independent native evidence; an internal
// conditional branch alone does not supply it. Original identities remain
// unrecovered and every view retains its address-qualified name.
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
BFME_INT_ONE_GETTER(Rva00262126OneGetter)
BFME_INT_ONE_GETTER(Rva000B2BDDOneGetter)
BFME_INT_ONE_GETTER(Rva000B4975OneGetter)
BFME_INT_ONE_GETTER(Rva0027000AOneGetter)
