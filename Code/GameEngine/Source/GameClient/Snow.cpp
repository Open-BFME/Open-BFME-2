// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
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
    virtual void targetSlot9();
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
    // Target-only state below +0x40 keeps offset-derived names until independently identified.
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
    m_targetFloat48 = 0.0f;
    m_targetFloat4C = 0.0f;
}

extern void * __cdecl operator new[](unsigned int);

void SnowManager::init()
{
    m_startingHeights = new float[64 * 64];
    m_time = 0.0f;
    updateIniSettings();
}
