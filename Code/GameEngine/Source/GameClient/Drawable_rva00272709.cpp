// cl: /DNDEBUG /MD /EHsc /Oy- /O1 /arch:SSE /G7
// ?rva00272709@Drawable@@QAEHXZ @0x00272709 (34B). Evidence: Drawable's adjacent
// slot-19 and slot-20 module-array walkers at 0x002726C3 and 0x0027272B share
// the +0x14C array; vtable offset 0xCC is proven by this body's indirect call.
#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
int Drawable::rva00272709()
{
	for (DrawModule **drawModule = ((DrawModule **)m_modules[0]); *drawModule; ++drawModule)
	{
		int v = (*drawModule)->slotCC();
		if (v != 0)
			return v;
	}
	return 0;
}
