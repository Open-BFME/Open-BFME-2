// cl: /DNDEBUG /MD
//
// Target evidence: 0x00477003 installs vtable 0x00C45D2C at the
// HordeTransportContain +0x28 subobject; its first entry is 0x00477B69.
// The target reads module data through this-0x24 and the owner through
// this-0x28, then optionally calls the helper at this+0xF5. The address-only
// callee 0x0047778B is reached directly from the target's REL32 call.
//
// Identity inference: the BFME1 OpenContain hierarchy places DieModuleInterface
// after CollideModuleInterface, consistent with the target's +0x28 vtable and
// one-pointer ABI. That supports the onDie name; the +0x82 module-data flag and
// helper meaning remain unnamed target fields. Donor source is a layout/slot
// lead, not proof of BFME2 field semantics.
class Rva00462785
{
public:
	int rva00462785();
};

// Row spellings: 0x00588E44 is Rva0047A040Base9E0::rva00588E44 and
// 0x0047778B is HordeTransportContain::rva0047778B.
class Object;
struct Coord3D;
class Rva00588E44Contain;
class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *);
	void rva00588BA8(Object *obj, bool flag);
	Object *rva00588C4E(void *contain, const struct Coord3D *obj);
	void rva00588F61(void *contain, Object *owner, enum CommandSourceType obj);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *object);
	Rva00588E44Contain *rva00588BF3(void *contain, Object *obj);
	bool rva00588D24(void *owner, Object *obj);
	void rva00588E44(void *argument);
};

class Thing;
class Object;
class DamageInfo;
struct Rva0047727EObjectPositionView;
enum NameKeyType { NK_UNKNOWN = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum ExitDoorType { DOOR_1 = 0 };

class OpenContain {
public:
	virtual void exitObjectViaDoor(Object *,ExitDoorType);
};

class TransportContain : public OpenContain {
public:
	virtual ~TransportContain();
	virtual UpdateSleepTime update();
};

// Retail stores no HordeTransportContain vptr (novtable): its dtor is a
// bare jmp to the TransportContain base dtor.
class __declspec(novtable) HordeTransportContain : public TransportContain {
public:
	virtual ~HordeTransportContain();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onDie(const DamageInfo *damageInfo);
	virtual void exitObjectViaDoor(Object *,ExitDoorType);
	void rva004779F9();
	void rva0047778B();
	void rva004776E7(const struct Rva004776E7UpgradeMask *,bool);
	void rva0047727E(Thing *object);
	void rva0047748E();
private:
	unsigned char prefix04[4];
	Rva0047727EObjectPositionView *m_object;
};

void HordeTransportContain::onDie(const DamageInfo *damageInfo)
{
	const unsigned char *moduleData =
		*(const unsigned char **)((char *)this - 0x24);
	if (moduleData[0x82] != 0) {
		((HordeTransportContain *)((char *)this - 0x28))->rva0047778B();
	} else {
		Rva00462785 *owner = (Rva00462785 *)((char *)this - 0x28);
		if ((unsigned char)owner->rva00462785() != 0)
			((Rva0047A040Base9E0 *)((char *)this + 0xF5))->rva00588E44(owner);
	}
}
