// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/iniexception
// The two static audio-settings helpers and their real retail caller
// INI::parseAudioSettingsDefinition (0x0004171A); the helpers' private
// register conventions come out only with the caller in the same unit, so
// it replaces the two source-only absent-from-retail callers that stood in.
#include "Common/INIException.h"

// Native00041403..00041457, RET0: ECX base and EAX byte offset.
// Checks three float words spaced72 bytes apart. A NaN in the first
// becomes zero; later NaNs receive the first word without float conversion.
// WorldBuilder 0x0073D4E0 names it copyAudioSettingIfNotDefault in
// MilesAudioDevice/MilesAudioSettings.cpp and passes it the setting name
// (debug-only "You must specify <name> in the AudioSettings entry"). The name
// parameter must be declared: only then does 0x000416EC keep pushing its own
// name argument as retail does while this callee's copy is dropped.
extern "C" __declspec(dllimport) int __cdecl _isnan(double);
static __forceinline void replaceNan(unsigned &value, const unsigned &replacement)
{
 if (_isnan(*(const float *)&value)) value = replacement;
}
static __declspec(noinline) void rva00041403(unsigned char *base, int offset, const char *name)
{
 float *first = (float *)(base + offset);
 float *second = (float *)(base + offset + 0x48);

 if (_isnan(*first)) *first = 0.0f;
 replaceNan(*(unsigned *)second, *(unsigned *)first);
 unsigned &third = *(unsigned *)((unsigned char *)first + 0x90);
 replaceNan(third, *(unsigned *)first);
}

// Native 000416EC..0004171A, RET0. The target and its debug counterpart
// establish three float values spaced72 bytes apart, copied from one
// offset to another after the existing NaN sanitizer and squared.
// MSVC reproduces the native private ABI (base in EDI, destination in ESI,
// source and the unused name on the stack) because the static helper and its
// only caller parseAudioSettingsDefinition share this TU.
static __declspec(noinline) void rva000416EC(unsigned char *base, int source,
 int destination, const char *name)
{
 rva00041403(base, source, name);
 for (int i = 0; i < 3; ++i)
 {
  float value = *(float *)(base + i * 0x48 + source);
  *(float *)(base + i * 0x48 + destination) = value * value;
 }
}

// ?parseAudioSettingsDefinition@INI@@SAXPAV1@@Z
// Retail 0x0004171A..0x00041839 (287 bytes). BFME 2 shape of Zero Hour's
// INI::parseAudioSettingsDefinition (GameAudio.cpp) and the BFME 1 donor
// (Open-BFME-1 game/GameEngine/Source/Common/INI/INIAudioSettings.cpp):
// refuses map.ini overrides (load type 2 -> INIException 3 with the retail
// literal) then parses TheAudio's settings (TheAudio +0x10) through a
// MultiIniFieldParse built from the table at 0x00BC16E8 plus the rowed
// Rva00238AB6::buildFieldParse into the rowed INI::initFromINIMulti; then
// squares eight microphone/zoom fields and defaults two more across the three
// 0x48-byte microphone records at settings +0x12C and finishes with the rowed
// settings methods 0x00238A61 (option-preference volumes) and 0x00238D38.
// Evidence: WorldBuilder 0x0073D300 (same strings calls and order); the
// eight setting-name literals; rowed callees INIException ctor 0x0002F681
// MultiIniFieldParse ctor 0x0002BAA0 / add 0x0002BC6E.
typedef float Real;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
 const char *token;
 INIFieldParseProc parse;
 const void *userData;
 int offset;
};

class MultiIniFieldParse
{
public:
 MultiIniFieldParse();
 void add(const FieldParse *parse, unsigned int extraOffset);
private:
 const FieldParse *m_fieldParse[16];
 unsigned int m_extraOffset[16];
 int m_count;
};

class Rva00238AB6
{
public:
 static void buildFieldParse(MultiIniFieldParse &parse);
};

class Rva00238A61
{
public:
 void rva00238A61();
};

class Rva00238CC2
{
public:
 void rva00238D38();
};

class AudioSettings;

class AudioManager
{
public:
 AudioSettings *friend_getAudioSettings() { return m_audioSettings; }
private:
 unsigned char m_pad00[0x10];
 AudioSettings *m_audioSettings; // +0x10
};

extern AudioManager *TheAudio;

extern const FieldParse g_00BC16E8[];

class INI
{
public:
 static void parseAudioSettingsDefinition(INI *ini);
 void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
 int getLoadType() const { return m_loadType; }
private:
 int m_pad00;
 int m_pad04;
 int m_loadType; // +0x08
};

void INI::parseAudioSettingsDefinition(INI *ini)
{
 if (ini->getLoadType() == 2)
  throw INIException(3, "You cannot define or override the AudioSettings in map.ini");

 AudioSettings *settings = TheAudio->friend_getAudioSettings();
 MultiIniFieldParse parse;
 parse.add(g_00BC16E8, 0);
 Rva00238AB6::buildFieldParse(parse);
 ini->initFromINIMulti(settings, parse);

 unsigned char *microphone = (unsigned char *)settings + 0x12C;
 rva000416EC(microphone, 0x00, 0x04, "MicrophonePreferredFractionCameraToGround");
 rva000416EC(microphone, 0x08, 0x0C, "MicrophoneMinDistanceToCamera");
 rva000416EC(microphone, 0x10, 0x14, "MicrophoneMaxDistanceToCamera");
 rva000416EC(microphone, 0x1C, 0x20, "ZoomMinDistance");
 rva000416EC(microphone, 0x24, 0x28, "ZoomMaxDistance");
 rva000416EC(microphone, 0x30, 0x34, "ZoomFadeDistanceForMaxEffect");
 rva000416EC(microphone, 0x38, 0x3C, "ZoomFadeZeroEffectEdgeLength");
 rva000416EC(microphone, 0x40, 0x44, "ZoomFadeFullEffectEdgeLength");
 rva00041403(microphone, 0x2C, "ZoomSoundVolumePercentageAmount");
 rva00041403(microphone, 0x18, "MicrophonePullTowardsTerrainLookAtPointPercentage");

 ((Rva00238A61 *)settings)->rva00238A61();
 ((Rva00238CC2 *)settings)->rva00238D38();
}
