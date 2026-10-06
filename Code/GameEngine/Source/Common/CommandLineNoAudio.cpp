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
