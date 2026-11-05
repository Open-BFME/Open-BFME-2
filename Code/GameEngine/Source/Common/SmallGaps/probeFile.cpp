// cl: /MD
// ?probeFile@@YAXPBDPAH@Z
// BFME1 imports these under its own slot names; the retail BFME2 slots are
// msvcr71!fopen + msvcr71!fclose.
#include <stdio.h>
void probeFile(const char *name, int *status)
{
	FILE *file = fopen(name, "w");
	*status = (file != 0) ? 0 : 10;
	fclose(file);
}
