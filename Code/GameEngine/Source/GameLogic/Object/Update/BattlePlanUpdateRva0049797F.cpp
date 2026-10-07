// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?onObjectCreated@BattlePlanUpdate@@QAEXXZ @0x0049797F 204B.
// Slot 5 (offset 0x14) of vtable 0x0084FBAC (class of ??1Rva004978A3 in
// BattlePlanUpdateRva004978A3Dtor.cpp). Calls FilteredFind 0x0028BB9E,
// OpaqueRefElement4 operator= 0x00239099 (10 copies), Object::setWeaponSetFlag
// 0x00290963, Object::setWeaponLock 0x00290B24 and BattlePlanUpdate::enableTurret
// 0x0049773F (rowed). Layout follows BattlePlanUpdate_enableTurret.cpp
// (m_object at +8, m_ai at +0x258 guarding the weapon lock).

enum WeaponSetType
{
	WST_0 = 0
};

enum WeaponSlotType
{
	WSLT_0 = 0
};

enum WeaponLockType
{
	WLT_0 = 0,
	WLT_1 = 1
};

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class AIUpdateInterface;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
	void setWeaponSetFlag(WeaponSetType type);
	bool setWeaponLock(WeaponSlotType slot, WeaponLockType lock);
	AIUpdateInterface *getAI() { return m_ai; }

private:
	unsigned char m_pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &that);

	void *m_data;
};

struct Payload0049797F
{
	char m_pad00[8];
	void *m_08; // +0x08
	char m_pad0C[0x1c - 0x0c];
	OpaqueRefElement4 m_1c; // +0x1c
	OpaqueRefElement4 m_20; // +0x20
	char m_pad24[4];
	OpaqueRefElement4 m_28; // +0x28
	OpaqueRefElement4 m_2c; // +0x2c
	OpaqueRefElement4 m_30; // +0x30
	OpaqueRefElement4 m_34; // +0x34
	char m_pad38[4];
	OpaqueRefElement4 m_3c; // +0x3c
	OpaqueRefElement4 m_40; // +0x40
	OpaqueRefElement4 m_44; // +0x44
	char m_pad48[4];
	OpaqueRefElement4 m_4c; // +0x4c
};

class BattlePlanUpdate
{
public:
	void onObjectCreated();

protected:
	void enableTurret(bool enable);

private:
	void *m_vtable; // +0x00
	Payload0049797F *m_payload; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x38 - 0x0c];
	void *m_38; // +0x38
	bool m_3c; // +0x3c
	char m_pad3D[0x48 - 0x3d];
	OpaqueRefElement4 m_48; // +0x48
	OpaqueRefElement4 m_4c; // +0x4c
	OpaqueRefElement4 m_50; // +0x50
	char m_pad54[4];
	OpaqueRefElement4 m_58; // +0x58
	OpaqueRefElement4 m_5c; // +0x5c
	OpaqueRefElement4 m_60; // +0x60
	char m_pad64[4];
	OpaqueRefElement4 m_68; // +0x68
	OpaqueRefElement4 m_6c; // +0x6c
	OpaqueRefElement4 m_70; // +0x70
	char m_pad74[0x80 - 0x74];
	OpaqueRefElement4 m_80; // +0x80
};

void BattlePlanUpdate::onObjectCreated()
{
	Payload0049797F *payload = m_payload;
	Object *obj = m_object;
	void *key = payload->m_08;
	if (key == 0)
	{
		m_3c = true;
	}
	else
	{
		m_38 = obj->getSpecialPowerModule(reinterpret_cast<const SpecialPowerTemplate *>(key));
		m_48 = payload->m_1c;
		m_58 = payload->m_20;
		m_68 = payload->m_28;
		m_50 = payload->m_2c;
		m_60 = payload->m_34;
		m_80 = payload->m_30;
		m_70 = payload->m_3c;
		m_4c = payload->m_40;
		m_5c = payload->m_44;
		m_6c = payload->m_4c;
		m_object->setWeaponSetFlag(WST_0);
		if (obj->getAI() != 0)
			obj->setWeaponLock(WSLT_0, WLT_1);
		enableTurret(false);
	}
}
