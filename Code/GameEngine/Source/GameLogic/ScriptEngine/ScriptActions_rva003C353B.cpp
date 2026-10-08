// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Landed from the banked attempt once Zero Hour's null-member skip
// (Object *obj = iter.cur(); if (!obj) continue;) was added to the member
// loop: it keeps the member in ecx from the loop test into the call, the
// mov-test wall the bank recorded.
// ?Rva003C353BDo@@YGXPAVParameter@@PAX@Z @0x003C353B 111B: team teleport-like via getTeamNamed TerrainLogic slot 0x88 iterate and Object rva0029660C. Evidence: single Rva003BD116Set same getUnitNamed slot88 rva0029660C caller 0x003CE7AC; rowed getTeamNamed 0x3584E9 iterate 0x263864 advance 0x263526 pin rva0029660C 0x29660C; caller 0x003CE7CE; ret 0x8 stdcall.
#include "ascii_string.h"

class Object;
class Team;
struct Coord3D { float x, y, z; };

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

class Object
{
public:
	void rva0029660C(const Coord3D *pos, int flag);
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern class ScriptEngine *TheScriptEngine;

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual void *s34(void *p);
};
extern TerrainLogic *TheTerrainLogic;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

void __stdcall Rva003C353BDo(Parameter *teamParm, void *p2)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamParm->getString(), false);
	if (team == 0)
		return;
	void *base = TheTerrainLogic->s34(p2);
	if (base == 0)
		return;
	const Coord3D *pos = (const Coord3D *)((const char *)base + 0xC);
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (!obj)
			continue;
		obj->rva0029660C(pos, 0);
	}
}
