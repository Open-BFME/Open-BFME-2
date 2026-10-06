// cl: /O1 /DNDEBUG /MD
// ?rva00479B3A@Rva00479B3A@@QAEXPAVObject@@@Z @ 0x00479B3A (69B).
// Garrison chain plus drawable reset plus object touch. Evidence: +0x20
// GarrisonContain pinned 0x00478D0A with Object arg; Thing getDrawable row;
// Rva00270260 bool row cmp 1; Rva002716Holder 0 row; Object +0x454 byte gate
// plus Object pinned 0x0028DCC4; ret 4 single Object arg; neighbours
// VslotSmallBodiesW /O1 and HordeGarrisonContainRva00479B7F /O1.
class Object;
class Drawable;

class Thing
{
public:
	Drawable *getDrawable() const;
};

class GarrisonContain
{
public:
	virtual void rva00464D02(Object *obj);
};

class Rva00270260
{
public:
	bool rva00270260();
};

class Rva002716Holder
{
public:
	void rva00271601(unsigned char val);
};

class Object
{
public:
	void rva0028DCC4();
	char m_pad00[0x454];
	unsigned char m_454;
};

class Rva00479B3A
{
public:
	void rva00479B3A(Object *obj);
private:
	char m_pad00[0x20];
	GarrisonContain m_20;
};

void Rva00479B3A::rva00479B3A(Object *obj)
{
	((GarrisonContain *)((char *)this + 0x20))->GarrisonContain::rva00464D02(obj);
	Drawable *d = ((Thing *)obj)->getDrawable();
	if (d && ((Rva00270260 *)d)->rva00270260() == 1)
		((Rva002716Holder *)d)->rva00271601(0);
	if (obj->m_454 == 0)
		obj->rva0028DCC4();
}
