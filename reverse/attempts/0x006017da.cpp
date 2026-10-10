// ?Rva006017DAParse@@YAPADPBDPADH@Z
// partial score=0.9825403185415206 date=2026-10-10
// ?Rva006017DAParse@@YAPADPBDPADH@Z
// partial score=0.95 date=2026-10-03
// cl: /O1 /MD
// ?Rva006017DAParse@@YAPADPBDPA DH@Z @0x006017DA 149B
// INI #include line parser. Evidence: callers 0x00601EE8 in 0x00601C53;
// strstr IAT 0x00BBA614 and strlen thunk 0x00629170 with table 0x00E06A50.

extern "C" __declspec(dllimport) char *__cdecl strstr(const char *s1, const char *s2);
extern "C" unsigned int __cdecl strlen(const char *s);
extern int TextFileCharacterClasses[];

// ?Rva006017DAParse@@YAPADPBDPADH@Z present-unmatched
char *__cdecl Rva006017DAParse(const char *src, char *dst, int maxLen)
{
	char ch = *src;
	int len = 0;
	if (ch == '\r')
		goto have_line;
	{
		int off = (int)dst - (int)src;
loop_top:
		if (ch == '\n')
			goto have_line;
		int lim = maxLen - 1;
		if (len >= lim)
			goto have_line;
		*(char *)(off + (int)src) = ch;
		++len;
		++src;
		ch = *src;
		if (ch != '\r')
			goto loop_top;
	}
have_line:
	dst[len] = 0;
	char *f = strstr(dst, "#include");
	if (f == 0)
		goto finish;
	f += strlen("#include");
	while (*f == ' ' || *f == '\t' || *f == '"')
		++f;
	int n = 0;
	unsigned char c2 = (unsigned char)*f;
	while (TextFileCharacterClasses[c2] == 0) {
		if (n >= maxLen)
			break;
		++n;
		c2 = ((const unsigned char*)f)[n];
	}
	--n;
	while (n > 0) {
		if (f[n] != '"')
			break;
		f[n] = 0;
		--n;
	}
finish:
	return f;
}
