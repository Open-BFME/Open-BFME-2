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

// ColdGlobalDwordGetters.cpp's g_Va00E04904 (set while a buddy invite
// is pending).
extern int g_Va00E04904;

// Rva00516F3FClear.cpp's record, reset by its rowed 0x00516F3F.
struct Rva00516F3F
{
	void rva00516F3F();

	int m_0;
	int m_4;
	int m_8;
	void *m_C;
	void *m_10;
	int m_14;
};

// The pending buddy invite at +0x298.
struct AptOnlineInvite
{
	Rva00516F3F m_info;
	int m_18; // +0x18
};

class AptOnline
{
public:
	void Options(const char *unused);
	void ShellExit(const char *unused);
	// Bound without a name as the answer to the "APT:BuddyInviteJoiningText"
	// and "APT:BuddyInviteTextOpenPlay" prompts (0x005178A3, 0x00517DBA),
	// so it keeps its address.
	void rva005170B4();

private:
	unsigned char m_pad000[0x298];
	AptOnlineInvite m_invite; // +0x298
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

// Retail 0x005170B4, 25 bytes. Name unknown. Drops the pending buddy
// invite while one is flagged.
void AptOnline::rva005170B4()
{
	if (g_Va00E04904)
	{
		AptOnlineInvite *invite = &m_invite;
		invite->m_18 = 0;
		invite->m_info.rva00516F3F();
	}
}
