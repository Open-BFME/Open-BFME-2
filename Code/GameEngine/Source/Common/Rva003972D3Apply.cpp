// cl: /O1 /DNDEBUG /MD
//
// ?rva003972D3@Rva003972D3@@QAEXPAURva003972D3Range@@PBVUpgradeTemplate@@@Z, retail 0x003972D3, 132 bytes.
// Iterates an ObjectID range and re-applies an UpgradeTemplate to qualifying objects.
// Evidence: callers at 0x0039738F 0x0039739B pass [esi+0x50]/[esi+0x74] ranges with ebp upgrade;
// rowed ?findObjectByID@GameLogic@@QAEPAVObject@@W4ObjectID@@@Z via TheGameLogic,
// rowed ?rva00293003@Object@@QAEXPBX@Z, rowed ?rva0028BCF4@Object@@QBEPAXXZ with
// virtual slot 3 (+0x0C) and slot 6 (+0x18), rowed ?rva00290D2B@Object@@QBE_NPBVUpgradeTemplate@@@Z,
// pin-only ?bfmeHas985C@BfmeArg985@@QAEDH@Z; prev/next share /O1 /DNDEBUG /MD.

enum ObjectID
{
	INVALID_OBJECTID = 0
};

class Object;
class UpgradeTemplate;
class BfmeArg985;
class GameLogic;

struct Rva003972D3Range
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Object
{
public:
	void rva00293003(const void *arg);
	void *rva0028BCF4() const;
	bool rva00290D2B(const UpgradeTemplate *templ) const;
};

class BfmeArg985
{
public:
	char bfmeHas985C(int v);
};

class GameLogic
{
public:
	class Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class MidHelper003972D3
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual bool s03();
	virtual void s04();
	virtual void s05();
	virtual class Object *s06();
};

class Rva003972D3
{
public:
	void rva003972D3(Rva003972D3Range *range, const UpgradeTemplate *upgrade);
};

void Rva003972D3::rva003972D3(Rva003972D3Range *range, const UpgradeTemplate *upgrade)
{
	for (ObjectID *p = range->m_begin; p != range->m_end; ++p)
	{
		Object *obj = TheGameLogic->findObjectByID(*p);
		if (obj == 0)
			continue;
		obj->rva00293003(upgrade);
		MidHelper003972D3 *mid = (MidHelper003972D3 *)obj->rva0028BCF4();
		if (mid == 0)
			continue;
		if (!mid->s03())
			continue;
		Object *obj2 = mid->s06();
		if (obj2 == 0)
			continue;
		if (obj2->rva00290D2B(upgrade))
			continue;
		if (!((BfmeArg985 *)obj2)->bfmeHas985C((int)upgrade))
			continue;
		obj2->rva00293003(upgrade);
	}
}
