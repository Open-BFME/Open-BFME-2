// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00409FCC@Rva00409FFA@@QAEXXZ @0x00409FCC 46B
// Evidence: unlock lane; same 0x9C Rva00409FFA layout as siblings 0x409FA0
// (landed) and 0x409FFA banked (array32 at +0x14, count +0x94, flag +0x98);
// resolves each non-null entry with +0xC>=1 via ControlBar::findCommandButton
// pin 0x31BE3C on g_bfmeWorldRV using entry +0x10 AsciiString; loop 0x20;
// caller 31E83B; LINK BONUS none.
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
class Rva001E3624
{
public:
    virtual ~Rva001E3624();
private:
    Rva001E3624 *m_next;
};

class Rva00409FFA : public Rva001E3624 {
    unsigned char flag08;
    unsigned int word0C;
    AsciiString str10;
    unsigned int arr14[32];
    unsigned int word94;
    unsigned int word98;
public:
    void rva00409FCC();
    virtual ~Rva00409FFA();
};
class CommandButton;
class ControlBar {
public:
    const CommandButton *findCommandButton(const AsciiString &name);
};
struct BfmeWorldRV;
extern struct BfmeWorldRV *g_bfmeWorldRV;
void Rva00409FFA::rva00409FCC()
{
    for (int i = 0; i < 0x20; ++i) {
        unsigned int entry = arr14[i];
        if (entry != 0 && *(int *)(entry + 0xC) >= 1)
            arr14[i] = (unsigned int)((ControlBar *)(void *)g_bfmeWorldRV)->findCommandButton(*(const AsciiString *)(entry + 0x10));
    }
}

// ??1Rva00409FFA@@UAE@XZ @0x0040A057 59B
// Evidence: unlock lane dtor; vptr store then AsciiString str10 at +0x10 via
// shared header (releaseBuffer) then rowed base ??1Rva001E3624@@UAE@XZ; caller
// 0x40A142 unclaimed; LINK BONUS none.
Rva00409FFA::~Rva00409FFA()
{
}
