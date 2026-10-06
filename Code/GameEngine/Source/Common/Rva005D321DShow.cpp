// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005D321D@Rva005D321D@@QAEX_N@Z retail 0x005D321D 85B
// Evidence: guard bool at +0x68; _show else _hide reusing arg slot; prefix from +4 else g_Rva0107301CEmptyString; level at +0; SetState via rowed 0x0050E9FE; global TheRva00222A8BTarget; caller jmp 0x005D3289; precedent Rva005F086E::rva005F086E
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);
struct Rva005D321DInner
{
	char m_pad8[8];
	char m_name[1];
};
class Rva005D321D
{
public:
	void rva005D321D(bool flag);
private:
	void *m_level00;
	Rva005D321DInner *m_inner04;
	char m_pad08[0x68 - 0x08];
	bool m_flag68;
};
void Rva005D321D::rva005D321D(bool flag)
{
	if (flag == m_flag68)
		return;
	const char *state = flag ? "_show" : "_hide";
	const char *prefix = m_inner04 ? m_inner04->m_name : g_Rva0107301CEmptyString;
	Rva0050E9FEAptCall(TheRva00222A8BTarget, m_level00, prefix, "SetState", &state);
	m_flag68 = flag;
}
