// ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z
// partial score=0.94 date=2026-10-04
// cl: /O1 /MD
// ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z @0x004320B1 160B: thiscall dispatcher on GameMessage+0x10 for 3 vs 6/0x10 via rowed Rva00431A4D Rva00431E95 plus TacticalView screenToTerrain and InGameUI slots. Evidence: chain via 0x00431E95; globals TheTacticalView TheInGameUI; rowed getArgument 0x0030F4EA rva0029AA27 0x0029AA27; prev Rva00431F61Ctor next Rva0043216DCtor same dir.
// RESIDUE (159B vs retail 160B, first diff +0x6): the register PAIR, not a
// missing push. Retail allocates msg->edx (8b 55 08 / 8b 42 10) and this->esi
// (56 8b f1); /O1 allocates msg->esi and this->edi, and every downstream push
// and mov follows the swap. Body v1 below is the banked shape; v2..v6 are the
// lever sweep and are byte-identical to it. See re_attempts.log row.
#include <stddef.h>

struct ICoord2D { int m_x; int m_y; };
struct Coord3D { float m_x; float m_y; float m_z; };

union GameMessageArgumentType
{
	int integer;
	struct Pix { int x; int y; } pixel;
};

class GameMessage
{
public:
	char m_pad[0x10];
	int m_10;
};

class Rva00431A4D
{
public:
	void rva00431A4D(GameMessage *msg);
};

class Rva00431E95
{
public:
	int rva00431E95(void *p);
};

class TacticalView
{
public:
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);
	virtual void f02(); virtual void f03(); virtual void f04(); virtual void f05();
	virtual void f06(); virtual void f07(); virtual void f08(); virtual void f09();
	virtual void f0a(); virtual void f0b(); virtual void f0c(); virtual void f0d();
	virtual void f0e(); virtual void f0f(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f1a(); virtual void f1b(); virtual void f1c(); virtual void f1d();
	virtual void f1e(); virtual void f1f(); virtual void f20(); virtual void f21();
	virtual void f22(); virtual void f23(); virtual void f24(); virtual void f25();
	virtual void f26(); virtual void f27(); virtual void f28(); virtual void f29();
	virtual void f2a(); virtual void f2b(); virtual void f2c(); virtual void f2d();
	virtual void f2e(); virtual void f2f(); virtual void f30(); virtual void f31();
	virtual void f32(); virtual void f33(); virtual void f34(); virtual void f35();
	virtual void f36(); virtual void f37(); virtual void f38(); virtual void f39();
	virtual void f3a(); virtual void f3b(); virtual void f3c(); virtual void f3d();
	virtual void f3e(); virtual void f3f(); virtual void f40(); virtual void f41();
	virtual void f42(); virtual void f43(); virtual void f44(); virtual void f45();
	virtual void f46(); virtual void f47(); virtual void f48(); virtual void f49();
	virtual void f4a(); virtual void f4b(); virtual void f4c(); virtual void f4d();
	virtual void f4e(); virtual void f4f(); virtual void f50(); virtual void f51();
	virtual void f52(); virtual void f53(); virtual void f54(); virtual void f55();
	virtual void f56(); virtual void f57(); virtual void f58(); virtual void f59();
	virtual void f5a(); virtual void f5b(); virtual void f5c(); virtual void f5d();
	virtual void f5e(); virtual void f5f(); virtual void f60(); virtual void f61();
	virtual void f62(); virtual void f63(); virtual void f64(); virtual void f65();
	virtual void f66(); virtual void f67(); virtual void f68(); virtual void f69();
	virtual void f6a(); virtual void f6b(); virtual void f6c(); virtual void f6d();
	virtual void f6e(); virtual void f6f(); virtual void f70(); virtual void f71();
	virtual void f72(); virtual void f73(); virtual void f74(); virtual void f75();
	virtual void f76(); virtual void f77(); virtual void f78(); virtual void f79();
	virtual void f7a(); virtual void f7b(); virtual void f7c(); virtual void f7d();
	virtual void f7e(); virtual void f7f(); virtual void f80(); virtual void f81();
	virtual void f82(); virtual void f83(); virtual void f84(); virtual void f85();
	virtual void f86(); virtual void f87(); virtual void f88(); virtual void f89();
};

class InGameUI
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49();
	virtual void slot50(Coord3D *pos);
	virtual bool slot51();
	char m_pad[0x9B4 - 4];
	unsigned char m_9b4;
};

struct S12_0029AA27 { int a; int b; int c; };
class Rva0029AA27
{
public:
	void rva0029AA27(const S12_0029AA27 *src);
};

extern TacticalView *TheTacticalView;
extern InGameUI *TheInGameUI;
extern Rva0029AA27 *TheRva0029AA27;
extern void *g_ks_30f4ea;

TacticalView *TheTacticalView;
InGameUI *TheInGameUI;
Rva0029AA27 *TheRva0029AA27;
void *g_ks_30f4ea;

#define CASE3_BODY \
	const GameMessageArgumentType *a0 = (const GameMessageArgumentType *)g_ks_30f4ea; \
	ICoord2D pixel; \
	pixel.m_x = a0->pixel.x; \
	pixel.m_y = a0->pixel.y; \
	Coord3D world; \
	TheTacticalView->screenToTerrain(&pixel, &world, false); \
	if (TheInGameUI->slot51()) \
		TheInGameUI->slot50(&world); \
	if (TheInGameUI->m_9b4 != 0) \
		TheRva0029AA27->rva0029AA27((const S12_0029AA27 *)&world); \
	return 0;

class C
{
	void *m_00;
	Rva00431A4D *m_04;
public:
	int v1(GameMessage *msg);
	int v2(GameMessage *msg);
	int v3(GameMessage *msg);
	int v4(GameMessage *msg);
	int v5(GameMessage *msg);
	int v6(GameMessage *msg);
};

// v1: switch, thiscall second half via m_00 receiver
int C::v1(GameMessage *msg)
{
	switch (msg->m_10)
	{
	case 3:
	{
		CASE3_BODY
	}
	case 6:
	case 0x10:
		m_04->rva00431A4D(msg);
		return ((Rva00431E95 *)this)->rva00431E95(msg);
	default:
		return 0;
	}
}

// v2: switch, second call through a member of this
int C::v2(GameMessage *msg)
{
	int t = msg->m_10;
	switch (t)
	{
	case 6:
	case 0x10:
		m_04->rva00431A4D(msg);
		return ((Rva00431E95 *)this)->rva00431E95(msg);
	case 3:
	{
		CASE3_BODY
	}
	default:
		return 0;
	}
}

// v3: switch, case 3 body has no global-pointer argument source
int C::v3(GameMessage *msg)
{
	switch (msg->m_10)
	{
	case 3:
	{
		CASE3_BODY
	}
	case 6:
	case 0x10:
	{
		Rva00431A4D *f = m_04;
		f->rva00431A4D(msg);
		return ((Rva00431E95 *)this)->rva00431E95(msg);
	}
	default:
		return 0;
	}
}

// v4: if/else-if chain, 6/16 first
int C::v4(GameMessage *msg)
{
	if (msg->m_10 == 3)
	{
		CASE3_BODY
	}
	if (msg->m_10 == 6 || msg->m_10 == 0x10)
	{
		m_04->rva00431A4D(msg);
		return ((Rva00431E95 *)this)->rva00431E95(msg);
	}
	return 0;
}

// v5: nested switches (outer on 3, inner on 6/0x10)
int C::v5(GameMessage *msg)
{
	switch (msg->m_10)
	{
	case 3:
	{
		CASE3_BODY
	}
	default:
		switch (msg->m_10)
		{
		case 6:
		case 0x10:
			m_04->rva00431A4D(msg);
			return ((Rva00431E95 *)this)->rva00431E95(msg);
		}
		return 0;
	}
}

// v6: case 3 and case 6 share the fallthrough, single exit
int C::v6(GameMessage *msg)
{
	int result = 0;
	switch (msg->m_10)
	{
	case 3:
	{
		CASE3_BODY
	}
	case 6:
	case 0x10:
		m_04->rva00431A4D(msg);
		return ((Rva00431E95 *)this)->rva00431E95(msg);
	default:
		break;
	}
	return result;
}