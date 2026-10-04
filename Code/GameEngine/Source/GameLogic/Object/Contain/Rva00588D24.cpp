// cl: /O1 /DNDEBUG /MD
// ?rva00588D24@Rva0047A040Base9E0@@QAE_NPAXPAVObject@@@Z @0x00588D24 117B
// Evidence: unlock lane, caller 0x00479ADA lea ecx [esi+0x9E0] (HordeGarrisonContain second base),
// pin rva00588BF3 member of Rva0047A040Base9E0, slots 0x20/0xF4/0x100,
// globals TheGameLogic and g_bfmeWorldRV, callers 0x00477315 and 0x00479AE8.
class Object;

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class ContainEntry
{
public:
	SLOT08(e00,e01,e02,e03,e04,e05,e06,e07)
	virtual void slot20(Object *obj);
	SLOT08(e09,e10,e11,e12,e13,e14,e15,e16)
	SLOT08(e17,e18,e19,e20,e21,e22,e23,e24)
	SLOT08(e25,e26,e27,e28,e29,e30,e31,e32)
	SLOT08(e33,e34,e35,e36,e37,e38,e39,e40)
	SLOT08(e41,e42,e43,e44,e45,e46,e47,e48)
	SLOT08(e49,e50,e51,e52,e53,e54,e55,e56)
	virtual void e57(); virtual void e58(); virtual void e59(); virtual void e60();
	virtual bool slotF4();
	virtual void e62(); virtual void e63();
	virtual void slot100(void *a);
};

class GameLogic
{
public:
	char _00[0x40];
	void *m_40;
};
extern GameLogic *TheGameLogic;

struct BfmeWorldRV
{
	char _00[0x28];
	unsigned char m_28;
};
extern struct BfmeWorldRV *g_bfmeWorldRV;

class Rva0047A040Base9E0
{
public:
	void *rva00588BF3(void *a, Object *b);
	bool rva00588D24(void *a, Object *b);
};

bool Rva0047A040Base9E0::rva00588D24(void *a, Object *b)
{
	ContainEntry *e = (ContainEntry *)rva00588BF3(a, b);
	if (e == 0)
		return false;
	if (!e->slotF4()) {
		e->slot20(b);
		e->slot100(TheGameLogic->m_40);
		if (e->slotF4()) {
			g_bfmeWorldRV->m_28 = 1;
			e->slot100(0);
		}
		return true;
	}
	e->slot100(0);
	return false;
}
