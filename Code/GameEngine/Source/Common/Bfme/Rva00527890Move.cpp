// cl: /MD
// ?rva00527890@Rva00527890@@QAEXH@Z @ 0x00527890 (77B): guarded Move fire via rowed 0x005277D9 with bool v==1 and prefix from +8 else empty. Evidence: callees rowed 0x005277D9; strings Move empty fallback g_Rva0107301CEmptyString; global TheRva00222A8BTarget; guard m_10 vs arg; caller 0x002D66FD.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);
class Rva002BED91
{
public:
	void clear();
};
struct Rva00527890Inner
{
	char m_pad8[8];
	char m_name[1];
};
class Rva00527890
{
public:
	void rva00527890(int v);
	void rva005278DD();
private:
	char m_pad00[4];
	void *m_level04;
	Rva00527890Inner *m_inner08;
	int m_state0C;
	int m_10;
	char m_pad14[0x1C - 0x14];
	Rva002BED91 m_clear1C;
};
void Rva00527890::rva00527890(int v)
{
	if (v == m_10)
		return;
	bool flag = (v == 1);
	const char *prefix = m_inner08 ? m_inner08->m_name : "";
	Rva005277D9Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, prefix, "Move", &flag);
	m_10 = v;
}
void Rva00527890::rva005278DD()
{
	if (m_state0C == 3 || m_state0C == 4)
	{
		const char *s = m_inner08 ? m_inner08->m_name : "";
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, s, "Hide");
		m_state0C = 2;
	}
	m_clear1C.clear();
}
