// cl: /DNDEBUG /MD
// EA BFME1 CommandLine.cpp parseWin; BFME2 live -win table81FB80.
// Retail3B955D full17B sets GlobalData+2C, also tested by debug DLL loader.
class GlobalData {
public:
    char prefix[0x2c];
    bool m_windowed;
};
extern GlobalData *TheWritableGlobalData;
int parseWin(char *args[],int) {
    if(TheWritableGlobalData) TheWritableGlobalData->m_windowed=true;
    return 1;
}
