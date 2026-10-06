// cl: /DNDEBUG /MD /EHsc /Ob2
// ?rva00561527@Rva00561527@@QAEXPAVXfer@@@Z @0x00561527 28B evidence: Version1 0x000053EE then Lightning xfer 0x005614D9 on base at +0x18; caller jmp 0x003ABBC6.
// Honest-address wrapper (naming rule).
class Xfer
{
public:
	void Version1();
};

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
	};

	GameClientRandomVariable();
	void setRange(float low, float high, DistributionType type = UNIFORM);

private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

namespace FXParticleSystem
{

class LightningDrawModuleInfoBase
{
public:
	virtual ~LightningDrawModuleInfoBase();
};

class LightningDrawModuleInfo : public LightningDrawModuleInfoBase
{
public:
	LightningDrawModuleInfo();
	virtual ~LightningDrawModuleInfo();
protected:
	virtual void xfer(Xfer *xfer);

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	float m_28;
	bool m_2c;
};

}

class Pad018
{
public:
	virtual ~Pad018();
private:
	char m_pad[0x18 - 4];
};

class Rva00561527 : public Pad018, public FXParticleSystem::LightningDrawModuleInfo
{
public:
	void rva00561527(Xfer *xfer);
};

void Rva00561527::rva00561527(Xfer *xfer)
{
	xfer->Version1();
	FXParticleSystem::LightningDrawModuleInfo::xfer(xfer);
}
