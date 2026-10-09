// ?rva0054C805@Rva0054C805@@QAEXM@Z
// partial score=0.9 date=2026-10-09
// ?rva0054C805@Rva0054C805@@QAEXM@Z
// partial score=0.88 date=2026-10-04
// cl: /O1 /G6 /DNDEBUG /MD
// ?rva0054C805@Rva0054C805@@QAEXM@Z @ 0x0054C805 (49B).
// __thiscall elapsed-time update: if m_14 is 0 or 3 return; else m_24 = timeGetTime() - (int)(arg * g_00C08A34).
// Evidence: ret 4 with float arg; IAT timeGetTime at 0x00BBA918; fmul float at VA 0x00C08A34; call __ftol2 row 0x00629228; caller 0x0054C877 passes member at +4.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern float g_00C08A34;
class Rva0054C805
{
public:
	void rva0054C805(float arg);
private:
	char _00[0x14];
	int m_14;
	char _18[0x0C];
	int m_24;
};

void Rva0054C805::rva0054C805(float arg)
{
	if (m_14 == 0)
		return;
	if (m_14 == 3)
		return;
	const volatile float &seconds=arg;
	unsigned long start = timeGetTime();
	m_24 = (int)(start - (int)(seconds * g_00C08A34));
}
