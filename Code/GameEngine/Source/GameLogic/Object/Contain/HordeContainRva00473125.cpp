// cl: /MD
//
// ?rva00473125@HordeContain@@QAEXPAVObject@@PAHH@Z @0x00473125 114B.
// Identity: HordeContain method (this is HordeContain: callers 0x00473197 and
// 0x00473212 pass HordeContain this; body calls HordeContain::rva0046A893 with
// this and uses the +0x11C second-base interface installed by the pinned
// HordeContain ctor 0x0046F543). Name by address.
// Body: store rider ID (+0x74) through out param; bfmeGoDSU table update;
// toggle drawable selectability off/on around +0x20 slot39 call; notify
// +0x2C8 slot2 with idx+1 and +0x11C slot12; finish via rva0046A893.

class Drawable
{
public:
	void setSelectable(bool selectable);
};

class Thing
{
public:
	Drawable *getDrawable() const;
	unsigned char m_pad[0x74];
	int m_74; // +0x74 ID
};

class Object : public Thing
{
};

class BfmeThingDSU
{
public:
	void bfmeGoDSU(void *what, void *v);
};

class ObjectArg;
class HordeContain20Iface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void slot39(Object *obj);
};

class HordeContain11CIface
{
public:
	virtual void t00();
	virtual void t01();
	virtual void t02();
	virtual void t03();
	virtual void t04();
	virtual void t05();
	virtual void t06();
	virtual void t07();
	virtual void t08();
	virtual void t09();
	virtual void t10();
	virtual void t11();
	virtual void slot12(Object *obj);
};

class HordeContain2C8Iface
{
public:
	virtual void u00();
	virtual void u01();
	virtual void slot02(int idx);
};

class HordeContain
{
public:
	void rva00473125(Object *obj, int *out, int idx);
	void rva0046A893(Object *rider);
	unsigned char m_pad0[0x20];
	HordeContain20Iface m_20; // +0x20 inline subobject with vptr
	unsigned char m_pad20[0x11C - 0x20 - 4];
	HordeContain11CIface m_11C; // +0x11C second base with vptr
	unsigned char m_pad11C[0x2C8 - 0x11C - 4];
	HordeContain2C8Iface *m_2C8; // +0x2C8 pointer to iface
};

void HordeContain::rva00473125(Object *obj, int *out, int idx)
{
	int id = obj->m_74;
	*out = id;
	((BfmeThingDSU *)this)->bfmeGoDSU((void *)id, (void *)idx);
	obj->getDrawable()->setSelectable(false);
	m_20.slot39(obj);
	obj->getDrawable()->setSelectable(true);
	m_2C8->slot02(idx + 1);
	m_11C.slot12(obj);
	rva0046A893(obj);
}
