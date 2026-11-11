// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva0053B914@Rva0053B914@@QAEXXZ 50B @0x0053B914: hide-all loop over this+0xDC window array with global 8B inventory entry clear. Clears two dwords per slot and hides present windows via rowed winHide. Evidence: rowed winHide at 0x00313C64 plus callers at 0x0031EAAE 0x0053D375 0x0053E7AC.
#include "../../Include/GameClient/Bfme2GameWindow.h"
#include "../../Include/Common/ControlBarInventoryEntry.h"
extern ControlBarInventoryEntry ControlBarInventoryEntries[32];
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
	int *p = &ControlBarInventoryEntries[0].objectID;
	GameWindow **gameWindow = m_windows;
	do
	{
		p[-1] = 0;
		p[0] = 0;
		if (*gameWindow)
			(*gameWindow)->winHide(true);
		p += 2;
		++gameWindow;
	} while ((int)p < (int)ControlBarInventoryEntries + (int)sizeof(ControlBarInventoryEntries) + 4);
}
