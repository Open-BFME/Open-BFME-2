// cl: /MD
// ?rva005E1008@Rva005E1008@@QAEXM@Z retail 0x005E1008 86B
// Evidence: chain via rowed Fire 0x005277D9 with ShowTimerOverlay using level +0x08 prefix +0x0C from +8 else g_Rva0107301CEmptyString plus flags +0x40 +0x43 and true bool temp plus float arg to +0x3C; same Fire shape as Rva00527890Move.cpp; ret 4 float
struct Rva005E1008Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);

class Rva005E1008
{
public:
	void rva005E1008(float v);
private:
	char m_pad00[8];
	void *m_level08;
	Rva005E1008Inner *m_inner0C;
	char m_pad10[0x3C - 0x10];
	float m_float3C;
	bool m_flag40;
	char m_pad41[2];
	bool m_flag43;
};

void Rva005E1008::rva005E1008(float v)
{
	if (m_flag43 == 0) {
		if (m_flag40 != 0) {
			bool flag = true;
			const char *prefix = m_inner0C ? m_inner0C->m_name : "";
			Rva005277D9Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, prefix, "ShowTimerOverlay", &flag);
		}
		m_flag43 = true;
	}
	m_float3C = v;
}
