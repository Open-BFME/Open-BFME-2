// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include "../../../../Include/GameClient/CommandSet.h"
#include "../../../../Include/Common/Overridable.h"
// ?refreshIfStale@CommandSet@@QAEXXZ @0x00409FCC 46B
// Evidence: unlock lane; same 0x9C CommandSet layout as siblings 0x409FA0
// (landed) and 0x409FFA banked (array32 at +0x14, count +0x94, flag +0x98);
// resolves each non-null entry with +0xC>=1 via ControlBar::findCommandButton
// pin 0x31BE3C on g_bfmeWorldRV using entry +0x10 AsciiString; loop 0x20;
// caller 31E83B; LINK BONUS none.
#include <memory>
#include "ascii_string.h"
class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

class CommandButton;
#include "../../../../Include/GameClient/ControlBar.h"
struct BfmeWorldRV;
extern class ControlBar *TheControlBar;
void CommandSet::refreshIfStale()
{
    for (int i = 0; i < 0x20; ++i) {
        unsigned int entry = (unsigned int)m_command[i];
        if (entry != 0 && *(int *)(entry + 0xC) >= 1)
            m_command[i] = ((ControlBar *)(void *)((BfmeWorldRV *)TheControlBar))->findCommandButton(*(const AsciiString *)(entry + 0x10));
    }
}

// ??1CommandSet@@UAE@XZ @0x0040A057 59B
// Evidence: unlock lane dtor; vptr store then AsciiString str10 at +0x10 via
// shared header (releaseBuffer) then rowed base ??1Overridable@@UAE@XZ; caller
// 0x40A142 unclaimed; LINK BONUS none.
CommandSet::~CommandSet()
{
}
