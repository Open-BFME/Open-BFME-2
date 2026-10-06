// cl: /MD
// ?rva00518359@Rva00518359@@QAEXXZ @0x00518359 71B
// Restores combo selection: if m_2B0 set, clears it, scans 6 items via GadgetComboBoxGetItemData for m_310 match then GadgetComboBoxSetSelectedPos false, restores m_2B0.
// Evidence: 5 callers pass this with no args ret void; rowed GadgetCombo calls; offsets +0x2B0 +0x310.
class GameWindow;
void *__cdecl GadgetComboBoxGetItemData(class GameWindow *win, int idx);
void __cdecl GadgetComboBoxSetSelectedPos(class GameWindow *win, int idx, bool sel);

class Rva00518359
{
	char m_pad[0x2B0];
	class GameWindow *m_2B0;
	char m_pad2[0x310 - 0x2B4];
	void *m_310;
public:
	void rva00518359();
};

void Rva00518359::rva00518359()
{
	class GameWindow *win = m_2B0;
	if (!win)
		return;
	m_2B0 = 0;
	for (int i = 0; i < 6; ++i)
	{
		void *data = GadgetComboBoxGetItemData(win, i);
		if (data == m_310)
		{
			GadgetComboBoxSetSelectedPos(win, i, false);
			break;
		}
	}
	m_2B0 = win;
}
