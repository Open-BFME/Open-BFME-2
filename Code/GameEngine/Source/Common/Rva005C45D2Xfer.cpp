// cl: /MD
// ?rva005C45D2@Rva005C45D2@@QAEXPAVXfer@@@Z retail 0x005C45D2 44B
// Version(1 1) via Xfer slot 0x28 then rowed Rva004CE6E4 0x004CE6E4 with this.
// Evidence: chain from 0x004CE6E4 landing; no callers; class unproven so honest Rva name.
class Snapshot;
#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"
class Xfer::Version
{
public:
    unsigned char m_current;
    unsigned char m_minimum;
};
#include "../../Include/Common/Rva004CE6E4.h"
class Rva005C45D2 {
public:
    void rva005C45D2(Xfer *xfer);
};
void Rva005C45D2::rva005C45D2(Xfer *xfer)
{
    Xfer::Version version;
    version.m_current = 1;
    version.m_minimum = 1;
    *xfer == version;
    ((Rva004CE6E4 *)this)->rva004CE6E4(xfer);
}
