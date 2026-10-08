// cl: /MD
//
// ?rva005E0FBE@Rva005E0FBE@@QAEXXZ @0x005E0FBE 74B
// Chain via rowed Fire 0x005277D9 with level +0x08 prefix +0x0C from +8 else
// g_Rva0107301CEmptyString plus flags +0x40 +0x42 and false bool temp.
// Same Fire shape as Rva005E1008Method.cpp but clearing 0x42 to 0 with
// ShowProductionCount and no float; ret void. Evidence: rowed Fire,
// globals g_Rva0107301CEmptyString and TheRva00222A8BTarget,
// string ShowProductionCount, caller jmp at 0x005E1173.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);

struct Rva005E0FBEInner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva005E0FBE
{
public:
	void rva005E0FBE();
private:
	char m_pad00[8];
	void *m_level08;
	Rva005E0FBEInner *m_inner0C;
	char m_pad10[0x40 - 0x10];
	bool m_flag40;
	char m_pad41;
	bool m_flag42;
};

void Rva005E0FBE::rva005E0FBE()
{
	if (m_flag42 == 0)
		return;
	if (m_flag40 != 0)
	{
		bool flag = false;
		const char *prefix = m_inner0C ? m_inner0C->m_name : "";
		Rva005277D9Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, prefix, "ShowProductionCount", &flag);
	}
	m_flag42 = 0;
}
