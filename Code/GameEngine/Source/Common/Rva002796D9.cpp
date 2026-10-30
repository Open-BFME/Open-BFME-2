// cl: /O1 /MD
// 0x00273808 (drawAmmo), 0x00273F74, 0x00277669 and 0x002778E1 are rowed on Drawable.
#include "../../Include/GameClient/DrawableBFME2.h"
class Rva0027601BHost
{
public:
	void rva0027601B();
};
class Rva00277C42Host
{
public:
	void rva00277C42();
};
class Rva002779CEHost
{
public:
	void drawConstructPercent();
};
class Rva00275F3FHost
{
public:
	void rva00275F3F();
};
class Rva00279074Host
{
public:
	void rva00279074();
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
