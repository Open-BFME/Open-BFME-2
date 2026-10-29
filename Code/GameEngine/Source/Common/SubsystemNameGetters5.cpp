// Subsystem literal name getters, fifth unit: six-byte const members with one
// shape (mov eax,<offset string literal> / ret). Split to keep concurrent
// contributors conflict-free; the BFME_LITERAL_NAME_GETTER macro is verbatim.
// Each body returns a pointer to a NUL-terminated class-name string in .rdata
// with exactly one vtable (body-VA) reference behind a C3 predecessor;
// verify_string_refs re-reads the string. Slot pattern: body at vtable slot 2
// behind a shared pair (slot 1 is 0xA9E440), closed by 0x5B5384.
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

BFME_LITERAL_NAME_GETTER(Rva006C0990Named, "TaintManager")
BFME_LITERAL_NAME_GETTER(Rva00739970Named, "ShroudManager")
