// cl: /MD /EHsc
// ?rva005FD6D2@Rva005FD6D2@@QAEX_N@Z retail 0x005FD6D2 91B
// Evidence: chain via 0x005F8EDA AptCall; suffix up disabled inner plus8; level at +4 flag at 0x4d; sibling 0x005FD677 precedent; caller 0x005FD8B1
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva005F8EDAAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0, void **ppA1);

struct Rva005FD6D2Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005FD6D2
{
	char m_pad0[4];
	void *m_level4;
	Rva005FD6D2Inner *m_inner8;
	char m_padC[0x4D - 0xC];
	bool m_flag4D;
	void rva005FD6D2(bool enabled);
};

void Rva005FD6D2::rva005FD6D2(bool enabled)
{
	if (enabled == m_flag4D)
		return;
	const char *suffix = enabled ? "_up" : "_disabled";
	const char *name = m_inner8 ? m_inner8->m_name : "";
	Rva005F8EDAAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level4, name, "SetButtonState", "moveUp", (void **)&suffix);
	m_flag4D = enabled;
}
