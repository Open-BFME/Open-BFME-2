// cl: /O1
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
// /O1: the state-name switch below needs the sub/dec/je decision chain
// (defaults emit a jump table); the 6-byte mov/ret getters are flag-proof.

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

// ?name@Rva00603938Named@@QBEPBDXZ @ 0x00603938 (6B): returns "English".
// Ret-terminated prev (lea/pop/ret), frameless-fn-start next bytes,
// no callers, no branch sources per byte-level whole-image scan.
// Opaque address-derived name.
BFME_LITERAL_NAME_GETTER(Rva00603938Named, "English")

// Rva00215EA4StateName @ 0x00215ea4 (45B): maps a small state index to its
// name string (0 -> _available, 1 -> _engaging, 2 -> _waiting,
// 3 -> _disabled, anything else -> NULL). The retail body is a
// sub/dec/je decision chain over four adjacent B8-literal arms with a
// shared xor-eax default tail; a plain switch reproduces it. The owning
// enum is unidentified, so the name stays address-derived. Stdcall-arg
// shape (mov eax,[esp+4]) with a cdecl tail (plain ret).
const char *Rva00215EA4StateName(int state)
{
	switch (state) {
	case 0:
		return "_available";
	case 1:
		return "_engaging";
	case 2:
		return "_waiting";
	case 3:
		return "_disabled";
	default:
		return 0;
	}
}
