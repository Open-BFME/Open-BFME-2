// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022CFE6@@QAE@XZ @0x0022CFE6 53B
// Non-virtual dtor over AsciiString at +0 and rowed member ??1Rva0022CCB0@@QAE@XZ
// at +4. Retail calls the +4 dtor first (lea ecx [esi+4] call 0x0022CCB0) then
// the narrow releaseBuffer 0x00036410 for +0 under an __EH_prolog frame with
// and [ebp-4] 0 and or [ebp-4] -1. Same 53B EH shape as ??1Rva0022304A@@QAE@XZ
// at 0x0022304A. Evidence: chain packet calls just-landed 0x0022CCB0 plus
// rowed releaseBuffer 0x00036410; callers at 0x0022D1C6 0x0022D9BF 0x0041841B
// and jmps at 0x0022D8C7 0x0078660E; unblocks 0x0022D1C3 0x0022D9B7 0x004183AC.
#include "ascii_string.h"

class Rva0022CCB0
{
public:
	~Rva0022CCB0();
};

class Rva0022CFE6
{
public:
	~Rva0022CFE6();
private:
	AsciiString m_head;
	Rva0022CCB0 m_item;
};

Rva0022CFE6::~Rva0022CFE6()
{
}
