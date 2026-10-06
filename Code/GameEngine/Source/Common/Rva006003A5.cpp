// cl: /MD
// ?rva006003A5@Rva006003FC@@QAEXPAVObject@@@Z @0x006003A5 8B vslot.
// Retail add ecx,8 then jmp performUpgradeFX 0x0047A69C. Evidence: vslot lane;
// slot 2 of 0x0087A638 class of ??1Rva006003FC@@UAE@XZ; pin-only callee
// ?performUpgradeFX@UpgradeMuxData@@QBEXPAVObject@@@Z; tail return-mem-method
// gives add-jmp at /O1.
class Object;
class UpgradeMuxData {
public: void performUpgradeFX(Object *obj) const;
};
class Xfer;
namespace FXParticleSystem
{
class EmissionVelocityInfo
{
public:
	virtual ~EmissionVelocityInfo();
	virtual void DoXfer(Xfer &xfer);
};
}
class Rva006003FC {
public: void rva006003A5(Object *obj);
private: char m_pad[8];
         UpgradeMuxData m_mux;
};
void Rva006003FC::rva006003A5(Object *obj)
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
