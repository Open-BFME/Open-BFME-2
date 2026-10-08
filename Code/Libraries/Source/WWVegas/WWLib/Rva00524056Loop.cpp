// cl: /DBFME_SB_CLEAR_DECL /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva00524056@Rva00524021@@QAEXXZ @0x00524056 53B
// Evidence: chain via rowed erase 0x00224705 plus StringBase::clear 0x0048BA39; loop over +0/+4 with global VA 0x009FE4CC guard TheRva00222A8BTarget; callers 0x0052435B 0x0052496E; precedent Rva00524021Loop single-vector shape.
#include "ascii_string.h"

class Rva00224705
{
public:
	int rva00224705(const AsciiString *key);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00524021
{
public:
	void rva00524056();
private:
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
};

void Rva00524021::rva00524056()
{
	if ((*(Rva00224705 **)&g_bfmeAptWindowManager) == 0)
		return;
	while (m_begin != m_end) {
		(*(Rva00224705 **)&g_bfmeAptWindowManager)->rva00224705((const AsciiString *)(m_end - 1));
		--m_end;
		m_end->clear();
	}
}
