// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs-
// platformsdk
//
// BFME2's online login screen link buttons "AptOnline::Login::OfficialSite",
// "::GameSpy" and "::ServiceTerms", 0x0056E998 onward, bound by those names
// as member pointers by the screen's registration; that binding is their
// only reference. Each opens a localized URL in Internet Explorer and
// minimizes the game window.

#include "unicode_string.h"
#include <windows.h>

#include "../../../../../Include/GameClient/GameText.h"

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
