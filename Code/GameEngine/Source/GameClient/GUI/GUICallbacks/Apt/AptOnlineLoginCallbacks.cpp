// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-
//
// BFME2's online login screen link buttons "AptOnline::Login::OfficialSite",
// "::GameSpy" and "::ServiceTerms", 0x0056E998 onward, bound by those names
// as member pointers by the screen's registration; that binding is their
// only reference. Each opens a localized URL in Internet Explorer and
// minimizes the game window.

#include "unicode_string.h"

extern "C" __declspec(dllimport) void *__stdcall ShellExecuteW(void *window, const unsigned short *operation, const unsigned short *file, const unsigned short *parameters, const unsigned short *directory, int show);

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

void bfmeMinimizeCurrentThreadWindow();

namespace AptOnline
{
class Login
{
public:
	void OfficialSite(const char *unused);
	void GameSpy(const char *unused);
	void ServiceTerms(const char *unused);
};
}

// Retail 0x0056E998, 83 bytes: "AptOnline::Login::OfficialSite".
void AptOnline::Login::OfficialSite(const char *unused)
{
	UnicodeString url = TheGameText->fetch("URL:LotrHome");
	ShellExecuteW(0, L"open", L"IEXPLORE.EXE", url.str(), 0, 5);
	bfmeMinimizeCurrentThreadWindow();
}

// Retail 0x0056E9EB, 83 bytes: "AptOnline::Login::GameSpy".
void AptOnline::Login::GameSpy(const char *unused)
{
	UnicodeString url = TheGameText->fetch("URL:GameSpyHome");
	ShellExecuteW(0, L"open", L"IEXPLORE.EXE", url.str(), 0, 5);
	bfmeMinimizeCurrentThreadWindow();
}

// Retail 0x0056EA3E, 83 bytes: "AptOnline::Login::ServiceTerms".
void AptOnline::Login::ServiceTerms(const char *unused)
{
	UnicodeString url = TheGameText->fetch("URL:LotrTOS");
	ShellExecuteW(0, L"open", L"IEXPLORE.EXE", url.str(), 0, 5);
	bfmeMinimizeCurrentThreadWindow();
}
