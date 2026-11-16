// AptOnlineLogin: canonical declarations for the members units call through private views of it;
// constructor 0x00572885 writes the four windows +0xA4..+0xB0 and +0xCE, and factory 0x00516D4D
// allocates 0xE0 bytes. The vftable, base and remaining members stay opaque.
#ifndef CANONICAL_APTONLINELOGIN_H
#define CANONICAL_APTONLINELOGIN_H

class AptOnline;
struct AptOnlineSubScreen;
class GameWindow;
class UnicodeString;

class AptOnlineLogin
{
public:
	AptOnlineLogin(AptOnline *shell);
	static AptOnlineSubScreen *Create(AptOnline *shell);
	bool rva005706D4();
	void rva0057179D(bool);
	void rva0056DCBF(bool enabled);
	UnicodeString rva0056EBD0();

private:
	unsigned char m_pad00[0xA4];
	GameWindow *m_a4; // +0xA4
	GameWindow *m_a8; // +0xA8
	GameWindow *m_ac; // +0xAC
	GameWindow *m_b0; // +0xB0
	unsigned char m_padB4[0xCE - 0xB4];
	bool m_ce; // +0xCE
	unsigned char m_padCF[0xE0 - 0xCF];
};

#endif // CANONICAL_APTONLINELOGIN_H
