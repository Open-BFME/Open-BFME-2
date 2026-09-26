// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ
// partial score=0.98 date=2026-09-26
// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ
// partial score=0.98 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE

// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ @0x0055EE5E 109B
// Retail stores info vtable 0x0081BCB0, inline-zeroes floats at +4/+8/+C/+10
// and the random variable at +0x14, runs setRange(0, 0) via rowed 0x002341E7,
// then zeroes flags at +0x20/+0x21. BFME1 donor fx_particle_system.h gives
// floats+int+var layout; BFME2 adds 2 bools; int stored as float (movss).
// Single EH state from the virtual base. Caller 0x003A9852
// (DefaultModuleTemplate@$02 default) calls here at the site its BFME1 donor
// calls the physics info default.

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

class DefaultPhysicsModuleInfoBase
{
public:
	virtual ~DefaultPhysicsModuleInfoBase();
};

class DefaultPhysicsModuleInfo : public DefaultPhysicsModuleInfoBase
{
public:
	DefaultPhysicsModuleInfo();
	virtual ~DefaultPhysicsModuleInfo();

private:
	float m_field0;
	float m_field1;
	float m_field2;
	float m_field3;
	GameClientRandomVariable m_var1;
	bool m_flag20;
	bool m_flag21;
};

// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ present-unmatched
DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo()
	: m_field0(0.0f)
	, m_field1(0.0f)
	, m_field2(0.0f)
	, m_field3(0.0f)
{
	m_var1.setRange(0.0f, 0.0f);
	m_flag20 = false;
	m_flag21 = false;
}

}
