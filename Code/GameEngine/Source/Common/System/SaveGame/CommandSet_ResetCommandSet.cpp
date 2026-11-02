// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?ResetCommandSet@CommandSet@@QAEXXZ @0x00409F83 29B
// Evidence: unlock lane; same 0x9C CommandSet layout as siblings 0x409FA0
// (landed) 0x409FCC (landed) and 0x409FFA banked (array32 +0x14 count +0x94
// flag +0x98); guarded clear by +0x98==1 then +0x94=0 via AND plus rep stosd;
// caller 407791; no callees.
#include <memory>
#include "ascii_string.h"
class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/GameClient/CommandSet.h"
void CommandSet::ResetCommandSet()
{
    if (m98 == 1) {
        m94 = 0;
        for (int i = 0; i < 32; ++i)
            m_command[i] = 0;
    }
}
