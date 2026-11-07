// cl: -DNDEBUG -MD -GX- -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw

struct FieldParse;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
#include "../../../../../../GameEngine/Include/Common/INI/INI.h"
#include "../../../../../../GameEngine/Include/Common/ModuleData.h"

// Native 0x306A6E..0x306A9B allocates eight bytes and only writes vptr VA
// 0xC4ED70: the data is a plain ModuleData (Snapshot vptr + tag key), and
// 0xC4ED70 is ModuleData's 31 default slots, the table every ModuleData
// class without overrides folds to. This differs from the recovered
// 0x14-byte ModuleData constructor at 0x6024FD (vptr VA 0xC7A808).
class W3DDebrisDrawModuleData : public ModuleData
{
public:
	W3DDebrisDrawModuleData() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DDebrisDraw.h
class W3DDebrisDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *W3DDebrisDraw::friend_newModuleData(INI *ini)
{
	W3DDebrisDrawModuleData *data = ::new W3DDebrisDrawModuleData;
	if (ini)
		ini->initFromINI(data, 0);
	return data;
}
