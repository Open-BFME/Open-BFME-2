// ?updateIniSettings@SnowManager@@UAEXXZ
// partial score=0.12871287128712872 date=2026-09-23
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour Snow.cpp donor with target layout and weather-copy adaptations.
// Unknown fields use offset views; their original names and types are unresolved.
class Overridable {
public:
    virtual ~Overridable();
    Overridable *m_nextOverride;
    bool m_isOverride;
    const Overridable *getFinalOverride() const;
};
class WeatherSetting : public Overridable {
public:
    unsigned char m_targetPrefix0C[16]; // Unidentified fields before the weather values.
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
    unsigned char m_weather44[4];
    unsigned int m_weather48;
    float m_weather4C;
    float m_weather50;
    unsigned char m_weather54[0x10];
    unsigned int m_weather64;
    unsigned char m_weather68[8];
    unsigned int m_weather70;
    float m_weather74;
    float m_weather78;
    float m_weather7C;
    float m_weather80;
    float m_weather84;
    float m_weather88;
};
typedef char WeatherSettingTargetSizeCheck[sizeof(WeatherSetting) == 0x8C ? 1 : -1];
template <class T> class OVERRIDE {
public:
    T *m_overridable;
    const T *operator->() const {
        T *value = m_overridable;
        if (value) {
            Overridable *next = value->m_nextOverride;
            if (next) return (const T *)next->getFinalOverride();
        }
        return value;
    }
};
extern OVERRIDE<WeatherSetting> TheWeatherSetting;
class SubsystemInterface {
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();
private:
    unsigned int m_targetBaseWords[2];
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
    virtual void targetSlot10();
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
    unsigned char m_targetFlag41;
    unsigned char m_targetPad42[2];
    unsigned int m_targetDword44;
    float m_targetFloat48;
    float m_targetFloat4C;
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
extern "C" __declspec(dllimport) int __cdecl rand(void);
void SnowManager::updateIniSettings() {
    float *dst = m_startingHeights;
    int boxDimensions = (int)TheWeatherSetting->m_snowBoxDimensions;
    for (int y = 0; y < 64; ++y) {
        for (int x = 0; x < 64; ++x) {
            *dst = (float)(rand() % boxDimensions);
            ++dst;
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
    m_targetDword44 = TheWeatherSetting->m_weather48;
    const WeatherSetting *extendedSettings = TheWeatherSetting.operator->();
    m_targetFloat48 = extendedSettings->m_weather4C;
    m_fullTimePeriod = m_boxDimensions / m_velocity;
    m_targetFloat4C = extendedSettings->m_weather50;
    m_targetFlag41 = TheWeatherSetting->m_weather44[2];
    m_targetDword54 = TheWeatherSetting->m_weather64;
    m_targetDword58 = TheWeatherSetting->m_weather70;
    m_targetFloat5C = TheWeatherSetting->m_weather74;
    m_targetFloat60 = TheWeatherSetting->m_weather78;
    m_targetFloat64 = TheWeatherSetting->m_weather84;
    m_targetFloat68 = TheWeatherSetting->m_weather88;
    m_targetFloat6C = TheWeatherSetting->m_weather7C;
    m_targetFloat70 = TheWeatherSetting->m_weather80;
}
