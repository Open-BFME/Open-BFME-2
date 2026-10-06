// cl: /Ireference/shims/bfme2_ascii
// ?Rva006CB9D0@@YAPAXPBD@Z @ 0x006CB9D0 (51B). Assert-guarded wrapper from
// AptValueFactory.cpp: it validates a string argument then hands it to the
// unnamed creational helper at 0x006D7090 and returns that helper's value.
//
// The single argument string and file literal come from the retail assert
// site (VA 0x00CE8AE8 / 0x00CE8AF8), read off the PE image directly; the
// assertion mechanism matches the already-matched AptValueGCRootBFME2.cpp
// (call through the global pointer at VA 0x00E17734, then break on the flag
// at VA 0x00DDC01C).
//
// Structural inference, NOT proven identity: the caller of 0x006D7090 reads
// it as a pool-allocate-and-initialise that returns the new value, so this
// body is a null-checked thin forwarder. The address-derived name is used
// because no ledger row names this function.
//
// 0x006D7090 is declared and pinned address-derived; it has its own body
// elsewhere and only the call is reproduced here.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

// Unnamed AptValueFactory helper at 0x006D7090.
void *__cdecl rva006D7090(const char *szValue);

void *Rva006CB9D0(const char *szValue)
{
	if (szValue == 0) {
		g_bfmeAptAssertAtE17734("szValue != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueFactory.cpp", 52);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return rva006D7090(szValue);
}
