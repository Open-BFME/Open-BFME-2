// cl: /O2 /MD /EHsc
// Native [0x6FD5B0,0x6FD625),117B, cdecl: returns the second character when the
// first is not a hex digit; otherwise asserts the second is a hex digit
// ("isxdigit(b)", AptActionInterpreter.cpp line 0xBED) and returns the value
// strtoul parses from the two characters in base 16. Address-derived names:
// the two CRT-like callees are not identified.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
int rva00629B6E(int c);
unsigned long rva006291C0(const char *text, void *end, int base);
unsigned char Rva006FD5B0(char hi, char lo)
{
	if (!rva00629B6E(hi))
		return lo;
	if (!rva00629B6E(lo)) {
		g_bfmeAptAssertAtE17734("isxdigit(b)", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0xbed);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	char buf[3];
	buf[0] = hi;
	buf[1] = lo;
	buf[2] = 0;
	return (unsigned char)rva006291C0(buf, 0, 16);
}
