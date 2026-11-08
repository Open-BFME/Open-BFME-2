// cl: /D_OPERATOR_NEW_DEFINED_ /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0006933D@Rva0006933D@@QAEHXZ @0x0006933D 113B
// Chain from 0x000687B8: calls rowed 0x00067878 then 0x000687B8 on same this,
// releases holder at +0x3818, clears BfmeResetTextureRef at +0x381C/+0x3828/
// +0x3838/+0x3844, releases holder at +0x37C0. Evidence: chain lane; callees
// rowed Rva00067878Clear Rva000687B8 BfmeResetTextureRefClear; neighbours
// share /O1; layout extends Rva000686F2/Rva000687B8 class to 0x3848.
struct RefObj0006933D
{
	virtual void v0();
	int m_ref;
};
struct BfmeResetResource;
#include "../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h"
class Rva000687B8
{
public:
	void rva000687B8();
};
int BaseHeightMapRenderObjClass::rva0006933D()
{
	rva00067878();
	((Rva000687B8 *)this)->rva000687B8();
	RefObj0006933D *a = (RefObj0006933D *)field3818;
	if (a)
	{
		if (--a->m_ref == 0)
			a->v0();
		field3818 = 0;
	}
	((BfmeResetTextureRef *)&field381C)->clear();
	((BfmeResetTextureRef *)&field3828)->clear();
	((BfmeResetTextureRef *)&field3838)->clear();
	((BfmeResetTextureRef *)&field3844)->clear();
	RefObj0006933D **slot = (RefObj0006933D **)&m_map;
	RefObj0006933D *b = *slot;
	if (b)
	{
		if (--b->m_ref == 0)
			b->v0();
		*slot = 0;
	}
	return 0;
}
