// cl: /O1 /DNDEBUG /MD
//
// ?rva00262453@Rva00262453@@QAEXPAVSequentialScript@@_NH@Z, retail 0x00262453, 74 bytes.
// Evidence: same +4/+8/+9/+0A/+0B layout as Rva00262436 setter; old ptr at
// +4 checked at +0x10 then rowed ScriptEngine::rva00205140 0x00205140 via
// TheScriptEngine; callers 0x0036E2D1 and 0x003B3DAF with (ptr 1 arg2).
class SequentialScript
{
public:
	char m_pad[0x10];
	unsigned char m_10;
};

class ScriptEngine
{
public:
	void rva00205140(SequentialScript *arg);
};

extern ScriptEngine *TheScriptEngine;

typedef bool Bool;

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Team;
class AIGroup;

class Object
{
public:
	char m_pad[0x304];
	Team *m_team;
};

class AIUpdateInterface : public BfmeVirtualSlots<110>
{
public:
	virtual Bool isIdle() const;
	char m_pad04[4];
	Object *m_08;
	char m_pad0C[0x3CA - 0x0C];
	unsigned char m_3CA;
};

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class AIGroup
{
public:
	Bool isIdle() const;
	Bool rva0036E0B6() const;
};

extern AI *g_Va009FF0F8;

class Rva00262453
{
	AIUpdateInterface *m_00;
	SequentialScript *m_04;
	bool m_08;
	bool m_09;
	bool m_0A;
	bool m_0B;
public:
	void rva00262453(SequentialScript *p, bool b, int dummy);
	void rva0026249D();
};

void Rva00262453::rva00262453(SequentialScript *p, bool b, int dummy)
{
	(void)dummy;
	if (m_08 != 0) {
		if (m_0A == 0)
			goto store;
	}
	if (p != m_04 && m_04 != 0 && m_04->m_10 != 0) {
		TheScriptEngine->rva00205140(m_04);
		m_0A = 0;
	}
store:
	m_04 = p;
	m_08 = 0;
	m_0B = 0;
	m_09 = b;
}

// ?rva0026249D@Rva00262453@@QAEXXZ, retail 0x0026249D, 118 bytes.
// Next row after rva00262453. Evidence: same +8/+9/+0A/+0B flag layout;
// m_00 is AIUpdateInterface (virtual isIdle slot 110 at +0x1b8 plus byte
// +0x3CA); +8 chain Object+0x304 Team via rowed getTeamAsAIGroup; callees
// rowed createGroup 0x002FEC4B getTeamAsAIGroup 0x003A0F62 isIdle 0x0036DF4D
// rva0036E0B6 0x0036E0B6; global g_Va009FF0F8; caller 0x0026E568.
void Rva00262453::rva0026249D()
{
	if (m_0B) {
		m_08 = true;
		m_0B = false;
	}
	if (m_08)
		return;
	if (m_0A)
		return;
	if (m_09) {
		AIGroup *grp = g_Va009FF0F8->createGroup();
		Team *team = m_00->m_08->m_team;
		team->getTeamAsAIGroup(grp);
		if (!grp->isIdle())
			return;
		if (grp->rva0036E0B6())
			return;
		m_0B = true;
	} else {
		if (!m_00->isIdle())
			return;
		if (m_00->m_3CA != 0)
			return;
		m_0B = true;
	}
}
