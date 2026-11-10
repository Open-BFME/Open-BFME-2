// cl: /O1 /DNDEBUG /MD /EHs
// Native 0041F4A7..0041F4E0, 57 bytes: clear POD hash nodes, then free
// the bucket allocation. This replaces the old gen-alias at its own address.
// Target accesses establish bucket pointers at +4/+8/+C and count at +10.
// Original key/value identities remain unknown. Armor's template supplies
// the already-rowed shared clear body, not this table's original identity.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Rva004DFC20.h"

struct Rva0041F4A7Buckets
{
    ~Rva0041F4A7Buckets();
    void **begin;
    void **end;
    void **storageEnd;
};

class Rva0041F4A7
{
public:
    ~Rva0041F4A7();
private:
    void *unused00;
    Rva0041F4A7Buckets buckets;
    unsigned int count;
};

// ?Rva0041F4A7Buckets::~Rva0041F4A7Buckets present-unmatched
inline Rva0041F4A7Buckets::~Rva0041F4A7Buckets()
{
    if (begin != 0)
        free(begin);
}

Rva0041F4A7::~Rva0041F4A7()
{
    reinterpret_cast<Rva004DFC20 *>(this)->clear();
}

// Native0x0041F4E0..0x0041F4E5 tail JMP to the sole owned destructor
// at0x0041F4A7: unchanged thiscall receiver and stack; no args; RET0.
// Original wrapper name enclosing class and lifetime role remain unknown.
struct Rva0041F4E0CleanupForward { void cleanup(); };
void Rva0041F4E0CleanupForward::cleanup()
{
    reinterpret_cast<Rva0041F4A7*>(this)->~Rva0041F4A7();
}
