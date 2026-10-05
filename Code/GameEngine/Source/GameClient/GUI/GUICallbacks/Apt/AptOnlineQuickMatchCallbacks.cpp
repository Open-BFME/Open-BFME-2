// cl: /O1 /DNDEBUG /MD
//
// BFME2's online quick match screen Apt callbacks, 0x005BA344 onward, and
// the login screen's CancelLogin, bound by these names
// ("AptOnline::OnlineQuickMatch::StartSimple" ...) as member pointers by
// the screens' registrations; that binding is their only reference. The
// scope and classes are named for the strings.

// Rva00516E92Enable.cpp's 0x00516E92.
void Rva00516E92Enable();

namespace AptOnline
{
class OnlineQuickMatch
{
public:
	void StartSimple(const char *unused);
	void PlayGame(const char *unused);
	void OnFoundMovieDone(const char *unused);

private:
	unsigned char m_pad00[0x60];
	int m_state; // +0x60
	unsigned char m_pad64[0x79 - 0x64];
	bool m_simple; // +0x79
	bool m_foundMovie; // +0x7A
};

class Login
{
public:
	void CancelLogin(const char *unused);
};
}

// Retail 0x005BA344, 7 bytes: "AptOnline::OnlineQuickMatch::StartSimple".
void AptOnline::OnlineQuickMatch::StartSimple(const char *unused)
{
	m_simple = true;
}

// Retail 0x005BA34B, 14 bytes: "AptOnline::OnlineQuickMatch::PlayGame".
void AptOnline::OnlineQuickMatch::PlayGame(const char *unused)
{
	m_simple = true;
	m_state = 1;
}

// Retail 0x005BA359, 20 bytes: "AptOnline::OnlineQuickMatch::OnFoundMovieDone".
void AptOnline::OnlineQuickMatch::OnFoundMovieDone(const char *unused)
{
	m_state = 2;
	if (m_foundMovie)
		m_foundMovie = false;
}

// Retail 0x0056DCB7, 8 bytes: "AptOnline::Login::CancelLogin".
void AptOnline::Login::CancelLogin(const char *unused)
{
	Rva00516E92Enable();
}
