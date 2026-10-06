// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ??1Rva00410688@@QAE@XZ at 0x00410688 (57B).
// Dtor with AsciiString at +0 plus TargetRef at +4 released via rowed
// fastcall 0x7DEEF. Evidence: releaseBuffer row 0x36410, 5 callers,
// unblocks 0x410792/0x410AAB/0x41112B.

#include "ascii_string.h"


struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva00410688
{
public:
	~Rva00410688();
private:
	AsciiString m_00;
	TargetRef00217D4C *m_04;
};

Rva00410688::~Rva00410688()
{
	if (m_04 != 0)
		ReleaseTreeHintRef00217D4C(m_04);
}
