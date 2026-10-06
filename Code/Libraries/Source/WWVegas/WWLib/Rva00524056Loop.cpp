// cl: /DBFME_SB_CLEAR_DECL /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva00524056@Rva00524021@@QAEXXZ @0x00524056 53B
// Evidence: chain via rowed erase 0x00224705 plus StringBase::clear 0x0048BA39; loop over +0/+4 with global VA 0x009FE4CC guard TheRva00222A8BTarget; callers 0x0052435B 0x0052496E; precedent Rva00524021Loop single-vector shape.
#include "ascii_string.h"

class Rva00224705
{
public:
	int rva00224705(const AsciiString *key);
};

extern Rva00224705 *g_Va009FE4CC;

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
	if (g_Va009FE4CC == 0)
		return;
	while (m_begin != m_end) {
		g_Va009FE4CC->rva00224705((const AsciiString *)(m_end - 1));
		--m_end;
		m_end->clear();
	}
}
// ?g_Va009FE4CC@@3PAVRva00224705@@A: the global at VA 0xdfe4cc is ?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE4CC@@3PAVRva00224705@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
