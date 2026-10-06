// cl: /MD /DNDEBUG
// Reference: GameLOD.cpp / GameLODManagerConstructor.cpp at BFME 1 revision
// 10af19f44a89ab7ecc23195bb9a842ceafbc02c9 guide the LOD default-initialization
// purpose. Retail manager constructor 0x00201EAC (Ghidra extent 353B) passes
// VA0x00601DC4 to the array-construction helper 0x00001423 with count6 and
// stride0x4C. Independent instruction decoding gives [0x00201DC4..0x00201E2B).
// Each scalar/flag offset and value below comes from that target body. Address
// labels retain uncertainty about the original component and member names;
// donor class layouts are not asserted as native types.
struct Rva00201DC4LODInfo
{
    Rva00201DC4LODInfo();
    int word00, word04, word08;
    bool flag0C, flag0D, flag0E;
    int word10;
    bool flag14, flag15;
    int word18;
    bool flag1C;
    int word20, word24, word28, word2C;
    bool flag30;
    int word34, word38;
    bool flag3C, flag3D;
    int word40, word44, word48;
};

Rva00201DC4LODInfo::Rva00201DC4LODInfo()
{
    word00=2; word04=3; word08=2500;
    flag0C=true; flag0D=true; flag0E=false;
    word10=3; flag14=true; flag15=true; word18=2;
    flag1C=true; word20=100; word24=25; word28=300000;
    word2C=0; flag30=true; word34=3; word38=0;
    flag3C=false; flag3D=false; word40=2; word44=1; word48=1;
}

// The same native manager passes VA0x00601E2B with count5, stride0x10,
// and destination +0x1C8. Full [0x00201E2B..0x00201E45) decoding stores
// three zero words and float1.0; /arch:SSE2 reproduces its MOVSS shape.
// Member labels below are donor semantics, not recovered native names.
struct Rva00201E2BLODInfo
{
    Rva00201E2BLODInfo();
    int minimumFPS, particleSkipMask, debrisSkipMask;
    float slowDeathScale;
};

Rva00201E2BLODInfo::Rva00201E2BLODInfo()
{
    minimumFPS=0; particleSkipMask=0; debrisSkipMask=0; slowDeathScale=1.0f;
}

// Native manager callback VA0x00601E45 constructs count2, stride8 at +0x218.
// Independent [0x00201E45..0x00201E56) decoding proves one word and two flags;
// the audio-related field names are carried from the clean BFME 1 donor.
struct Rva00201E45LODInfo
{
    Rva00201E45LODInfo();
    int maximumAmbientStreams;
    bool allowDolby, allowReverb;
};

Rva00201E45LODInfo::Rva00201E45LODInfo()
{
    maximumAmbientStreams=2; allowDolby=true; allowReverb=true;
}

typedef char Rva00201DC4StrideCheck[sizeof(Rva00201DC4LODInfo)==0x4C ? 1 : -1];
typedef char Rva00201E2BStrideCheck[sizeof(Rva00201E2BLODInfo)==0x10 ? 1 : -1];
typedef char Rva00201E45StrideCheck[sizeof(Rva00201E45LODInfo)==8 ? 1 : -1];

// Native manager passes VA0x00601D48 for count0xA0, stride0x20 at +0x228.
// Target leaf [0x00201D48..0x00201D79) and each scalar position are independently
// decoded; descriptive member names remain BFME 1 LOD-preset donor semantics.
struct Rva00201D48LODPreset
{
    Rva00201D48LODPreset();
    int cpuType, mhz;
    float cpuPerfIndex;
    int videoType, memory, word14, width, height;
};

Rva00201D48LODPreset::Rva00201D48LODPreset()
{
    cpuType=0; mhz=1; cpuPerfIndex=1.0f; videoType=0;
    memory=1; word14=1; width=800; height=600;
}

typedef char Rva00201D48StrideCheck[sizeof(Rva00201D48LODPreset)==0x20 ? 1 : -1];

// Native manager passes VA0x00601D79 for count0x10, stride0x14 at +0x1628.
// Target [0x00201D79..0x00201D9D) independently sets the first two words
// and three floats. Field roles below are donor benchmark-profile semantics.
struct Rva00201D79BenchProfile
{
    Rva00201D79BenchProfile();
    int cpuType, mhz;
    float intBenchIndex, floatBenchIndex, memBenchIndex;
};

Rva00201D79BenchProfile::Rva00201D79BenchProfile()
{
    cpuType=0; mhz=1; intBenchIndex=1.0f; floatBenchIndex=1.0f; memBenchIndex=1.0f;
}

typedef char Rva00201D79StrideCheck[sizeof(Rva00201D79BenchProfile)==0x14 ? 1 : -1];

// BFME 1's enclosing GameLODManager constructor guides the array composition
// and default-initialization purpose. This address view uses the independently
// decoded BFME 2 array counts/strides and every scalar store, not the donor's
// overall layout. Target Ghidra boundary [0x00201EAC..0x0020200D) is 353B;
// callbacks above and array iterator0x1423 are separately verified recoveries.
struct Rva00201EACLODManager
{
    Rva00201EACLODManager();
    Rva00201DC4LODInfo staticInfo[6];
    Rva00201E2BLODInfo dynamicInfo[5];
    Rva00201E45LODInfo audioInfo[2];
    Rva00201D48LODPreset presets[5][32];
    Rva00201D79BenchProfile benchmarks[16];
    int word1768, word176C, word1770, word1774, word1778, word177C;
    int word1780, word1784, word1788, word178C, word1790, word1794, word1798;
    float word179C;
    int word17A0, word17A4;
    bool flag17A8, flag17A9, flag17AA;
    int counts17AC[5];
    int word17C0, word17C4, word17C8, word17CC, word17D0, word17D4, word17D8;
    float word17DC, word17E0, word17E4, word17E8;
    int word17EC, word17F0;
};

Rva00201EACLODManager::Rva00201EACLODManager()
{
    word1768=-1; word176C=3; word1770=-1; word1774=2;
    word1778=3; word177C=3; word1780=2; word1784=2; word1788=3;
    word178C=0; word1790=0; word1794=0; word1798=0; word179C=1.0f;
    word17A0=0; word17A4=0; flag17A8=false; flag17A9=false; flag17AA=false;
    word17C0=0; word17C4=-1; word17C8=0; word17CC=0;
    word17D0=0; word17D4=0; word17D8=0;
    word17DC=0.0f; word17E0=0.0f; word17E4=0.0f; word17E8=0.0f;
    word17EC=400; word17F0=1500;
    for (int i=0;i<5;++i) counts17AC[i]=0;
}

typedef char Rva00201EACSizeCheck[sizeof(Rva00201EACLODManager)==0x17F4 ? 1 : -1];
