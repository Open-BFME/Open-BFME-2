// cl: -O1 -GR- -EHsc-
// ?Run@Rva005B5B39Box@@QAEXPAD@Z @0x005B5B39 89B: digit-string slot apply.
// Null-guarded string must start with a digit (imported isdigit) and atoi
// to 1..10 (imported atoi, minus one); a value already current returns,
// else the +0x27C sub-object resolves it through the pinned 1-arg callee
// and the (K, K, pointer) triple runs through the rowed cdecl callee before
// stamping +0x24. K recomposed as in the 0x5B5AC3 unit (runtime constant).
// Targets from retail REL32; imports declared dllimport explicitly.
extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

enum Rva005B5B39Const
{
	Rva005B5B39_K = 0xDE0000 + 0x878
};

struct Rva005B5B39Sub
{
	void *M(int v);
};

struct Rva005B5B39Box
{
	char pad[4];
	void *m_4;
	char pad2[0x24 - 8];
	int m_24;

	void Run(char *s);
};

void Rva005B23D7Wrap(int a, int b, int c);

void Rva005B23D7Wrap(int a, int b, int c);

void Rva005B5B39Box::Run(char *s)
{
	if (s == 0)
		return;
	if (!isdigit(s[0]))
		return;
	int v = atoi(s) - 1;
	if (v < 0 || v >= 10 || v == m_24)
		return;
	void *p = ((Rva005B5B39Sub *)((char *)m_4 + 0x27c))->M(v);
	Rva005B23D7Wrap((int)p, Rva005B5B39_K, Rva005B5B39_K);
	m_24 = v;
}
