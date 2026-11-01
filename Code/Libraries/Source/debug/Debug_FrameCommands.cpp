// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Oy-
// Retail frame-delayed debug commands ("<frame>:<command>" handled by
// Debug::ExecCommand). Pending entries live in a frame-sorted array on the
// Debug instance; this TU will host the schedule/execute helpers plus
// ExecCommand itself once their callees resolve.
#include <string.h>

// Retail keeps the frame pointer here (cf. internal.h in the sibling TU).

extern void *DebugReAllocMemory(void *, unsigned);
extern void DebugFreeMemory(void *);

// upstream layout: reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
#include "../../../GameEngine/Source/Common/debug.h"

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
