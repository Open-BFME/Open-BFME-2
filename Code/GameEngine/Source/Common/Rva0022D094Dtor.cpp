// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022D094@@QAE@XZ @0x0022D094 53B: non-virtual dtor over AsciiString at +0 and rowed member ??1Rva002294A3@@QAE@XZ at +4. Retail calls the +4 dtor first (lea ecx [esi+4] call 0x0022C917) then the narrow releaseBuffer 0x00036410 for +0 under an __EH_prolog frame with and [ebp-4] 0 and or [ebp-4] -1. Same 53B EH shape as ??1Rva0022D1DF at 0x0022D1DF. Evidence: unlock packet calls rowed 0x0022C917 plus rowed releaseBuffer 0x00036410; callers at 0x0022D261 0x00419A32.
#include "ascii_string.h"

class Rva002294A3
{
public:
	~Rva002294A3();
};

class Rva0022D094
{
public:
	~Rva0022D094();
private:
	AsciiString m_head;
	Rva002294A3 m_item;
};

Rva0022D094::~Rva0022D094()
{
}
