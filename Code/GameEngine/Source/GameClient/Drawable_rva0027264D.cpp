// cl: /DNDEBUG /MD /EHsc /Oy-
// ?rva0027264D@Drawable@@QAEHXZ retail 0x0027264D 48 bytes.
// Scan null-terminated Elem array at +0x14C: e = elem->slotA8; if e then v = e->slotA4; if v return v else next. Evidence: same +0x14C walk and slot 0xA8 as neighbour Drawable_rva0027261D 0x0027261D but second slot 0xA4; prev 0x0027261D same size and flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
int Drawable::rva0027264D()
{
	DrawModule **pp = ((DrawModule **)m_modules[0]);
	while (*pp != 0) {
		ObjectDrawInterface *elem2 = (*pp)->getObjectDrawInterface();
		if (elem2 != 0) {
			int v = elem2->slotA4();
			if (v != 0)
				return v;
		}
		++pp;
	}
	return 0;
}
