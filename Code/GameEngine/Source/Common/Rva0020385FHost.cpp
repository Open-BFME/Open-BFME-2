// cl: /MD
// ?setSway@ScriptEngine@@IAEXPAVScriptAction@@@Z @0x0020385F 192B. __thiscall method reading the action's 5-slot param block (count at +8, pointers at +0xc..+0x1c); float slot at +0xc of slot0 becomes angle/sin/cos, dwords at +0xc of slots1,2,4 and word at +8 of slot3 (clamped >=1) fill members. Callees Sin/Cos rowed in wwmath.cpp. Retail-selected pointers deref unconditionally (null+0xc when count short), hence the xor-then-load shape.
float Sin(float value);
float Cos(float value);

struct Elem0020385F
{
	char m_pad[8];
	int m_word32;
	union
	{
		float m_float;
		int m_int;
	};
};

class ScriptAction
{
public:
	char m_pad[8];
	int m_count;
	Elem0020385F *m_e0;
	Elem0020385F *m_e1;
	Elem0020385F *m_e2;
	Elem0020385F *m_e3;
	Elem0020385F *m_e4;
};

class ScriptEngine
{
protected:
	void setSway(ScriptAction *p);

public:
	char m_lead[0x1A4A8];
	float m_angle;
	float m_sin;
	float m_cos;
	int m_a;
	int m_b;
	int m_c;
	short m_d;
	unsigned short m_n;
};

void ScriptEngine::setSway(ScriptAction *p)
{
	++m_n;
	Elem0020385F *e0 = p->m_count > 0 ? p->m_e0 : (Elem0020385F *)0;
	float ang = e0->m_float;
	m_angle = ang;
	m_sin = Sin(ang);
	m_cos = Cos(m_angle);
	Elem0020385F *e1 = p->m_count > 1 ? p->m_e1 : (Elem0020385F *)0;
	m_a = e1->m_int;
	Elem0020385F *e2 = p->m_count > 2 ? p->m_e2 : (Elem0020385F *)0;
	m_b = e2->m_int;
	Elem0020385F *e3 = p->m_count > 3 ? p->m_e3 : (Elem0020385F *)0;
	int full = e3->m_word32;
	m_d = (short)full;
	if (m_d < 1)
		m_d = 1;
	Elem0020385F *e4 = p->m_count > 4 ? p->m_e4 : (Elem0020385F *)0;
	m_c = e4->m_int;
}
