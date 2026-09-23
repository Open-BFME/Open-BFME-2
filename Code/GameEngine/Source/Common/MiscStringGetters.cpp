// Miscellaneous literal string getters: six-byte const members with one shape:
//
//     mov eax,<offset string literal> / ret
//
// Each body returns a pointer to a NUL-terminated string in .rdata/.data.
// Unlike the Module/Subsystem name getters, these carry no vtable slot and
// have no direct callers: each address is phase-proven (no branch or call
// in .text targets it, byte-level whole-image scan), the boundary is a
// genuine padding/ret stop, and the string evidence is stated per body.
// Kept in a contributor-local unit to stay clear of the hot
// ModuleNameGetters/SubsystemNameGetters appends on origin/master.
// No // cl: line (defaults match the frameless 6-byte shape).

#define BFME_LITERAL_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	public: \
		const char *name() const; \
	}; \
	const char *NAME::name() const \
	{ \
		return TEXT; \
	}

// ?name@Rva001B5830Named@@QBEPBDXZ @ 0x001b5830 (6B): returns "6.1.0.5".
// CC-padding both sides, sole .text dword-ref to the "6.1.0.5" string,
// no callers, no branch sources. Opaque address-derived name.
BFME_LITERAL_NAME_GETTER(Rva001B5830Named, "6.1.0.5")
