// cl: /DNDEBUG /MD
// ?rva0049C5F4@Rva0049C5F4@@QAEPAXPAVObject@@@Z @0x0049C5F4 48B
// Producer-provider slot31 forward. Retail takes Object arg with +0x78
// producer ID; finds producer via TheGameLogic at 0x00DFE78C through rowed
// findObjectByID; returns null when arg null or producer missing or its
// +0x250 provider null; else returns provider vtable slot 0x7C (slot31).
// Evidence: unlock lane; callers at 0x0049C70F in 0x0049C6E1 plus 0x0049CAC0;
// unblocks 0x0049C6E1; thiscall ecx passed by callers but unused so the
// class stays empty and address-derived. Flags /O1 /DNDEBUG /MD already fit.
enum ObjectID
{
	INVALID_ID = 0
};

class Provider31
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual void *slot31();
};

class Object
{
public:
	char m_pad00[0x78];
	ObjectID m_id78;
	char m_pad7C[0x250 - 0x7C];
	Provider31 *m_prov250;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva0049C5F4
{
public:
	void *rva0049C5F4(Object *arg);
};

void *Rva0049C5F4::rva0049C5F4(Object *arg)
{
	if (arg == 0)
		return 0;
	Object *found = TheGameLogic->findObjectByID(arg->m_id78);
	if (found == 0)
		return 0;
	Provider31 *prov = found->m_prov250;
	if (prov == 0)
		return 0;
	return prov->slot31();
}
