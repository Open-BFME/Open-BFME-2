// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva0056D76B@@QAE@XZ retail 0x0056D76B 57B
// The ref holder at +8 is released through the rowed fastcall
// ReleaseTreeHintRef00217D4C 0x0007DEEF when set (EH state 0), then the
// AsciiString at +0 through releaseBuffer 0x00036410. Called on the +0x258
// member by dtor 0x005C9659. Names address-derived.

#include "ascii_string.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class Rva0056D76BRef
{
public:
	~Rva0056D76BRef()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}

	TargetRef00217D4C *m_ref;
};

class Rva0056D76B
{
public:
	~Rva0056D76B();

private:
	AsciiString m_name; // +0x00
	int m_04;
	Rva0056D76BRef m_ref; // +0x08
};

Rva0056D76B::~Rva0056D76B()
{
}
