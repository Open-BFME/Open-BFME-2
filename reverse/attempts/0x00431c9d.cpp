// ?rva00431C9D@WaitForSecondButtonDownStateHandler@FormationTranslator@@QAEHPAVGameMessage@@@Z
// partial score=0.93 date=2026-10-07
// cl: /MD
// FormationTranslator::WaitForSecondButtonDownStateHandler::Restart (WorldBuilder name, FormationTranslator.cpp lines 373..378: re-emits the stored pixel and ints and pushes a new 8B state).
// ?rva00431C35@Rva00431C35@@QAEXPAX@Z @0x00431C35 104B: thiscall method emitting GameMessage via MessageStream slot 0x4c then helper new 8B with vtable 0x0083C97C plus final Rva00575674 call. Evidence: unlock lane; MessageStreamSubsystem global 0x00A00950; rowed appendPixel 0x0030F9D8 appendInteger 0x0030F936 new 0x0002FDA0 rva00575674 0x00575674; vtables g_00C3C97C; callers 0x00431CB7 0x00431E4D 0x004320A4.
struct ICoord2D
{
	int m_x;
	int m_y;
};

class GameMessage
{
public:
	void appendPixelArgument(const ICoord2D &v);
	void appendIntegerArgument(int v);
};

class MessageStream
{
public:
	virtual void _d00(); virtual void _d01(); virtual void _d02(); virtual void _d03();
	virtual void _d04(); virtual void _d05(); virtual void _d06(); virtual void _d07();
	virtual void _d08(); virtual void _d09(); virtual void _d10(); virtual void _d11();
	virtual void _d12(); virtual void _d13(); virtual void _d14(); virtual void _d15();
	virtual void _d16(); virtual void _d17();
	virtual GameMessage *createMessage(int type);
	virtual GameMessage *v19(int a, int b);
};

extern MessageStream *MessageStreamSubsystem;
extern const void *const g_00C3C97C[];

struct Rva00431C35Helper
{
	void *m_vptr;
	void *m_parent;
};

struct Rva00431C35Param
{
	int m_00;
	int m_04;
	int m_08;
};

class Object;
class Rva00575674
{
public:
	void rva00575674(Object *o);
};

class FormationTranslator
{
public:
	class WaitForSecondButtonDownStateHandler;
};
class FormationTranslator::WaitForSecondButtonDownStateHandler
{
	void *m_00;
	void *m_04;
	int m_08;
	ICoord2D m_0C;
	int m_14;
	int m_18;
public:
	void Restart(void *p);
	int rva00431C9D(GameMessage *msg);
};

void *__cdecl operator new(unsigned int size);

void FormationTranslator::WaitForSecondButtonDownStateHandler::Restart(void *p)
{
	Rva00431C35Param *par = (Rva00431C35Param *)p;
	int v = par->m_08;
	GameMessage *msg = MessageStreamSubsystem->v19(m_08, v);
	msg->appendPixelArgument(m_0C);
	msg->appendIntegerArgument(m_14);
	msg->appendIntegerArgument(m_18);
	void *mem = operator new(8);
	Rva00431C35Helper *h;
	if (mem != 0)
	{
		h = (Rva00431C35Helper *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)g_00C3C97C;
	}
	else
	{
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
}

// ?rva00431C9D@WaitForSecondButtonDownStateHandler@FormationTranslator@@QAEHPAVGameMessage@@@Z @0x00431C9D 445B
struct Coord3D
{
	float m_x;
	float m_y;
	float m_z;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
	char m_pad[0xFC];
	struct FcOuter *m_fc;
};

class View
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08();
	virtual BFMERopeDrawable *s09(const ICoord2D *a, bool b, unsigned int c);
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
	virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
	virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
	virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
	virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
	virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
	virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
	virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
	virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65();
	virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69();
	virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73();
	virtual void s74(); virtual void s75(); virtual void s76(); virtual void s77();
	virtual void s78(); virtual void s79(); virtual void s80(); virtual void s81();
	virtual void s82(); virtual void s83(); virtual void s84(); virtual void s85();
	virtual void s86(); virtual void s87(); virtual void s88(); virtual void s89();
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);
};

struct Slot48Ret
{
	char m_pad[0x14];
	int m_14;
};

struct FcInner
{
	char m_pad[0x04];
	void *m_04;
};

struct FcOuter
{
	char m_pad[0x04];
	FcInner *m_04;
};

struct DrawWrap
{
	char m_pad[0xFC];
	FcOuter *m_fc;
};

class InGameUI
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual Slot48Ret *slot48();
	virtual void slot49(Coord3D *p);
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
	virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
	virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
	virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65();
	virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69();
	virtual int slot70();
	virtual void s71(); virtual void s72();
	virtual void *slot73();
	char m_pad2[0x8B8 - 4];
	bool m_8B8;
};

class ClientFrameSubsystem
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
	virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
	virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
	virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
	virtual void c16(); virtual void c17();
	virtual int c18(void *a, const Coord3D *b, int c);
};

extern InGameUI *TheInGameUI;
extern View *TheTacticalView;
extern ClientFrameSubsystem *TheGameClient;
extern const void *const g_00C3C9A0[];
extern void *g_00E03160;

class Rva0029AA3F
{
public:
	void rva0029A9FF(const Coord3D *src);
};

unsigned int __cdecl Rva0030F099(bool v);
bool __stdcall rva00422CF3HasOne(void *p);

struct Rva00431C9DHelper
{
	void *m_vptr;
	void *m_parent;
};

int FormationTranslator::WaitForSecondButtonDownStateHandler::rva00431C9D(GameMessage *msg)
{
	if (TheInGameUI->m_8B8)
	{
		Restart(msg);
		return 0;
	}
	ICoord2D tmp = m_0C;
	bool b = TheInGameUI->m_8B8;
	unsigned int mode = Rva0030F099(b);
	b = TheInGameUI->m_8B8;
	BFMERopeDrawable *draw = TheTacticalView->s09(&tmp, b, mode);
	Slot48Ret *v = TheInGameUI->slot48();
	Coord3D out;
	if (v != 0)
	{
		int t = v->m_14;
		if (t != 0)
		{
			if (t != 0xA)
				goto phase2;
		}
	}
	if (draw == 0)
		goto phase3;
	if (TheGameClient->c18(draw, draw->getPosition(), 2) == 0x42F)
		goto phase3;
phase2:
	if (draw == 0)
		goto fail;
	if (TheInGameUI->slot70() <= 0)
		goto fail;
	if (draw->m_fc == 0)
		goto fail;
	if (!(*(float *)((char *)draw->m_fc->m_04 + 0x53C) < 360.0f))
		goto fail;
	TheTacticalView->screenToTerrain(&tmp, &out, false);
	((Rva0029AA3F *)TheInGameUI)->rva0029A9FF(&out);
make:
	{
		void *mem = operator new(8);
		Rva00431C9DHelper *h;
		if (mem != 0)
		{
			h = (Rva00431C9DHelper *)mem;
			h->m_parent = m_04;
			h->m_vptr = (void *)g_00C3C9A0;
		}
		else
		{
			h = 0;
		}
		Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
		q->rva00575674((Object *)h);
		return 1;
	}
phase3:
	if (TheInGameUI->slot70() <= 0)
		goto fail;
	{
		void *w = TheInGameUI->slot73();
		if (!rva00422CF3HasOne(w))
			goto fail;
	}
	TheTacticalView->screenToTerrain(&tmp, &out, false);
	TheInGameUI->slot49(&out);
	goto make;
fail:
	Restart(msg);
	return 0;
}
