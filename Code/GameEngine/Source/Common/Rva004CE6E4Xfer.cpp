// cl: /MD
// ?rva004CE6E4@Rva004CE6E4@@QAEXPAVXfer@@@Z retail 0x004CE6E4 28B
// Version(1 1) stamp through Xfer slot 0x28 like rowed Version1 0x000053EE.
// Evidence: 5 callers 0x004CEE39 0x004FAF73 0x005C4469 0x005C45D2 0x005C4808; unlocks 4 ready; class unproven so honest Rva name.
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
void Rva004CE6E4::rva004CE6E4(Xfer *xfer)
{
    Xfer::Version version;
    version.m_current = 1;
    version.m_minimum = 1;
    *xfer == version;
}
