// cl: /DNDEBUG /MD /EHs-c- /Oy-
// BFME Debug input-line helper.  The IO factory list begins at +0x0C.

#include <string.h>

// Retail calls the game realloc wrapper at RVA 0x0003E4B0 directly.
// Use the CRT declaration without importing MSVCR71's realloc instead.
#pragma push_macro("_CRTIMP")
#undef _CRTIMP
#define _CRTIMP
#include <stdlib.h>
#pragma pop_macro("_CRTIMP")

class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface(void) {}

public:
    virtual int Read(char *, int)=0;
    virtual bool HasInput(void)=0;
};

#include "../../../../GameEngine/Source/Common/debug.h"

// ?GetInput@Debug@@UAEHPADHPA_N@Z
int Debug::GetInput(char *buf, int maxchar, bool *hasInput)
{
    for (IOFactoryListEntry *cur=firstIOFactory;cur;cur=cur->next)
    {
        if (!cur->io)
            continue;

        bool gotInput=false;
        if (!cur->io->HasInput())
            continue;

        *hasInput=true;
        for (;;)
        {
            if (cur->inputAlloc-cur->inputUsed<64)
                cur->input=(char *)realloc(
                    cur->input,(cur->inputAlloc+=64)+1);

            int numChars=cur->io->Read(cur->input+cur->inputUsed,
                                       cur->inputAlloc-cur->inputUsed);
            if (!numChars)
                break;

            cur->inputUsed+=numChars;
            cur->input[cur->inputUsed]=0;
            gotInput=true;
        }

        if (!gotInput)
            continue;

        *hasInput=true;
        char *p=strchr(cur->input,'\n');
        if (!p)
            continue;

        int numChars=p-cur->input;
        if (numChars>maxchar-1)
            numChars=maxchar-1;
        strncpy(buf,cur->input,numChars);
        buf[numChars]=0;
        strcpy(cur->input,p+1);
        cur->inputUsed=strlen(cur->input);
        return numChars;
    }

    return 0;
}
