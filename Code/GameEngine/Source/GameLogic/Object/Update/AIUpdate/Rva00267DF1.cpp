// cl: /DNDEBUG /MD
// ?rva00267DF1@Rva00267DF1@@QAEXPAXPBUCoord3D@@HH@Z
//
// retail 0x00267DF1 (85 bytes). Chain lane: calls rowed 0x00265667 with own
// pos plus flag, so every callee is resolved. Guard on first arg, three
// StateMachine virtuals (slots 5, 14, 8 with 62), field +0x48 takes flag,
// then rowed Object::getCurrentWeapon(0) and write third arg to weapon+0x34.
// Evidence: vtable slot 66 of AIUpdate derivatives; layout (+8 object,
// +0x30 machine) plus this-call into Rva00263910::rva00265667 shared with
// sibling TU Rva00263910Goal.cpp.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva00263910
{
public:
	void rva00265667(const Coord3D *pos, int flag);
};

class StateMachine
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4();
	virtual void m5();
	virtual void m6();
	virtual void m7();
	virtual void m8(int v);
	virtual void m9();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14(void *target);
};

class Weapon
{
public:
	char m_pad00[0x34];
	int m_val34;
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
};

class Rva00267DF1 : public Rva00263910
{
public:
	void rva00267DF1(void *target, const Coord3D *pos, int weaponVal, int flag);

private:
	char m_pad00[8];
	Object *m_object;
	char m_pad0C[0x30 - 0x0C];
	StateMachine *m_machine;
	char m_pad34[0x48 - 0x34];
	int m_field48;
};

void Rva00267DF1::rva00267DF1(void *target, const Coord3D *pos, int weaponVal, int flag)
{
	if (target == 0)
		return;
	m_machine->m5();
	m_machine->m14(target);
	rva00265667(pos, flag);
	m_field48 = flag;
	m_machine->m8(62);
	const Weapon *w = m_object->getCurrentWeapon((WeaponSlotType *)0);
	if (w == 0)
		return;
	const_cast<Weapon *>(w)->m_val34 = weaponVal;
}
