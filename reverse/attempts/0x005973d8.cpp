// ?rva005973D8@Rva005973D8@@QAEHXZ
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD
// ?rva00597476@Rva0059734B@@UAEMPAX@Z @0x00597476 86B: slot8 cost ratio via UpgradeTemplate calcCostToBuild and rva0026EE30 with idiv and fild; vtable 0x00870BD0
enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad[4];
	void *rva0028BC58(int x);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Player;
class UpgradeTemplate
{
public:
	unsigned int calcCostToBuild(Player *p, unsigned int u) const;
	int rva0026EE30(void *a, void *b);
};

class Holder
{
public:
	char m_pad00[0x24];
	UpgradeTemplate *m_24;
};

class Rva0055B0CC
{
public:
	virtual ~Rva0055B0CC();
protected:
	float m_04;
	ObjectID m_08;
	char m_pad0c[0x2c - 0x0c];
};

class Rva0059734B : public Rva0055B0CC
{
public:
	virtual float rva00597476(void *p);
private:
	int m_2C;
	Holder *m_30;
};

float Rva0059734B::rva00597476(void *p)
{
	UpgradeTemplate *tmpl = m_30->m_24;
	Object *o1 = TheGameLogic->findObjectByID(m_08);
	unsigned int cost = tmpl->calcCostToBuild((Player *)p, (unsigned int)o1);
	Object *o2 = TheGameLogic->findObjectByID(m_08);
	int denom = tmpl->rva0026EE30(p, o2);
	int quot = (int)cost / denom;
	float f = (float)quot;
	return f;
}

class Rva005973D8Slot
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual bool slot6(UpgradeTemplate *tmpl);
};

class Rva005973D8
{
	char m_pad00[8];
	ObjectID m_id08;
	char m_pad0C[0x10 - 0x0C];
	int m_int10;
	char m_pad14[0x30 - 0x14];
	Holder *m_holder30;
public:
	int rva005973D8();
};

// ?rva005973D8@Rva005973D8@@QAEHXZ @0x005973D8 78B unlock upgrade check via TheGameLogic double find plus pin plus slot6 plus Holder 0x30/0x24 same TU flags callers 0x005975C3
// ?rva005973D8@Rva005973D8@@QAEHXZ present-unmatched
int Rva005973D8::rva005973D8()
{
	if (m_int10 <= 0)
		goto ret_zero;
	GameLogic *gl = TheGameLogic;
	ObjectID id = m_id08;
	if (gl->findObjectByID(id) == 0)
		goto ret_one;
	{
		void *p = gl->findObjectByID(id)->rva0028BC58(0);
		UpgradeTemplate *tmpl = m_holder30->m_24;
		if (((Rva005973D8Slot *)p)->slot6(tmpl))
			goto ret_zero;
		goto ret_one;
	}
ret_zero:
	return 0;
ret_one:
	return 1;
}
