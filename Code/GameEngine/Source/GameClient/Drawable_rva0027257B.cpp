// cl: /DNDEBUG /MD /EHsc
// ?rva0027257B@Drawable@@QAEHH@Z retail 0x0027257B 54 bytes.
// Scan null-terminated Elem array at +0x14C: e = elem->slotA8; if e then v = e->slot94(a); if v return v else next. Evidence: same +0x14C walk and slot 0xA8 as neighbour Drawable_rva0027261D 0x0027261D but second slot 0x94 with 1 arg; prev 0x002724FD next 0x0027261D same flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
int Drawable::rva0027257B(int a)
{
	DrawModule **pp = ((DrawModule **)m_modules[0]);
	while (*pp != 0) {
		ObjectDrawInterface *elem2 = (*pp)->getObjectDrawInterface();
		if (elem2 != 0) {
			int v = elem2->slot94(a);
			if (v != 0)
				return v;
		}
		++pp;
	}
	return 0;
}
