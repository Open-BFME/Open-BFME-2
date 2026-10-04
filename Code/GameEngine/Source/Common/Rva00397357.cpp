// cl: /O1 /DNDEBUG /MD
// ?rva00397357@Rva003972D3@@QAEXPBVUpgradeTemplate@@@Z RVA 0x00397357 148B
// Evidence: finish from stash 0.9 ebp-ebx mirror; callers none; rowed findObjectByID via TheGameLogic;
//   rowed rva00290D2B rva00293003 rva003972D3; pin bfmeHas985C; prev/next share /O1 /DNDEBUG /MD.

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

static __forceinline Object *findByID(ObjectID id)
{
	return TheGameLogic->findObjectByID(id);
}

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
	void rva00397357(const UpgradeTemplate *upgrade);

private:
	char m_pad00[0x38];
	ObjectID m_id38;
	char m_pad3C[0x50 - 0x3C];
	Rva003972D3Range m_range50;
	char m_pad58[0x5C - 0x58];
	ObjectID *m_begin5C;
	ObjectID *m_end60;
	char m_pad64[0x74 - 0x64];
	Rva003972D3Range m_range74;
};

void Rva003972D3::rva00397357(const UpgradeTemplate *upgrade)
{
	Object *obj = findByID(m_id38);
	if (obj != 0)
	{
		if (!obj->rva00290D2B(upgrade))
			obj->rva00293003(upgrade);
	}
	rva003972D3(&m_range50, upgrade);
	rva003972D3(&m_range74, upgrade);
	for (ObjectID *p = m_begin5C; p != m_end60; ++p)
	{
		Object *obj2 = findByID(*p);
		if (obj2 == 0)
			continue;
		if (obj2->rva00290D2B(upgrade))
			continue;
		if (!((BfmeArg985 *)obj2)->bfmeHas985C((int)upgrade))
			continue;
		obj2->rva00293003(upgrade);
	}
}
