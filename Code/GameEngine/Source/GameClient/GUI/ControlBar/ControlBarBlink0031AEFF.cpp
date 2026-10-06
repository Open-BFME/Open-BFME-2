// cl: /DNDEBUG /MD
// ?rva0031AEFF@Rva0031AEFF@@QAEXXZ @0x0031AEFF 85B: blink countdown at +0x294 with flag +0x290 and window +0x298; modulo 15 toggles winEnable via winGetStatus bit3. Evidence: packet disasm with rowed winEnable 0x00313BEC and pinned winGetStatus 0x0030F45F at same ICF address as getName rows.
class GameWindow
{
public:
	unsigned int winGetStatus();
	int winEnable(bool enable);
};

class Rva0031AEFF
{
public:
	void rva0031AEFF();

	unsigned char m_pad[0x290];
	unsigned char m_flag;
	unsigned char m_pad2[3];
	int m_counter;
	GameWindow *m_window;
};

void Rva0031AEFF::rva0031AEFF()
{
	if (m_flag == 0)
		return;
	if (m_window == 0)
		return;
	if (--m_counter <= 0) {
		m_flag = 0;
		m_window->winEnable(true);
	} else {
		if ((m_counter % 15) != 0)
			return;
		m_window->winEnable(((m_window->winGetStatus() >> 3) & 1) == 0);
	}
}
