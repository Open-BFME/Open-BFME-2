// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ob2

// LifeEventModuleInfo default constructor @0x564001 (91B). Retail: own
// vtable, an AsciiString at +4 (its inline ctor stores the null buffer and
// its rowed dtor 0x0048BA39 is what the state-1 unwind funclet calls on
// this+4), a GameClientRandomVariable at +8 zeroed inline then ranged (0, 0)
// through the rowed setRange 0x002341E7, and a zeroed int at +0x14.

#include "ascii_string.h"

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

class Xfer;

class Snapshot
{
public:
	Snapshot() {}
	Snapshot(const Snapshot &that);

	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class LifeEventModuleInfo : public Snapshot
{
public:
	LifeEventModuleInfo();
	virtual ~LifeEventModuleInfo();

private:
	AsciiString m_name;
	GameClientRandomVariable m_var;
	int m_14;
};

// ??0LifeEventModuleInfo@FXParticleSystem@@QAE@XZ @0x564001
LifeEventModuleInfo::LifeEventModuleInfo() : m_14(0)
{
	m_var.setRange(0.0f, 0.0f);
}

}
