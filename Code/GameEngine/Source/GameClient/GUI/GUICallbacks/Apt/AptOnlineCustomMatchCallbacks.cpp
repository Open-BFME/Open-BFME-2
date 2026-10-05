// cl: /O1 /DNDEBUG /MD
//
// BFME2's online custom match screen Apt callbacks, 0x0059EC65 onward,
// bound by these names ("AptOnline::CustomMatch::PlayGame" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The scope and class are named for the strings. +0x488 is the
// screen's state.

class Rva00222A8BTarget;
extern class Rva00222A8BTarget *TheRva00222A8BTarget;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);
void __cdecl Rva00434160Init(int a, int b, bool c);

// The screen's owner at +0x58 keeps its Apt movie at +0x274.
struct AptOnlineCustomMatchOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
};

namespace AptOnline
{
class CustomMatch
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	// vslot 10: the screen's Apt path for its callbacks.
	virtual const char *v10();

	void PlayGame(const char *unused);
	void LoadGame(const char *unused);
	void CancelPopUpCreate(const char *unused);
	void CancelPopUpHost(const char *unused);
	void OnOpenConnectionsScreen(const char *unused);
	void OnClosingConnectionsScreen(const char *unused);
	void Refresh(const char *unused);

	// Unrowed 0x005A0D61 (97 bytes; ret 4, a byte flag), pinned by address.
	void rva005A0D61(bool force);

private:
	unsigned char m_pad004[0x58 - 0x04];
	AptOnlineCustomMatchOwner *m_owner; // +0x58
	unsigned char m_pad05c[0x488 - 0x5C];
	int m_state; // +0x488
	unsigned char m_pad48c[0x4A0 - 0x48C];
	bool m_popUp; // +0x4A0
	unsigned char m_pad4a1[0x4D8 - 0x4A1];
	bool m_connectionsScreen; // +0x4D8
};
}

// Retail 0x0059EC65, 13 bytes: "AptOnline::CustomMatch::PlayGame".
void AptOnline::CustomMatch::PlayGame(const char *unused)
{
	m_state = 7;
}

// Retail 0x0059ECC1, 17 bytes: "AptOnline::CustomMatch::LoadGame".
void AptOnline::CustomMatch::LoadGame(const char *unused)
{
	Rva00434160Init(2, 16, false);
}

// Retail 0x0059ED18, 20 bytes: "AptOnline::CustomMatch::CancelPopUpCreate".
void AptOnline::CustomMatch::CancelPopUpCreate(const char *unused)
{
	m_state = 1;
	m_popUp = false;
}

// Retail 0x0059ED2C, 61 bytes: "AptOnline::CustomMatch::CancelPopUpHost"
// also tells the movie "ClosePassword".
void AptOnline::CustomMatch::CancelPopUpHost(const char *unused)
{
	void *movie = m_owner->m_movie;
	Rva00524EF4AptCall(TheRva00222A8BTarget, movie, v10(), "ClosePassword");
	m_state = 1;
	m_popUp = false;
}

// Retail 0x0059ED69, 17 bytes: "AptOnline::CustomMatch::OnOpenConnectionsScreen".
void AptOnline::CustomMatch::OnOpenConnectionsScreen(const char *unused)
{
	if (!m_connectionsScreen)
		m_connectionsScreen = true;
}

// Retail 0x0059ED7A, 17 bytes: "AptOnline::CustomMatch::OnClosingConnectionsScreen".
void AptOnline::CustomMatch::OnClosingConnectionsScreen(const char *unused)
{
	if (m_connectionsScreen)
		m_connectionsScreen = false;
}

// Retail 0x005A0F15, 10 bytes: "AptOnline::CustomMatch::Refresh".
void AptOnline::CustomMatch::Refresh(const char *unused)
{
	rva005A0D61(true);
}
