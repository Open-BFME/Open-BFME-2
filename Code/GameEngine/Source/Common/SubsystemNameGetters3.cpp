// Subsystem literal name getters, third unit: six-byte const members with one
// shape (mov eax,<offset string literal> / ret). Split from
// Code/GameEngine/Source/Common/SubsystemNameGetters2.cpp to keep concurrent
// contributors conflict-free; the BFME_LITERAL_NAME_GETTER macro is verbatim.
// Each body returns a pointer to a NUL-terminated class-name string in .rdata
// with exactly one vtable (body-VA) reference behind a C3 predecessor;
// verify_string_refs re-reads the string.
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

#include "../../Include/GameLogic/AI.h"

const char *AI::GetSnapshotName() const
{
	return "AI";
}
