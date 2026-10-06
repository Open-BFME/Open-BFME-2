// cl: /EHsc
// ?rva0050F2AF@Rva0050F0AB@@QAEXI@Z @0x0050F2AF
// (87B): clamp val to 99999, update m_68/m_6c with focus-gated text refresh
// plus Send; chain from Send 0x0050E776 plus F0AB 0x0050F0AB.
// Identity via cmova 99999 plus winGetFocus slot 0xC0 plus caller 0x0050F586;
// /arch:SSE for cmova like string_base_compare_range precedent.

class GameWindow;

class GameWindowManager {
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual void *winGetFocus();
#undef V
	virtual int winSetFocus(GameWindow *window);
#define W(n) virtual void pad##n() = 0;
	W(50) W(51) W(52) W(53) W(54) W(55) W(56) W(57)
#undef W
	virtual int winSendSystemMsg(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
};

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
