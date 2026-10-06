// cl: /O1 /DNDEBUG /MD
//
// ?rva0049355E@Rva0049355E@@QAEMXZ @0x0049355E 194B.
// Early outs return the global at VA 0x00BBAEAC, 1, or the float at +0x14.
// Otherwise 1 minus the unsigned ready delta over the unsigned at +4.

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x59];
	unsigned char m_59;
};

class SpecialPowerTemplate : public Overridable
{
};

class Rva002AC6B1PlayerTimers
{
public:
	unsigned int getOrStart(const SpecialPowerTemplate *tmpl);
};

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

struct Rva0049355EHolder
{
	char m_pad[8];
	Overridable *m_ov;
};

class Rva0049355E
{
public:
	virtual void s0();
	virtual bool s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual SpecialPowerTemplate *s6();
	float rva0049355E();
	unsigned int m_4;
	unsigned int m_8;
	int m_c;
	char m_gap[4];
	float m_14;
	unsigned char m_18;
};

float Rva0049355E::rva0049355E()
{
	if (m_18 != 0)
		return 0.0f;
	if (s1())
		return 1.0f;
	if (m_c > 0)
		return m_14;
	Rva0049355EHolder *holder = *(Rva0049355EHolder **)((char *)this - 0xC);
	if (holder->m_ov == 0)
		return 0.0f;
	Object *obj = *(Object **)((char *)this - 8);
	unsigned int value = m_8;
	if (obj != 0)
	{
		Player *player = obj->getControllingPlayer();
		if (player != 0 && holder->m_ov->friend_getFinalOverride()->m_59 != 0)
			value = ((Rva002AC6B1PlayerTimers *)player)->getOrStart(s6());
		value -= TheGameLogic->m_frame;
		return 1.0f - (float)value / (float)m_4;
	}
	return 0.0f;
}
