// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?Rva003000F6Get@@YAH_N0@Z @ 0x003000F6, 23 bytes.
// Honest address-derived name; callers pass two boolean flags.
int Rva003000F6Get(bool a, bool b)
{
	int v = (a == 0);
	v++;
	if (b)
		v |= 8;
	else
		v |= 4;
	return v;
}
