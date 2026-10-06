// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// ?Rva00559F11Parse@@YAXPBDPAH@Z, retail 0x00559F11, 55 bytes.
// Free-function parse up to 10 space-separated ints via atoi.
// Evidence: callers 0x0038D0BF 0x00401485 0x0044DB97 push array then string then pop 8B = __cdecl 2 args; caller 0x0044DB54 pushes array and string and ignores return; IAT atoi at 0x00BBA624.
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
void __cdecl Rva00559F11Parse(const char *s, int *out)
{
	for (int i = 0; i < 10; ++i) {
		out[i] = atoi(s);
		while (*s != 0 && *s != 0x20)
			++s;
		if (*s != 0)
			++s;
	}
}
