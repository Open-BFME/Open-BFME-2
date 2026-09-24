// ??1OilSpillUpdate@@UAE@XZ
// partial score=0.8 date=2026-09-24
// cl: /O1 /DNDEBUG /MD /GX
//
// ??1OilSpillUpdate@@UAE@XZ, retail 0x0048C2A2, 80 bytes. Virtual dtor
// shard: ctor TU keeps its verified shape untouched, so the class is
// re-declared here with the ctor declared-only and only the dtor defined.
//
// Shape: EH prologue with frame (states arm around the throwing free),
// explicit 3 vtable installs, null-checked pool pointer at +0x2C freed via
// the C++-decoration free pin at 0x30830 (whose decoration emits the unwind
// state store), implicit FireWeaponUpdate base-dtor call. Zero new pins.

class Thing;
class ModuleData;

void __cdecl free(void *ptr);

class FireWeaponUpdate
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate();
private:
	char m_pad[0x28];
};

class OilSpillUpdate : public FireWeaponUpdate
{
public:
	OilSpillUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~OilSpillUpdate();
private:
	void *m_2C;
};

// ??1OilSpillUpdate@@UAE@XZ @0x0048C2A2
OilSpillUpdate::~OilSpillUpdate()
{
	*(const void **)this = (const void *)0x00C4C380;
	*(const void **)((char *)this + 0x0C) = (const void *)0x00BEFF90;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C4C374;
	if (m_2C)
		free(m_2C);
}
