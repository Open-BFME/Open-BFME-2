// ??0LightningEmissionInfo@FXParticleSystem@@QAE@XZ
// partial score=0.93 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ob1 /Ireference/shims/moduledata
// Retail55D9A5..55DB41 (412B) LightningEmissionInfo default constructor.
// Target layout20..80 expands donor/sibling random-variable default idiom.
// Parent class shape carried from existing FX source; complete vtable identity
// still needs independent target verification before landing.
#include "Common/Snapshot.h"

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

namespace FXParticleSystem {
class EmissionVolumeInfo:public Snapshot {public:EmissionVolumeInfo(){flag=false;}virtual ~EmissionVolumeInfo();virtual void v1()=0;virtual const char *GetSnapshotName();bool flag;};
struct LightningCoordInfo {float x,y,z;};
class LightningEmissionInfo:public EmissionVolumeInfo {public:LightningEmissionInfo();virtual ~LightningEmissionInfo();LightningCoordInfo unknown08,unknown14;GameClientRandomVariable var0,var1,var2,var3,var4,var5,var6,var7,var8;};
// Native55D9A5..55DB41 (412B) and rowed template caller3A6C59 supply
// identity and base flag04/two coordinates08+14/nine random variables20..80.
// Existing source sibling DefaultUpdateModuleInfo supplies default-range idiom.
LightningEmissionInfo::LightningEmissionInfo() {
 unknown08.x=0.0f;unknown08.y=0.0f;unknown08.z=0.0f;
 unknown14.x=0.0f;unknown14.y=0.0f;unknown14.z=0.0f;
 var0.setRange(0.0f,0.0f);var1.setRange(0.0f,0.0f);var2.setRange(0.0f,0.0f);
 var3.setRange(0.0f,0.0f);var4.setRange(0.0f,0.0f);var5.setRange(0.0f,0.0f);
 var6.setRange(0.0f,0.0f);var7.setRange(0.0f,0.0f);var8.setRange(0.0f,0.0f);
}
}
