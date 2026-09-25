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

}
