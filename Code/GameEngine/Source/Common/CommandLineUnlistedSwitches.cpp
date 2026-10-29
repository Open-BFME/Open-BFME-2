// cl: /DNDEBUG /MD
// Command-line switch parsers that BFME 2's -command table (0x0081FB58..
// 0x0081FBD0, sixteen entries, all rowed) no longer lists but whose bodies
// survive between the listed ones (0x003B9505..0x003B9FD3). Each has the
// BFME 1 / Zero Hour CommandLine.cpp parser shape: int (char *args[], int
// num), a TheWritableGlobalData guard, one GlobalData store, and the number
// of arguments consumed. Their command names are not recovered, so they keep
// address-derived names; the GlobalData offsets are the stores retail makes.
#include <stdlib.h>
template<class T> class StringBase {
    T *data;
public: void set(const T*);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct CommandLineSwitchPair
{
    int m_00;
    int m_04;
    int m_08;
    int m_0C;
};

struct CommandLineSwitchView
{
    char pad0000[0x27 - 0x0];
    bool m_dumpAssetUsage;
    char pad0028[0x2d - 0x28];
    bool m_skipMapUnroll;
    char pad002E[0x8c - 0x2e];
    StringBase<char> m_bfme8C;
    char pad0090[0x9bf - 0x90];
    bool m_showTooltips;
    bool m_bfme9C0;
    char pad09C1[0xaec - 0x9c1];
    StringBase<char> m_shellMapName;
    char pad0AF0[0xb04 - 0xaf0];
    int m_bfmeB04;
    CommandLineSwitchPair m_bfmeB08;
    char pad0B18[0xb38 - 0xb18];
    int m_bfmeB38;
    char pad0B3C[0xbd4 - 0xb3c];
    bool m_shouldUpdateTGAToDDS;
    char pad0BD5[0xd46 - 0xbd5];
    bool m_bfmeD46;
    char pad0D47[0xd48 - 0xd47];
    int m_bfmeD48;
    char pad0D4C[0xea4 - 0xd4c];
    bool m_bfmeEA4;
    bool m_bfmeEA5;
    char pad0EA6[0x1111 - 0xea6];
    bool m_bfme1111;
    char pad1112[0x11c8 - 0x1112];
    bool m_bfme11C8;
    char pad11C9[0x11ca - 0x11c9];
    bool m_planningModeEnabled;
    bool m_bfme11CB;
};

#define TheSwitches ((CommandLineSwitchView *)TheWritableGlobalData)

// Native 3B9505..3B9516: sets +2D true.
int Rva003B9505Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_skipMapUnroll=true;
    return 1;
}

// Native 3B9521..3B9535: sets +11CA false.
int Rva003B9521Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_planningModeEnabled=false;
    return 1;
}

// Native 3B9535..3B9549: sets +11CA true.
int Rva003B9535Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_planningModeEnabled=true;
    return 1;
}

// Native 3B9549..3B955D: sets +11CB true.
int Rva003B9549Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme11CB=true;
    return 1;
}

// Native 3B96F5..3B9709: sets +EA5 false.
int Rva003B96F5Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfmeEA5=false;
    return 1;
}

// Native 3B9737..3B974B: sets +EA4 false.
int Rva003B9737Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfmeEA4=false;
    return 1;
}

// Native 3B99AB..3B99BF: sets +1111 true.
int Rva003B99ABParse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme1111=true;
    return 1;
}

// Native 3B99BF..3B99D0: sets +27 true.
int parseDumpAssetUsage(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_dumpAssetUsage=true;
    return 1;
}

// Native 3B9A0C..3B9A20: sets +BD4 true.
int parseUpdateImages(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_shouldUpdateTGAToDDS=true;
    return 1;
}

// Native 3B9A29..3B9A3D: sets +D46 true.
int Rva003B9A29Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfmeD46=true;
    return 1;
}

// Native 3B9AA5..3B9AB9: sets +9BF false.
int Rva003B9AA5Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_showTooltips=false;
    return 1;
}

// Native 3B9AB9..3B9ACD: sets +9C0 true.
int Rva003B9AB9Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches->m_bfme9C0=true;
    return 1;
}

// Native 3B9D5F..3B9D6F: sets +11C8 without the guard.
int Rva003B9D5FParse(char *args[],int num) {
    TheSwitches->m_bfme11C8=true;
    return 1;
}

// Native 3B9F30..3B9F56: copies the argument into the +AEC string.
int parseShellMap(char *args[],int num) {
    if(TheWritableGlobalData && num>1)
        TheSwitches->m_shellMapName.set(args[1]);
    return 2;
}

// Native 3B9FB7..3B9FD3: copies the argument into the +8C string, unguarded.
int Rva003B9FB7Parse(char *args[],int num) {
    TheSwitches->m_bfme8C.set(args[1]);
    return 2;
}

// Native 3B9A3D..3B9A62: atoi of the argument into +D48 (no guard on
// TheWritableGlobalData, only on the argument count).
int Rva003B9A3DParse(char *args[],int num) {
    if(num>1)
        TheSwitches->m_bfmeD48=atoi(args[1]);
    return 2;
}

// Native 3B9A62..3B9A9C: clears the +B10/+B14 pair and stores the
// 0xBAADEC4C marker at +B38 and +B04.
int Rva003B9A62Parse(char *args[],int num) {
    if(TheWritableGlobalData) {
        CommandLineSwitchPair *pair=&TheSwitches->m_bfmeB08;
        pair->m_08=0;
        pair->m_0C=0;
        TheSwitches->m_bfmeB38=0xBAADEC4C;
        TheSwitches->m_bfmeB04=0xBAADEC4C;
    }
    return 1;
}

// Native 3B9F83..3B9F8C: runs the rowed mod-cinematics setup
// Rva003B9E0FInit 0x003B9E0F (CommandLineRva003B9E0F.cpp) and consumes one.
void Rva003B9E0FInit();
int Rva003B9F83Parse(char *args[],int num) {
    Rva003B9E0FInit();
    return 1;
}

// Native 3B9F8C..3B9FB7: raises the byte at VA 0x00E02D8B and copies the
// next two arguments, unguarded, into the file-scope strings at VA
// 0x00E02D90 and 0x00E02D94 (no other users are named; address-derived).
extern bool g_00E02D8B;
// Owned here (its only reader); retail .bss zero-initializes it (VA 0x00E02D8B).
bool g_00E02D8B = false;
extern StringBase<char> g_Va00E02D90;
// Owned here (one of its readers); retail .bss zero-initializes it (VA 0x00E02D90).
StringBase<char> g_Va00E02D90;
extern StringBase<char> g_Va00E02D94;
// Owned here (one of its readers); retail .bss zero-initializes it (VA 0x00E02D94).
StringBase<char> g_Va00E02D94;
int Rva003B9F8CParse(char *args[],int num) {
    g_00E02D8B=true;
    g_Va00E02D90.set(args[1]);
    g_Va00E02D94.set(args[2]);
    return 1;
}

// The run of unlisted parsers at 0x003B97C0..0x003B9977 (same shape as the
// ones above): byte switches, and three atoi stores that consume the next
// argument. Their command names are not recovered; the GlobalData offsets
// are the stores retail makes.
struct CommandLineSwitchView2
{
    char pad0000[0x2c - 0x0];
    bool m_windowed;
    char pad002D[0x9a4 - 0x2d];
    bool m_disableCameraMovement;
    char pad09A5[0x9ac - 0x9a5];
    bool m_bfme9AC;
    char pad09AD[0x9af - 0x9ad];
    bool m_useFX;
    char pad09B0[0x9c2 - 0x9b0];
    bool m_particleEdit;
    char pad09C3[0x9c6 - 0x9c3];
    bool m_winCursors;
    char pad09C7[0x9c8 - 0x9c7];
    bool m_showTeamDot;
    char pad09C9[0x9d0 - 0x9c9];
    bool m_bfme9D0;
    bool m_bfme9D1;
    bool m_bfme9D2;
    char pad09D3[0x9d8 - 0x9d3];
    bool m_bfme9D8;
    char pad09D9[0x9e4 - 0x9d9];
    bool m_forceBenchmark;
    char pad09E5[0x9e8 - 0x9e5];
    int m_fixedSeed;
    char pad09EC[0xa44 - 0x9ec];
    int m_netMinPlayers;
    char pad0A48[0xab5 - 0xa48];
    bool m_buildMapCache;
    char pad0AB6[0xb01 - 0xab6];
    bool m_incrementalAGPBuf;
    char pad0B02[0xb6e - 0xb02];
    bool m_loadScreenDemo;
    char pad0B6F[0xc30 - 0xb6f];
    int m_playStats;
};

#define TheSwitches2 ((CommandLineSwitchView2 *)TheWritableGlobalData)

// Native 3B97C0..3B97E9: sets +9C2, +9C6 and +2C true.
int parseParticleEdit(char *args[],int num) {
    if(TheWritableGlobalData) {
        TheSwitches2->m_particleEdit=true;
        TheSwitches2->m_winCursors=true;
        TheSwitches2->m_windowed=true;
    }
    return 1;
}

// Native 3B97E9: sets +AB5 true.
int parseBuildMapCache(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_buildMapCache=true;
    return 1;
}

// Native 3B97FD: sets +9AF false.
int parseNoFX(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_useFX=false;
    return 1;
}

// Native 3B9811: sets +9E4 true.
int parseForceBenchmark(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_forceBenchmark=true;
    return 1;
}

// Native 3B9825: sets +9A4 true.
int parseNoMoveCamera(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_disableCameraMovement=true;
    return 1;
}

// Native 3B9839: sets +9C6 true.
int parseWinCursors(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_winCursors=true;
    return 1;
}

// Native 3B984D: sets +9C8 true.
int parseShowTeamDot(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_showTeamDot=true;
    return 1;
}

// Native 3B9861: sets +9D0 true.
int Rva003B9861Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_bfme9D0=true;
    return 1;
}

// Native 3B9875: sets +9D1 true.
int Rva003B9875Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_bfme9D1=true;
    return 1;
}

// Native 3B9889: sets +9D2 true.
int Rva003B9889Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_bfme9D2=true;
    return 1;
}

// Native 3B989D: sets +9D8 true.
int Rva003B989DParse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_bfme9D8=true;
    return 1;
}

// Native 3B98B1: atoi of the argument into +9E8.
int parseSeed(char *args[],int num) {
    if(TheWritableGlobalData && num>1)
        TheSwitches2->m_fixedSeed=atoi(args[1]);
    return 2;
}

// Native 3B98DF: sets +B01 true.
int parseIncrAGPBuf(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_incrementalAGPBuf=true;
    return 1;
}

// Native 3B98F3: atoi of the argument into +A44.
int parseNetMinPlayers(char *args[],int num) {
    if(TheWritableGlobalData && num>1)
        TheSwitches2->m_netMinPlayers=atoi(args[1]);
    return 2;
}

// Native 3B9921: sets +9AC true.
int Rva003B9921Parse(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_bfme9AC=true;
    return 1;
}

// Native 3B9935: atoi of the argument into +C30.
int parsePlayStats(char *args[],int num) {
    if(TheWritableGlobalData && num>1)
        TheSwitches2->m_playStats=atoi(args[1]);
    return 2;
}

// Native 3B9963: sets +B6E true.
int parseDemoLoadScreen(char *args[],int num) {
    if(TheWritableGlobalData)
        TheSwitches2->m_loadScreenDemo=true;
    return 1;
}

// Native 3B94FC..3B9505: calls the shared empty body 0x000B3FD0 (a release
// build's emptied hook, reached through its pinned no-argument spelling)
// and consumes one, the shape of the rowed Rva003B9D23 (GapBodiesGE14.cpp).
void rva001216E7ShutdownPhase();
int Rva003B94FCParse(char *args[],int num) {
    rva001216E7ShutdownPhase();
    return 1;
}
