// cl: /O1 /DNDEBUG /MD
//
// BFME2's online home screen Apt callbacks, bound as member pointers by
// the screen's registration under three spellings of its name
// ("AptOnline::OnlineHome::OnOpened", "AptOnlineHome::InitGadgets",
// "OnlineHome::NumTickerFields"); that binding is their only reference.
// They act on one object, viewed here as the first spelling's class.

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);

class GameWindow;
class BfmeKeyLC;

void GadgetListBoxReset(GameWindow *listBox);
void bfmeGo924A(BfmeKeyLC *listBox, char flag);

// The online home screen instance (Rva005B922FDtor.cpp's g_Va00E06480).
extern int g_Va00E06480;

namespace AptOnline
{
class OnlineHome
{
public:
	void OnOpened(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void NumTickerFields(int query, char *result, bool skip);

	// Unrowed 0x005B977B (366 bytes) and 0x005B98E9 (refills the message of
	// the day), pinned by address.
	void rva005B977B();
	void rva005B98E9();

private:
	unsigned char m_pad00[0x60];
	GameWindow *m_messageOfTheDay; // +0x60
};
}

// Retail 0x005B9B6B, 8 bytes: "AptOnline::OnlineHome::OnOpened".
void AptOnline::OnlineHome::OnOpened(const char *unused)
{
	rva005B977B();
}

// Retail 0x005B9B73, 73 bytes: "AptOnlineHome::InitGadgets" keeps the
// "OnlineHome::MessageOfTheDay" list box and fills it.
void AptOnline::OnlineHome::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!g_Va00E06480)
		return;
	if (!window)
		return;
	GadgetListBoxReset(window);
	if (strcmp(name, "OnlineHome::MessageOfTheDay") == 0)
	{
		m_messageOfTheDay = window;
		bfmeGo924A((BfmeKeyLC *)window, 0);
		rva005B98E9();
	}
}

// Retail 0x005B906C, 51 bytes: "OnlineHome::NumTickerFields", an Apt query
// answering 12.
void AptOnline::OnlineHome::NumTickerFields(int query, char *result, bool skip)
{
	if (!skip)
		*result = 0;
	if (query == 0 && !skip)
		_snprintf(result, 0xFF, "%d", 12);
}
