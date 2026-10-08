// cl: -DNDEBUG -MD -GX- -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw

struct FieldParse;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *object, const FieldParse *fields);
};

// Native 0x306A6E..0x306A9B allocates eight bytes and only writes
// vptr VA 0xC4ED70. This differs from the recovered 0x14-byte ModuleData
// constructor at 0x6024FD (vptr VA 0xC7A808). Keep this data view anonymous.
class ModuleData;
// The table at VA 0xC4ED70 is shared (folded) by several ModuleData classes;
// PilotFindVehicleUpdateCtor.cpp defines the unit-level symbol for it.
extern "C" char PilotFindVehicleUpdate_vftable;
struct Rva00306A6EData {
    Rva00306A6EData() : vtable(reinterpret_cast<void *const *>(&PilotFindVehicleUpdate_vftable)) {}
    void *const *vtable;
    unsigned int opaque04;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DDebrisDraw.h
class W3DDebrisDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *W3DDebrisDraw::friend_newModuleData(INI *ini)
{
	Rva00306A6EData *data = ::new Rva00306A6EData;
	if (ini)
		ini->initFromINI(data, 0);
	return reinterpret_cast<ModuleData *>(data);
}
