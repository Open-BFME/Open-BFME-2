// cl: /MD
// ??0Rva005EE30C@@QAE@XZ, retail 0x005EE2E6, 38 bytes.
// Derived ctor for Rva005EE30C (vtable 0x008786E8 same as rowed dtor 0x005EE30C
// in Rva005EE30CChain.cpp). Calls base Rva0058AD7A ctor 0x0058AD4D with 5
// then inits three floats at +0x1C +0x20 +0x24 to 0. Base size 0x1C.

#include "../../Include/Common/Rva0058AD7A.h"

class Rva005EE30C : public Rva0058AD7A
{
public:
	Rva005EE30C();
	virtual ~Rva005EE30C();

private:
	float m_1C;
	float m_20;
	float m_24;
};

Rva005EE30C::Rva005EE30C()
	: Rva0058AD7A(5)
	, m_1C(0.0f)
	, m_20(0.0f)
	, m_24(0.0f)
{
}
