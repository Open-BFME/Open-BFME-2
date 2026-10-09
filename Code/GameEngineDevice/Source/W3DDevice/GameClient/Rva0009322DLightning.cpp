// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ?target_0009322D@W3DSnowManager@@AAEXXZ @0x0009322D 180B (Ghidra splits it
// at 0x0009323B; the prologue and first override hop sit in 0x0009322D..0x0009323B).
// W3DSnowManager::update (0x000949D9) ends by calling it on the same receiver
// at 0x00094A8C, which proves the owner; the pinned name keeps the address.
// Donor: Open-BFME-1 W3DSnowManagerLightningRva00723B60.cpp (BFME 1 retail
// 0x00723B60) -- counts down the lightning flash while one is active, else
// rolls LightningChance and starts a new flash lasting LightningDuration
// scaled by Random_Float(0.7f 1.2f) (multiplier 0x3F000001 is the folded
// 1.2f - 0.7f). BFME 2 offsets from target reads: WeatherSetting +0x54 flag
// +0x64 duration +0x68 chance (BFME 1 +0x40/+0x50/+0x54); manager +0x50 flag
// and +0x54 countdown (BFME 1 +0x44/+0x48). Callees: rowed WWMath::Random_Float
// 0x00711B90 and pinned Overridable::getFinalOverride 0x001E35DF.

class WWMath
{
public:
	static float Random_Float();
	static float Random_Float(float min, float max) { return Random_Float() * (max - min) + min; }
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	__inline const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

private:
	const T *m_overridable;
};

class WeatherSetting : public Overridable
{
public:
	char m_unmodelled_08[0x54 - 0x08];
	bool m_lightningEnabled;
	char m_unmodelled_55[0x64 - 0x55];
	int m_lightningDuration;
	float m_lightningChance;
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

class W3DSnowManager
{
private:
	void target_0009322D(void);

	char m_unmodelled_00[0x50];
	bool m_lightningActive;
	char m_unmodelled_51[0x54 - 0x51];
	int m_lightningFrames;
};

void W3DSnowManager::target_0009322D(void)
{
	if (!TheWeatherSetting->m_lightningEnabled)
		return;
	if (m_lightningActive)
	{
		if (--m_lightningFrames > 0)
			return;
		m_lightningFrames = 0;
		m_lightningActive = false;
		return;
	}
	float chance = WWMath::Random_Float();
	if (chance < TheWeatherSetting->m_lightningChance)
	{
		m_lightningActive = true;
		m_lightningFrames = (int)(WWMath::Random_Float(0.7f, 1.2f) * TheWeatherSetting->m_lightningDuration + 0.5f);
	}
}
