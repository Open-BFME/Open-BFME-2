// cl: /DNDEBUG /MD /EHsc
//
// ?rva002728C5@Drawable@@QAEXMM@Z, retail 0x002728C5, 71 bytes.
// Drawable float forwarder plus average-half store: if the +0x14C list head
// is present forward (a,b) to its slot 0x54 target, then store (a+b)*0.5
// (half: the __real@3f000000 literal at 0x00BC26F0) to +0xAC. Evidence: unlock lane; same +0x14C head
// pattern as Drawable_rva00272835; slot 0x54 callee pops 8B (no add esp);
// callers at 0x00485773; neighbours Drawable share flags.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
void Drawable::rva002728C5(float a, float b)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	DrawModule **head = ((DrawModule **)m_modules[0]);
	if (*head != 0)
		(*head)->slot54(a, b);
	self->m_ac = (a + b) * 0.5f;
}
