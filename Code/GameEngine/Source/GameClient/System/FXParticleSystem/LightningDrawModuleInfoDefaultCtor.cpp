// cl: /DNDEBUG /MD /EHsc /Ob2 /Ireference/shims/moduledata

// LightningDrawModuleInfo default constructor.
//
// Retail 0x0056142E (171B) stores the info vtable (0xC1BD80), inline-zeroes
// three random variables at +4/+0x10/+0x1C, runs setRange(0, 0) on each
// through the rowed 0x002341E7, then zeroes the float at +0x28 and the flag
// byte at +0x2C. Single EH state from the virtual base (members are plain
// data plus trivial variables), same shape as the landed emission-velocity
// defaults in EmissionInfoDefaultCtors.cpp.

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

// Use the existing BFME2 Snapshot ABI and destructor provider.
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"

namespace FXParticleSystem
{

class LightningDrawModuleInfo : public Snapshot
{
public:
	LightningDrawModuleInfo();
	__declspec(noinline) virtual ~LightningDrawModuleInfo();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	float m_28;
	unsigned char m_2c;
};

// ??0LightningDrawModuleInfo@FXParticleSystem@@QAE@XZ @0x56142E
LightningDrawModuleInfo::LightningDrawModuleInfo()
{
	m_var0.setRange(0.0f, 0.0f);
	m_var1.setRange(0.0f, 0.0f);
	m_var2.setRange(0.0f, 0.0f);
	m_28 = 0.0f;
	m_2c = 0;
}

}
