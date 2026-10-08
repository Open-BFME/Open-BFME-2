// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva005F086E@Rva005F086E@@QAEX_N@Z @ 0x005F086E (86B): guarded SetRegionFortressIconState fire via rowed 0x0050E9FE with _show/_hide and prefix from +8 else empty. Evidence: same shape as Rva005F921F 91B and Rva005FD677 91B; callees rowed 0x0050E9FE; strings SetRegionFortressIconState _show _hide empty fallback; global TheRva00222A8BTarget; guard m_4D.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);
struct Rva005F086EInner
{
	char m_pad8[8];
	char m_name[1];
};
class Rva005F086E
{
public:
	void rva005F086E(bool flag);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005F086EInner *m_inner08;
	char m_pad0C[0x4D - 0x0C];
	bool m_flag4D;
};
void Rva005F086E::rva005F086E(bool flag)
{
	if (flag == m_flag4D)
		return;
	const char *state = flag ? "_show" : "_hide";
	const char *prefix = m_inner08 ? m_inner08->m_name : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, prefix, "SetRegionFortressIconState", &state);
	m_flag4D = flag;
}
