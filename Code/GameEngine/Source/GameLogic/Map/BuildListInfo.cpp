// cl: /DNDEBUG /MD /EHsc
//
// ??1BuildListInfo@@MAE@XZ @0x0032A186 120B. BuildListInfo list destructor.
// Each +0x2C link is unlinked then released through the virtual deleteInstance(0)
// slot 0 whose pointer result feeds ::operator delete (??3 @0x2FD60). The
// _ReadWriteBarrier after setNextBuildList keeps retail's and-then-vtable-load
// order inside the loop. Layout: vptr +0, AsciiStrings +4/+8/+0x30,
// m_nextBuildList +0x2C, padding +0xC..+0x2B.
// Retail C0D904 has four slots: deleting destructor, the shared empty
// post-load hook, the existing name getter and xfer. Use the shared Snapshot
// interface; the destructor loop invokes slot 0 with flags zero through its
// compiler ABI view and separately frees the returned allocation.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
class BuildListDeleteSlot
{
public:
    virtual void *deleteInstance(int flags) = 0;
};
#include "../../../Include/GameLogic/Bfme2BuildListInfo.h"
BuildListInfo::~BuildListInfo()
{
    register BuildListInfo *next;
    if (m_nextBuildList) {
        register BuildListInfo *cur = m_nextBuildList;
        while (cur) {
            next = cur->m_nextBuildList;
            cur->setNextBuildList(0);
            _ReadWriteBarrier();
            ::operator delete(reinterpret_cast<BuildListDeleteSlot *>(cur)->deleteInstance(0));
            cur = next;
        }
    }
}

// Native C0D904 slot 1 is the complete shared RET at RVA 000B3FD0.
void BuildListInfo::loadPostProcess() {}
