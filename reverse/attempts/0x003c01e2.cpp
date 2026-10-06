// ?Rva003C01E2Do@@YGXPBVAsciiString@@0@Z
// partial score=0.983 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva003C01E2Do@@YGXPBVAsciiString@@0@Z @0x003C01E2 294B (dump range 18).
// Team-to-team wiring: two team-name copies, getTeamNamed both, bail unless
// both non-null and different; compare controlling players, adopt t2's when
// different through the pinned Team 0x0039D97E member; up to 3 outer passes
// rebuilding the member iterator (rowed 0x00263864/0x00263526), emitting the
// rowed Object 0x00298AE4 member plus the rowed cdecl 0x003BA83F helper for
// members whose +0x274 chain is null or flag-clear; then the rowed Team
// first member 0x0039E8EB or the rowed Team 0x003A10FE zero member; finally
// deposit bytes on t2. Flag/extra identities unproven.
#include "ascii_string.h"

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Player;
class Object;

struct Rva003C01E2FlagInner
{
	char m_pad[0x115];
	unsigned char m_f115;
};

struct Rva003C01E2Flag
{
	char m_pad[4];
	Rva003C01E2FlagInner *m_p04;
};

class Object
{
public:
	void rva00298AE4(struct Team *team);
	char m_pad00[0x274 - 0];
	Rva003C01E2Flag *m_p274; // +0x274
};

class Team;

class Player
{
public:
	char m_pad[1];
};

class Team
{
public:
	Player *getControllingPlayer() const;
	void rva0039D97E(Player *player);
	Object *rva0039E8EB();
	void rva003A10FE(int v);
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	char m_pad[0x5D];
	unsigned char m_5d;
	unsigned char m_5e;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

void __cdecl rva003BA83F(void *obj, int v);

void __stdcall Rva003C01E2Do(const AsciiString *str1, const AsciiString *str2)
{
	Team *t1 = TheScriptEngine->getTeamNamed(*str1, false);
	Team *t2 = TheScriptEngine->getTeamNamed(*str2, true);
	if (t1 == 0)
		return;
	if (t2 == 0)
		return;
	if (t1 == t2)
		return;
	Player *p2 = t2->getControllingPlayer();
	Player *p1 = t1->getControllingPlayer();
	if (p1 != p2) {
		Player *p2again = t2->getControllingPlayer();
		t1->rva0039D97E(p2again);
	}
	int tries = 3;
	do {
		DLINK_ITERATOR<Object> iter = t1->iterate_TeamMemberList();
		Object *first = iter.cur();
		if (first == 0)
			break;
		Object *obj = first;
		do {
			obj = first;
			first = iter.cur();
			iter.advance();
			Rva003C01E2Flag *f = obj->m_p274;
			if (f == 0 || (f->m_p04->m_f115 & 0x20) == 0) {
				obj->rva00298AE4(t2);
				rva003BA83F(obj, 0);
			}
		} while (iter.cur() != 0);
		if (first == 0)
			break;
		first->rva00298AE4(t2);
		rva003BA83F(first, 0);
		Object *mem = t1->rva0039E8EB();
		if (mem == 0) {
			t1->rva003A10FE(0);
			break;
		}
	} while (--tries > 0);
	if (t2->m_5d == 0) {
		t2->m_5e = 1;
		t2->m_5d = 1;
	}
}
