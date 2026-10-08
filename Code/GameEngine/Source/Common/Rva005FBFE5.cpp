// cl: /MD
// ?rva005FBFE5@Rva005FBFE5@@QAEXH@Z @0x005FBFE5 69B
// SetResultState setter: m_04 level m_08 name holder +8 m_20 state.
// Evidence: chain via rowed 0x0050E9FE AptCall; caller 0x005FC1A1; prev 0x005FBEBA;
// prefix empty g_Rva0107301CEmptyString else +8; function SetResultState;
// table 0x00C7A05C; target TheRva00222A8BTarget 0x009FE4CC.
class Rva00222A8BTarget
{
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_00C7A05C[];
int Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva005FBFE5Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva005FBFE5
{
public:
	void rva005FBFE5(int state);
private:
	char m_pad00[4];
	int m_04;
	Rva005FBFE5Inner *m_08;
	char m_pad0C[0x14];
	int m_20;
};

void Rva005FBFE5::rva005FBFE5(int state)
{
	if (state == m_20)
		return;
	const char *prefix = m_08 ? m_08->m_name : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_04, prefix, "SetResultState", &g_00C7A05C[state]);
	m_20 = state;
}
