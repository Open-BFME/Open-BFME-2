// cl: /DNDEBUG /MD
//
// ?rva00278C6B@Drawable@@QAEXXZ @0x00278C6B 17B: Drawable flag check at +0x44B,
// calls pinned Host 0x002783F6 with 0 when set. Evidence: packet disasm,
// neighbour Drawable flag cluster +0x447/+0x448/+0x44A/+0x44B, same Host call
// shape as Drawable::setAudible and Drawable::rva002785FB, caller 0x0023F52C.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
class Object;
class Rva002783F6Host
{
public:
	void rva002783F6(int v);
	void rva00278341(int query, int v); // 0x00278341
	char m_pad00[0xFC];
private:
	Object *m_object; // +0xFC
	char m_pad100[0x347];
	unsigned char m_x447; // +0x447
	unsigned char m_x448; // +0x448
	char m_pad449[0x1];
	unsigned char m_x44A; // +0x44A
	char m_pad44B[0x1];
};

void Drawable::rva00278C6B()
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	if (self->m_44B != 0)
		((Rva002783F6Host *)this)->rva002783F6(0);
}
