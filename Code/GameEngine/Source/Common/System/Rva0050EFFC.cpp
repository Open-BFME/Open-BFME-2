// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva0050EFFC@Rva0050F041@@QAEXH@Z @0x0050EFFC 69B
// SetState setter on Rva0050F041 layout: m_5c level m_60 name holder +8 m_74 state.
// Evidence: chain via rowed 0x0050E9FE AptCall; caller 0x0050FF48; sibling Rva0050F041;
// prefix empty g_Rva0107301CEmptyString else +8; function "SetState"; table 0x00C6556C;
// target TheRva00222A8BTarget 0x009FE4CC.
class Rva00222A8BTarget
{
};
extern class Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
extern const char *g_00C6556C[];
int Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva0050F041Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva0050F041
{
public:
	void rva0050EFFC(int state);
private:
	char m_pad00[0x5c];
	int m_5c;
	Rva0050F041Inner *m_60;
	char m_pad64[0x10];
	int m_74;
};

void Rva0050F041::rva0050EFFC(int state)
{
	if (state == m_74)
		return;
	const char *prefix = m_60 ? m_60->m_name : g_Rva0107301CEmptyString;
	Rva0050E9FEAptCall(TheRva00222A8BTarget, (void *)m_5c, prefix, "SetState", &g_00C6556C[state]);
	m_74 = state;
}
