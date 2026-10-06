// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022D249@@QAE@XZ @0x0022D249 53B: non-virtual dtor over AsciiString at +0 and rowed member ??1Rva0022D094@@QAE@XZ at +4. Retail calls the +4 dtor first (lea ecx [esi+4] call 0x0022D094) then the narrow releaseBuffer 0x00036410 for +0 under an __EH_prolog frame with and [ebp-4] 0 and or [ebp-4] -1. Same 53B EH shape as ??1Rva0022D1DF at 0x0022D1DF. Evidence: chain packet calls just-landed 0x0022D094 plus rowed releaseBuffer 0x00036410; callers at 0x0022D907 0x0022DBB2 0x00419A26.
#include "ascii_string.h"

class Rva0022D094
{
public:
	~Rva0022D094();
};

class Rva0022D249
{
public:
	~Rva0022D249();
private:
	AsciiString m_head;
	Rva0022D094 m_item;
};

Rva0022D249::~Rva0022D249()
{
}
