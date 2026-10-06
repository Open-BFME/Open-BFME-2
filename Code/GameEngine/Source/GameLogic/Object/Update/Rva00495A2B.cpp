// cl: /DNDEBUG /MD
//
// ?rva00495A2B@Rva00495A2B@@QAEXXZ, retail 0x00495A2B (73 bytes).
// Identity: unlock predicate firing a temp weapon then killing the object;
// testStatus 2 and 0x13 gate the fire, kill is Damage 8 Death 0, flag +0x24
// set. Callers in DemoTrap area; TheWeaponStore via rowed name.
enum ObjectStatusTypes
{
	STATUS_2 = 2,
	STATUS_13 = 0x13
};
enum DamageType
{
	DAMAGE_8 = 8
};
enum DeathType
{
	DEATH_0 = 0
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class WeaponTemplate;
class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	void kill(DamageType d, DeathType t);
	unsigned char m_pad00[0x38];
	Coord3D m_coord38;
};
class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *obj, const Coord3D *pos);
};
extern WeaponStore *TheWeaponStore;
struct Rva00495A2B_H04
{
	unsigned char m_pad[8];
	const WeaponTemplate *m_wt08;
};
class Rva00495A2B
{
public:
	void rva00495A2B();
private:
	unsigned char m_pad00[4];
	Rva00495A2B_H04 *m_p04; // +0x04
	Object *m_obj08; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	unsigned char m_b24; // +0x24
};
void Rva00495A2B::rva00495A2B()
{
	Object *obj = m_obj08;
	if (obj->testStatus(STATUS_2))
		goto doKill;
	if (obj->testStatus(STATUS_13))
		goto doKill;
	TheWeaponStore->createAndFireTempWeapon(m_p04->m_wt08, obj, &obj->m_coord38);
doKill:
	obj->kill(DAMAGE_8, DEATH_0);
	m_b24 = 1;
}
