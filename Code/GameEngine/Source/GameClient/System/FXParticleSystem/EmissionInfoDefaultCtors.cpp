// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE

// Emission info default constructors.
//
// SphericalEmissionVelocityInfo retail 0x003A721F: implicit base, own
// vtable 0x00C1BC30, inline zeroing of the single random variable, then
// setRange(0, 0) through the default UNIFORM distribution at rowed
// 0x002341E7. Needs /EHsc (outlined prologue with unwind state), unlike
// the /GX- copy ctors in EmissionInfoCopyCtors.cpp.

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
	};

	GameClientRandomVariable() : m_type(CONSTANT), m_low(0.0f), m_high(0.0f) {}
	void setRange(float low, float high, DistributionType type = UNIFORM);

private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

#include "../../../../Include/GameClient/EmissionVolumeInfo.h"
namespace FXParticleSystem
{

class EmissionVelocityInfo : public Snapshot
{
public:
	virtual ~EmissionVelocityInfo() {}
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);
};

class SphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
	SphericalEmissionVelocityInfo();
	virtual ~SphericalEmissionVelocityInfo() {}

private:
	GameClientRandomVariable m_var0;
};

// ??0SphericalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ @0x3A721F
inline SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo()
{
	m_var0.setRange(0.0f, 0.0f);
}

class CylindricalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
	CylindricalEmissionVelocityInfo();
	virtual ~CylindricalEmissionVelocityInfo();

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
};

// ??0CylindricalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ @0x3A7489
// (Outward folds its default body here too; pin 5263.)
CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo()
{
	m_var0.setRange(0.0f, 0.0f);
	m_var1.setRange(0.0f, 0.0f);
}

class OrthoEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
	OrthoEmissionVelocityInfo();
	virtual ~OrthoEmissionVelocityInfo();

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
};

// ??0OrthoEmissionVelocityInfo@FXParticleSystem@@QAE@XZ @0x3A6FD0
OrthoEmissionVelocityInfo::OrthoEmissionVelocityInfo()
{
	m_var0.setRange(0.0f, 0.0f);
	m_var1.setRange(0.0f, 0.0f);
	m_var2.setRange(0.0f, 0.0f);
}

// Retail 0x3A6D5F orders the flag store before the single vtable store:
// the flag is set by the volume base's own inline default (its vtable
// store dies against the derived one, as in the velocity defaults above),
// so the bool lives in the base here. The virtual destructor is only
// declared: it resolves to the folded 0x0049B47C family and supplies the
// unwinding behind the EH frame.

class TerrainFireEmissionInfo : public EmissionVolumeInfo
{
public:
	TerrainFireEmissionInfo();
	virtual ~TerrainFireEmissionInfo();

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	float m_unknown2C;
};

// ??0TerrainFireEmissionInfo@FXParticleSystem@@QAE@XZ @0x3A6D5F
TerrainFireEmissionInfo::TerrainFireEmissionInfo()
{
	m_var0.setRange(0.0f, 0.0f);
	m_var1.setRange(0.0f, 0.0f);
	m_var2.setRange(0.0f, 0.0f);
	m_unknown2C = 0.7f;
}

// DefaultPhysicsModuleInfo retail 0x0055EE5E, the out-of-line default the
// DefaultModuleTemplate<3> constructor calls. The base is Snapshot: the
// folded 0x0049B47C destructor stores its vtable 0x00BBB554, and the base's
// unwind state is the one EH state retail sets. The WorldBuilder twin
// (0x0141ED90) builds the +0x04 coordinate through its own inline default
// (which leaves nothing behind in the release build), the random variable
// through its zeroing default, then assigns +0x10, zeroes the coordinate,
// sets the range and clears the two flags.
class DefaultPhysicsModuleInfo : public Snapshot
{
public:
	DefaultPhysicsModuleInfo();
	__declspec(noinline) virtual ~DefaultPhysicsModuleInfo();
	// Retail vtable 0x00C1BCB0 slot 1 is the exported LoadPostProcess 0x000B3FD0.
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &);

private:
	struct PhysicsCoord
	{
		PhysicsCoord() {}
		void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }

		float x;
		float y;
		float z;
	};

	PhysicsCoord m_unknown04;
	float m_unknown10;
	GameClientRandomVariable m_unknown14;
	bool m_unknown20;
	bool m_unknown21;
};

// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ @0x55EE5E
__declspec(noinline) DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo()
{
	m_unknown10 = 0.0f;
	m_unknown04.zero();
	m_unknown14.setRange(0.0f, 0.0f);
	m_unknown20 = false;
	m_unknown21 = false;
}

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0OutwardEmissionVelocityInfo@FXParticleSystem@@QAE@XZ=??0CylindricalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ")

// ??0SphericalEmissionVelocityInfo is a header inline elsewhere: another unit
// emits a select-any copy of it, so a strong definition here was a duplicate
// symbol in the linked build. This anchor only makes this unit emit its copy
// for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitEmissionInfoDefaultCtors@@YAXPAVSphericalEmissionVelocityInfo@FXParticleSystem@@@Z present-unmatched
void bfmeEmitEmissionInfoDefaultCtors(FXParticleSystem::SphericalEmissionVelocityInfo *p)
{
	p->SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo();
}
#pragma inline_depth()
