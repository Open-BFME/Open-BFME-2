// cl: /O1 /arch:SSE /G7 /Oy- /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?onBodyDamageStateChange@SpawnBehavior@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z @0x004604D5 177B.
// Damage-state SSB: old/new as ints, ModuleData at +4 via secondary this, count at +0x54.
// Evidence: VTABLE slot 2 of 0x0084259C plus slot 21 offset 0x54 of 0x00842550, class SpawnBehavior,
// donor ZH SpawnBehavior.h, callees rva00460175 plus createSpawn rowed, ret 0xC with EBP frame.
class DamageInfo;
enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_DAMAGED = 1,
	BODY_REALLY_DAMAGED = 2
};
struct SpawnBehaviorModuleDataView
{
	char pad00[8];
	int m_spawnNumberData;
	char pad0C[0x170 - 0x0C];
	unsigned char m_170;
};
class UpdateModule
{
public:
	virtual void updateDummy();
	const SpawnBehaviorModuleDataView *m_moduleData;
	char pad08[0x20 - 8];
};
class SpawnBehaviorInterface
{
public:
	virtual void spawnAnchor();
};
class DieModuleInterface
{
public:
	virtual void dieAnchor();
};
class DamageModuleInterface
{
public:
	virtual void onDamage();
	virtual void onHealing();
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
};
class SpawnExtraBase
{
public:
	virtual void extraAnchor();
};
class UpgradeMux
{
public:
	virtual void muxAnchor();
	UpgradeMux();
private:
	bool m_executed;
	char pad05[3];
};
class ThingTemplate;
class SpawnBehavior : public UpdateModule,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnExtraBase,
	public UpgradeMux
{
public:
	void rva00460175(int v);
	void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
private:
	bool createSpawn();

	const ThingTemplate *m_spawnTemplate;
	int m_oneShotCountdown;
	int m_framesToWait;
	int m_firstBatchCount;
	char pad48[0x54 - 0x48];
	int m_54;
};
// ?onBodyDamageStateChange@SpawnBehavior@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z
void SpawnBehavior::onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState)
{
	(void)damageInfo;
	const SpawnBehaviorModuleDataView *md = m_moduleData;
	if (!md)
		return;
	if (!md->m_170)
		return;
	if (oldState == 0)
	{
		if (newState != 1)
			return;
		int v = m_54 / 3;
		rva00460175(v);
		return;
	}
	if (oldState == 1 && newState == 2)
	{
		int v = m_54 / 2;
		rva00460175(v);
		return;
	}
	if (oldState == 2 && newState == 1)
	{
		int want = md->m_spawnNumberData;
		int cur = m_54;
		int n = (want - cur) / 2;
		if (n <= 0)
			return;
		SpawnBehavior *self = this;
		int i = n;
		do
		{
			self->createSpawn();
			--i;
		} while (i != 0);
		return;
	}
	if (oldState != 1 || newState != 0)
		return;
	int want = md->m_spawnNumberData;
	int cur = m_54;
	int n = want - cur;
	if (n <= 0)
		return;
	SpawnBehavior *self = this;
	int i = n;
	do
	{
		self->createSpawn();
		--i;
	} while (i != 0);
}
