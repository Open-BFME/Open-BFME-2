// cl: /GX-
// ?OnSystemMsg@AptObjectivesMenu@@QAEHHII@Z @0x004E4038 110B evidence: gap between 0x004E400D and 0x004E40A6 same flags; calls rowed base 0x0051274F pin _bfme_AptGameWindow slot2 with three message args plus rowed getSlot 0x003FF29F on TheGameInfo and rowed GadgetCheckBoxIsChecked 0x00327B33; msg 0x4008 with 8-window loop at +0x28c and slot index bytes at +0x2ac storing checkbox result at GameSlot+0xA.
class _bfme_AptGameWindow
{
public:
	int rva0051274F(int a1, unsigned int a2, unsigned int a3);
};

class GameSlot
{
public:
	char m_pad[0x0A];
	unsigned char m_flag0A;
};

class GameInfo
{
public:
	GameSlot *getSlot(int slotNum);
};

extern GameInfo *TheGameInfo;

class GameWindow;
extern bool __cdecl GadgetCheckBoxIsChecked(GameWindow *win);

class AptObjectivesMenu
{
public:
	int OnSystemMsg(int msg, unsigned int wParam, unsigned int lParam);
private:
	char m_pad[0x28C];
	void *m_windows[8];
	signed char m_slotIdx[8];
};

int AptObjectivesMenu::OnSystemMsg(int msg, unsigned int wParam, unsigned int lParam)
{
	int r = ((_bfme_AptGameWindow *)this)->rva0051274F(msg, wParam, lParam);
	if (msg != 0x4008)
		return r;
	for (int i = 0; i < 8; i++)
	{
		if (wParam != (unsigned int)m_windows[i])
			continue;
		int idx = m_slotIdx[i];
		GameSlot *slot = TheGameInfo->getSlot(idx);
		bool checked = GadgetCheckBoxIsChecked((GameWindow *)wParam);
		if (slot == 0)
			break;
		slot->m_flag0A = checked;
	}
	return 1;
}
