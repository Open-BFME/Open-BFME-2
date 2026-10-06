// cl: /DNDEBUG /MD
// ?rva00346B6D@@QAEXH@Z @0x00346B6D 80B.
// Void damage setup (thiscall, one unused int): inits a 0x7C info block on
// the frame through the pinned 0x263895 member init plus field stores,
// resolves the +0x258 slot virtual (float out, dead store) and scales the
// BBB8D8 global into the block, then fires rowed Object::attemptDamage on
// the slot self. This stays transient; the slot self homes in esi.
class DamageInfo;
class Object;

template <int N>
class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <>
class VSlots<0>
{
};

class Slot6 : public VSlots<6>
{
public:
	virtual double slot6();
};

class Rva00263895Member
{
public:
	void init();
};

class Object
{
public:
	void attemptDamage(DamageInfo *info);

	char m_pad00[0x254];
	Slot6 *m_slot254;
};

class StateMachine
{
public:
	char m_pad00[0x14];
	Object *m_obj14;
};

struct Rva00346B6DInfo
{
	char m_00[8];
	int m_08;
	char m_0C[4];
	int m_10;
	char m_14[8];
	int m_1C;
	float m_20;
	bool m_24;
	char m_25[3];
	float m_28;
	char m_2C[0x7C - 0x2C];
};

extern float g_00BBB8D8;

class Rva00346B6D
{
public:
	void rva00346B6D(int unused);

	char m_pad00[0x18];
	StateMachine *m_machine;
};

void Rva00346B6D::rva00346B6D(int unused)
{
	(void)unused;
	Object *self = m_machine->m_obj14;
	Rva00346B6DInfo info;
	((Rva00263895Member *)&info)->init();
	info.m_1C = 0;
	info.m_08 = 0;
	info.m_10 = 8;
	info.m_20 = (float)self->m_slot254->slot6();
	info.m_24 = true;
	info.m_28 = g_00BBB8D8;
	self->attemptDamage((DamageInfo *)&info);
}
