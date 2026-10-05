// ?Rva003C301DDo@@YGXPAVParameter@@0@Z
// partial score=0.97 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C301DDo@@YGXPAVParameter@@0@Z @0x003C301D 188B: team float-clamped body module via getTeamNamed iterate. Evidence: rowed getTeamNamed 0x3584E9 iterate 0x263864 advance 0x263526 StringBase copy 0x365F0 kF7C; caller 0x003CE3E8; ret 0x8 stdcall.
#include "ascii_string.h"

extern "C" float kF7C;

class Object;
class Team;

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

template<class OBJCLASS>
class Rva001705A0DlinkIterator
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
};

class BodyModule
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03(); virtual void b04();
	virtual void b05(); virtual void b06(); virtual void b07(); virtual void b08(); virtual void b09();
	virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14();
	virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19();
	virtual void b20(); virtual void b21(float f, int i); virtual void b22(); virtual void b23();
};

class Object
{
public:
	char m_pad00[0x254];
	BodyModule *m_body;
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
extern ScriptEngine *g_Va009FE16C;

inline const float &FloatMinRef(const float &a, const float &b) { return (b > a) ? a : b; }
inline const float &FloatMaxRef(const float &a, const float &b) { return (b > a) ? b : a; }

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

void __stdcall Rva003C301DDo(Parameter *teamParm, Parameter *floatParm)
{
	Team *team = g_Va009FE16C->getTeamNamed((AsciiString &)teamParm->getString(), false);
	if (team == 0)
		return;
	float a = floatParm->m_real;
	float v1 = FloatMinRef(a, kF7C);
	float v2 = FloatMaxRef(v1, 0.0f);
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); ((Rva001705A0DlinkIterator<Object> *)&it)->advance()) {
		BodyModule *body = it.cur()->m_body;
		if (body == 0)
			continue;
		body->b21(v2, 1);
		body->b23();
	}
}
