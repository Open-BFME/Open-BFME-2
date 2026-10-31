// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// ?LoadPostProcess@Drawable@@UAEXXZ 0x002717BC 47B
// Slot 1 of Drawable's Snapshot sub-vtable 0x00BFB0A4 (the canonical
// LoadPostProcess slot); Zero Hour Drawable::loadPostProcess likewise restores
// the transform from the bound object.
// Retail: if the Thing* at +0x9c is set, Thing::setTransformMatrix on the
// base at this-0x60 gets that Thing's matrix (+8). Then the module pointer
// at +0x3f0 is tail-called through vslot +4. WB debug uses +0x10 / this-0x68;
// retail displacements are +8 and -0x60.
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
class Rva002717BCModule {
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
};
void Drawable::LoadPostProcess()
{
	if (m_object)
		setTransformMatrix(((Thing *)m_object)->getTransformMatrix());
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	if (self->m_buffManager)
		((Rva002717BCModule *)self->m_buffManager)->slot4();
}
