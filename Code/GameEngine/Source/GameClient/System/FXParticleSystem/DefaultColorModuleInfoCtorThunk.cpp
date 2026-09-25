// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE

// Open-BFME5: DefaultColorModuleInfo default constructor @0x55BC39.
// Retail: own vtable, eight RGBColorKeyframe elements at +4 built by the
// rowed vector_constructor_iterator helper through the rowed element
// default at 0x00001E67, then an inline-zeroed trailing random variable.
// The element's declared (never defined) destructor carries the EH frame.

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

class RGBColorKeyframe
{
public:
	RGBColorKeyframe();

private:
	char m_data[0x10];
};

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

class DefaultColorModuleInfo : public Snapshot
{
public:
	DefaultColorModuleInfo();
	virtual ~DefaultColorModuleInfo();

private:
	RGBColorKeyframe m_keys[8];
	GameClientRandomVariable m_trailing;
};

// ??0DefaultColorModuleInfo@FXParticleSystem@@QAE@XZ
DefaultColorModuleInfo::DefaultColorModuleInfo()
{
}

}
