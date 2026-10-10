// cl: /O1 /DNDEBUG /MD
//
// ?rva004B327F@Rva004B327F@@QAEHXZ @0x004B327F 211B.
// Sits at AISpecialPowerUpdate+0x10. A clear byte at +0x11 runs post-init.
// A set player byte at +0x734 clears the flag at +0x10 and returns 1.
// Otherwise the power object at +0x14 is armed and the answer is its
// virtual slot 3, or 0x3fffffff when the flag, the power, or the
// skirmish record is missing.

class Player;
class Object;
class SpecialPowerTemplate;
class Rva003A2BD4M08;
class Rva002A9BF2
{
public:
	bool fromGate(Rva002A9BF2 *key);
};
class Rva004B327F;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva002AA22AByteField
{
public:
	unsigned char get() const;
};

struct Rva002A8AB1Record;
// 0x002A8AB1 by its row name (Rva002A8AB1.cpp).
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};

extern Rva002A8F24 *g_00DFEEF8;

class AISpecialPowerUpdate
{
	friend class Rva004B327F;

private:
	void postInitAISpecialPower();
};

class Rva004B2F7B
{
public:
	bool rva004B2F7B(const SpecialPowerTemplate *tmpl);
};

class PowerInner
{
public:
	char m_pad[0x44];
	SpecialPowerTemplate *m_tmpl;
};

class Rva0058AD94
{
public:
	virtual int v00();
	virtual int v01();
	virtual int v02();
	virtual int v03();

	char m_pad4[4];
	PowerInner *m_inner;

	void rva0058AD94(int arg);
};

class Rva0058ADD0
{
public:
	bool rva0058ADD0(void *target, bool flag19, bool flag1A);
};

class Rva0058ADA8
{
public:
	void rva0058ADA8(int arg);
};

int Rva0058AEB6Get();
bool __stdcall Rva0058AF47Check(Rva002A9BF2 *p);

class FlagSrc
{
public:
	char m_pad[0x18];
	bool m_18;
	bool m_19;
};

class Rva004B327F
{
public:
	int rva004B327F();

private:
	Object *object()
	{
		return *(Object **)((char *)this - 8);
	}

	char m_pad[0x10];
	bool m_flag;
	bool m_inited;
	char m_pad12[2];
	Rva0058AD94 *m_power;
};

int Rva004B327F::rva004B327F()
{
	if (!m_inited)
		((AISpecialPowerUpdate *)((char *)this - 0x10))->postInitAISpecialPower();

	int result = 0x3fffffff;
	if (m_flag)
	{
		if (((Rva002AA22AByteField *)object()->getControllingPlayer())->get() != 0)
		{
			m_flag = false;
			return 1;
		}
		if (m_power && g_00DFEEF8->rva002A8AB1(
				(Rva003A2BD4M08 *)object()->getControllingPlayer()))
		{

	m_power->rva0058AD94((int)object());

	SpecialPowerTemplate *tmpl = m_power->m_inner->m_tmpl;
	FlagSrc *src = *(FlagSrc **)((char *)this - 0x0C);
	bool ok = tmpl != 0
		? ((Rva004B2F7B *)((char *)this - 0x10))->rva004B2F7B(tmpl)
		: true;
	if (ok)
	{
		if (((Rva0058ADD0 *)m_power)->rva0058ADD0(object(), src->m_18, src->m_19))
		{
			if (((Rva002A9BF2 *)Rva0058AEB6Get())->fromGate(
					(Rva002A9BF2 *)object()->getControllingPlayer()))
				((Rva0058ADA8 *)m_power)->rva0058ADA8((int)object());
		}
	}
		return m_power->v03();
		}
	}
	return result;
}
