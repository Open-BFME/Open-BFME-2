// ?updateIniSettings@W3DSnowManager@@UAEXXZ
// partial score=0.983 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour W3DSnow.cpp update with target-specific accumulator fields.
// The two final helpers retain address-derived names; their results are unused.
class SubsystemInterface {
public:
    virtual ~SubsystemInterface();
private:
    unsigned int m_targetBase[2];
};

class SnowManager : public SubsystemInterface {
public:
    virtual ~SnowManager();
    virtual void init();
    virtual void targetSlot2();
    virtual void targetSlot3();
    virtual void targetSlot4();
    virtual void targetSlot5();
    virtual void targetSlot6();
    virtual void targetSlot7();
    virtual void targetSlot8();
    virtual void reset();
    virtual void update();
    virtual void targetSlot11();
    virtual void targetSlot12();
    virtual void targetSlot13();
    // Pure here, as Code/GameEngine/Source/GameClient/Snow.cpp models it: this base
    // body is not recovered yet (retail 0x00201165, pinned), so the call below
    // resolves to the pin through the alternatename at the foot of this unit.
    virtual void updateIniSettings() = 0;
protected:
    float *m_startingHeights;
    float m_time, m_velocity, m_fullTimePeriod;
    unsigned char m_target1C[0x2C];
    float m_targetFloat48, m_targetFloat4C;
    unsigned char m_target50[0x24];
};

class TextureClass;

template <class T>
class RefCountPtr
{
public:
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }

	T *m_ptr;
};

class TextureClass
{
public:
	void Release_Ref();
};

// BFME 2 particle-texture loader (pinned at 0x00132D89); its result is a
// RefCountPtr<TextureClass> the caller copies and releases.
class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *filename, int a, int b);

class W3DSnowManager : public SnowManager {
public:
    virtual void update();
    virtual void updateIniSettings();
private:
    // Call views: thiscall without explicit arguments; original returns unknown.
    void target_00094652();
    void target_0009322D();
    unsigned char m_target74[0x4];
    RefCountPtr<TextureClass> m_snowTexture;                  // +0x78
    unsigned char m_target7C[0x18];
    float m_targetFloat94, m_targetFloat98, m_targetFloat9C;
    unsigned char m_targetA0[0x10];
};

typedef char SnowBaseExtent[sizeof(SnowManager) == 0x74 ? 1 : -1];
typedef char W3DSnowExtent[sizeof(W3DSnowManager) == 0xB0 ? 1 : -1];

class WW3D {
public:
    static unsigned int SyncTime;
    static unsigned int PreviousSyncTime;
};
extern float __cdecl Rva000930C0(float, float);

void W3DSnowManager::update()
{
    float oldTime = m_time;
    unsigned int elapsed = WW3D::SyncTime - WW3D::PreviousSyncTime;
    m_time += (float)elapsed * 0.001f;
    m_time = Rva000930C0(m_time, m_fullTimePeriod);
    m_targetFloat94 += (m_time - oldTime) * m_velocity;
    m_targetFloat98 += (m_time - oldTime) * m_targetFloat48;
    m_targetFloat9C += (m_time - oldTime) * m_targetFloat4C;
    target_00094652();
    target_0009322D();
}

// Overridable/OVERRIDE as Snow.cpp models them: the final override is found
// through the out-of-line getFinalOverride.
class Overridable
{
public:
    virtual ~Overridable();
    Overridable *m_nextOverride;
    bool m_isOverride;
    const Overridable *getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->getFinalOverride();
        return this;
    }
};

// BFME 2 WeatherSetting: the snow texture name (a length-prefixed string
// whose characters start at +8) is at +0x18.
class WeatherSetting : public Overridable
{
public:
    unsigned char m_unrecovered0C[0x18 - 0x0C];
    const char *m_snowTextureData;                            // +0x18
    const char *getSnowTexture() const { return m_snowTextureData ? m_snowTextureData + 8 : ""; }
};

template <class T> class OVERRIDE {
public:
    const T *m_overridable;
    const T *operator->() const
    {
        if (!m_overridable) return 0;
        return static_cast<const T *>(m_overridable->getFinalOverride());
    }
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

//-------------------------------------------------------------------------------------------------
/** Zero Hour W3DSnowManager::updateIniSettings: BFME 2 always reloads the snow
	* texture, through the particle-texture loader, after the base update. */
//-------------------------------------------------------------------------------------------------
void W3DSnowManager::updateIniSettings()
{
    SnowManager::updateIniSettings();
    m_snowTexture = BFME2LoadParticleTexture(TheWeatherSetting->getSnowTexture(), 0, 0);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?SyncTime@WW3D@@2IA=?SyncTime@WW3D@@0IA")
#pragma comment(linker, "/alternatename:?PreviousSyncTime@WW3D@@2IA=?PreviousSyncTime@WW3D@@0IA")
#pragma comment(linker, "/alternatename:?TheWeatherSetting@@3V?$OVERRIDE@VWeatherSetting@@@@A=?g_Va00DFE118@@3PAVWeatherSetting@@A")
