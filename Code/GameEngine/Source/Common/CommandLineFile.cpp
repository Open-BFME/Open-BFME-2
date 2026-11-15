// cl: /DNDEBUG /MD
// EA BFME1 CommandLine.cpp parseFile; BFME2's live -file table entry
// identifies RVA3BA233 and the complete 63-byte body.
// Initial file is +ABC. The adjacent +AB8 name below is descriptive:
// retail's extended map normalizer writes a timestamped label there.
// Helper identity is based on the full 453-byte body at 3BA06E:
// source-derived slash/token/.map normalization plus BFME2's second output.
#include <stdlib.h>
#include "../../../../reference/shims/bfme2_ascii/string_base.h"
class GlobalData {
public:
    char prefix[0xc];
    StringBase<char> m_bfmeMapPath; // map path of the unlisted 0x003BA30A parser
    char unknown10[0x60 - 0x10];
    bool m_bfme60, m_bfme61, m_bfme62; // cleared by the unlisted 0x003B9679 switch
    char unknown63[0x9c1 - 0x63];
    bool m_bfme9C1; // set by the unlisted 0x003B974B switch
    char unknown9C2[0x9c6 - 0x9c2];
    bool m_bfme9C6; // set by the unlisted 0x003B974B switch
    char unknown9C7[0x9d4 - 0x9c7];
    int m_bfme9D4; // set to 2 by the unlisted 0x003B9F56 parser below
    char unknown9D8[0xab8 - 0x9d8];
    StringBase<char> m_bfmeFileLabel;
    StringBase<char> m_initialFile;
    char unknownAC0[4];
    bool m_bfmeResumeRequested; // descriptive name; live -resumeGame writes +AC4
    bool m_bfmeAC5; // written by the unlisted 0x003BA2BE parser below
    char unknownAC6[0xd38 - 0xac6];
    StringBase<char> m_bfmeModDir; // descriptive: the 0x003B9F56 parser stores "Mods\open_beta"
    char unknownD3C[0xea0 - 0xd3c];
    int m_bfmeEA0; // atoi of the argument, unlisted 0x003B9709 parser
};
extern GlobalData *TheWritableGlobalData;
void ConvertShortMapPathToLongMapPath(StringBase<char>&,StringBase<char>&);
int parseFile(char *args[],int num) {
    if(TheWritableGlobalData && num>1) {
        TheWritableGlobalData->m_initialFile.set(args[1]);
        ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_initialFile,TheWritableGlobalData->m_bfmeFileLabel);
    }
    return 2;
}

// Retail command table at81FBC8 maps -resumeGame to3BA272 (76 bytes).
// Reuses parseFile's source-backed flow with the independently observed flag.
int parseResumeGame(char *args[],int num) {
    if(TheWritableGlobalData && num>1) {
        TheWritableGlobalData->m_bfmeResumeRequested=true;
        TheWritableGlobalData->m_initialFile.set(args[1]);
        ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_initialFile,TheWritableGlobalData->m_bfmeFileLabel);
    }
    return 2;
}

// Native 3BA2BE..3BA30A (76 bytes), directly after parseResumeGame and not
// in the -command table at 81FBC8: the same file flow, raising the +AC5 flag.
// Its command name is not recovered; address-derived name.
int Rva003BA2BEParse(char *args[],int num) {
    if(TheWritableGlobalData && num>1) {
        TheWritableGlobalData->m_bfmeAC5=true;
        TheWritableGlobalData->m_initialFile.set(args[1]);
        ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_initialFile,TheWritableGlobalData->m_bfmeFileLabel);
    }
    return 2;
}

// Native 3B9F56..3B9F83 (45 bytes), not in the -command table at 81FBC8:
// a one-argument switch selecting the open-beta mod directory (+D38) and
// mode 2 at +9D4. Command name not recovered; address-derived name.
int Rva003B9F56Parse(char *args[],int num) {
    if(TheWritableGlobalData) {
        TheWritableGlobalData->m_bfme9D4=2;
        TheWritableGlobalData->m_bfmeModDir.set("Mods\\open_beta");
    }
    return 1;
}

// Three more parsers between parseFullVersion and parseScriptDebug2 that the
// 81FB70 -command table no longer lists (BFME1 CommandLine.cpp shapes); their
// command names are not recovered, so they keep address-derived names.
// Native 3B9679..3B969B: clears the +60/+61/+62 switches.
int Rva003B9679Parse(char *args[],int num) {
    if(TheWritableGlobalData) {
        TheWritableGlobalData->m_bfme62=false;
        TheWritableGlobalData->m_bfme60=false;
        TheWritableGlobalData->m_bfme61=false;
    }
    return 1;
}

// Native 3B9709..3B9737: atoi of the argument into +EA0.
int Rva003B9709Parse(char *args[],int num) {
    if(TheWritableGlobalData && num>1)
        TheWritableGlobalData->m_bfmeEA0=atoi(args[1]);
    return 2;
}

// Native 3B974B..3B976B: raises the +9C1 and +9C6 switches.
int Rva003B974BParse(char *args[],int num) {
    if(TheWritableGlobalData) {
        TheWritableGlobalData->m_bfme9C1=true;
        TheWritableGlobalData->m_bfme9C6=true;
    }
    return 1;
}

// Native 3BA30A..3BA348 (62 bytes), directly before parseMod and not in the
// -command table: parseFile's flow into the +0C path with the same label.
int Rva003BA30AParse(char *args[],int num) {
    if(TheWritableGlobalData && num>=2) {
        TheWritableGlobalData->m_bfmeMapPath.set(args[1]);
        ConvertShortMapPathToLongMapPath(TheWritableGlobalData->m_bfmeMapPath,TheWritableGlobalData->m_bfmeFileLabel);
        return 2;
    }
    return 1;
}
