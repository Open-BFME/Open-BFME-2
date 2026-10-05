// cl: /O1 /DNDEBUG /MD /EHsc
// Reconstruction of the 15-bit to 2-byte mask emitter at 0x003187A8 (95B):
// zero two local bytes, fold bits 0-14 of the owner's mask word into them,
// then issue the slot-9 virtual (arg+0x24) with (bytes, 2). The slot, arity
// and (ptr,int) shape match Xfer::xferUser, but the caller identity is only
// a lead, so the callee is spelled as a slot-exact local interface rather
// than a real Xfer: the emitted indirect call carries no callee relocation
// either way. All names are address-derived; member offsets are target facts.
#include <string.h>
#pragma function(memset)

// Slot-exact stand-in for the callee at arg+0x24 (Xfer::xferUser lead:
// dtor, mode, options x3, open, close, begin/end block, then xferUser).
class Rva003187A8Xfer {
public:
    virtual ~Rva003187A8Xfer();
    virtual int rva003187A801();
    virtual int rva003187A802();
    virtual int rva003187A803();
    virtual int rva003187A804();
    virtual int rva003187A805();
    virtual int rva003187A806();
    virtual int rva003187A807();
    virtual int rva003187A808();
    virtual void rva003187A8Emit(unsigned char* bytes, int count);
};

class Rva003187A8Owner {
public:
    void rva003187A8(Rva003187A8Xfer* xfer);
private:
    int m_mask00[1];
};

void Rva003187A8Owner::rva003187A8(Rva003187A8Xfer* xfer)
{
    unsigned char bytes[4];
    memset(bytes, 0, 2);
    for (int i = 0; i < 15; ++i) {
        if (m_mask00[(unsigned int)i >> 5] & (1 << (i & 31))) {
            bytes[i / 8] |= (unsigned char)(1 << (i % 8));
        }
    }
    xfer->rva003187A8Emit(bytes, 2);
}
