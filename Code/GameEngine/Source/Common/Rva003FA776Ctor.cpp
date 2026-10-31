// cl: /MD
// ??0Rva003FA776@@QAE@XZ, retail 0x003FA745 (49B).
// Ctor for Rva003FA776 (vtable 0x00C37930, dtor at 0x003FA776): base Overridable (+4 0, +8 0, +0xC -1), +0x10 6, +0x14 0.0f, +0x18 1.0f (VA 0x00BBB8D8).
// Evidence: vtable store at [this], tail-jmp base dtor 0x001E3624, callers 0x0021116F 0x00213814.

#include "../../Include/Common/Overridable.h"

class Rva003FA776 : public Overridable
{
public:
	Rva003FA776();
	virtual ~Rva003FA776();
private:
	int m_10;
	float m_14;
	float m_18;
};

Rva003FA776::Rva003FA776()
	: Overridable()
	, m_10(6)
	, m_14(0.0f)
	, m_18(1.0f)
{
}
