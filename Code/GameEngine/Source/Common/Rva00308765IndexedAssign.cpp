// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00308765@Rva00308765@@QAEXHABVAsciiString@@@Z, retail 0x00308765, 52B.
// Indexed AsciiString assign at +0x78 with change notify via vtable slot 7.
// Evidence: lea edi [esi+ebx*4+0x78], rowed StringBase compare 0x69D6,
// pinned AsciiString assign 0x366F0, virtual call [eax+0x1c] with index;
// callers 0x30923E 0x3292F1 0x3292FE. Honest address name.
#include "ascii_string.h"


class Rva00308765
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07(int index);
	void rva00308765(int index, const AsciiString &value);
private:
	char m_pad04[0x78 - 4];
	AsciiString m_arr78[64];
};

void Rva00308765::rva00308765(int index, const AsciiString &value)
{
	AsciiString *slot = &m_arr78[index];
	if (value.compare(*slot) != 0)
	{
		*slot = value;
		s07(index);
	}
}
