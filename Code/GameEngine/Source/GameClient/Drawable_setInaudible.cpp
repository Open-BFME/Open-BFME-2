// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?setInaudible@Drawable@@QAEXXZ, retail 0x00274401, 68 bytes.
// Drawable conditional reset plus array notify: if +0x44a flag set clear it
// then rowed Rva002714CA release plus rowed Drawable stopAmbientSound audio clear
// then walk the +0x154 null-terminated element list calling slot 0x30 get
// then slot 4 notify when present.
// Evidence: packet disasm plus chain callees 0x002714CA and 0x002743D7 plus
// neighbour Drawable_rva00274176 TU and flags plus loop precedent rva00274445.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
class Rva002714CA
{
public:
	void rva002714CA();
private:
	unsigned char m_pre[0x148]; // +0x00
	unsigned int m_handle; // +0x148
};

class ElemB274401
{
public:
	virtual void _00() = 0;
	virtual void slot1() = 0;
};

class ElemA274401
{
public:
	virtual void _00() = 0;
	virtual void _01() = 0;
	virtual void _02() = 0;
	virtual void _03() = 0;
	virtual void _04() = 0;
	virtual void _05() = 0;
	virtual void _06() = 0;
	virtual void _07() = 0;
	virtual void _08() = 0;
	virtual void _09() = 0;
	virtual void _10() = 0;
	virtual void _11() = 0;
	virtual ElemB274401 *slot12() = 0;
};

void Drawable::setInaudible()
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	if (!self->m_44A)
		return;
	self->m_44A = false;
	((Rva002714CA *)this)->rva002714CA();
	stopAmbientSound();
	for (ElemA274401 **p = ((ElemA274401 **)m_modules[2]); p != 0; ++p) {
		ElemA274401 *a = *p;
		if (a == 0)
			return;
		ElemB274401 *b = a->slot12();
		if (b != 0)
			b->slot1();
	}
}
