// cl: /DNDEBUG /MD
//
// ?rva004807C7@CitadelSlaughterHordeContain@@UAE_NPAVObject@@@Z, retail 0x004807C7, 90 bytes.
// Slot 33 of ??_7CitadelSlaughterHordeContain 0x00C48CC0 (SlaughterHordeContain
// adds slots 32 and 33; its own slot 33 is the shared default 0x005CB9FA).
// Refuses (false) an object whose four-dword flag set at +0x94 overlaps the
// module data's set at +0xEC (rowed Rva00331682Holder::test), or, when the
// rowed Object::rva002931BA holds, whose producer (Object+0x78 through the
// rowed GameLogic::findObjectByID) overlaps it; accepts everything else.
// Address name: class and slot are proven, the method identity is not.

enum ObjectID
{
	INVALID_ID = 0
};

class Rva00331682Holder
{
public:
	bool test(const void *other) const;
};

class Object
{
public:
	bool rva002931BA();
	unsigned char m_pad00[0x78];
	ObjectID m_78;
	unsigned char m_pad7C[0x94 - 0x7C];
	unsigned int m_94[4];
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct CitadelSlaughterHordeContainModuleData
{
	unsigned char m_pad00[0xEC];
	Rva00331682Holder m_EC;
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class SlaughterHordeContain
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	virtual void s20();
	virtual bool rva004807C7(Object *obj);
protected:
	const CitadelSlaughterHordeContainModuleData *m_moduleData;
};

class CitadelSlaughterHordeContain : public SlaughterHordeContain
{
public:
	virtual bool rva004807C7(Object *obj);
};

// ?rva004807C7@CitadelSlaughterHordeContain@@UAE_NPAVObject@@@Z @0x004807C7
bool CitadelSlaughterHordeContain::rva004807C7(Object *obj)
{
	const CitadelSlaughterHordeContainModuleData *data = m_moduleData;
	if (data->m_EC.test(obj->m_94))
		return false;
	if (obj->rva002931BA())
	{
		Object *producer = TheGameLogic->findObjectByID(obj->m_78);
		if (producer && data->m_EC.test(producer->m_94))
			return false;
	}
	return true;
}
