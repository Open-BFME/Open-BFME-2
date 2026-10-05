// ?rva0059E098@Rva0059E098Class@@QAEHH@Z
// partial score=0.9 date=2026-10-05
// cl: -O1 -GR- -EHsc-
// STASH for 0x0059E098 (41B): verified 42B twin, ebp frame matches, only diff
// is mov-vs-and zero-store encoding for a kept-but-unread slot. Tried:
// plain int (slot dropped), z&=0 (dropped), struct-ctor (dropped),
// *a=z fold (use folds, init dropped). Callee decl/pin may need rework:
// twin used (int,int) thiscall spelling; push order suggests (a,t).
struct Rva0059E098Class
{
	int m_0[14];
	int m_38;

	int rva0059E098(int a);
	void callee(int x, int y);
};

int Rva0059E098Class::rva0059E098(int a)
{
	int t = m_38;
	volatile int z = 0;
	if (t)
		callee(t, a);
	else
		*(int*)a = 0;
	return a;
}
