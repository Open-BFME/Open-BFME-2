// EA BFME1 CommandLine.cpp parseNoAudio adapted to BFME2's six switches.
// Live -noaudio table81FB68 identifies3B95BB; complete83B body.
// BFME2 INI table7E8FF0..7E9040 independently identifies all six fields.
// AmbientStreamsOn is +9A1; VideoOn is +9A3 and is not touched here.
// BFME2CommandFlags is a descriptive name for the retail word at VA DC1170.
// cl: /DNDEBUG /MD
class GlobalData {
public:
    char prefix[0x99c];
    bool m_audioOn,m_musicOn,m_soundsOn,m_sounds3DOn,m_speechOn,m_ambientStreamsOn;
};
extern GlobalData *TheWritableGlobalData;
extern unsigned BFME2CommandFlags;
// BFME2CommandFlags: matched references place it at VA 0xdc1170 (retail .data initial value 0u).
unsigned int BFME2CommandFlags = 0u;
int parseNoAudio(char *args[],int) {
    BFME2CommandFlags|=2;
    if(TheWritableGlobalData) {
        TheWritableGlobalData->m_audioOn=false;
        TheWritableGlobalData->m_speechOn=false;
        TheWritableGlobalData->m_soundsOn=false;
        TheWritableGlobalData->m_sounds3DOn=false;
        TheWritableGlobalData->m_musicOn=false;
        TheWritableGlobalData->m_ambientStreamsOn=false;
    }
    return 1;
}

// CRC option leaves: clean BF1 9cbfb551fe R2GlobalOptionFlagSetters.cpp is
// the semantic guide, recompiled with the normal BFME2 O1/SSE/G7 settings.
// Each target has its own complete RET boundary. Native stores establish the
// bits and globals; exact GameLogicPopulateGameReport at 247378 independently
// ties the byte globals to the CRC option strings. Handler names below are
// descriptive, with original spelling and ignored argument types unresolved.
// All added byte providers are zero in retail .data. The shared command word
// and client-check byte reuse their existing providers, without alias names.
extern unsigned char BfmeClientCRCCheckEnabled;
bool TheXObjectCRC = false;
bool TheXPartitionCRC = false;
bool TheXCollisionCRC = false;
bool TheXShroudCRC = false;
bool TheXTaintCRC = false;
bool TheXPlayerCRC = false;
bool TheXAICRC = false;
bool TheXLWCRC = false;
bool TheBinaryDeepCRC = false;

// Native 003B9ACD..003B9ADD: OR command bit 0x20, enable TheXObjectCRC, return int 1.
int bfmeEnableObjectCRC()
{
    BFME2CommandFlags |= 0x20;
    TheXObjectCRC = true;
    return 1;
}

// Native 003B9ADD..003B9AED: OR command bit 0x40, enable TheXPartitionCRC, return int 1.
int bfmeEnablePartitionCRC()
{
    BFME2CommandFlags |= 0x40;
    TheXPartitionCRC = true;
    return 1;
}

// Native 003B9AED..003B9AFD: OR command bit 0x80, enable TheXCollisionCRC, return int 1.
int bfmeEnableCollisionCRC()
{
    BFME2CommandFlags |= 0x80;
    TheXCollisionCRC = true;
    return 1;
}

// Native 003B9AFD..003B9B0D: OR command bit 0x100, enable TheXShroudCRC, return int 1.
int bfmeEnableShroudCRC()
{
    BFME2CommandFlags |= 0x100;
    TheXShroudCRC = true;
    return 1;
}

// Native 003B9B0D..003B9B1D: OR command bit 0x200, enable TheXTaintCRC, return int 1.
int bfmeEnableTaintCRC()
{
    BFME2CommandFlags |= 0x200;
    TheXTaintCRC = true;
    return 1;
}

// Native 003B9B1D..003B9B2D: OR command bit 0x400, enable TheXPlayerCRC, return int 1.
int bfmeEnablePlayerCRC()
{
    BFME2CommandFlags |= 0x400;
    TheXPlayerCRC = true;
    return 1;
}

// Native 003B9B2D..003B9B3D: OR command bit 0x800, enable TheXAICRC, return int 1.
int bfmeEnableAICRC()
{
    BFME2CommandFlags |= 0x800;
    TheXAICRC = true;
    return 1;
}

// Native 003B9B3D..003B9B4D: OR command bit 0x80000, enable TheXLWCRC, return int 1.
int bfmeEnableLWCRC()
{
    BFME2CommandFlags |= 0x80000;
    TheXLWCRC = true;
    return 1;
}

// Native 003B9C60..003B9C70: OR command bit 0x1000, enable BfmeClientCRCCheckEnabled, return int 1.
int bfmeEnableVerifyClientCRC()
{
    BFME2CommandFlags |= 0x1000;
    BfmeClientCRCCheckEnabled = 1;
    return 1;
}

// Native 003B9C57..003B9C60: enable TheBinaryDeepCRC, return int 1.
int bfmeEnableBinaryDeepCRC()
{
    TheBinaryDeepCRC = true;
    return 1;
}
