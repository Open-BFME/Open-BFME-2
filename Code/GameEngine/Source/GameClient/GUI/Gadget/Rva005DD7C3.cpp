// cl: /DNDEBUG /MD
//
// ?rva005DD7C3@Rva005DD7C3@@QAEXPAVGameWindow@@PBUWidths@@@Z, retail 0x005DD7C3, 56 bytes.
// __thiscall void method with window and widths-vector args caching window
// at this+0x10. Calls rowed GadgetListBoxSetColumnWidths then rowed
// GadgetListBoxAddMultiSelect. Evidence: chain lane calls 0x00325199.

class GameWindow;

void GadgetListBoxSetColumnWidths(GameWindow *window, int count, int *widths);
void GadgetListBoxAddMultiSelect(GameWindow *window);

struct Widths
{
	int *begin;
	int *end;
};

class Rva005DD7C3
{
public:
	void rva005DD7C3(GameWindow *window, const Widths *widths);
private:
	char m_pad[0x10];
	GameWindow *m_win10;
};

void Rva005DD7C3::rva005DD7C3(GameWindow *window, const Widths *widths)
{
	m_win10 = window;
	if (window == 0)
		return;
	int *begin = widths->begin;
	int *end = widths->end;
	if (begin != end)
	{
		int count = end - begin;
		GadgetListBoxSetColumnWidths(window, count, begin);
	}
	GadgetListBoxAddMultiSelect(m_win10);
}
