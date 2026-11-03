// cl: /MD
#include "../../Include/GameClient/AptSaveLoad.h"
// ?Rva00433D3CClear@@YAXXZ, retail 0x00433D3C, 17 bytes.
// If AptSaveLoad::s_instance is non-null, clears byte at +0x29D.
// Evidence: global AptSaveLoad::s_instance ?AptSaveLoad::s_instance@@3HA shared with 0x00433D27,
// caller at 0x0051E3D1.
void Rva00433D3CClear()
{
	char *p = (char *)AptSaveLoad::s_instance;
	if (!p)
		return;
	p[0x29D] = 0;
}
