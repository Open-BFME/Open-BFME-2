// ?rva00435BB3@AptSaveLoad@@QAEHHPAVGameWindow@@H@Z
// partial score=0.82 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Partial reconstruction of the AptSaveLoad event handler at 0x00435BB3.
class GameWindow
{
};
class Rva005126F5
{
public:
	int rva0051274F(int message, unsigned int source, unsigned int value);
};
void GadgetListBoxSetSelected(GameWindow *window, int index);
class AptSaveLoad
{
public:
	int rva00435BB3(int message, GameWindow *source, int value);
	void rva00434432();
	void rva00434AAE();
	void rva00434A2F();
	void rva0043566A(const char *unused);
	int rva00433F7F();
	void Load(const char *unused);
private:
	unsigned char m_pad000[0x27C];
	int m_state;
	unsigned char m_pad280[0x288 - 0x280];
	GameWindow *m_gameList;
	GameWindow *m_autoSaveList;
	GameWindow *m_fileName;
	int m_294;
};

int AptSaveLoad::rva00435BB3(int message, GameWindow *source, int value)
{
	if ((m_state >= 0x12 && m_state <= 0x17) ||
		(message != 0x4014 && message != 0x4015 && message != 0x4031))
		return ((Rva005126F5 *)this)->rva0051274F(
			message, (unsigned int)source, (unsigned int)value);

	if (message == 0x4014)
	{
		if (value >= 0)
		{
			if (source == m_gameList)
				GadgetListBoxSetSelected(m_autoSaveList, -1);
			else if (source == m_autoSaveList)
				GadgetListBoxSetSelected(m_gameList, -1);
		}
		rva00434432();
		if (m_294 != 2)
			rva00434AAE();
		rva00434A2F();
	}
	else if (message == 0x4015)
	{
		if (source == m_gameList || source == m_autoSaveList)
		{
			if (rva00433F7F())
			{
				if (m_294 == 3)
					rva0043566A(0);
				else if (m_294 == 2)
					Load(0);
			}
		}
	}
	else if (source == m_fileName && value == 0 && m_294 == 3)
		rva0043566A(0);

	return 1;
}
