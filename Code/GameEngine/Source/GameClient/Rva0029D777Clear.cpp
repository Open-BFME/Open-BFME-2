// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
//
// ?rva0029D777@Rva0029D777@@QAEXXZ, retail 0x0029D777, 75 bytes.
// Clears a button label to empty plus 20 list holders: if the window at +0x978
// is set, GadgetButtonSetText it with UnicodeString::TheEmptyString (via the
// shared wide copy ctor), set +0x97C to -1, then clear the 20 holders at +0x928.
#include "unicode_string.h"

class GameWindow;
void GadgetButtonSetText(GameWindow *g, UnicodeString text);

class Rva001EB130Holder
{
public:
	void rva001EB130();
private:
	void *m_head;
};

class Rva0029D777
{
public:
	void rva0029D777();
private:
	unsigned char m_pad[0x928];
	Rva001EB130Holder m_holders[20];
	GameWindow *m_window978;
	int m_97C;
};

void Rva0029D777::rva0029D777()
{
	if (m_window978 != 0)
		GadgetButtonSetText(m_window978, UnicodeString::TheEmptyString);
	m_97C = -1;
	for (int i = 0; i < 20; ++i)
		m_holders[i].rva001EB130();
}
