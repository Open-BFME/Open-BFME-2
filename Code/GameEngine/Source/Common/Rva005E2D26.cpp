// cl: /MD /EHsc
// ?Rva005E2D26Get@@YAPBDH@Z @0x005E2D26 32B: direct-index table lookup in 3-entry {id result name} at 0x00C77B40 returning name or 0. Evidence: same table as rowed Rva005E2CFA 0x005E2CFA plus callers 0x005E2E3A 0x005E2E91 0x005E2EED 0x005E314B plus LINK bonus.
struct Rva005E2CFAEntry
{
	void *m_result;
	const char *m_name;
};
extern const Rva005E2CFAEntry g_00C77B40[3];
const char *Rva005E2D26Get(int key)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		if (key == (int)g_00C77B40[i].m_result)
			return g_00C77B40[i].m_name;
	}
	return 0;
}
