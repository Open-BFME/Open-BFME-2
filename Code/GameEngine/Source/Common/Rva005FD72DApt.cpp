// cl: /MD /EHsc
// ?rva005FD72D@Rva005FD72D@@QAEX_N@Z retail 0x005FD72D 91B
// Evidence: chain via 0x005F8EDA AptCall; suffix up disabled inner plus8; level at +4 flag at 0x4e; sibling 0x005FD677 precedent; caller 0x005FD8B9
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva005F8EDAAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0, void **ppA1);

struct Rva005FD72DInner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005FD72D
{
	char m_pad0[4];
	void *m_level4;
	Rva005FD72DInner *m_inner8;
	char m_padC[0x4E - 0xC];
	bool m_flag4E;
	void rva005FD72D(bool enabled);
};

void Rva005FD72D::rva005FD72D(bool enabled)
{
	if (enabled == m_flag4E)
		return;
	const char *suffix = enabled ? "_up" : "_disabled";
	const char *name = m_inner8 ? m_inner8->m_name : "";
	Rva005F8EDAAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level4, name, "SetButtonState", "swap", (void **)&suffix);
	m_flag4E = enabled;
}
