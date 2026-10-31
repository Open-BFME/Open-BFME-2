// cl: /DNDEBUG /MD /EHsc
// ?rva002725B1@Drawable@@QAEHH@Z retail 0x002725B1 54 bytes.
// Scan null-terminated Elem array at +0x14C: e = elem->slotA8; if e then v = e->slot98(a); if v return v else next. Evidence: same +0x14C walk and slot 0xA8 as neighbour Drawable_rva0027257B 0x0027257B but second slot 0x98 with 1 arg; prev 0x0027257B same flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
int Drawable::rva002725B1(int a)
{
	DrawModule **pp = ((DrawModule **)m_modules[0]);
	while (*pp != 0) {
		ObjectDrawInterface *elem2 = (*pp)->getObjectDrawInterface();
		if (elem2 != 0) {
			int v = elem2->slot98(a);
			if (v != 0)
				return v;
		}
		++pp;
	}
	return 0;
}
