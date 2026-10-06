// ??0LightningEmissionInfo@FXParticleSystem@@QAE@XZ
// partial score=0.9785 date=2026-10-06
// ??0LightningEmissionInfo@FXParticleSystem@@QAE@XZ
// partial score=0.95 date=2026-09-26
// ??0LightningEmissionInfo@FXParticleSystem@@QAE@XZ
// partial score=0.95 date=2026-09-26
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

namespace FXParticleSystem
{

class EmissionVelocityInfo
{
public:
	virtual ~EmissionVelocityInfo();
};

class SphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
	SphericalEmissionVelocityInfo();
	virtual ~SphericalEmissionVelocityInfo();

private:
	GameClientRandomVariable m_var0;
};

// ??0SphericalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ @0x3A721F
SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo()
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
class EmissionVolumeInfo
{
public:
	EmissionVolumeInfo() : m_flag(false) {}
	virtual ~EmissionVolumeInfo();

protected:
	bool m_flag;
};

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

// ??0LightningEmissionInfo@FXParticleSystem@@QAE@XZ @0x0055D9A5 412B
// Pinned name; caller ??0LightningEmissionModuleTemplate@FXParticleSystem@@QAE@XZ
// at 0x003A6C88; vtable 0x00C1BBA0 (RVA 0x0081BBA0); donor
// reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system.h
// LightningEmissionInfo plus copy-ctor stash reverse/attempts/0x003a6af5.cpp
// (2 leading Point3D + 9 GameClientRandomVariable, 0x8C bytes).
struct Point3D
{
	float x;
	float y;
	float z;
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
public:
	LightningEmissionInfo();
	virtual ~LightningEmissionInfo();

private:
	Point3D m_point0;
	Point3D m_point1;
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	GameClientRandomVariable m_var3;
	GameClientRandomVariable m_var4;
	GameClientRandomVariable m_var5;
	GameClientRandomVariable m_var6;
	GameClientRandomVariable m_var7;
	GameClientRandomVariable m_var8;
};

LightningEmissionInfo::LightningEmissionInfo()
{
	m_point0.x = 0.0f;
	m_point0.y = 0.0f;
	m_point0.z = 0.0f;
	m_point1.x = 0.0f;
	m_point1.y = 0.0f;
	m_point1.z = 0.0f;
	m_var0.setRange(0.0f, 0.0f);
	m_var1.setRange(0.0f, 0.0f);
	m_var2.setRange(0.0f, 0.0f);
	m_var3.setRange(0.0f, 0.0f);
	m_var4.setRange(0.0f, 0.0f);
	m_var5.setRange(0.0f, 0.0f);
	m_var6.setRange(0.0f, 0.0f);
	m_var7.setRange(0.0f, 0.0f);
	m_var8.setRange(0.0f, 0.0f);
}

}
