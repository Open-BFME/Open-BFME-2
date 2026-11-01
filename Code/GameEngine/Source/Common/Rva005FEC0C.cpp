// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// platformsdk
// ?rva005FEC0C@Rva005FA854Inner@@QAEXXZ @0x005FEC0C 240B
// Countdown-timer display refresh (class built by Rva005FEB01's constructor: keys
// show/seconds/minutes at +0/+4/+8, owner +C, last whole second +10, deadline +14,
// show-flag +18). Evidence: WB debug body 01634B10 (unnamed) structure; callees
// rowed invoke 0x00222A8B (int-return), timeGetTime, UnicodeString::format 0x006CB5D0
// ("%02d"), bfmeSetText pin 0x00225301, releaseBuffer 0x00036E70.
// The meaning of the +18 flag (first-call visibility query) is inferred from the WB body.
#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../Include/Common/Rva00222A8BTarget.h"

extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class Rva005FA854Inner
{
public:
	void rva005FEC0C();
private:
	AsciiString m_show;
	AsciiString m_seconds;
	AsciiString m_minutes;
	void *m_owner;
	int m_lastSecond;
	unsigned long m_deadline;
	bool m_visible;
};

void Rva005FA854Inner::rva005FEC0C()
{
	if (m_lastSecond == 0)
		return;
	if (!m_visible)
	{
		const char *result = (const char *)Rva0043DB23(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager, m_owner, m_show.str());
		m_visible = *result != 0;
	}
	int remaining = (int)(m_deadline - timeGetTime());
	if (remaining < 0)
		remaining = 0;
	int second = remaining / 1000;
	if (m_lastSecond == second)
		return;
	m_lastSecond = second;
	int minutes = second / 60;
	second = second % 60;
	UnicodeString secondText;
	secondText.format(L"%02d", second);
	UnicodeString minuteText;
	minuteText.format(L"%02d", minutes);
	g_bfmeAptWindowManager->bfmeSetText(m_seconds, secondText, false);
	g_bfmeAptWindowManager->bfmeSetText(m_minutes, minuteText, false);
}
