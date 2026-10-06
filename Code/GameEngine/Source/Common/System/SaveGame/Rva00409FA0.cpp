// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00409FA0@Rva00409FFA@@QAEXHH@Z @0x00409FA0 44B
// Evidence: unlock lane; same 0x9C layout as sibling ctor 0x00409FFA banked
// (vtable C3906C, +0x14 array32, +0x94 count, +0x98 flag); guarded by +0x98==1
// and index<0x20 then arr[index]=value and count=max(count,index+1);
// callers 4077C3 407823 40786F in 419B body; ret 8 void HH.
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
    void rva00409FA0(int value, int index);
    virtual ~Rva00409FFA();
};
void Rva00409FFA::rva00409FA0(int value, int index)
{
    if (word98 == 1) {
        if ((unsigned int)index < 0x20) {
            arr14[index] = (unsigned int)value;
            if ((unsigned int)(index + 1) > word94)
                word94 = (unsigned int)(index + 1);
        }
    }
}
