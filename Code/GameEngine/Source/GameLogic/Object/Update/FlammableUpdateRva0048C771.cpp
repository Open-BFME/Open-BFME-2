// cl: /DNDEBUG /MD /GX-
// ?rva0048C771@FlammableUpdate@@QAEXXZ @0x0048C771 78B
// Evidence: stack DamageInfo 0x7C via rowed ??0Rva00263895Member@@QAE@XZ; Object::attemptDamage pin 0x0029848E; neighbor ??1FlammableUpdate; ModuleData+0x14 int->float and this+0x48 int.
class DamageInfo;
class Object;

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

class Object
{
public:
	void attemptDamage(DamageInfo *damageInfo);
};

class FlammableUpdateModuleData
{
public:
	unsigned char pad_00[0x14];
	int m_14;
};

class FlammableUpdate
{
public:
	void rva0048C771();
private:
	const void *m_vtbl;
	const FlammableUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char pad_0C[0x3C];
	int m_48;
};

void FlammableUpdate::rva0048C771()
{
	Object *obj = m_object;
	const FlammableUpdateModuleData *md = m_moduleData;
	Rva00263895Member damageInfo;
	float f = (float)md->m_14;
	*(int *)((char *)&damageInfo + 0x08) = m_48;
	*(float *)((char *)&damageInfo + 0x20) = f;
	*(int *)((char *)&damageInfo + 0x10) = 6;
	*(int *)((char *)&damageInfo + 0x1C) = 3;
	*(int *)((char *)&damageInfo + 0x18) = 2;
	obj->attemptDamage((DamageInfo *)&damageInfo);
}
