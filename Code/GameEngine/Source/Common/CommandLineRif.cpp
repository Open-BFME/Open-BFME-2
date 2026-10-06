// BFME1 T3CommandLineParsers global-data/command-bit handler family.
// BFME2 live -rif table81FBB8 identifies3B94D6..3B94F0 (27 bytes).
// Field name describes only the observed switch request at +11C9; no expanded
// meaning of RIF is asserted. The command word is shared with parseNoAudio.
// cl: /DNDEBUG /MD
class GlobalData {
public:
    char prefix[0x11c9];
    bool m_bfmeRifRequested;
};
extern GlobalData *TheWritableGlobalData;
extern unsigned BFME2CommandFlags;
int parseRif(char *args[],int num) {
    if(TheWritableGlobalData) TheWritableGlobalData->m_bfmeRifRequested=true;
    BFME2CommandFlags|=0x100000;
    return 1;
}
