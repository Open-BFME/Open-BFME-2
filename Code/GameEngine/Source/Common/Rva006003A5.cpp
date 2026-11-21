// cl: /MD
// ?rva006003A5@Rva006003FC@@UAEXPAVObject@@@Z @0x006003A5 8B vslot.
// Retail add ecx,8 then jmp performUpgradeFX 0x0047A69C. Evidence: vslot lane;
// slot 2 of 0x0087A638 class of ??1Rva006003FC@@UAE@XZ; pin-only callee
// ?performUpgradeFX@UpgradeMuxData@@QBEXPAVObject@@@Z; tail return-mem-method
// gives add-jmp at /O1.
class Object;
class UpgradeMuxData {
public: void performUpgradeFX(Object *obj) const;
};
class Xfer;
#include "../../Include/GameClient/EmissionVelocityInfo.h"
namespace FXParticleSystem
{
}
// Retail table 0x0087A638 slots 2-4 all hold this body: identical-code folding
// merged three virtuals that forward to the +8 upgrade mux. The base is the
// canonical Rva0007DF07 (vptr, +4).
#include "../../Include/Common/Rva0007DF07.h"

class Rva006003FC : public Rva0007DF07 {
public:
	virtual void rva006003AD();
	virtual void rva006003A5(Object *obj);
	virtual void slot03(Object *obj);
	virtual void slot04(Object *obj);
private: UpgradeMuxData m_mux;
};
void Rva006003FC::rva006003A5(Object *obj)
{
	m_mux.performUpgradeFX(obj);
}

// ?slot03@Rva006003FC@@UAEXPAVObject@@@Z and ?slot04@... @0x006003A5 8B:
// slots 3 and 4 of 0x0087A638, folded into slot 2's body.
void Rva006003FC::slot03(Object *obj)
{
	m_mux.performUpgradeFX(obj);
}

void Rva006003FC::slot04(Object *obj)
{
	m_mux.performUpgradeFX(obj);
}

// ?rva004EC05A@Rva004EC05A@@QAEXPAX@Z @0x004EC05A 8B.
// Retail adds 0x38 to ECX and tail-jumps to the shared three-byte ret-4 body
// at 0x0047A69C. That body has unrelated aliases from ICF; call its rowed
// EmissionVelocityInfo::DoXfer owner here. Keep the single stack word opaque
// at this wrapper; pass it through in the callee's Xfer-reference view without
// loading it. The +0x38 view does not identify the outer target class.
class Rva004EC05A
{
public:
	void rva004EC05A(void *opaque_arg);

private:
	char m_pad[0x38];
	FXParticleSystem::EmissionVelocityInfo m_xfer;
};

void Rva004EC05A::rva004EC05A(void *opaque_arg)
{
	m_xfer.FXParticleSystem::EmissionVelocityInfo::DoXfer(*(Xfer *)opaque_arg);
}
