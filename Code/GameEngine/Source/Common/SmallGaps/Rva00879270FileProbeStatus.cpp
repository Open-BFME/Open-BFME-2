// cl: /MD
// Transferred from Open-BFME-1 5cae4bdff game/GameEngine/Source/Common/SmallGaps/Rva00879270FileProbeStatus.cpp;
// bfme1_sweep places the same masked body: Rva00879270FileProbeStatus at BFME2 0x006B8B10. Addresses in the donor text are BFME1.
// Retail 0x00879270 opens the path in update mode and reports status 0
// on success or 13 on failure. No caller proves a more specific identity.
// BFME2 retail slot 0x00BBA5D4 is msvcr71!fopen (import-ref verified); the donor
// reached it through a decorated alias, which that check refuses.
#include <stdio.h>

void *Rva00879270FileProbeStatus(const char *name, int *status)
{
	void *file = fopen(name, "w+");
	*status = (file != 0) ? 0 : 13;
	return file;
}
