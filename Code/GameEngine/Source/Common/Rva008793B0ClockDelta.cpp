// cl: /MD
// Open-BFME: clock delta reconstructed from retail RVA 0x008793B0.

#include <time.h>

int Rva008793B0(int start)
{
    return clock() - start;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?StopStopwatch@@YAKK@Z=?Rva008793B0@@YAHH@Z")
