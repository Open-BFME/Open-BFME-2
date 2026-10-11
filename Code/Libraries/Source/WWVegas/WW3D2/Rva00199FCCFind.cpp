// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva00199FCC@Rva00199FCC@@QAEPAXABVAsciiString@@@Z at retail 0x00199FCC (47B).
// Linear search over array of 0x24-byte records with AsciiString key at +0 via
// rowed StringBase compareNoCase 0x00006A00; returns record pointer or 0 via
// neg/sbb/and. Evidence: 5 waiting callers plus prev/next WW3D2 neighbours.
#include "ascii_string.h"

struct Rva00199FCCRec
{
	AsciiString m_key;
	char m_pad[32];
};

class Rva00199FCC
{
public:
	void *rva00199FCC(const AsciiString &name);

private:
	Rva00199FCCRec *m_begin;
	Rva00199FCCRec *m_end;
};

void *Rva00199FCC::rva00199FCC(const AsciiString &name)
{
	Rva00199FCCRec *p = m_begin;
	for (; p != m_end; ++p)
	{
		if (((const StringBase<char> &)p->m_key).compareNoCase(*(const StringBase<char> *)&name) == 0)
			break;
	}
	return p != m_end ? p : 0;
}
