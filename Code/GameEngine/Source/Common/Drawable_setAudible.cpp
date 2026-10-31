// cl: /MD
//
// ?setAudible@Drawable@@QAEXXZ retail 0x00278644 69B Drawable one-shot
// audio trigger: +0x44A flag once via rowed Drawable::rva002784EB then Host
// 0x002783F6 with 0, then walk null-terminated +0x154 table calling vslot
// 0x30 and vslot 0. Caller 0x002900A9; LINK names no new pin.

#include "../../Include/GameClient/DrawableBFME2.h"
class Rva00278644Item
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11)
#undef V
	virtual void *slot12();
};

class Rva00278644Inner
{
public:
	virtual void slot0();
};

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

void Drawable::setAudible()
{
	unsigned char *flag = (unsigned char *)this + 0x44A;
	if (*flag != 0)
		return;
	*flag = 1;
	rva002784EB();
	((Rva002783F6Host *)this)->rva002783F6(0);
	Rva00278644Item **list = ((Rva00278644Item **)m_modules[2]);
	while (list != 0)
	{
		Rva00278644Item *item = *list;
		if (item == 0)
			return;
		void *p = item->slot12();
		if (p != 0)
			((Rva00278644Inner *)p)->slot0();
		list++;
	}
}
