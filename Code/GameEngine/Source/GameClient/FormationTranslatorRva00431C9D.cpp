// cl: /MD /O1 /ICode/Libraries/Include/Lib
//
// ?rva00431C9D@WaitForSecondButtonDownStateHandler@FormationTranslator@@QAEHPAVGameMessage@@@Z
// @0x00431C9D (445B): the formation drag-start state handler's second
// button-down step. WorldBuilder shape (bool flags, no gotos): phase3 starts
// true and is cleared when the in-game UI's selection slot 48 reports a state
// other than 0/0xA, or (no such state) when the client's slot c18 does not
// report the drawable as 0x42F; phase2 is raised only when phase3 is down and
// the drawable's template field +0x53C is below 360. Phase 3 reads the
// formation assistant (rowed 0x00422CF3, a thiscall that ignores ecx) before
// converting the cursor to terrain and handing it to slot 49; phase 2 hands it
// to 0x0029A9FF; both end in the 8-byte helper new for the stored drag state.
// Anything else restarts the handler and returns 0.
// FormationTranslator::WaitForSecondButtonDownStateHandler::Restart (WorldBuilder name, FormationTranslator.cpp lines 373..378: re-emits the stored pixel and ints and pushes a new 8B state).
// ?rva00431C35@Rva00431C35@@QAEXPAX@Z @0x00431C35 104B: thiscall method emitting GameMessage via MessageStream slot 0x4c then helper new 8B with vtable 0x0083C97C plus final Rva00575674 call. Evidence: unlock lane; MessageStreamSubsystem global 0x00A00950; rowed appendPixel 0x0030F9D8 appendInteger 0x0030F936 new 0x0002FDA0 rva00575674 0x00575674; vtables g_00C3C97C; callers 0x00431CB7 0x00431E4D 0x004320A4.
#include "ICoord2D.h"
#include "Coord3D.h"

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

extern class MessageStream *TheMessageStream;
extern "C" const void *const __identifier("??_7Rva004318FC@@6B@")[];

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
#include "../../Include/Common/Rva00575674.h"

#include "../../Include/GameClient/FormationTranslator.h"
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

#include <new>

void FormationTranslator::WaitForSecondButtonDownStateHandler::Restart(void *message)
{
	Rva00431C35Param *par = (Rva00431C35Param *)message;
	int prevMessage = par->m_08;
	GameMessage *msg = TheMessageStream->v19(m_08, prevMessage);
	msg->appendPixelArgument(m_0C);
	msg->appendIntegerArgument(m_14);
	msg->appendIntegerArgument(m_18);
	void *mem = operator new(8);
	Rva00431C35Helper *h;
	if (mem != 0)
	{
		h = (Rva00431C35Helper *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)__identifier("??_7Rva004318FC@@6B@");
	}
	else
	{
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
}

// ?rva00431C9D@WaitForSecondButtonDownStateHandler@FormationTranslator@@QAEHPAVGameMessage@@@Z @0x00431C9D 445B

class Drawable
{
public:
	const Coord3D *getPosition() const;
	char m_pad[0xFC];
	struct FcOuter *m_fc;
};

#include "../../Include/GameClient/View.h"

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
class GameClient;
extern GameClient *TheGameClient;
extern "C" const void *const __identifier("??_7Rva004319C2@@6B@")[];

#include "../../Include/Common/Rva0029AA3F.h"

unsigned int __cdecl Rva0030F099(bool v);
class Rva0022AD10Subsystem { public: bool rva00422CF3HasOne(void *p); };
extern Rva0022AD10Subsystem *TheFormationAssistant;

struct MouseDragStateHandler
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
	ICoord2D pixel = m_0C;
	Coord3D out;
	bool phase3 = true;
	bool phase2 = false;
	bool b = TheInGameUI->m_8B8;
	unsigned int mode = Rva0030F099(b);
	b = TheInGameUI->m_8B8;
	Drawable *draw = TheTacticalView->pickDrawable(&pixel, b, mode);
	Slot48Ret *slot48Ret = TheInGameUI->slot48();
	if (slot48Ret != 0 && slot48Ret->m_14 != 0 && slot48Ret->m_14 != 0xA)
	{
		phase3 = false;
	}
	else if (draw != 0)
	{
		if (((ClientFrameSubsystem *)TheGameClient)->c18(draw, draw->getPosition(), 2) != 0x42F)
			phase3 = false;
	}
	if (!phase3 && draw != 0)
	{
		if (TheInGameUI->slot70() > 0 && draw->m_fc != 0)
		{
			if (*(float *)((char *)draw->m_fc->m_04 + 0x53C) < 360.0f)
				phase2 = true;
		}
	}
	if (phase3)
	{
		if (TheInGameUI->slot70() > 0 && TheFormationAssistant->rva00422CF3HasOne(TheInGameUI->slot73()))
		{
			TheTacticalView->screenToTerrain(&pixel, &out, false);
			TheInGameUI->slot49(&out);
		}
		else
		{
			Restart(msg);
			return 0;
		}
	}
	else if (phase2)
	{
		TheTacticalView->screenToTerrain(&pixel, &out, false);
		((Rva0029AA3F *)TheInGameUI)->rva0029A9FF(&out);
	}
	else
	{
		Restart(msg);
		return 0;
	}
	void *mem = operator new(8);
	MouseDragStateHandler *h;
	if (mem != 0)
	{
		h = (MouseDragStateHandler *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)__identifier("??_7Rva004319C2@@6B@");
	}
	else
	{
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
	return 1;
}
