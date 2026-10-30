// cl: /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour/BFME1 Snow.cpp donor, adapted to target layout and initialization.
// Donor field names are retained through visibility; later fields are offset views.
// Unidentified virtual slots retain neutral names in this target ABI view.
#include <new>
#include <stdlib.h>

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

// Two adjacent floats that retail copies with one override lookup.
struct SnowFloatPair {
    float a;
    float b;
};

class SnowManager : public SubsystemInterface {
public:
    SnowManager();
    virtual ~SnowManager();
    // Slot 1 of retail's base table; slot 2 is the base's
    // loadIniFilesFromLegend (0x001B5384), which the canonical header leaves
    // undeclared.
    virtual void init();
    virtual bool targetSlot2();
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
    virtual void targetSlot15();
    virtual void targetSlot16();
    virtual void targetSlot17();
    virtual void targetSlot18();
    virtual void targetSlot19();
    virtual void targetSlot20();
    virtual void targetSlot21();
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

extern SnowManager *TheSnowManager;


void SnowManager::init()
{
    m_startingHeights = new float[64 * 64];
    m_time = 0.0f;
    updateIniSettings();
}

#include "../../Include/Common/MemoryPoolObject.h"

class Overridable : public MemoryPoolObject {
public:
    Overridable *m_nextOverride;
    bool m_isOverride;
    Overridable *deleteOverrides();
    Overridable *friend_getFinalOverride()
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }
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
    virtual WeatherSetting *rva00201153();
    virtual void rva00201085();
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
// Owned here: the weather override readers use; retail .data starts it at 0.
// (TU view and ZH agree the object is one pointer; the ledger's provisional
// 12B span has no +4/+8 reader behind it.)
OVERRIDE<WeatherSetting> TheWeatherSetting;

// WeatherSetting secondary table VA 0x00BE3064 slot 0 reads the final
// weather override through Overridable::friend_getFinalOverride.
WeatherSetting *WeatherSetting::rva00201153()
{
    WeatherSetting *setting = const_cast<WeatherSetting *>(TheWeatherSetting.getNonOverloadedPointer());
    return static_cast<WeatherSetting *>(setting->friend_getFinalOverride());
}


void SnowManager::reset()
{
    m_isVisible = true;
    WeatherSetting *setting = const_cast<WeatherSetting *>(
        TheWeatherSetting.getNonOverloadedPointer());
    TheWeatherSetting = static_cast<WeatherSetting *>(setting->deleteOverrides());
    updateIniSettings();
}


// Retail 0x00201165, 685B (vftable slot 14). Zero Hour's random starting
// height table, then the snow settings copied one override lookup at a
// time; BFME2 stores the box density as the emitter spacing unchanged and
// copies nine target-only settings.
void SnowManager::updateIniSettings()
{
    float *dst = m_startingHeights;
    int boxDimensions = (int)TheWeatherSetting->m_snowBoxDimensions;
    for (int row = 0; row < 64; row++)
    {
        for (int column = 0; column < 64; column++)
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

// WeatherSetting secondary table VA 0x00BE3064 slot 1 refreshes the
// snow manager when the singleton exists.
void WeatherSetting::rva00201085()
{
    if (TheSnowManager)
        TheSnowManager->updateIniSettings();
}
