// cl: /MD
// ??1Rva005E8EA1@@QAE@XZ @0x005E8EA1 8B
// Non-virtual dtor holding rowed member Rva005F86FE at +8 via tail-jmp.
// Same recipe as 0x005E888A with wider pad. No vptr and no EH frame.
#include "../../../Include/Common/Rva005F86FE.h"

class Rva005E8EA1
{
public:
	~Rva005E8EA1();

private:
	char m_pad00[8];
	Rva005F86FE m_08; // +8
};

Rva005E8EA1::~Rva005E8EA1()
{
}
