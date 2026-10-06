// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022D1DF@@QAE@XZ @0x0022D1DF 53B
// Non-virtual dtor over AsciiString at +0 and rowed member ??1Rva0022D01B@@QAE@XZ
// at +4. Retail calls the +4 dtor first (lea ecx [esi+4] call 0x0022D01B) then
// the narrow releaseBuffer 0x00036410 for +0 under an __EH_prolog frame with
// and [ebp-4] 0 and or [ebp-4] -1. Same 53B EH shape as ??1Rva0022CFE6@@QAE@XZ
// at 0x0022CFE6 and ??1Rva0022304A@@QAE@XZ at 0x0022304A. Evidence: chain packet
// calls 0x0022D01B just landed plus rowed releaseBuffer 0x00036410; callers at
// 0x0022D8CF 0x0022DB7A 0x00418B44 and jmps at 0x0022D9D7 0x007866CB; unblocks
// 0x0022DB72 0x00418AC6.
#include "ascii_string.h"

class Rva0022D01B
{
public:
	~Rva0022D01B();
};

class Rva0022D1DF
{
public:
	~Rva0022D1DF();
private:
	AsciiString m_head;
	Rva0022D01B m_item;
};

Rva0022D1DF::~Rva0022D1DF()
{
}
