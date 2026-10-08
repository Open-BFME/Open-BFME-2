// cl: /Ireference/shims/bfme2_ascii /MD /GX
// ?Rva003E803DGet@@YG_NPAVParameter@@0@Z @0x003E803D 157B: free stdcall team contains unit test.
// Evidence: ret 8 two params; Parameter+0x10 AsciiString by-value plus false to ScriptEngine::getTeamNamed row; Parameter to getUnitNamed row; null je; Team::iterate_TeamMemberList row plus Rva001705A0 advance row walking members; Object+0x250 AI virtual +0x7c sub virtual +0xe8 with unit+0x74 plus Object+0x44c equals unit+0x74; caller 0x003EBEED.
#include "ascii_string.h"
class Parameter
{
public:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};
class Object;
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_rest[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};
class Rva003E803DAI
{
public:
	virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
	virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
	virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
	virtual void f24(); virtual void f25(); virtual void f26(); virtual void f27();
	virtual void f28(); virtual void f29(); virtual void f30();
	virtual void *f31();
};
class Rva003E803DSub
{
public:
	virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
	virtual void g04(); virtual void g05(); virtual void g06(); virtual void g07();
	virtual void g08(); virtual void g09(); virtual void g10(); virtual void g11();
	virtual void g12(); virtual void g13(); virtual void g14(); virtual void g15();
	virtual void g16(); virtual void g17(); virtual void g18(); virtual void g19();
	virtual void g20(); virtual void g21(); virtual void g22(); virtual void g23();
	virtual void g24(); virtual void g25(); virtual void g26(); virtual void g27();
	virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
	virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37(); virtual void g38(); virtual void g39();
	virtual void g40(); virtual void g41(); virtual void g42(); virtual void g43();
	virtual void g44(); virtual void g45(); virtual void g46(); virtual void g47();
	virtual void g48(); virtual void g49(); virtual void g50(); virtual void g51();
	virtual void g52(); virtual void g53(); virtual void g54(); virtual void g55();
	virtual void g56(); virtual void g57();
	virtual bool g58(int val);
};
class Object
{
public:
	unsigned char m_pad00[0x74];
	int m_id;
	unsigned char m_pad78[0x250 - 0x78];
	Rva003E803DAI *m_ai;
	unsigned char m_pad254[0x44c - 0x254];
	int m_44c;
};
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool b);
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

bool __stdcall Rva003E803DGet(Parameter *p0, Parameter *p1)
{
	Team *team = TheScriptEngine->getTeamNamed(p0->m_string, false);
	Object *unit = TheScriptEngine->getUnitNamed(p1);
	if (team == 0 || unit == 0)
		return false;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		Rva003E803DAI *ai = cur->m_ai;
		void *sub = ai ? (void *)ai->f31() : 0;
		if (sub != 0) {
			int id = unit->m_id;
			if (((Rva003E803DSub *)sub)->g58(id))
				return true;
		}
		if (cur->m_44c == unit->m_id)
			return true;
	}
	return false;
}
