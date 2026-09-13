// Minimal declarations needed by the reference UpdateFrameStatus sweep unit.
// The full debug module is not required to compile this isolated body.
#ifndef RVA_UPDATE_FRAME_STATUS_PCH_H
#define RVA_UPDATE_FRAME_STATUS_PCH_H

#pragma optimize("y", off)

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);
#define wsprintf wsprintfA

class Debug
{
public:
    static bool SimpleMatch(const char *str, const char *pattern);
};

#endif
