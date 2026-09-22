// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Retail frame-delayed debug commands ("<frame>:<command>" handled by
// Debug::ExecCommand). Pending entries live in a frame-sorted array on the
// Debug instance; this TU will host the schedule/execute helpers plus
// ExecCommand itself once their callees resolve.
#include <string.h>

// Retail keeps the frame pointer here (cf. internal.h in the sibling TU).
#pragma optimize("y", off)

extern "C" __declspec(dllimport) void *__cdecl memmove(void *, const void *, unsigned);
extern void *DebugReAllocMemory(void *, unsigned);
extern void DebugFreeMemory(void *);

// upstream layout: reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
public:
    // One pending frame-delayed command (8 bytes; array grows 0x10 at a time).
    struct FrameCommand
    {
        int frame;
        const char *command;
    };

    // Runs and frees every pending command whose frame has arrived. Debug
    // vtable (RVA 0x7BE810) slot 0x90; the name is inferred from behavior
    // (pops due entries off the sorted list, re-runs them through
    // ExecCommand, frees the strings).
    virtual void ExecuteFrameCommands(int frame);

private:
    // Retail Debug layout window used here (cf. debug_debug.cpp views).
    char m_pad[0x9E04];                 // after the vptr
    FrameCommand *frameCommands;        // 0x9E08, sorted by frame
    unsigned numFrameCommands;          // 0x9E0C
    unsigned frameCommandsAlloc;        // 0x9E10, capacity in entries

    // Sorted-insert of (frame, command); grows via DebugReAllocMemory.
    // Returns the new entry count. Identity inferred from behavior
    // (sole caller is ExecCommand's "<frame>:" prefix path, which discards
    // the result; retail materializes ++numFrameCommands in eax, not the
    // array base, so the count -- not the base -- is the true return).
    unsigned ScheduleFrameCommand(int frame, const char *command);

    // Resolves via the existing ExecCommand pin (private non-virtual AAEX).
    void ExecCommand(const char *, const char *);
};

// ?ScheduleFrameCommand@Debug@@AAEIHPBD@Z
unsigned Debug::ScheduleFrameCommand(int frame, const char *command)
{
    if (numFrameCommands==frameCommandsAlloc)
    {
        frameCommandsAlloc+=0x10;
        frameCommands=(FrameCommand *)DebugReAllocMemory(frameCommands,frameCommandsAlloc*sizeof(FrameCommand));
    }

    // Entries stay sorted by descending frame; the executor pops due
    // commands off the end.
    unsigned index=0;
    if (numFrameCommands>0)
    {
        FrameCommand *entry=frameCommands;
        do
        {
            if (frame>=entry->frame)
                break;
            index++;
            entry++;
        // Retail re-reads the bound every iteration (never hoisted); the
        // volatile read pins that shape without touching the other uses.
        } while (index<*(volatile unsigned *)&numFrameCommands);
    }

    // Shifting [index..count) right only when something sits at index.
    if (index<numFrameCommands)
        memmove(frameCommands+index+1,frameCommands+index,(numFrameCommands-index)*sizeof(FrameCommand));
    frameCommands[index].frame=frame;
    frameCommands[index].command=command;
    return ++numFrameCommands;
}

// ?ExecuteFrameCommands@Debug@@UAEXH@Z
void Debug::ExecuteFrameCommands(int frame)
{
    while (numFrameCommands>0)
    {
        if (frameCommands[numFrameCommands-1].frame>frame)
            break;
        const char *cmd=frameCommands[--numFrameCommands].command;

        // run whatever follows a nested "<frame>:" prefix
        unsigned len=strlen(cmd);
        const char *p=cmd;
        for (;len>0;len--,p++)
            if (*p==':')
                break;
        if (len>1)
            ExecCommand(p+1,p+len);
        DebugFreeMemory((void *)cmd);
    }
}
