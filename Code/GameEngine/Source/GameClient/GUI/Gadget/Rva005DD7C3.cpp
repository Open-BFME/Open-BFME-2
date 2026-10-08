// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
#include <algorithm>
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

// Retail walks 24-byte entries and calls the two-argument member at 0x005DDBAB.
class Rva005DDBAB
{
public:
    void rva005DDBAB(int window, int focus);
protected:
    unsigned char m_pad[0x18];
};

struct Rva005DE059Action
{
    const int window, focus;
    Rva005DE059Action(int a, int b) : window(a), focus(b) {}
    void operator()(Rva005DDBAB &row) const { row.rva005DDBAB(window, focus); }
};

int GadgetListBoxGetTopVisibleEntry(GameWindow *window);
void GadgetListBoxReset(GameWindow *window);
void GadgetListBoxSetTopVisibleEntry(GameWindow *window, int top);

class Rva005DD7C3
{
public:
	void rva005DD7C3(GameWindow *window, const Widths *widths);
	void rva005DE433(const Widths *focus);
private:
	unsigned m_unknown;
	Rva005DDBAB *m_begin, *m_end, *m_capacity;
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

// ?rva005DE433@Rva005DD7C3@@QAEXPBUWidths@@@Z present-unmatched
// Retail 0x005DE433, 70 bytes; preserves the visible row around the entry refresh.
void Rva005DD7C3::rva005DE433(const Widths *focus)
{
    if (m_win10)
    {
        int top = GadgetListBoxGetTopVisibleEntry(m_win10);
        GadgetListBoxReset(m_win10);
        _STL::for_each(m_begin, m_end, Rva005DE059Action((int)m_win10, (int)focus));
        GadgetListBoxSetTopVisibleEntry(m_win10, top);
    }
}
