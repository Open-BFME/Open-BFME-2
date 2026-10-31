// cl: /DNDEBUG /MD /EHsc
// ?rva00272A51@Drawable@@QAEXXZ retail 0x00272A51 25 bytes.
// Void walk over null-terminated Elem array at +0x14C calling slot38. Evidence: same +0x14C walk as neighbour Drawable_rva00272A38 0x00272A38 but slot 0x38; prev 0x00272A38 same flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
void Drawable::rva00272A51()
{
	for (DrawModule **pp = ((DrawModule **)m_modules[0]); *pp != 0; ++pp)
		(*pp)->slot38();
}
