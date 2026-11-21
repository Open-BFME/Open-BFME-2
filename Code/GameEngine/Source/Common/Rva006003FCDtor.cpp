// cl: /MD /EHsc
//
// ??1Rva006003FC@@UAE@XZ @0x006003FC 54B and ??_GRva006003FC@@UAEPAXI@Z
// @0x006004A5 28B. Dual-vtable dtor: stores derived vtable 0x0087A638,
// calls member dtor ??1Rva00600084@@UAE@XZ at +8, then stores base vtable
// 0x007C6F20 inline via the empty base dtor. Same recipe as
// BfmeDualVtableReleaseDtor.cpp. Evidence: ctor 0x00600432 stores the same
// 0x0087A638; deleting dtor 0x006004A5 calls 0x006003FC then operator
// delete; callers 0x005FB1D6/0x006004A8 plus jmp thunks 0x005FB20A/0x005FB3DF.

namespace StrategicHUD {
class BattlePromptPlayerPageMovieClip
{
public:
	virtual ~BattlePromptPlayerPageMovieClip();
};
}

// The base is the canonical Rva0007DF07 (table 0x007C6F20), as the ctor's unit
// Rva00600352.cpp spells it: its empty inline dtor is the inline base-table store,
// and the derived table's first slot is this class's own deleting dtor.
#include "../../Include/Common/Rva0007DF07.h"

class Object;

class Rva006003FC : public Rva0007DF07
{
public:
	virtual ~Rva006003FC();
	virtual void rva006003AD();
	virtual void rva006003A5(Object *obj);
	virtual void slot03(Object *obj);
	virtual void slot04(Object *obj);

private:
	StrategicHUD::BattlePromptPlayerPageMovieClip m_member08;
};

Rva006003FC::~Rva006003FC()
{
}
