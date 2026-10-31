// cl: /DNDEBUG /MD /EHsc
// ?rva0027267D@Drawable@@QAE_NHHHH@Z retail 0x0027267D 70 bytes.
// Scan null-terminated Elem array at +0x14C: e = elem->slotA8; if e then if e->slotA8(a,b,c,d) return true else next. Evidence: same +0x14C walk and slot 0xA8 as neighbour Drawable_rva0027261D 0x0027261D; bool 4-arg shape as Drawable_rva00272835 0x00272835; prev 0x0027261D next 0x0027272B share flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
bool Drawable::rva0027267D(int a, int b, int c, int d)
{
	DrawModule **pp = ((DrawModule **)m_modules[0]);
	while (*pp != 0) {
		ObjectDrawInterface *e = (*pp)->getObjectDrawInterface();
		if (e != 0) {
			if (e->slotA8(a, b, c, d))
				return true;
		}
		++pp;
	}
	return false;
}
