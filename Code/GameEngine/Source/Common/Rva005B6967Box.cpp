// cl: -Oy- -GR- -EHsc-
// ?Run@Rva005B6967Box@@QAEXPADH0@Z @0x005B6967 158B: two-path validated set.
// Unless the third arg is null, strcmp it (imported) against two runtime
// tables; a first-table miss fills a 3-int buffer (9/0x2E/0x2D) for the
// pinned 3-arg callee, stamps +0x8 and runs the pinned helper, while a
// second-table miss fills (0x50/0x14) for the same callee plus the pinned
// 1-arg callee, stamps +0xC and runs the pinned tail body. The middle arg
// is unused. Targets from retail REL32; strcmp via plain C decl reusing
// the existing thunk pin; tables as named externs.
extern "C" int __cdecl strcmp(const char *a, const char *b);
extern char g_rva005B6967T0[];
extern char g_rva005B6967T1[];

struct Rva005B6967Buf
{
	int x;
	int y;
	int z;
};

struct Rva005B6967Box
{
	char pad[8];
	char *m_8;
	char *m_C;

	void Helper();
	void Tail();
	void Run(char *a, int unused, char *c);
};

void Rva005B6967F(char *s, int n, int *p);
void Rva005B6967G(char *s);

void Rva005B6967Box::Run(char *a, int unused, char *c)
{
	if (c == 0)
		return;
	Rva005B6967Buf buf;
	if (strcmp(a, g_rva005B6967T0) == 0) {
		buf.x = 9;
		buf.y = 0x2e;
		buf.z = 0x2d;
		Rva005B6967F(c, 3, &buf.x);
		m_8 = c;
		Helper();
	} else {
		if (strcmp(a, g_rva005B6967T1) != 0)
			return;
		buf.y = 0x50;
		buf.z = 0x14;
		Rva005B6967F(c, 2, &buf.y);
		Rva005B6967G(c);
		m_C = c;
		Tail();
	}
}
