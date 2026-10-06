// cl: -O1 -GR- -EHsc-
// ?Run@Rva005C38EFBox@@QAEXXZ @0x005C38EF 59B: guarded triple dispatch.
// Resolves a handle through the first global's pinned 1-arg callee; a
// non-null handle must survive the second global (null-checked) and its
// pinned check, otherwise return; then the third global runs its pinned
// 2-arg callee on (+0xC, 0). Globals as named externs; targets from REL32.
struct Rva005C38EFinder
{
	void *Find(int id);
};

struct Rva005C38EChecker
{
	bool Check(void *h);
};

struct Rva005C38EExec
{
	void Exec(int v, int z);
};

extern Rva005C38EFinder *g_rva005C38EFinder;
extern Rva005C38EChecker *g_rva005C38EChecker;
extern Rva005C38EExec *g_rva005C38EExec;

struct Rva005C38EFBox
{
	char pad[0xc];
	int m_C;
	int m_10;

	void Run();
};

void Rva005C38EFBox::Run()
{
	void *r = g_rva005C38EFinder->Find(m_10);
	if (r != 0) {
		if (g_rva005C38EChecker == 0)
			return;
		if (!g_rva005C38EChecker->Check(r))
			return;
	}
	g_rva005C38EExec->Exec(m_C, 0);
}
