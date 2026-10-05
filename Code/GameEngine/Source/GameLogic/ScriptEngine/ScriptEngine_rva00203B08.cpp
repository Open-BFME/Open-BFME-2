// cl: /O1
// ?rva00203B08@Rva00203B08@@QAE_NXZ at retail 0x00203B08 (35B).
// Evidence: [ecx+0x1A4D9] flag like ScriptEngine m_useLogicDebugFrame in
// ScriptEngine_updateClientDebugFrame.cpp (same offset); dword at 0x00DFE158
// and byte at 0x00DFE15C same pair as g_00DFE158/g_00DFE15C there; callers at
// 0x0004250D and 0x00225DCD test al,al for bool; unlock lane.

typedef int HMODULE;
extern HMODULE g_00DFE158;
extern unsigned char g_00DFE15C;
extern unsigned char g_00DFE15D;

class Rva00203B08
{
	char m_pad[0x1A4D9];
	bool m_flag;
public:
	bool rva00203B08();
	bool rva00203AE5();
};

bool Rva00203B08::rva00203B08()
{
	if (!m_flag)
	{
		if (g_00DFE158 != 0)
			return g_00DFE15C == 0;
	}
	return false;
}

bool Rva00203B08::rva00203AE5()
{
	if (m_flag)
	{
		if (g_00DFE158 != 0)
			return g_00DFE15D == 0;
	}
	return false;
}
