// cl: /MD /EHsc
// ?Rva005E2CFAGet@@YAPAXPBD@Z @0x005E2CFA 44B
// Unlock table lookup: 3-entry {result, name} at 0x00C77B40 searched with strcmp.
// Evidence: unlock lane plus callers 0x005E2D52 0x005E2DC8 plus callee strcmp 0x006291C6.
extern "C" int __cdecl strcmp(const char *a, const char *b);

struct Rva005E2CFAEntry
{
	void *m_result;
	const char *m_name;
};

extern const Rva005E2CFAEntry g_00C77B40[3];

void *Rva005E2CFAGet(const char *s)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		if (strcmp(s, g_00C77B40[i].m_name) == 0)
			return g_00C77B40[i].m_result;
	}
	return 0;
}
