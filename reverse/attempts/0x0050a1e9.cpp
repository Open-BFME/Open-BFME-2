// ?rva0050A1E9@Made002CC8A4@@QAEXPAXPAVObject@@@Z
// partial score=0.88 date=2026-10-04
// cl: /O1 /MD /EHsc /DNDEBUG /arch:SSE
//
// ?rva0050A1E9@Made002CC8A4@@QAEXPBXH@Z @ 0x0050A1E9 (434B).
// Slot 15 (0x3C) of Made002CC8A4 vtable 0x008649A0 (MetaImpactNugget).
// Evidence: vtable slot 15; callers none; callees rowed findObjectByID,
// isValid, getControllingPlayer, kill, rva0028C149, GetGameLogicRandomValueReal,
// testStatus; pins bfmeHas1026, report, attemptDamage; TheGameLogic,
// BfmeZeroRange, g_00C6499C, string literal.

class Object;
class Player;
class GameLogic;
enum ObjectID
{
	INVALID_ID = 0
};
enum DamageType
{
	DT_8 = 8
};
enum DeathType
{
	DT_0 = 0
};
enum ObjectStatusTypes
{
	ST_26 = 0x26
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class ObjectFilter
{
public:
	bool isValid() const;
};
class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
};
class Player
{
};
class Object
{
public:
	Player *getControllingPlayer() const;
	void kill(DamageType a, DeathType b);
	bool rva0028C149(int attr, float *value, int arg);
	bool testStatus(ObjectStatusTypes s) const;
	class DamageInfo;
	void attemptDamage(DamageInfo *info);
public:
	char m_pad00[4];
	void *m_04;
};
extern float BfmeZeroRange;
extern float g_00C6499C;
float __cdecl GetGameLogicRandomValueReal(float a, float b, char *name, int line);

class Rva00263653
{
public:
	Rva00263653() throw();
	char m_data[0x68];
};
class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	virtual void rva00263895_dummy();
private:
	Rva00263653 m_mem;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};
class Rva00294D61
{
public:
	void report(Object *o, int v);
};
class DamageInfoish
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void *v14();
	virtual void v15(void *a);
};
class TargetIface
{
public:
	virtual void v00();
	virtual void *v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void *v31(Object *o);
};
class SelfIface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual bool v14(const void *a, Object *b, const void *c);
};

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};
extern const BfmeFixedStorage0004543D g_009FEFA4;
class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
private:
	int m_x;
};
class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	char m_pad[0x128 - 4];
};
class Made002CC8A4 : public Rva00507823
{
public:
	Made002CC8A4();
	void rva0050A1E9(void *a, Object *b);
private:
	float m_128;
	float m_12C;
	float m_130;
	bool m_134;
	char m_pad135[3];
	float m_138;
	float m_13C;
	float m_140;
	float m_144;
	int m_148;
	bool m_14C;
	bool m_14D;
	char m_pad14E[2];
	float m_150;
	bool m_154;
	bool m_155;
	char m_pad156[2];
	float m_158;
	float m_15C;
	Rva003623E5Member m_160;
};

// ?rva0050A1E9@Made002CC8A4@@QAEXPAXPAVObject@@@Z present-unmatched
void Made002CC8A4::rva0050A1E9(void *a, Object *shooter)
{
	if (!a)
		return;
	if (!shooter)
		return;
	Object *found = TheGameLogic->findObjectByID((ObjectID)*(int *)((char *)a + 8));
	if (found)
	{
		char *base = (char *)this + 0x160;
		if (!((ObjectFilter *)base)->isValid())
			goto doAttr;
		if (!((BfmeTab1026 *)base)->bfmeHas1026((int)found->getControllingPlayer(), (int)shooter))
			goto doAttr;
		shooter->kill(DT_8, DT_0);
		return;
	}
doAttr:
	{
		shooter->rva0028C149(0xA, (float *)&shooter, 0);
		float v = *(float *)&shooter;
		if (v <= BfmeZeroRange)
			goto checkBit;
		float r = GetGameLogicRandomValueReal(0.0f, g_00C6499C, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\MetaImpactNugget.cpp", 0x19B);
		if (v <= r)
			return;
	}
checkBit:
	{
		void *vp = (void *)*(int *)((char *)shooter + 4);
		if (*(unsigned char *)((char *)vp + 0x113) & 4)
		{
			float r2 = GetGameLogicRandomValueReal(0.0f, g_00C6499C, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\MetaImpactNugget.cpp", 0x1A4);
			if (r2 > m_150)
				return;
		}
	}
	{
		Object *o = shooter;
		void *tail = (void *)*(int *)((char *)o + 0x274);
		if (!o->testStatus(ST_26))
			goto tryDamage;
		if (!tail)
			goto tryDamage;
		if (!*(int *)((char *)tail + 0x274))
			goto tryDamage;
		void *t4 = (void *)*(int *)((char *)tail + 4);
		if (!(*(unsigned char *)((char *)t4 + 0x115) & 0x20))
			goto tryDamage;
		void *t274 = (void *)*(int *)((char *)tail + 0x274);
		void *t250 = (void *)*(int *)((char *)t274 + 0x250);
		if (!t250)
			return;
		Object *found2 = TheGameLogic->findObjectByID((ObjectID)*(int *)((char *)a + 8));
		if (found2)
			((Rva00294D61 *)found2)->report(o, 1);
		void *rv = ((TargetIface *)t250)->v01();
		void *rv2 = ((TargetIface *)t250)->v31(o);
		((DamageInfoish *)rv)->v15(rv2);
		return;
	}
tryDamage:
	{
		Rva00263895Member info;
		if (!((SelfIface *)this)->v14(a, shooter, &info))
			return;
		shooter->attemptDamage((Object::DamageInfo *)&info);
	}
}
