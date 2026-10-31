// cl: /MD
// ?rva002761F3@Drawable@@QAEXPBH0@Z @0x002761F3 48B: set pendingClear at +0x2A4 and pendingSet at +0x2F0 from 19-dword masks then apply with immediate true.
// Evidence: callee Drawable_rva00274176.cpp layout plus rowed 0x00274176 via caller 0x000BFC16; rep movsd 0x13.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
class BfmeDrawableClientIface
{
public:
	virtual void replaceModelConditionState(const void *state, bool immediate, int effect);
};

void Drawable::rva002761F3(const int *a, const int *b)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	self->m_pendingClear = *(const Rva00271C8A *)a;
	self->m_pendingSet = *(const Rva00271C8A *)b;
	rva00274176(true);
}
