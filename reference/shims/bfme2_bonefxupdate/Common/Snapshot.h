// BFME 2 BoneFXUpdate TU: the canonical Snapshot in place of Zero Hour's. Rows 0x00487797 and 0x00487877 call no
// out-of-line Snapshot constructor and 0x00487877 restores the base table 0x00BBB554 inline; vftable 0x00C4B170
// holds the name getter 0x00487A5E in slot 2, where the Zero Hour classes have crc.
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../moduledata/Common/Snapshot.h"
