// Target facts (game.dat 1.06; code addresses are RVAs, data addresses are VAs): GameLODManager has no virtual functions or base subobjects. Its constructor 0x00201EAC stores no vptr; 0x002305DF..0x002305FC calls its empty destructor 0x000B3FD0 directly, then operator delete. There is no constructor or destructor vtable to choose between.
// 0x0022E551 pushes sizeof 0x17F8 to operator new at 0x0002FDA0; 0x0022E569 calls 0x00201EAC. That constructor calls 0x00001423 for five arrays: +0 (6 elements, stride 0x4C, callback 0x00201DC4), +0x1C8 (5, 0x10, 0x00201E2B), +0x218 (2, 8, 0x00201E45), +0x228 (160, 0x20, 0x00201D48) and +0x1628 (16, 0x14, 0x00201D79). The callbacks prove their element fields. 0x00201F18..0x00202007 proves the scalar, byte, float and counter offsets +0x1768..+0x17F0. 0x00202886 passes +0x17D0 to the 64-bit RAM output of 0x000768F5; 0x002032D1..0x002032FE consumes both words as one unsigned quantity. The 64-bit field accounts for the allocation's eight-byte alignment.
// Ledger methods: constructor 0x00201EAC, destructor 0x000B3FD0, newLODPreset 0x0020202B, getDynamicGameLODLevelName 0x00202605, getAudioLODLevelName 0x00202678, findAudioLODLevel 0x002026A0, init(int) 0x002027EA, getStaticGameLODIndex 0x00202C30, getAudioLODIndex 0x00202C76 and findStaticLODLevel 0x00203288. The call from W3DDisplay::init at 0x00046A50 also names rva00202739(int), whose body is 0x00202739. INI's 0x00202FFF passes table VA 0x00BE34B8, naming MaximumAmbientStreams, AllowDolby and AllowReverb at AudioLODInfo +0, +4 and +5. Zero Hour Common/GameLOD.h supplies the accessor names: getStaticLODLevel reads +0x1768 at retail 0x002486EE, getSlowDeathScale reads float +0x179C at 0x0045DB34 and 0x0045DF4D, and isDebrisSkipped increments +0x1794 and tests mask +0x1798 at 0x001F19DC..0x001F19F4. The neutral get1774 exposes the dword read at 0x00244E0B. Unsettled member names remain neutral.

#pragma once
#ifndef BFME2_GAMELODMANAGER_H
#define BFME2_GAMELODMANAGER_H

class AsciiString;
enum StaticGameLODLevel;
enum DynamicGameLODLevel;
struct LODPresetInfo;

struct Rva00201DC4LODInfo
{
    Rva00201DC4LODInfo();
    int field00, field04, field08;
    bool field0C, field0D, field0E;
    int field10;
    bool field14, field15;
    int field18;
    bool field1C;
    int field20, field24, field28, field2C;
    bool field30;
    int field34, field38;
    bool field3C, field3D;
    int field40, field44, field48;
};

struct Rva00201E2BLODInfo
{
    Rva00201E2BLODInfo();
    int field00, field04, field08;
    float field0C;
};

struct AudioLODInfo
{
    AudioLODInfo();
    int maximumAmbientStreams;
    bool allowDolby, allowReverb;
};

struct Rva00201D48LODPreset
{
    Rva00201D48LODPreset();
    int field00, field04;
    float field08;
    int field0C, field10, field14, field18, field1C;
};

struct Rva00201D79BenchProfile
{
    Rva00201D79BenchProfile();
    int field00, field04;
    float field08, field0C, field10;
};

class GameLODManager
{
public:
    GameLODManager();
    ~GameLODManager();

    LODPresetInfo *newLODPreset(StaticGameLODLevel level);
    const char *getDynamicGameLODLevelName(DynamicGameLODLevel level);
    const char *getAudioLODLevelName(int level);
    int findAudioLODLevel() const;
    void init(int level);
    int getStaticGameLODIndex(AsciiString name);
    int getAudioLODIndex(const AsciiString &name);
    StaticGameLODLevel findStaticLODLevel();
    bool rva00202739(int level);
    StaticGameLODLevel getStaticLODLevel() const { return (StaticGameLODLevel)m_1768; }
    int get1774() const { return m_1774; }
    float getSlowDeathScale() const { return m_slowDeathScale; }
    bool isDebrisSkipped() { return (++word1794 & word1798) != word1798; }

    Rva00201DC4LODInfo staticInfo[6];
    Rva00201E2BLODInfo dynamicInfo[5];
    AudioLODInfo audioInfo[2];
    Rva00201D48LODPreset presets[5][32];
    Rva00201D79BenchProfile benchmarks[16];
    int m_1768, word176C, m_1770, m_1774, word1778, word177C;
    int word1780, word1784, m_1788, word178C, word1790, word1794, word1798;
    float m_slowDeathScale;
    int word17A0, word17A4;
    bool flag17A8, flag17A9, flag17AA;
    int counts17AC[5];
    int word17C0, m_17c4, word17C8, word17CC;
    unsigned __int64 m_numRAM;
    int word17D8;
    float word17DC, word17E0, word17E4, word17E8;
    int word17EC, word17F0;
};

extern GameLODManager *TheGameLODManager;

#endif
