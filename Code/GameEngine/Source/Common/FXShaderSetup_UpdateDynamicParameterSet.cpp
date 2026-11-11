// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// Dump-lane range 5: holder-gated render-state applier.
//
// ?UpdateDynamicParameterSet@FXShaderSetup@@UAEXI@Z, retail 0x00151D1A (69 bytes).
// Frameless thiscall: gates on the +8 holder's pointer, revalidates through
// the rowed 0x15148D getter, skips on zero +0x20, applies the rowed DX8
// render-state changes, forwards (arg, +0x20) to the rowed 0x1514B2 chain,
// then invokes vtable slot 0x104 on a fresh getter result. The +8 member
// serves two rowed method families (getter + chain).
// Early exits are bare returns (retail leaves eax undefined there).

class Rva0015148D
{
public:
	void *rva0015148D();
	void *m_ptr;
};

class Rva001514B2
{
public:
	void *rva001514B2(int, int);
	char m_pad00[0x18];
};

#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
#include "../../../Libraries/Source/WWVegas/WW3D2/FXShaderSetup.h"

class Rva00151D1AVt
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void v52() = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual void v56() = 0;
	virtual void v57() = 0;
	virtual void v58() = 0;
	virtual void v59() = 0;
	virtual void v60() = 0;
	virtual void v61() = 0;
	virtual void v62() = 0;
	virtual void v63() = 0;
	virtual void v64() = 0;
	virtual void __stdcall v65() = 0;
};

// ?UpdateDynamicParameterSet@FXShaderSetup@@UAEXI@Z
void FXShaderSetup::UpdateDynamicParameterSet(unsigned int a)
{
	Rva0015148D *holder = reinterpret_cast<Rva0015148D *>(&field08);
	if (field08 == 0) {
		return;
	}
	if (holder->rva0015148D() == 0) {
		return;
	}
	if (field20 == 0) {
		return;
	}
	DX8Wrapper::Apply_Render_State_Changes();
	reinterpret_cast<Rva001514B2 *>(&field08)->rva001514B2(a, reinterpret_cast<int>(field20));
	Rva00151D1AVt *vt = (Rva00151D1AVt *)holder->rva0015148D();
	vt->v65();
}
