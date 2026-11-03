// cl: /O2 /MD /GX /DNDEBUG /arch:SSE
//
// ??0DeployStyleAIUpdateModuleData@@QAE@XZ, retail 0x00255154 (42 bytes).
// Frameless ctor over the pinned Transport base (0x0026E5D7): the compiler
// installs the class's own vftable (0x00BF3440, slot 0 the rowed deleting
// dtor 0x00255F54; the dtor is declared, rowed elsewhere), then zeroes the
// unpack time at +0x64 plus the pack time at +0x68, clears the three turret
// bools at +0x6C/+0x6D/+0x6E, sets must-deploy-to-attack at +0x6F, and nulls
// the deployed attribute modifier at +0x70. Flat classes throughout (no
// declared dtors anywhere) keep the body frameless. Field identity is the
// rowed base-call buildFieldParse proc at 0x0024D1CB (Transport base proc
// plus table 0x00BEECB0 holding UnpackTime at +0x64 through
// DeployedAttributeModifier at +0x70, five of seven fields matching BFME1's
// DeployStyleAIUpdateModuleData table verbatim). Sole raw caller is the
// rowed ModuleData factory 0x0025517E (news 0x74); this row supersedes the
// ctor pin.
//
// Scheduling lever (RebuildHole/WeaponFire address-take law, third instance):
// retail wants xor-zero, then vtable, then zeros. A plain source order sinks
// the vtable below the zeros under /O1 and /O2, while a barrier pins it above
// the xor (too coarse: it traps every hoist). Two sourced-before pointer
// locals (one per store that must stay below the vtable) commit exactly those
// stores to source position, folding to addressing mode with zero emitted
// bytes, while the reg-only xor still floats above the vtable. 42 of 42.

#include "../../../../../Include/GameLogic/Module/TransportAIUpdateModuleData.h"

class DeployStyleAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	DeployStyleAIUpdateModuleData();
	virtual ~DeployStyleAIUpdateModuleData();

private:
	int m_unpackTime;							// +0x64
	int m_packTime;								// +0x68
	bool m_resetTurretBeforePacking;			// +0x6C
	bool m_turretsFunctionOnlyWhenDeployed;		// +0x6D
	bool m_turretsMustCenterBeforePacking;		// +0x6E
	bool m_mustDeployToAttack;					// +0x6F
	void *m_deployedAttributeModifier;			// +0x70
};

// ??0DeployStyleAIUpdateModuleData@@QAE@XZ @0x255154
inline DeployStyleAIUpdateModuleData::DeployStyleAIUpdateModuleData()
	: TransportAIUpdateModuleData()
{
	int *unpackTime = &m_unpackTime;
	void **attributeModifier = &m_deployedAttributeModifier;
	*attributeModifier = 0;
	*unpackTime = 0;
	m_packTime = 0;
	m_resetTurretBeforePacking = false;
	m_turretsFunctionOnlyWhenDeployed = false;
	m_turretsMustCenterBeforePacking = false;
	m_mustDeployToAttack = true;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeDeployStyleAIUpdateModuleDataInlineAnchor@@YAXPAVDeployStyleAIUpdateModuleData@@@Z absent-from-retail
void _bfmeDeployStyleAIUpdateModuleDataInlineAnchor(DeployStyleAIUpdateModuleData *deployStyleAIUpdateModuleData)
{
    deployStyleAIUpdateModuleData->DeployStyleAIUpdateModuleData::DeployStyleAIUpdateModuleData();
}
#pragma inline_depth()
