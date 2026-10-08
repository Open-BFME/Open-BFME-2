// cl: /MD /EHsc
// ?rva005FD677@Rva005FD677@@QAEX_N@Z retail 0x005FD677 91B
// Evidence: chain via 0x005F8EDA AptCall; suffix _up/_disabled; inner name at +8 else g_Rva0107301CEmptyString; level at +4 flag at 0x4c; neighbours 0x005FD53E/0x005FD788; caller 0x005FD8A9
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva005F8EDAAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0, void **ppA1);

struct Rva005FD677Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005FD677
{
	char m_pad0[4];
	void *m_level4;
	Rva005FD677Inner *m_inner8;
	char m_padC[0x4C - 0xC];
	bool m_flag4C;
	void rva005FD677(bool enabled);
};

void Rva005FD677::rva005FD677(bool enabled)
{
	if (enabled == m_flag4C)
		return;
	const char *suffix = enabled ? "_up" : "_disabled";
	const char *name = m_inner8 ? m_inner8->m_name : "";
	Rva005F8EDAAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level4, name, "SetButtonState", "moveDown", (void **)&suffix);
	m_flag4C = enabled;
}
