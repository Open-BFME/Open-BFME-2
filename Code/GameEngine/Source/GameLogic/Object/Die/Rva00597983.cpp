// cl: /O1 /GX- /arch:SSE /G7
// ?rva00597983@Rva00597983@@QAEXXZ @0x00597983 431B: Die-dir leaf called by
// Rva00597FC5 0x00597FDC counting Rva004E9378-false plus m_34 entries then
// gating on PlayerList record +0x16c 1->1 2->3 then best via rowed
// Rva005978ED plus float-gated scan with pinned int-retype Rva0059710E
// then m_40 switch with GetGameLogicRandomValueReal and slot6 call.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Player
{
public:
	char m_pad00[0x94];
	int m_94;
};

class Object
{
public:
	int rva00294ADD(int x);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva004E9378
{
public:
	bool rva004E9378();
};

struct Rva002A8AB1Data
{
	char m_pad00[0xC8];
	float m_c8;
	float m_cc;
	float m_d0;
	float m_d4;
};

struct Rva002A8AB1Record
{
	char m_pad00[0x160];
	Rva002A8AB1Data *m_160;
	char m_pad164[0x16C - 0x164];
	int m_16C;
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};

extern Rva002A8F24 *g_00DFEEF8;

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Rva005970ED
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6(Player *owner, int x);
	int rva0059710E(int x);
	float m_04;
	ObjectID m_id08;
	char m_pad0C[0x10 - 0x0C];
	int m_10;
	char m_pad14[0x2C - 0x14];
	int m_2C;
	int m_30;
	unsigned char m_34;
	char m_pad35[3];
	char m_pad38[0x40 - 0x38];
	int m_40;
};

class Rva005978ED
{
public:
	Rva005970ED *rva005978ED();
};

class Rva00597983
{
public:
	void rva00597983();
private:
	char m_pad00[0x14];
	union
	{
		Player *m_owner;
		int m_14;
	};
	char m_pad18[0x24 - 0x18];
	_STL::vector<void *, _STL::allocator<void *> > m_vec24;
};

void Rva00597983::rva00597983()
{
	unsigned count = 0;
	void **finish = m_vec24.m_finish;
	void **it = m_vec24.m_start;
	while (it != finish)
	{
		if (!((Rva004E9378 *)*it)->rva004E9378() && ((Rva005970ED *)*it)->m_34 != 0)
			++count;
		++it;
	}
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(m_owner);
	unsigned need;
	switch (rec->m_16C)
	{
	case 1:
		need = 1;
		break;
	case 2:
		need = 3;
		break;
	default:
		return;
	}
	if (count >= need)
		return;
	unsigned u = count + 1;
	float scale = (float)u;
	int threshInt = m_owner->m_94;
	Rva005970ED *best = reinterpret_cast<Rva005978ED *>(this)->rva005978ED();
	if (best == 0)
	{
		it = m_vec24.m_start;
		finish = m_vec24.m_finish;
		while (it != finish)
		{
			Rva005970ED *e = (Rva005970ED *)*it;
			if (e->m_34 == 0)
			{
				int v30 = e->m_30;
				ObjectID id = e->m_id08;
				if (TheGameLogic->findObjectByID(id)->rva00294ADD(v30) == 0)
				{
					if (best == 0 || e->m_2C < best->m_2C)
					{
						double prod = (double)e->m_2C * (double)scale;
						float thr = (float)(unsigned)threshInt;
						if (thr >= prod)
						{
							if (e->rva0059710E(m_14) != 3)
								best = e;
						}
					}
				}
			}
			++it;
		}
		if (best == 0)
			return;
	}
	best->m_34 = 1;
	switch (best->m_40)
	{
	case 0:
		best->m_04 = GetGameLogicRandomValueReal(rec->m_160->m_c8, rec->m_160->m_cc, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUpgradeScienceBuilder\\AIUpgradeScienceBuilder.cpp", 0x18B);
		break;
	case 1:
		best->m_04 = GetGameLogicRandomValueReal(rec->m_160->m_d0, rec->m_160->m_d4, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUpgradeScienceBuilder\\AIUpgradeScienceBuilder.cpp", 0x18E);
		break;
	case 2:
		best->m_04 = -1.0f;
		break;
	default:
		break;
	}
	best->s6(m_owner, 0);
}
