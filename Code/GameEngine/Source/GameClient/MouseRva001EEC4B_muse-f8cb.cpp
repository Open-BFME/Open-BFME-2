// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva001EEC4B@Rva001EEC4B@@QAEXXZ @ 0x001EEC4B (76B): Mouse tooltip reset with Hide.
// Retail calls timeGetTime and stores to +0x4FD8 then clears +0x1308. If tooltip string
// at +0x12F8 is not empty it fires HideToolTip via Rva003807B7Hide (landed 60B) and clears
// +0x12F8. Then clears +0x12FC and tail-jmps to clear +0x1300 through StringBase wide
// releaseBuffer (row 0x36E70) plus isEmpty (row 0x35740). Callers 0x0029F27E. Prev
// Mouse::setVisibility proves Mouse area but owner uses honest-address Rva class per packet.
// timeGetTime via winmm IAT needs dllimport for FF15.
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();

#include "unicode_string.h"

void Rva003807B7Hide();

class Rva001EEC4B
{
	char m_pad0[0x12F8];
	UnicodeString m_12F8;
	UnicodeString m_12FC;
	UnicodeString m_1300;
	char m_pad1[0x1308 - 0x1304];
	unsigned char m_1308;
	char m_pad2[0x4FD8 - 0x1309];
	int m_4FD8;
public:
	void rva001EEC4B();
};

void Rva001EEC4B::rva001EEC4B()
{
	m_4FD8 = timeGetTime();
	m_1308 = 0;
	if (!m_12F8.isEmpty())
	{
		Rva003807B7Hide();
		m_12F8.clear();
	}
	m_12FC.clear();
	m_1300.clear();
}
