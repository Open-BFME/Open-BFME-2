// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272945@Drawable@@QAEXH@Z @0x00272945 (22B): Drawable forwards `a` to
// the first draw module's virtual slot 0x60/4 (the 0x14C module-pointer array),
// tail-calling through the vtable when the slot is non-null. Keeping the array
// pointer named (rather than naming the element) is what reproduces retail's
// `mov eax,[eax]` reuse plus the `mov ecx,eax` call setup.


// ?rva00272945@Drawable@@QAEXH@Z
#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
void Drawable::rva00272945(int a)
{
	DrawModule **drawModule = ((DrawModule **)m_modules[0]);
	if (*drawModule)
		(*drawModule)->slot60(a);
}
