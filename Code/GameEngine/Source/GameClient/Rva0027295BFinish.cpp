// cl: /DNDEBUG /MD /EHsc
//
// ?rva0027295B@Drawable@@QAEXPAX@Z retail 0x0027295B 22B
// Unlock lane: first-element tail call through member +0x14C array of ptrs;
// virtual slot 0x68 takes one void* and returns void. Caller 0x002975AC.
// The element-list local must be the pointer-to-pointer so the loaded element
// stays in eax while the vtable goes to edx.


#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
void Drawable::rva0027295B(void *arg)
{
	DrawModule **p = ((DrawModule **)m_modules[0]);
	if (*p != 0)
		(*p)->slot68(arg);
}
