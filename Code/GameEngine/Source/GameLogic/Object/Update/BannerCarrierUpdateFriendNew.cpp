// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BannerCarrierUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E173, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x496A98. Class identity is the
// "BannerCarrierUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BannerCarrierUpdate
{
public:
	BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@BannerCarrierUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BannerCarrierUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BannerCarrierUpdate(thing, moduleData));
}
