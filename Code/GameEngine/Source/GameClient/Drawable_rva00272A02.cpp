// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272A02@Drawable@@QAEX_N@Z, retail 0x00272A02, 54 bytes.
// Flag plus broadcast: bit 2 at +0x114 follows the bool arg, then walk
// this+0x14C modules forwarding the bool to slot 0x30 targets.
// Evidence: same +0x14C walk/flags as Drawable_rva0027290C neighbour
// (// cl: /O1 /DNDEBUG /MD /EHsc /G7 frameless); cmp byte proves bool;
// or/and dword at +0x114; ret 4; unblocks 6 incl 0x001E9083 0x00471464.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
void Drawable::rva00272A02(bool flag)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	if (flag)
		self->m_status |= 2;
	else
		self->m_status &= ~2;
	for (DrawModule **p = ((DrawModule **)m_modules[0]); *p; ++p)
		(*p)->slot30(flag);
}
