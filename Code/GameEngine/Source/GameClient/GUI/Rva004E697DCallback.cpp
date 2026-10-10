// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

// Native004E697D..004E6A01: formats the float then selects bool text and
// invokes the existing eight-argument Apt level callback. WB and the
// notification Open caller4E701E establish the argument roles. The original
// function name is unproven. Keeping the output slot in the outer scope and
// passing the number temporary by const reference recovers its native frame
// and the returned-buffer pointer lifetime, without changing the callee ABI.

class Rva00222A8BTarget {public:
 int invoke(void*,const char*,int,const char*,void*,void*,void*,void*);
};
AsciiString Rva002228E8Get(float);
char **Rva004E678BGet(char**,bool);
static __forceinline int invokeFormatted(Rva00222A8BTarget *target,void *owner,const char *method,
 const AsciiString &number,const bool *flag,const char *const *location, char **flagText)
{
 const char *place=*location;
 char *value=*Rva004E678BGet(flagText,*flag);
 return target->invoke(owner,method,3,number.str(),value,const_cast<char*>(place),0,0);
}

int Rva004E697DCall(Rva00222A8BTarget *target,void *owner,const char *method,
 const float *height,const bool *flag,const char *const *location)
{
 char *flagText;
 return invokeFormatted(target,owner,method,Rva002228E8Get(*height),flag,location,&flagText);
}
