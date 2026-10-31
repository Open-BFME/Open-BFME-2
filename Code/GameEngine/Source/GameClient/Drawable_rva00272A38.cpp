// cl: /DNDEBUG /MD /EHsc
// ?rva00272A38@Drawable@@QAEXXZ retail 0x00272A38 25 bytes.
// Void walk over null-terminated Elem array at +0x14C calling slot34. Evidence: same +0x14C walk as neighbour Drawable_rva00272A02 0x00272A02; prev 0x00272A02 same flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
void Drawable::rva00272A38()
{
	for (DrawModule **pp = ((DrawModule **)m_modules[0]); *pp != 0; ++pp)
		(*pp)->slot34();
}
