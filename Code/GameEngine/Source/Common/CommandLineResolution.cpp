// cl: /DNDEBUG /MD
// EA BFME1 CommandLine.cpp parseXRes/parseYRes reference flow.
// BFME2 live -xres table81FB70 identifies3B969B (45B); field is +30.
#include <stdlib.h>
class GlobalData {
public:
    char prefix[0x30];
    int m_xResolution;
    int m_yResolution;
};
extern GlobalData *TheWritableGlobalData;
int parseXRes(char *args[],int num) {
    if(TheWritableGlobalData && num>1) {
        TheWritableGlobalData->m_xResolution=atoi(args[1]);
        return 2;
    }
    return 1;
}

// Live -yres table81FB78 identifies3B96C8 (45B); field is +34.
int parseYRes(char *args[],int num) {
    if(TheWritableGlobalData && num>1) {
        TheWritableGlobalData->m_yResolution=atoi(args[1]);
        return 2;
    }
    return 1;
}
