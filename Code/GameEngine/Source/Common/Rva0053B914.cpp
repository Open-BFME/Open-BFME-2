// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE
// ?rva0053B914@Rva0053B914@@QAEXXZ 50B @0x0053B914: hide-all loop over this+0xDC window array with global 8B clear at g_00E05E24. Clears two dwords per slot and hides present windows via rowed winHide. Evidence: rowed winHide at 0x00313C64 plus callers at 0x0031EAAE 0x0053D375 0x0053E7AC.
class GameWindow
{
public:
	int winHide(bool hide);
};
extern int g_00E05E24;
extern int g_00E05F24;
class Rva0053B914
{
public:
	void rva0053B914();
private:
	char m_pad00[0xDC];
	GameWindow *m_windows[32];
};
void Rva0053B914::rva0053B914()
{
	int *p = &g_00E05E24;
	GameWindow **w = m_windows;
	do
	{
		p[-1] = 0;
		p[0] = 0;
		if (*w)
			(*w)->winHide(true);
		p += 2;
		++w;
	} while ((int)p < (int)&g_00E05F24);
}
