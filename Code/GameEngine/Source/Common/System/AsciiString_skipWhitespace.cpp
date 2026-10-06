// cl: /Ob0 /DNDEBUG /MD
//
// Retail 0x000357C0 (42B). Whitespace skipper over a char pointer.
// Transferred from the BFME1 reconstruction (BFME1 0x00887260, 42B, same
// AsciiString.cpp TU family). `static` is load-bearing: it gives MSVC its
// private EAX argument convention (mov esi,eax head). /Ob0 keeps the worker
// out-of-line. The anchor wrapper is absent from retail; it only forces the
// emission.

extern "C" __declspec(dllimport) int __cdecl isspace(int c);

static char *skipWhitespace(char *p)
{
	while (*p && isspace(*p))
		++p;
	return p;
}

// C++ integration entry, absent from retail. Keeping the worker static gives
// MSVC its private EAX argument convention. Only the 42B worker is claimed.
char *SkipWhitespaceAnchor(char *p) { return skipWhitespace(p); }
