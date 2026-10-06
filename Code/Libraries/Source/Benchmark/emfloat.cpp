// cl: /GS /MD /GR- /EHsc- -Ireference/shims/nbench
#include "emfloat.c"

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?StartStopwatch@@YAKXZ=?ji_006b8c30@@YAXXZ")
