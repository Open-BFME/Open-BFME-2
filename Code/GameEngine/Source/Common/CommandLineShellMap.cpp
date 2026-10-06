// cl: /DNDEBUG /MD
// EA BFME1 CommandLine.cpp parseNoShellMap; BFME2 live table81FB58.
// Retail3B945E full32B disables shell map+AF0 and sets adjacent flag+AF1.
// BFME2 INI table7E94B0/7E94C0 names ShellMapOn/ShellMapOffByCommandArgument.
class GlobalData {
public:
    char prefix[0xaf0];
    bool m_shellMapOn;
    bool m_shellMapOffByCommandArgument;
};
extern GlobalData *TheWritableGlobalData;
int parseNoShellMap(char *args[],int) {
    if(TheWritableGlobalData) {
        TheWritableGlobalData->m_shellMapOn=false;
        TheWritableGlobalData->m_shellMapOffByCommandArgument=true;
    }
    return 1;
}
