// cl: /MD
// ??1Rva005E888A@@QAE@XZ @0x005E888A 8B
// Non-virtual dtor holding rowed member Rva005F86FE at +4 via tail-jmp.
// No vptr and no EH frame. Unlocks 0x005E88C1.
#include "../../../Include/Common/Rva005F86FE.h"

class Rva005E888A
{
public:
	~Rva005E888A();

private:
	int m_pad00;
	Rva005F86FE m_04; // +4
};

Rva005E888A::~Rva005E888A()
{
}
