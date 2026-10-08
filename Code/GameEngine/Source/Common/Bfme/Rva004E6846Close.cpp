// cl: /MD
// ?rva004E6846@Rva004E6846@@QAEXXZ @ 0x004E6846 (60B): timeout check via timeGetTime firing Rva0043DB23 with "Close". Callers: jmp at 0x004E7294 in 0x004E7277. Callee row Rva0043DB23 in MpGameSetupSlots.cpp, global TheRva00222A8BTarget, IAT timeGetTime.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void __cdecl Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
struct Rva004E6846Timer
{
	unsigned char m_pad[0x18];
	unsigned long m_timeout;
};
class Rva004E6846
{
public:
	void rva004E6846();
	unsigned char m_pad00[4];
	void *m_owner;
	int m_state;
	unsigned char m_pad0C[0x44 - 0x0C];
	Rva004E6846Timer *m_timer;
	unsigned long m_start;
};
void Rva004E6846::rva004E6846()
{
	if (m_timer->m_timeout != 0)
	{
		unsigned long elapsed = timeGetTime() - m_start;
		if (elapsed >= m_timer->m_timeout)
		{
			Rva0043DB23((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_owner, "Close");
			m_state = 4;
		}
	}
}
