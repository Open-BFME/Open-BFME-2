// cl: /EHsc
// ?rva0050F2AF@Rva0050F0AB@@QAEXI@Z @0x0050F2AF
// (87B): clamp val to 99999, update m_68/m_6c with focus-gated text refresh
// plus Send; chain from Send 0x0050E776 plus F0AB 0x0050F0AB.
// Identity via cmova 99999 plus winGetFocus slot 0xC0 plus caller 0x0050F586;
// /arch:SSE for cmova like string_base_compare_range precedent.

class GameWindow;

#include "../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

int __cdecl Rva0050E776Send(GameWindow *window, int data);

class Rva0050F0AB
{
public:
	void rva0050F0AB();
	void rva0050F2AF(unsigned int val);
private:
	char m_pad00[0x68];
	unsigned int m_68;
	unsigned int m_6c;
	char m_pad70[0x78 - 0x70];
	GameWindow *m_78;
	GameWindow *m_7c;
};

void Rva0050F0AB::rva0050F2AF(unsigned int val)
{
	if (val > 99999)
		val = 99999;
	if (val == m_68)
		return;
	unsigned int old6c = m_6c;
	m_68 = val;
	if (old6c <= val)
		return;
	m_6c = val;
	if (m_7c)
	{
		if (TheWindowManager->winGetFocus() != m_7c)
			rva0050F0AB();
	}
	if (m_78)
		Rva0050E776Send(m_78, (int)m_6c);
}
