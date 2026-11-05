// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
// ??1SecondaryBase@@UAE@XZ @0x004FAC80 25B
// Evidence: Native4FAC80..4FAC99 RET, ctor4FAC6B calls member ctor330757 at+4; same ctor installs primary vptr and derived4FADF4 invokes it. Existing parent view establishes nonpolymorphic secondary base+4; ordinary base teardown plus inline pointer release gives native LEA NEG SBB AND and free30830; no integer pointer arithmetic. Member and complete class original names unresolved. Consumers Rva004FB130 0x004FB130 and Rva005C48E5 destroy this class as the base at their +0x0C and call 0x004FAC80 as its destructor (pinned name SecondaryBase; the original class name is not established). No vptr store: the class is novtable.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../../../Include/Common/Rva00330757Member.h"

__forceinline Rva00330757Member::~Rva00330757Member()
{
    if (field00) free(field00);
}
class Rva004FAC80Primary {public:virtual void anchor();};
class __declspec(novtable) SecondaryBase:public Rva004FAC80Primary,public Rva00330757Member {public:virtual ~SecondaryBase();};
SecondaryBase::~SecondaryBase() {}
