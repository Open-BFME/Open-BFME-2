// cl: /DNDEBUG /MD /EHsc
// ?rva002726C3@Drawable@@QAE_NHHHH@Z retail 0x002726C3 70 bytes.
// Scan null-terminated Elem array at +0x14C: e = elem->slotA8; if e then if e->slotAC(a,b,c,d) return true else next. Evidence: same +0x14C walk and slot 0xA8 as neighbour Drawable_rva0027267D 0x0027267D but second slot 0xAC; bool 4-arg shape as Drawable_rva00272835; prev 0x0027267D same flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
bool Drawable::rva002726C3(int a, int b, int c, int d)
{
	DrawModule **pp = ((DrawModule **)m_modules[0]);
	while (*pp != 0) {
		ObjectDrawInterface *e = (*pp)->getObjectDrawInterface();
		if (e != 0) {
			if (e->slotAC(a, b, c, d))
				return true;
		}
		++pp;
	}
	return false;
}
