// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// Retail 0x00435BB3, 281 bytes: the save/load screen's list/text-entry event handler (WorldBuilder: switch on
// the message with 0x4014 list selection, 0x4015 double click, 0x4031 text-entry commit, 0x4032 text change).
// Partial reconstruction of the AptSaveLoad event handler at 0x00435BB3.
#include "../../../../../Include/GameClient/Bfme2GameWindow.h"
#include "../../../../../Include/GameClient/_bfme_AptGameWindow.h"
void GadgetListBoxSetSelected(GameWindow *window, int index);
class AptSaveLoad
{
public:
	int rva00435BB3(int message, GameWindow *source, int value);
	void rva00434432();
	void SetDefaultFileName();
	void rva00434A2F();
	void OnButtonSave(const char *unused);
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
	if (m_state >= 0x12 && m_state <= 0x17)
		return ((_bfme_AptGameWindow *)this)->rva0051274F(message, (unsigned int)source, (unsigned int)value);

	switch (message)
	{
	case 0x4014:
		if (value >= 0)
		{
			if (source == m_gameList)
				GadgetListBoxSetSelected(m_autoSaveList, -1);
			else if (source == m_autoSaveList)
				GadgetListBoxSetSelected(m_gameList, -1);
		}
		rva00434432();
		if (m_294 != 2)
			SetDefaultFileName();
		rva00434A2F();
		return 1;
	case 0x4015:
		if (source == m_gameList || source == m_autoSaveList)
		{
			if (rva00433F7F())
			{
				if (m_294 == 3)
					OnButtonSave(0);
				else if (m_294 == 2)
					Load(0);
			}
		}
		return 1;
	case 0x4031:
		{
			bool changed = value != 0;
			if (source == m_fileName && !changed && m_294 == 3)
				OnButtonSave(0);
		}
		return 1;
	case 0x4032:
		if (source == m_fileName)
			rva00434A2F();
		return 1;
	default:
		return ((_bfme_AptGameWindow *)this)->rva0051274F(message, (unsigned int)source, (unsigned int)value);
	}
}
