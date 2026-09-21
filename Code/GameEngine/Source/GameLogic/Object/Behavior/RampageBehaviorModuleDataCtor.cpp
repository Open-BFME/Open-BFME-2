// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0RampageBehaviorModuleData@@QAE@XZ, retail 0x00458C0F, 112 bytes.
// ModuleData-side ctor: vtable 0xC40EF8, RequiredUpgrade vector at +8 via
// Vector_base alias (0x211E58) cleared via erase (0x2CCFC), HealthThreshold
// at +14 from global+0xB8, LifeTimer/Angry/Reset at +18/+1C/+20 zero,
// EnemyCheckRange at +24 float-zero, EnemyThreshold at +28 zero. Table
// 0xC40E78 carries all seven fields; factory 0x24AD38 news 0x2C sole caller;
// rowed poolkey 0x458B0A ends where proc 0x458B4F begins. Shape follows
// CrateCollide (empty base + declared-only dtor for EH, explicit vtable,
// all-init-list) with vector clear in body.

#include <vector>
#include <string.h>

#include <vector>

class AsciiString
{
public:
	AsciiString();
	~AsciiString();

private:
	void *m_data;
};

class BehaviorModuleData
{
public:
	BehaviorModuleData() {}
	~BehaviorModuleData();

private:
};

struct GlobalWithB8
{
	int m_pad[0xB8 / 4];
	int m_value;
};

extern GlobalWithB8 *g_rampageGlobal;

class RampageBehaviorModuleData : public BehaviorModuleData
{
public:
	RampageBehaviorModuleData();

private:
	const void *m_vtable; // +0x00
	unsigned int m_unused04; // +0x04
	_STL::vector<AsciiString> m_requiredUpgrade; // +0x08
	int m_healthThreshold; // +0x14
	int m_lifeTimer; // +0x18
	int m_angryLifeTimer; // +0x1C
	int m_resetTimer; // +0x20
	float m_enemyCheckRange; // +0x24
	int m_enemyThreshold; // +0x28
};

// ??0RampageBehaviorModuleData@@QAE@XZ @0x458C0F
RampageBehaviorModuleData::RampageBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C40EF8))
	, m_healthThreshold(g_rampageGlobal->m_value)
	, m_lifeTimer(0)
	, m_angryLifeTimer(0)
	, m_resetTimer(0)
	, m_enemyCheckRange(0.0f)
	, m_enemyThreshold(0)
{
	m_requiredUpgrade.clear();
}
