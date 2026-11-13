// cl: /MD
// ??0Rva005CC61E@@QAE@XZ @0x005CC61E 28B evidence: calls rowed new 0x0002FDA0 size 4 zeroes then stores at +0; callers 0x005753D1 0x0057621A
// Allocates 4 bytes via rowed operator new zeroes it and stores at +0 returning this.
#include <new>
#include "../../Include/Common/Rva005CC61E.h"
Rva005CC61E::Rva005CC61E()
{
	m_ptr00 = new int(0);
}
