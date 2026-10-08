// cl: /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour/BFME1 Snow.cpp donor, adapted to target layout and initialization.
// Donor field names are retained through visibility; later fields are offset views.
// Unidentified virtual slots retain neutral names in this target ABI view.
class SubsystemInterface {
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
private:
    unsigned int m_targetBaseWords[2]; // Offset evidence: SnowManager begins at +0x0C.
};

// Two adjacent floats that retail copies with one override lookup.
struct SnowFloatPair {
    float a;
    float b;
};

class SnowManager : public SubsystemInterface {
public:
    SnowManager();
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
    virtual void targetSlot10() = 0;
    virtual void targetSlot11();
    virtual void targetSlot12();
    virtual void targetSlot13();
    virtual void updateIniSettings();
private:
    float *m_startingHeights;
    float m_time;
    float m_velocity;
    float m_fullTimePeriod;
    float m_frequencyScaleX;
    float m_frequencyScaleY;
    float m_amplitude;
    float m_pointSize;
    float m_maxPointSize;
    float m_minPointSize;
    float m_quadSize;
    float m_boxDimensions;
    float m_emitterSpacing;
    bool m_isVisible;
    // Target-only state below +0x40 keeps offset-derived names until independently identified.
    unsigned char m_targetFlag41;
    unsigned char m_targetPad42[2];
    unsigned int m_targetDword44;
    SnowFloatPair m_targetPair48;
    unsigned char m_targetFlag50;
    unsigned int m_targetDword54;
    unsigned int m_targetDword58;
    float m_targetFloat5C;
    float m_targetFloat60;
    float m_targetFloat64;
    float m_targetFloat68;
    float m_targetFloat6C;
    float m_targetFloat70;
};

typedef char SnowManagerSizeCheck[sizeof(SnowManager) == 0x74 ? 1 : -1];

SnowManager::SnowManager()
    : SubsystemInterface(),
      m_startingHeights(0), m_time(0.0f), m_velocity(1.0f),
      m_fullTimePeriod(0.0f), m_frequencyScaleX(0.0f),
      m_frequencyScaleY(0.0f), m_amplitude(0.0f), m_pointSize(0.0f),
      m_maxPointSize(0.0f), m_minPointSize(0.0f), m_quadSize(0.0f),
      m_boxDimensions(0.0f), m_emitterSpacing(0.0f), m_isVisible(1),
      m_targetFlag41(0), m_targetDword44(0),
      m_targetFlag50(0), m_targetDword54(0),
      m_targetDword58(0)
{
    m_targetFloat5C = 0.0f;
    m_targetFloat60 = 0.0f;
    m_targetFloat64 = 0.0f;
    m_targetFloat68 = 0.0f;
    m_targetFloat6C = 0.0f;
    m_targetFloat70 = 0.0f;
    m_targetPair48.a = 0.0f;
    m_targetPair48.b = 0.0f;
}

extern void * __cdecl operator new[](unsigned int);

void SnowManager::init()
{
    m_startingHeights = new float[64 * 64];
    m_time = 0.0f;
    updateIniSettings();
}

class MemoryPoolObject {
public:
    virtual ~MemoryPoolObject();
};

class Overridable : public MemoryPoolObject {
public:
    Overridable *m_nextOverride;
    bool m_isOverride;
    Overridable *deleteOverrides();
    const Overridable *getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->getFinalOverride();
        return this;
    }
};

// Field offsets read from retail's compiler-generated WeatherSetting
// copy assignment (0x00201412, 0xB4 bytes). +0x1C..+0x44 follow Zero Hour's
// snow fields in order; the rest keep offset names.
class WeatherSetting : public Overridable {
public:
    unsigned int m_target0C;
    unsigned int m_targetBase10[2];
    unsigned int m_snowTexture;
    float m_snowFrequencyScaleX;
    float m_snowFrequencyScaleY;
    float m_snowAmplitude;
    float m_snowPointSize;
    float m_snowMaxPointSize;
    float m_snowMinPointSize;
    float m_snowQuadSize;
    float m_snowBoxDimensions;
    float m_snowBoxDensity;
    float m_snowVelocity;
    bool m_usePointSprites;
    bool m_snowEnabled;
    bool m_target46;
    unsigned int m_target48;
    SnowFloatPair m_target4C;
    bool m_target54;
    float m_target58[3];
    unsigned int m_target64;
    unsigned int m_target68;
    bool m_target6C;
    unsigned int m_target70;
    float m_target74;
    float m_target78;
    float m_target7C;
    float m_target80;
    float m_target84;
    float m_target88;
};

template <class T> class OVERRIDE {
public:
    const T *m_overridable;
    operator const T *() const
    {
        if (!m_overridable) return 0;
        return static_cast<const T *>(m_overridable->getFinalOverride());
    }
    OVERRIDE &operator=(const T *value)
    {
        m_overridable = value;
        return *this;
    }
    const T *operator->() const
    {
        if (!m_overridable) return 0;
        return static_cast<const T *>(m_overridable->getFinalOverride());
    }
    const T *getNonOverloadedPointer() const { return m_overridable; }
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;
extern void __cdecl operator delete[](void *);

SnowManager::~SnowManager()
{
    delete [] m_startingHeights;
    m_startingHeights = 0;
    if (TheWeatherSetting) {
        ::delete TheWeatherSetting;
        TheWeatherSetting = static_cast<const WeatherSetting *>(0);
    }
}

void SnowManager::reset()
{
    m_isVisible = true;
    WeatherSetting *setting = const_cast<WeatherSetting *>(
        TheWeatherSetting.getNonOverloadedPointer());
    TheWeatherSetting = static_cast<WeatherSetting *>(setting->deleteOverrides());
    updateIniSettings();
}

extern "C" __declspec(dllimport) int __cdecl rand(void);

// Retail 0x00201165, 685B (vftable slot 14). Zero Hour's random starting
// height table, then the snow settings copied one override lookup at a
// time; BFME2 stores the box density as the emitter spacing unchanged and
// copies nine target-only settings.
void SnowManager::updateIniSettings()
{
    float *dst = m_startingHeights;
    int boxDimensions = (int)TheWeatherSetting->m_snowBoxDimensions;
    for (int y = 0; y < 64; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            *dst = (float)(rand() % boxDimensions);
            dst++;
        }
    }

    m_velocity = TheWeatherSetting->m_snowVelocity;
    m_frequencyScaleX = TheWeatherSetting->m_snowFrequencyScaleX;
    m_frequencyScaleY = TheWeatherSetting->m_snowFrequencyScaleY;
    m_amplitude = TheWeatherSetting->m_snowAmplitude;
    m_pointSize = TheWeatherSetting->m_snowPointSize;
    m_quadSize = TheWeatherSetting->m_snowQuadSize;
    m_boxDimensions = TheWeatherSetting->m_snowBoxDimensions;
    m_emitterSpacing = TheWeatherSetting->m_snowBoxDensity;
    m_maxPointSize = TheWeatherSetting->m_snowMaxPointSize;
    m_minPointSize = TheWeatherSetting->m_snowMinPointSize;
    m_targetDword44 = TheWeatherSetting->m_target48;
    m_targetPair48 = TheWeatherSetting->m_target4C;

    m_fullTimePeriod = m_boxDimensions / m_velocity;
    m_targetFlag41 = TheWeatherSetting->m_target46;
    m_targetDword54 = TheWeatherSetting->m_target64;
    m_targetDword58 = TheWeatherSetting->m_target70;
    m_targetFloat5C = TheWeatherSetting->m_target74;
    m_targetFloat60 = TheWeatherSetting->m_target78;
    m_targetFloat64 = TheWeatherSetting->m_target84;
    m_targetFloat68 = TheWeatherSetting->m_target88;
    m_targetFloat6C = TheWeatherSetting->m_target7C;
    m_targetFloat70 = TheWeatherSetting->m_target80;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?targetSlot3@SnowManager@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?targetSlot4@SnowManager@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?targetSlot5@SnowManager@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?targetSlot6@SnowManager@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?targetSlot8@SnowManager@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?targetSlot11@SnowManager@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?targetSlot12@SnowManager@@UAEXXZ=??1Coord2D@@QAE@XZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?targetSlot7@SnowManager@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?targetSlot13@SnowManager@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?TheWeatherSetting@@3V?$OVERRIDE@VWeatherSetting@@@@A=?g_Va00DFE118@@3PAVWeatherSetting@@A")
