// cl: /DNDEBUG /MD
// EA BFME1/Zero Hour CommandLine.cpp parseScriptDebug, adapted to BFME2's
// retained command-table entries. Names follow their exact table tokens.
// -scriptDebug2: table RVA81FB88 maps string C1FC50 to handler3B976B (39B).
// -scriptDebugLite: table RVA81FB90 maps C1FC3C to handler3B9792 (46B).
// These are parser handlers; reproducing them does not prove an editor works.
// TheWritableGlobalData is VA DFE758. ScriptEngine initialization checks
// +9C1 and byte E02D7A before loading DebugWindowLite.dll or DebugWindow.dll.
// The two BFME2-prefixed global names below are descriptive recovered names.
class GlobalData {
public:
    char prefix[0x9c1];
    bool m_scriptDebug;
    char gap[4];
    bool m_winCursors;
};
extern GlobalData *TheWritableGlobalData;
extern bool BFME2UseDebugWindowLite;   // VA E02D7A: selects the Lite DLL.
// BFME2UseDebugWindowLite: VA 0xe02d7a (zero-filled .bss).
bool BFME2UseDebugWindowLite;
extern bool BFME2ScriptDebugLiteMode; // VA E02D78: additional Lite-mode flag.
// BFME2ScriptDebugLiteMode: matched references place it at VA 0xe02d78 (zero-filled .bss).
bool BFME2ScriptDebugLiteMode;

int parseScriptDebug2(char *args[],int) {
    if(TheWritableGlobalData) {
        TheWritableGlobalData->m_scriptDebug=true;
        TheWritableGlobalData->m_winCursors=true;
        BFME2UseDebugWindowLite=true;
    }
    return 1;
}

int parseScriptDebugLite(char *args[],int) {
    if(TheWritableGlobalData) {
        TheWritableGlobalData->m_scriptDebug=true;
        TheWritableGlobalData->m_winCursors=true;
        BFME2UseDebugWindowLite=true;
        BFME2ScriptDebugLiteMode=true;
    }
    return 1;
}
