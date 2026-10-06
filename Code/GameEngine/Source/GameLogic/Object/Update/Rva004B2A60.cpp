// cl: /MD
//
// ?rva004B2A60@Rva004B2A60@@QAEXPAVObject@@@Z, retail 0x004B2A60, 61 bytes.
// Unlock-lane helper: builds a 0x7C DamageInfo temp via rowed Rva00263895Member ctor 0x263895,
// stamps id from m_thing (+8) id (+0x74) at +8 and flag 1 at +0x24, calls pinned
// Object::attemptDamage 0x29848E on the Object arg, then rowed GameLogic::destroyObject 0x242C09.
// Caller 0x004B2C8E passes its Object arg; [esi+8] Thing shape matches UpdateModule m_object.
// LINK: TheGameLogic extern used by 72 TUs.
class Thing;
class Object;
class GameLogic;
class DamageInfo;
class Rva00263895Member;

class Thing
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual Object *asObject();

	unsigned char m_pad04[0x70];
	unsigned int m_id;
};

class Object
{
public:
	void attemptDamage(DamageInfo *info);
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class Rva00263895Member
{
public:
	Rva00263895Member();

private:
	unsigned char m_data[0x7C];
};

struct DamageInfoView
{
	unsigned char m_pad00[8];
	unsigned int m_id;
	unsigned char m_pad0C[0x18];
	bool m_flag;
};

class Rva004B2A60
{
public:
	void rva004B2A60(Object *obj);

private:
	unsigned char m_pad00[8];
	Thing *m_thing;
};

void Rva004B2A60::rva004B2A60(Object *obj)
{
	Rva00263895Member info;
	((DamageInfoView *)&info)->m_flag = true;
	((DamageInfoView *)&info)->m_id = m_thing->m_id;
	obj->attemptDamage((DamageInfo *)&info);
	TheGameLogic->destroyObject(obj);
}
