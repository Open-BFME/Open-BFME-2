// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022D05F@@QAE@XZ @0x0022D05F 53B: non-virtual dtor over AsciiString at +0 and rowed member ??1Rva002294D0@@QAE@XZ at +4. Retail calls the +4 dtor first (lea ecx [esi+4] call 0x0022C94F) then the narrow releaseBuffer 0x00036410 for +0 under an __EH_prolog frame with and [ebp-4] 0 and or [ebp-4] -1. Same 53B EH shape as ??1Rva0022D1DF@@QAE@XZ at 0x0022D1DF. Evidence: unlock packet calls rowed 0x0022C94F plus rowed releaseBuffer 0x00036410; callers at 0x0022D22C 0x0041946F.
#include "ascii_string.h"

class Rva002294D0
{
public:
	~Rva002294D0();
};

class Rva0022D05F
{
public:
	~Rva0022D05F();
private:
	AsciiString m_head;
	Rva002294D0 m_item;
};

Rva0022D05F::~Rva0022D05F()
{
}
