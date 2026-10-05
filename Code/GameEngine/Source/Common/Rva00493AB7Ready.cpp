// cl: /O1 /DNDEBUG /MD
//
// ?rva00493AB7@Rva00493AB7@@QAEIXZ @0x00493AB7 103B.
// Slot 0x18's final override flag selects the controlling player's ready
// frame. Otherwise a positive count or a disabled-mask bit returns
// TheGameLogic frame minus +0x10 plus +8, and a clear mask returns +8.

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

template<int N>
class BitFlags
{
public:
	bool any() const;
};

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Rva00493AB7
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual SpecialPowerTemplate *s6();
	unsigned int rva00493AB7();

private:
	char m_pad4[4];
	unsigned int m_ready;
	int m_count;
	unsigned int m_base;
};

unsigned int Rva00493AB7::rva00493AB7()
{
	const Overridable *finalOverride = s6()->friend_getFinalOverride();
	if (finalOverride->m_59 != 0)
	{
		Object *obj = *(Object **)((char *)this - 8);
		if (obj != 0)
		{
			Player *player = obj->getControllingPlayer();
			if (player != 0)
				return ((Rva002AC6B1PlayerTimers *)player)->getOrStart(s6());
		}
	}
	if (m_count > 0 || ((BitFlags<11> *)((char *)*(Object **)((char *)this - 8) + 0x1C8))->any())
		return TheGameLogic->m_frame - m_base + m_ready;
	return m_ready;
}
