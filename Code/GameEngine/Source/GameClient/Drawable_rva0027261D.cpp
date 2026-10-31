// cl: /DNDEBUG /MD /EHsc /Oy-
// ?rva0027261D@Drawable@@QAEHXZ retail 0x0027261D 48 bytes.
// Scan null-terminated Elem array at +0x14C: e = elem->slotA8; if e then v = e->slotA0; if v return v; else next. Evidence: caller 0x0010D049; neighbours Drawable_rva002724FD prev Drawable_rva00272BE7 next same flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
int Drawable::rva0027261D()
{
	DrawModule **pp = ((DrawModule **)m_modules[0]);
	while (*pp != 0) {
		ObjectDrawInterface *elem2 = (*pp)->getObjectDrawInterface();
		if (elem2 != 0) {
			int v = elem2->slotA0();
			if (v != 0)
				return v;
		}
		++pp;
	}
	return 0;
}
