// Donor: Open-BFME-1 game/Libraries/Source/EA/Apt/Bfme5PrefixCheck8C5680.cpp.
// The matched target body reads the prefix pointer, calls strlen and strncmp,
// then tests for equality. Its imported CRT thunk is pinned to the existing
// BFME2 strncmp import at 0x0062995E. The descriptive donor name remains
// provisional because the target has no named direct callers.
extern "C" int __cdecl strncmp(const char *, const char *, unsigned int);
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)

// The retail cell at VA 0x00DDC920 (pointing to "FSCommand:") is defined in
// AptActionInterpreterConstantHandlers.cpp.
extern const char *g_bfmeAptFSCommandAtDDC920;

unsigned char __stdcall bfmeHasPrefix8C5680(const char *text)
{
	const char *prefix = g_bfmeAptFSCommandAtDDC920;
	return strncmp(text, prefix, strlen(prefix)) == 0;
}
