// cl: /DNDEBUG /MD /EHsc
// ?rva00273648@Drawable@@QAEX PAX@Z @0x00273648 34B: Drawable module walk at +0x14c calling slot 0xEC; callers 0x00275F24 0x00275F33; unblocks 0x00275DCE.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
class Rva00270025
{
public:
	void rva0027006C(int v);
};

void Drawable::rva00273648(void* arg)
{
	DrawModule** mods = ((DrawModule **)m_modules[0]);
	while (*mods != 0) {
		(*mods)->slotEC(arg);
		++mods;
	}
}

void Drawable::rva00273686(bool arg)
{
	DrawModule** mods = ((DrawModule **)m_modules[0]);
	while (*mods != 0) {
		(*mods)->slotE8(arg);
		++mods;
	}
}

void Drawable::rva002736A8()
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	if (self->m_iconInfo != 0)
		self->m_iconInfo->rva0027006C(10);
}

void Drawable::rva0027366A()
{
	DrawModule** mods = ((DrawModule **)m_modules[0]);
	while (*mods != 0) {
		(*mods)->slotE4();
		++mods;
	}
}
