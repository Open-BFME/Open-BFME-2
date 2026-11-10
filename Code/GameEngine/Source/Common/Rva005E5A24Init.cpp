// cl: /GX- /MD /DNDEBUG
// ?Rva005E5A24Init@@YAPAV?$BitFlags@$0L@@@PAV1@@Z @ 0x005E5A24 20B
// Evidence: rowed BitFlags<11> ctor 0x005E5963 with pushes 0 0 3; caller 0x005E5A46 passes stack temp; prev Rva005E59FCCopy same flags.
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../Include/Common/BitFlagsTemplate.h"

BitFlags<11> *Rva005E5A24Init(BitFlags<11> *p)
{
	p->BitFlags<11>::BitFlags(BitFlags<11>::kInit, 0, 3);
	return p;
}
