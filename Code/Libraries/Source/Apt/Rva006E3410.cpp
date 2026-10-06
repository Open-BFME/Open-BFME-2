// cl: /MD
//
// ?rva006E3410@Rva006E3410@@QAEHH@Z @0x006E3410 70B
// Linear search of an int array, returning the index or -1: if count > 0
// scan with pointer cursor for v and return i on match; else assert
// NOT_REACHED at AptAnimation.cpp:210 via the shared Apt assert triple
// (E17734 + DDC01C + int3) and return -1.
// Evidence: unlock lane, 8 callers all in 0x006E5940; file string pinned by
// reverse/string_xrefs.tsv (AptAnimation.cpp referenced from 0x006E3410);
// assert-triple spelling copied from Rva006E3230Validate.cpp.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006E3410
{
public:
	int rva006E3410(int v);
private:
	char m_pad0[0xC];
	int m_count;
	int *m_arr;
};

int Rva006E3410::rva006E3410(int v)
{
	int n = m_count;
	int i = 0;
	if (n > 0) {
		int *p = m_arr;
		int x = v;
		do {
			if (*p == x)
				return i;
			++i;
			++p;
		} while (i < n);
	}
	g_bfmeAptAssertAtE17734("NOT_REACHED", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0xD2);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__debugbreak();
	return -1;
}
