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

class Rva005DD7C3
{
public:
	void rva005DD7C3(GameWindow *window, const Widths *widths);
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

// The live refresh owner now resides in AptTimeLineStats.cpp. Retain
// only this verified STLport47B instantiation, identical to retail5DE059
// and its existing C loop owner, including the callback relocation.
template Rva005DE059Action _STL::for_each(Rva005DDBAB *, Rva005DDBAB *, Rva005DE059Action);
