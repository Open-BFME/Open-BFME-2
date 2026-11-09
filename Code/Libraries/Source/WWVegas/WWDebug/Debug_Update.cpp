// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug::Update: the polymorphic Debug instance is passed in ECX and
// keeps its I/O factory head at +0x0C.

#include <string.h>

// Retail calls the game realloc wrapper at RVA 0x0003E4B0 directly.
// A call to realloc binds to MSVCR71's in a /MD link, so this names the wrapper.
#pragma push_macro("_CRTIMP")
#undef _CRTIMP
#define _CRTIMP
#include <stdlib.h>
#pragma pop_macro("_CRTIMP")
void *DebugReAllocMemory(void *oldPtr, unsigned int newSize);

class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface(void) {}

public:
    virtual int Read(char *, int)=0;
};

#include "../../../../GameEngine/Source/Common/debug.h"

// ?Update@Debug@@UAEXXZ
void Debug::Update(void)
{
    for (IOFactoryListEntry *cur=firstIOFactory;cur;cur=cur->next)
    {
        if (!cur->io)
            continue;

        bool hadInput=false;
        for (;;)
        {
            if (cur->inputAlloc-cur->inputUsed<64)
                cur->input=(char *)DebugReAllocMemory(
                    cur->input,(cur->inputAlloc+=64)+1);
            int numChars=cur->io->Read(cur->input+cur->inputUsed,
                                       cur->inputAlloc-cur->inputUsed);
            if (!numChars)
                break;

            cur->inputUsed+=numChars;
            cur->input[cur->inputUsed]=0;
            hadInput=true;
        }

        if (!hadInput)
            continue;

        for (;;)
        {
            char *p=strchr(cur->input,'\n');
            if (!p)
                break;

            ExecCommand(cur->input,p);
            strcpy(cur->input,p+1);
            cur->inputUsed=strlen(cur->input);
        }
    }
}
