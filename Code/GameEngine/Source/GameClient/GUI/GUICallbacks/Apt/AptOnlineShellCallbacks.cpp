// cl: /O1 /DNDEBUG /MD
//
// BFME2's online shell screen Apt callbacks, 0x00516EC0 onward, bound by
// these names ("AptOnline::Options", "AptOnline::ShellExit") as member
// pointers by the screen's registration; that binding is their only
// reference. The class is named for the strings' prefix.

void __cdecl Rva005185D8Init(bool a, bool b, bool c, bool d);

// Rva00516E92Enable.cpp's 0x00516E92.
void Rva00516E92Enable();

// Rva0059FF9DDo.cpp's two words (retail .data initial value -1).
extern int g_009C0758;
extern int g_009C075C;

class AptOnline
{
public:
	void Options(const char *unused);
	void ShellExit(const char *unused);
};

// Retail 0x00516EC0, 19 bytes: "AptOnline::Options".
void AptOnline::Options(const char *unused)
{
	Rva005185D8Init(true, false, true, false);
}

// Retail 0x00516ED3, 22 bytes: "AptOnline::ShellExit" resets both words
// and leaves through 0x00516E92.
void AptOnline::ShellExit(const char *unused)
{
	g_009C075C = -1;
	g_009C0758 = -1;
	Rva00516E92Enable();
}
