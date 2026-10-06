// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022D214@@QAE@XZ @0x0022D214 53B: non-virtual dtor over AsciiString at +0 and rowed member ??1Rva0022D05F@@QAE@XZ at +4. Retail calls the +4 dtor first (lea ecx [esi+4] call 0x0022D05F) then the narrow releaseBuffer 0x00036410 for +0 under an __EH_prolog frame with and [ebp-4] 0 and or [ebp-4] -1. Same 53B EH shape as ??1Rva0022D1DF@@QAE@XZ at 0x0022D1DF. Evidence: chain packet calls just-landed 0x0022D05F plus rowed releaseBuffer 0x00036410; callers at 0x0022D8EB 0x0022DB96 0x00419463.
#include "ascii_string.h"

class Rva0022D05F
{
public:
	~Rva0022D05F();
};

class Rva0022D214
{
public:
	~Rva0022D214();
private:
	AsciiString m_head;
	Rva0022D05F m_item;
};

Rva0022D214::~Rva0022D214()
{
}
