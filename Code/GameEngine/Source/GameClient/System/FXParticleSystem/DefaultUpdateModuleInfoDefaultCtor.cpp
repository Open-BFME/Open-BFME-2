// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE

// ??0DefaultUpdateModuleInfo@FXParticleSystem@@QAE@XZ @0x0055F529 339B
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/FXParticleSystem/DefaultUpdateModuleInfoCtorThunk.cpp
// (5 vars + extra, all setRange(0,0,UNIFORM)). BFME2 retail extends to 8 vars
// + int extra at +0x40: pattern 0,1,0,0,1,0,0,1 from disasm, extra=1.
// Callers: DefaultModuleTemplate<$01> ctor at 0x003A98D8, FUN_0095f9b4 at 0x0055F9DC.
// Callee: GameClientRandomVariable::setRange at rowed 0x002341E7.

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

class Snapshot
{
public:
	virtual ~Snapshot();
};

class DefaultUpdateModuleInfo : public Snapshot
{
public:
	DefaultUpdateModuleInfo();
	virtual ~DefaultUpdateModuleInfo();

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	GameClientRandomVariable m_var3;
	GameClientRandomVariable m_var4;
	int m_extra;
	GameClientRandomVariable m_var5;
	GameClientRandomVariable m_var6;
	GameClientRandomVariable m_var7;
};

DefaultUpdateModuleInfo::DefaultUpdateModuleInfo()
{
	m_var0.setRange(0.0f, 0.0f);
	m_var1.setRange(1.0f, 1.0f);
	m_var2.setRange(0.0f, 0.0f);
	m_var3.setRange(0.0f, 0.0f);
	m_var4.setRange(1.0f, 1.0f);
	m_extra = 1;
	m_var5.setRange(0.0f, 0.0f);
	m_var6.setRange(0.0f, 0.0f);
	m_var7.setRange(1.0f, 1.0f);
}

}
