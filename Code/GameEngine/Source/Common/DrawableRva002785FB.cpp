// cl: /MD
//
// ?rva002785FB@Drawable@@QAEX_N@Z retail 0x002785FB 49B Drawable bool setter +0x448
// true: Host 0x002783F6 with 0 then rowed Drawable::rva002784EB
// false: rowed Drawable::stopAmbientSound then rowed Rva002714CA::rva002714CA
// LINK BONUS names this mangling; callers 0x0029577E 0x002957CB 0x003BA967.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "../GameClient/DrawableFieldsView.h"
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

class Rva002714CA
{
public:
	void rva002714CA();
private:
	unsigned char m_pre[0x148]; // +0x00
	unsigned int m_handle; // +0x148
};

void Drawable::rva002785FB(bool v)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	self->m_448 = v;
	if (v)
	{
		((Rva002783F6Host *)this)->rva002783F6(0);
		rva002784EB();
	}
	else
	{
		stopAmbientSound();
		((Rva002714CA *)this)->rva002714CA();
	}
}
