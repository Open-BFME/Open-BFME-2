// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0SupplyTruckAIUpdateModuleData@@QAE@XZ, retail 0x004BF59F, 258 bytes.
// SupplyTruckAIUpdateModuleData ctor over the MaxHealth-led damage table
// 0xC5B228 (21 fields). All callees rowed: Vector_base 0x211E58,
// StringBase::set 0x55F5, clear/dtor fold 0x36410, isEmpty 0x1E2F,
// findFXList 0x1E281A. Factory 0x2513E8 news 0x64, sole caller.
// Empty UpdateModuleData base (inline-empty ctor + declared-only dtor)
// arms single-state EH with zero code (Topple precedent). Pre-vector
// stores (vtable, grab strings, cheer 200, remove/burning zeros) run in
// init-list order; post-vector stores follow retail body order.

#include <vector>

struct BfmeE16
{
	unsigned char m_pad[16];
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

	void set(const char *str);
	bool isEmpty() const;
	const char *c_str() const { return m_data ? (const char *)m_data + 8 : ""; }

private:
	void *m_data;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

class GlobalData
{
public:
	unsigned char m_pad[0x9DC];
	AsciiString m_healingBuff;
};

extern GlobalData *TheGlobalData;

class FXList;
class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

extern FXListStore *TheFXListStore;

class SupplyTruckAIUpdateModuleData : public UpdateModuleData
{
public:
	SupplyTruckAIUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	float m_maxHealth; // +8
	float m_initialHealth; // +0xC
	float m_maxHealthDamaged; // +0x10
	float m_maxHealthReallyDamaged; // +0x14
	float m_dodgePercent; // +0x18
	int m_enteringDamaged; // +0x1C
	int m_enteringReallyDamaged; // +0x20
	int m_recoveryTime; // +0x24
	unsigned char m_useDefault; // +0x28
	unsigned char m_pad29[3];
	AsciiString m_grabObject; // +0x2C
	AsciiString m_damagedAttr; // +0x30
	AsciiString m_reallyDamagedAttr; // +0x34
	int m_grabFX; // +0x38
	float m_grabDamage; // +0x3C
	float m_grabOffsetX; // +0x40
	float m_grabOffsetY; // +0x44
	const FXList *m_healingBuffFx; // +0x48
	float m_cheerRadius; // +0x4C
	unsigned char m_removeUpgrades; // +0x50
	unsigned char m_burningBehavior; // +0x51
	unsigned char m_pad52[2];
	int m_burningFX; // +0x54
	_STL::vector<BfmeE16> m_damageCreation; // +0x58
};

// ??0SupplyTruckAIUpdateModuleData@@QAE@XZ @0x4BF59F
SupplyTruckAIUpdateModuleData::SupplyTruckAIUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C5AFB8))
	, m_grabObject()
	, m_damagedAttr()
	, m_reallyDamagedAttr()
	, m_cheerRadius(200.0f)
	, m_removeUpgrades(0)
	, m_burningBehavior(0)
	, m_burningFX(0)
{
	m_maxHealth = 0.0f;
	m_maxHealthDamaged = 0.0f;
	m_maxHealthReallyDamaged = 0.0f;
	m_initialHealth = -1.0f;
	m_recoveryTime = 0;
	m_enteringDamaged = 0;
	m_enteringReallyDamaged = 0;
	m_dodgePercent = 0.0f;
	m_useDefault = 1;
	m_grabObject.set("EntThrownBuildingRock");
	m_grabDamage = 200.0f;
	m_grabFX = 0;
	m_healingBuffFx = 0;
	m_grabOffsetX = 0.0f;
	m_grabOffsetY = 0.0f;
	m_damagedAttr.clear();
	m_reallyDamagedAttr.clear();
	AsciiString &healingDefault = TheGlobalData->m_healingBuff;
	if (!healingDefault.isEmpty())
		m_healingBuffFx = TheFXListStore->findFXList(healingDefault.c_str());
}
