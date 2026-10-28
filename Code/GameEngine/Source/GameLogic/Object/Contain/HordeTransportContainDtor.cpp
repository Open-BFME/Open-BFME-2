// cl: /DNDEBUG /MD
//
// ??1HordeTransportContain@@UAE@XZ retail 0x004771E6 5 bytes.
// HordeTransportContain virtual dtor is a 5-byte jmp thunk to the rowed
// TransportContain base dtor at 0x00467E61. Retail stores no vptr (novtable).
// Identity via deleting wrapper 0x004771CA slot 0 vtable 0x00C45EB8
// and pool key 0x00477185 with HordeTransportContain string.
// Donor BFME1 HordeTransportContainDestructorThunk (naked).
// Shape follows HordeGarrisonContainDtor 5B precedent (novtable jmp thunk).

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

HordeTransportContain::~HordeTransportContain()
{
}
