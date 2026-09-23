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
    virtual void updateIniSettings();
protected:
    float *m_startingHeights;
    float m_time, m_velocity, m_fullTimePeriod;
    unsigned char m_target1C[0x2C];
    float m_targetFloat48, m_targetFloat4C;
    unsigned char m_target50[0x24];
};

class W3DSnowManager : public SnowManager {
public:
    virtual void update();
private:
    // Call views: thiscall without explicit arguments; original returns unknown.
    void target_00094652();
    void target_0009322D();
    unsigned char m_target74[0x20];
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
