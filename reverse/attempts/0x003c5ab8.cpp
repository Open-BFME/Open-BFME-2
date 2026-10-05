// ?Rva003C5AB8Do@@YGXABVAsciiString@@0_NH@Z
// partial score=0.75 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C5AB8Do@@YGXABVAsciiString@@0_NH@Z @0x003C5AB8 433B: team-member closest-by-+0x74 with drawable player message audio tactical. Evidence: rowed getTeamNamed 0x3584E9 StringBase copy 0x365F0 iterate 0x263864 advance 0x263526 compare 0x69D6 getDrawable 0x5508E2 getControllingPlayer 0x28AFA9 appendBoolean 0x30F963 appendObjectID 0x30F979 BfmeAudioEventPrefix136 0x2D97D6 DwordSlot set 0x33F15D tail dtor 0x2D9A43 Release_Ref 0x50ED3 g_Va009FE16C ThePlayerList MessageStreamSubsystem TheInGameUI TheAudio TheTacticalView; caller 0x003CD0D6; ret 0x10 stdcall.
#include "ascii_string.h"

class Parameter;
class Drawable;
class Player;
class Object
{
public:
	char m_pad00[0x38];
	float m_38, m_3C, m_40;
	char m_pad44[0x64 - 0x44];
	AsciiString m_name64;
	int m_id74;
	const AsciiString *rva00290E67() const;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
};
class Team;
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool flag);
};
extern ScriptEngine *g_Va009FE16C;

struct DLINK_ITERATOR_Node
{
	DLINK_ITERATOR_Node *m_next;
	Object *m_obj;
};
struct DLINK_ITERATOR_Object
{
	DLINK_ITERATOR_Node *m_cur;
};
class Team2
{
public:
	DLINK_ITERATOR_Object iterate_TeamMemberList() const;
};
class Rva001705A0DlinkIterator
{
public:
	void advance();
};

class PlayerList
{
public:
	char m_pad[0x10];
	Player *m_local10;
};
extern PlayerList *ThePlayerList;

class GameMessage
{
public:
	void appendBooleanArgument(bool b);
	void appendObjectIDArgument(int id);
};

class MessageStream
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17();
	virtual GameMessage *s18(int v);
};
extern MessageStream *MessageStreamSubsystem;

class InGameUI
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(Drawable *d);
};
extern InGameUI *TheInGameUI;

struct OpaqueRefElement4
{
	char data[8];
};
class AudioManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(OpaqueRefElement4 *o, int v);
	virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
	virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
	virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45();
	virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(OpaqueRefElement4 *o);
};
extern AudioManager *TheAudio;

class BfmeAudioEventPrefix136
{
public:
	BfmeAudioEventPrefix136(const OpaqueRefElement4 &o, int v);
	void set(int v);
	~BfmeAudioEventPrefix136();
};
class TacticalView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(float *p, float a, float b, int c, int d, int e, float *q);
};
extern TacticalView *TheTacticalView;

// ?Rva003C5AB8Do@@YGXABVAsciiString@@0_NH@Z present-unmatched
void __stdcall Rva003C5AB8Do(const AsciiString &teamName, const AsciiString &typeName, bool doCamera, int audioArg)
{
	Team2 *team = (Team2 *)g_Va009FE16C->getTeamNamed((AsciiString)teamName, false);
	if (team == 0)
		return;
	DLINK_ITERATOR_Object it = team->iterate_TeamMemberList();
	Object *best = 0;
	for (DLINK_ITERATOR_Node *cur = it.m_cur; cur != 0; )
	{
		Object *o = cur->m_obj;
		if (o != 0)
		{
			const StringBase<char> &on = (const StringBase<char> &)o->m_name64;
			if (on.compare((const StringBase<char> &)typeName) == 0)
			{
				if (best == 0 || o->m_id74 < best->m_id74)
					best = o;
			}
		}
		((Rva001705A0DlinkIterator *)&it)->advance();
		cur = it.m_cur;
		if (cur == 0)
			break;
	}
	if (best == 0)
		return;
	Drawable *d = best->getDrawable();
	if (d == 0)
		return;
	if (best->getControllingPlayer() == ThePlayerList->m_local10)
	{
		GameMessage *msg = MessageStreamSubsystem->s18(0x3E9);
		msg->appendBooleanArgument(true);
		msg->appendObjectIDArgument(best->m_id74);
		TheInGameUI->s66(d);
	}
	OpaqueRefElement4 ref;
	TheAudio->s25(&ref, audioArg);
	BfmeAudioEventPrefix136 ev(ref, 0);
	ev.set(ThePlayerList->m_local10 ? *(int *)((char *)ThePlayerList->m_local10 + 0x54) : 0);
	TheAudio->s50((OpaqueRefElement4 *)&ev);
	if (doCamera)
	{
		float cx = best->m_38;
		float cy = best->m_3C;
		float cz = best->m_40;
		float zero = 0.0f;
		float pos[3];
		pos[0] = cx; pos[1] = cy; pos[2] = cz;
		TheTacticalView->s24(pos, zero, zero, 0, 0, 0, pos);
	}
}
