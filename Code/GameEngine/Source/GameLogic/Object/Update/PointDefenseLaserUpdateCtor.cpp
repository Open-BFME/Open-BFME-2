// cl: /O1 /MD /DNDEBUG
// Identity: ModuleFactory registers this module as "BeaconClientUpdate" (addModule pairs
// the name with its factories); formerly misnamed PointDefenseLaserUpdate.
// Trial: ??0BeaconClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z.
// Base 0x00362EC7 (pinned opaque); and-zeroed slot, hand-placed vtable
// (novtable), then a global-pointer member load. Factory stub order.
class Thing;
class ModuleData;

// PointDefenseLaserUpdate_vftable: matched references place it at VA 0xc5eb30 (retail .rdata value -26).
extern "C" char PointDefenseLaserUpdate_vftable = -26;

struct OpaqueGlobal
{
	char m_pad[0x40];
	void *m_p40;
};

extern class GameLogic *TheGameLogic;

// Opaque intermediate; ctor resolves to the opaque pin at 0x00362EC7.
class Rva00362EC7
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00362EC7();

protected:
	unsigned char m_pad0[8];
	int m_i0C;
	const void *m_p10;
	unsigned char m_pad1[0x20 - 0x14];
};

class __declspec(novtable) BeaconClientUpdate : public Rva00362EC7
{
public:
	BeaconClientUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BeaconClientUpdate();

};

BeaconClientUpdate::BeaconClientUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva00362EC7(thing, moduleData)
{
	m_i0C = 0;
	*reinterpret_cast<char **>(this) = &PointDefenseLaserUpdate_vftable;
	m_p10 = (*(OpaqueGlobal **)&TheGameLogic)->m_p40;
}

// ??1BeaconClientUpdate@@ present-unmatched
BeaconClientUpdate::~BeaconClientUpdate()
{
}
