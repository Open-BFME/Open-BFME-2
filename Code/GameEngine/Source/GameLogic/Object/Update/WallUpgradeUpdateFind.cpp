// cl: /DNDEBUG /MD /EHsc
// ?rva004AB1F5@WallUpgradeUpdate@@SAPAVModule@@PAVObject@@@Z @0x004AB1F5 81B: static WallUpgradeUpdate lookup over an Object guards a function-local NameKeyType for WallUpgradeUpdate through TheNameKeyGenerator then returns obj findModule key (matched row 0x0028B6D6). Plain ret proves static member not thiscall. Class from pool string at 0x007F4F30. Callers at 0x0027614A 0x0028D0AF 0x004B6ECC. Recipe CastleMemberBehaviorFind precedent 81B.

#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Module;
class Drawable;
class AIUpdateInterface;
class Thing;
class ModuleData;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum KindOfType
{
	KIND_45 = 0x45
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class WallUpgradeUpdate;
public:
	bool isKindOf(KindOfType kind) const;
	void rva0028C2DD(Coord3D *center) const;	// 0x0028C2DD
	int rva0028B511() const;			// 0x0028B511
	void teleportTo(const Coord3D *pos, bool flag);  // rowed 0x0029660C
	__declspec(dllimport) __forceinline void rva0029660C(const Coord3D *pos, int flag) { (this->*reinterpret_cast<void (Object::*)(const Coord3D *, int)>(&Object::teleportTo))(pos, flag); }
	Drawable *getDrawable() const;			// 0x005508E2
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;			// +0x74
	char m_pad078[0xB8 - 0x78];
	float m_B8;			// +0xB8 (geometry +0xA8, its +0x10 radius)
	char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai;	// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_flag438;	// +0x438
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class WallUpgradeUpdate : public UpdateModule
{
public:
	WallUpgradeUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *rva004AB1F5(Object *obj);
private:
	const void *m_secondary20;
	const void *m_secondary24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned char m_30;
	unsigned char m_31;
	unsigned char m_pad32[2];
public:
	void scanForBuildingAndPossess();
	void rva004AB57E();
};

Module *WallUpgradeUpdate::rva004AB1F5(Object *obj)
{
	static NameKeyType TheWallUpgradeUpdateKey =
		TheNameKeyGenerator->nameToKey("WallUpgradeUpdate");
	return obj->findModule(TheWallUpgradeUpdateKey);
}
