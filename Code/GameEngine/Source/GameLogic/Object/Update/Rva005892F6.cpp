// cl: /O1 /DNDEBUG /MD
// ?rva005892F6@Rva005892F6@@QAEMXZ @0x005892F6 (183B). Ratio of two unsigned distances:
// returns 1.0f when the first virtual flag holds, +0x10 when +0x8 is positive, 0.0f when the
// target has no +0x8 object. Otherwise 1.0f - (frame - TheGameLogic+0x40) / final override +0x20,
// where the numerator is replaced by the player timer start when a controlling player with a
// final override exists. Callees are rowed matched getters; owner identity remains unproven.

class Player;
class SpecialPowerTemplate;
class Object;
class GameLogic;

extern GameLogic *TheGameLogic;

// class-gate: allow GameLogic proved codegen view of the +0x40 frame word only; the shared header keeps it private
class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad00[0x20];
	int m_20;
	char m_pad24[0x59 - 0x24];
	unsigned char m_59;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva002AC6B1PlayerTimers
{
public:
	unsigned int getOrStart(const SpecialPowerTemplate *tmpl);
};

struct Rva005892F6Target
{
	char m_pad00[8];
	Overridable *m_8;
};

class Rva005892F6
{
public:
	float rva005892F6();
	virtual void slot0();
	virtual bool slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual const SpecialPowerTemplate *slot6();
private:
	int m_4;
	int m_8;
	int m_0c;
	float m_10;
};

float Rva005892F6::rva005892F6()
{
	if (slot1())
		return 1.0f;
	if (m_8 > 0)
		return m_10;
	char *self = reinterpret_cast<char *>(this);
	Rva005892F6Target *target = *reinterpret_cast<Rva005892F6Target **>(self - 0x20);
	if (target->m_8 == 0)
		return 0.0f;
	Object *obj = *reinterpret_cast<Object **>(self - 0x1c);
	int frame = m_4;
	if (obj != 0)
	{
		Player *player = obj->getControllingPlayer();
		if (player != 0)
		{
			if (target->m_8->friend_getFinalOverride()->m_59 != 0)
			{
				const SpecialPowerTemplate *tmpl = slot6();
				frame = (int)reinterpret_cast<Rva002AC6B1PlayerTimers *>(player)->getOrStart(tmpl);
			}
		}
	}
	GameLogic *gl = TheGameLogic;
	const float numer = (float)(unsigned int)(frame - gl->m_40);
	const float denom = (float)(unsigned int)target->m_8->friend_getFinalOverride()->m_20;
	return 1.0f - numer / denom;
}
