// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE

// ??0RenderObjectUpdateModuleInfo@FXParticleSystem@@QAE@XZ @0x00561F99 489B
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/FXParticleSystem/FXParticleSystem_RenderObjectUpdateModuleInfo_ctor_Thunk.cpp
// (12 vars + m_mode=1, order 0,3,6,1,4,7,2,5,8,9,10,11 all setRange(0,0,UNIFORM)).
// BFME2 retail same order and offsets (+4..+0x88 step 0xC, mode at +0x94=1).
// Callers: RenderObjectUpdateModuleTemplate ctor at 0x003A80D7, FUN_009624de at 0x00562506.
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

class RenderObjectUpdateModuleInfo : public Snapshot
{
public:
	RenderObjectUpdateModuleInfo();
	virtual ~RenderObjectUpdateModuleInfo();

private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	GameClientRandomVariable m_var3;
	GameClientRandomVariable m_var4;
	GameClientRandomVariable m_var5;
	GameClientRandomVariable m_var6;
	GameClientRandomVariable m_var7;
	GameClientRandomVariable m_var8;
	GameClientRandomVariable m_var9;
	GameClientRandomVariable m_var10;
	GameClientRandomVariable m_var11;
	unsigned int m_mode;
};

RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo()
{
	m_var0.setRange(0.0f, 0.0f);
	m_var3.setRange(0.0f, 0.0f);
	m_var6.setRange(0.0f, 0.0f);
	m_var1.setRange(0.0f, 0.0f);
	m_var4.setRange(0.0f, 0.0f);
	m_var7.setRange(0.0f, 0.0f);
	m_var2.setRange(0.0f, 0.0f);
	m_var5.setRange(0.0f, 0.0f);
	m_var8.setRange(0.0f, 0.0f);
	m_var9.setRange(0.0f, 0.0f);
	m_var10.setRange(0.0f, 0.0f);
	m_var11.setRange(0.0f, 0.0f);
	m_mode = 1;
}

}
