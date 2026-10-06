// cl: /MD
// ?rva005E10A8@Rva005E10A8@@QAEXH@Z retail 0x005E10A8 176B
// Evidence: chain via rowed Fire 0x005277D9 triple Enable ShowProductionCount ShowTimerOverlay using level +0x08 prefix +0x0C from +8 else empty plus flags +0x41 +0x42 +0x43 and bool temps 0 1 1 plus final +0x40 to 1; same Fire shape as Rva00527890Move.cpp; ret 4 dummy int
struct Rva005E10A8Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);

class Rva005E10A8
{
public:
	void rva005E10A8(int dummy);
private:
	char m_pad00[8];
	void *m_level08;
	Rva005E10A8Inner *m_inner0C;
	char m_pad10[0x40 - 0x10];
	bool m_flag40;
	bool m_flag41;
	bool m_flag42;
	bool m_flag43;
};

void Rva005E10A8::rva005E10A8(int dummy)
{
	(void)dummy;
	const char *empty = g_Rva0107301CEmptyString;
	if (m_flag41 == 0) {
		bool flag0 = false;
		const char *prefix0 = m_inner0C ? m_inner0C->m_name : empty;
		Rva005277D9Fire(TheRva00222A8BTarget, m_level08, prefix0, "Enable", &flag0);
	}
	if (m_flag42 != 0) {
		bool flag1 = true;
		const char *prefix1 = m_inner0C ? m_inner0C->m_name : empty;
		Rva005277D9Fire(TheRva00222A8BTarget, m_level08, prefix1, "ShowProductionCount", &flag1);
	}
	if (m_flag43 != 0) {
		bool flag2 = true;
		const char *prefix2 = m_inner0C ? m_inner0C->m_name : empty;
		Rva005277D9Fire(TheRva00222A8BTarget, m_level08, prefix2, "ShowTimerOverlay", &flag2);
	}
	m_flag40 = true;
}
