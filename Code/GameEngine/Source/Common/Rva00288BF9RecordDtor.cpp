// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 00288BF9/59 is a destructor, independently established by its
// deleting caller 00288FEE/28 (flag1 calls rowed scalar delete 0002FD60),
// and owner destructor 00289D7A/239 that invokes it before deleting records.
// It releases an AsciiString at +0C via rowed 00036410, then frees the
// pointer at +00 through rowed free 00030830. +04/+08 are not interpreted.
// Donor vector<Record24> destructor lead is refuted: there is no record loop.
// The allocation member is a structural lifetime view to preserve cleanup on exceptions,
// not evidence for an original member type or application name.
#include "ascii_string.h"
void Rva00030830FreeAllocation(void *);
#pragma comment(linker, "/alternatename:?Rva00030830FreeAllocation@@YAXPAX@Z=_free")

struct Rva00288BF9AllocationLifetime
{
    void *allocation;
    unsigned char unknown04[8];
    // ?Rva00288BF9AllocationLifetime::~Rva00288BF9AllocationLifetime present-unmatched
    __forceinline ~Rva00288BF9AllocationLifetime()
    {
        if (allocation) Rva00030830FreeAllocation(allocation);
    }
};
struct Rva00288BF9Record
{
    Rva00288BF9AllocationLifetime buffer;
    AsciiString text;
    ~Rva00288BF9Record();
    void *destroy(unsigned flags);
};
typedef char Rva00288BF9RecordSize[(sizeof(Rva00288BF9Record) == 16) ? 1 : -1];

// ?Rva00288BF9Record::~Rva00288BF9Record present-unmatched
Rva00288BF9Record::~Rva00288BF9Record() {}

// ?Rva00288BF9Record::destroy present-unmatched
void *Rva00288BF9Record::destroy(unsigned flags)
{
    this->~Rva00288BF9Record();
    if (flags & 1) ::operator delete(this);
    return this;
}
