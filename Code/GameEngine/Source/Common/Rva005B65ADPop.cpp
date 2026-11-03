// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B65ADPop@@YAXPAPAX0VRva005B61B3@@@Z @0x005B65AD 27B.
// Honest-address pop heap forwarder over void* elements. Forwards first last
// and a null Tp* dummy plus the 8-byte comparator to the rowed pop at
// 0x5B6521. Caller at 0x5B65EA; prev is final sort TU with /O1 flags.

#include "../../Include/Common/Rva005B61B3.h"

void Rva005B6521Pop(void **first, void **last, void **dummy, Rva005B61B3 comp);
void Rva005B65ADPop(void **first, void **last, Rva005B61B3 comp);

void Rva005B65ADPop(void **first, void **last, Rva005B61B3 comp)
{
	Rva005B6521Pop(first, last, 0, comp);
}
