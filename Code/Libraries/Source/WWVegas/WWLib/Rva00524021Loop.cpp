// cl: /DBFME_SB_CLEAR_DECL /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva00524021@Rva00524021@@QAEXXZ @0x00524021 53B
// Evidence: chain via rowed erase 0x00223A94 and StringBase::clear 0x0048BA39;
// loop over +0/+4 with global VA 0x009FE4CC guard; callers 0x004E6B4A 0x004E6BDE 0x005242E9 0x00524965
#include "ascii_string.h"


class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00524021
{
public:
	void rva00524021();
private:
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
};

void Rva00524021::rva00524021()
{
	if ((*(Rva00223A94 **)&g_bfmeAptWindowManager) == 0)
		return;
	while (m_begin != m_end) {
		(*(Rva00223A94 **)&g_bfmeAptWindowManager)->rva00223A94((const AsciiString *)(m_end - 1));
		--m_end;
		m_end->clear();
	}
}
