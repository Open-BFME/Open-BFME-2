// cl: -GR- -EHsc-
// ?Run@Rva005BC474Box@@QAEXXZ @0x005BC474 33B: two-flag clearer. Runs the
// pinned 0-arg callee when +0x78 is clear, returns when +0x79 is clear,
// else runs the pinned 0-arg callee and clears +0x79. Targets from retail
// REL32; both callees unrowed.
struct Rva005BC474Box
{
	char pad[0x78];
	unsigned char m_78;
	unsigned char m_79;

	void MB5CE();
	void MBF15();
	void Run();
};

void Rva005BC474Box::Run()
{
	if (m_78 == 0)
		MB5CE();
	if (m_79 == 0)
		return;
	MBF15();
	m_79 = 0;
}
