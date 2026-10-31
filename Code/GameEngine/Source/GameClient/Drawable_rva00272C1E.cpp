// cl: /DNDEBUG /MD /EHsc /Oy-
// ?rva00272C1E@Drawable@@QAE_NXZ retail 0x00272C1E 36 bytes.
// OR-accumulate slotDC over null-terminated Elem array at +0x14C. Evidence: same +0x14C walk as neighbours Drawable_rva00272BE7 0x00272BE7 and Drawable_rva0027267D 0x0027267D; prev 0x00272BE7 same flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
bool Drawable::rva00272C1E()
{
	DrawModule **pp = ((DrawModule **)m_modules[0]);
	bool acc = false;
	while (*pp != 0) {
		acc |= (*pp)->slotDC();
		++pp;
	}
	return acc;
}
