// cl: /O1 /GX /DNDEBUG /MD
// ??1OilSpillUpdate@@UAE@XZ @0x0048C2A3 79B
// Dtor restores three vptrs (+0 +0xC +0x10) then frees buffer at +0x2C via rowed _free and calls rowed base ??1FireWeaponUpdate at 0x0048BD11. Buffer is the vector<int> payload at +0x2C proven by ctor TU; modeled as void* since trivial-int destruction only frees. Model otherwise follows OilSpillUpdateCtor.
extern "C" void free(void *p);

class Thing;
class ModuleData;
class Object;

class FireWeaponBaseA
{
	virtual void unusedA();
	int m_a0;

protected:
	void *m_owner08;
};

class FireWeaponBaseB
{
	virtual void unusedB();
};

class FireWeaponBaseC
{
	virtual void unusedC();
};

class FireWeaponUpdate : public FireWeaponBaseA, public FireWeaponBaseB, public FireWeaponBaseC
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate();

protected:
	void setWakeFrame(Object *obj, unsigned int frames);

private:
	unsigned char m_pad14[0x2C - 0x14];
};

class OilSpillUpdate : public FireWeaponUpdate
{
public:
	OilSpillUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~OilSpillUpdate();

private:
	void *m_buf2C;
	unsigned char m_pad30[0x38 - 0x30];
};

OilSpillUpdate::~OilSpillUpdate()
{
	if (m_buf2C)
		free(m_buf2C);
}
