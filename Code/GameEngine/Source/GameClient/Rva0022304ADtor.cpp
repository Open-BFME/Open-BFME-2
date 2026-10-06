// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022304A@@QAE@XZ @0x0022304A 53B
// Non-virtual dtor over AsciiString at +0 and rowed member ??1Rva0022300F@@QAE@XZ
// at +4. Retail calls the +4 dtor first (lea ecx [esi+4] call 0x0022300F) then
// the narrow releaseBuffer 0x00036410 for +0, under an __EH_prolog frame with
// and [ebp-4] 0 and or [ebp-4] -1. Same EH clear shape as the rowed member.
// Evidence: chain packet (calls 0x0022300F just landed, all callees rowed);
// callers at 0x002231CE 0x002238A0 0x00224C4E and jmps at 0x002235B1 0x0076F5DE;
// unblocks 0x00223898 0x00224BDB.
#include "ascii_string.h"

class Rva0022300F
{
public:
	~Rva0022300F();
};

class Rva0022304A
{
public:
	~Rva0022304A();
private:
	AsciiString m_head;
	Rva0022300F m_item;
};

Rva0022304A::~Rva0022304A()
{
}
