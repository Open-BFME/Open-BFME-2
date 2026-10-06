// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00409F83@Rva00409FFA@@QAEXXZ @0x00409F83 29B
// Evidence: unlock lane; same 0x9C Rva00409FFA layout as siblings 0x409FA0
// (landed) 0x409FCC (landed) and 0x409FFA banked (array32 +0x14 count +0x94
// flag +0x98); guarded clear by +0x98==1 then +0x94=0 via AND plus rep stosd;
// caller 407791; no callees.
#include <memory>
#include "ascii_string.h"
class Xfer;
class Snapshot {
public:
    __forceinline virtual ~Snapshot() {}
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
class Rva00409FFA {
    unsigned int word04;
    unsigned char flag08;
    unsigned int word0C;
    AsciiString str10;
    unsigned int arr14[32];
    unsigned int word94;
    unsigned int word98;
public:
    void rva00409F83();
    virtual ~Rva00409FFA();
};
void Rva00409FFA::rva00409F83()
{
    if (word98 == 1) {
        word94 = 0;
        for (int i = 0; i < 32; ++i)
            arr14[i] = 0;
    }
}
