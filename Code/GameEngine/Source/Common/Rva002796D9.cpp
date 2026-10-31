// cl: /O1 /MD
// 0x00273808 (drawAmmo), 0x00273F74, 0x00277669 and 0x002778E1 are rowed on Drawable.
#include "../../Include/GameClient/DrawableBFME2.h"
class Rva0027601BHost
{
public:
	void rva0027601B();
};
class DisplayString;
class Rva00277C42Host
{
public:
	void rva00277C42();
	char m_pad00[0x344];
private:
	DisplayString *m_captionDisplayString; // +0x344
};
class Object;
class Rva002779CEHost
{
public:
	void drawConstructPercent();
	Object *getObject() const { return m_object; }
	char m_pad00[0xFC];
private:
	Object *m_object; // +0xFC
	char m_pad100[0x23C];
	float m_lastConstructDisplayed; // +0x33C
	DisplayString *m_constructDisplayString; // +0x340
};
struct DrawableDisabledObjectView;
class Rva00270025;
class Rva00275F3FHost
{
public:
	void rva00275F3F();
private:
	unsigned char unreconstructed000[0xFC]; // +0x00
	DrawableDisabledObjectView *object; // +0xFC
	unsigned char unreconstructed100[0x354 - 0x100]; // +0x100
	Rva00270025 *iconInfo; // +0x354
	unsigned char unreconstructed358[0x460 - 0x358]; // +0x358
	int screenLeft; // +0x460
	int screenTop; // +0x464
	int screenRight; // +0x468
	int screenBottom; // +0x46C
};
class Rva00279074Host
{
public:
	void rva00279074();
	char m_pad00[0xFC];
private:
	Object *m_object; // +0xFC
};
class Rva00273C47Host
{
public:
	void rva00273C47();
};
class Rva002796D9Host
{
public:
	void drawIconLayer(int v);
};
// ?drawIconLayer@Rva002796D9Host@@QAEXH@Z
void Rva002796D9Host::drawIconLayer(int v)
{
	switch (v)
	{
	case 0:
		((Rva0027601BHost *)this)->rva0027601B();
		((Drawable *)this)->rva00273755();
		((Rva00277C42Host *)this)->rva00277C42();
		((Rva002779CEHost *)this)->drawConstructPercent();
		break;
	case 1:
		((Drawable *)this)->rva00273F74();
		((Rva00275F3FHost *)this)->rva00275F3F();
		((Drawable *)this)->drawAmmo();
		((Drawable *)this)->rva00277669();
		break;
	case 2:
		((Rva00279074Host *)this)->rva00279074();
		break;
	case 3:
		((Rva00273C47Host *)this)->rva00273C47();
		break;
	case 4:
		return;
	case 5:
		((Drawable *)this)->rva002778E1();
		break;
	default:
		break;
	}
}
