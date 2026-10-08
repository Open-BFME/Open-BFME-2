// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// BFME1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 and ZH GameState.cpp
// establish the registration purpose and nested record relationship. Native
// 2DE34B independently tests the string and Snapshot pointer then copies an
// 8-byte record: Snapshot pointer at +0 and AsciiString at +4. Its list array
// is at receiver+0x10 with a four-byte stride. Unused prefix remains opaque;
// this TU does not assert a complete GameState layout or names for kinds 3/4.
// Native initializer 2DE641 repeatedly calls this helper with CHUNK_ labels.
// The native insertion chain proves push_back2DDEA6 -> insert2DDE02 ->
// create_node2DD021 -> Construct2DCD64 -> copyCF475 -> StringBase copy365F0.
// The last two helpers already have verified rows under opaque TreeKey names;
// their SnapshotBlock spellings are proven folded aliases and count no gain.
// All six complete emitted extents match strictly with the actual callees.
// stlport
#include <list>
#include "ascii_string.h"
class Snapshot;
enum SnapshotType { SNAPSHOT_SAVELOAD=0, SNAPSHOT_DEEPCRC_LOGICONLY=1, SNAPSHOT_NATIVE3=3, SNAPSHOT_NATIVE4=4 };
class GameState
{
    struct SnapshotBlock { Snapshot *snapshot; AsciiString blockName; };
    char m_opaque00[0x10];
    _STL::list<SnapshotBlock> m_snapshotBlockList[5];
    void addSnapshotBlock(AsciiString blockName, Snapshot *snapshot, SnapshotType which);
    SnapshotBlock *findBlockInfoByToken(AsciiString token, SnapshotType which);
};
void GameState::addSnapshotBlock(AsciiString blockName, Snapshot *snapshot, SnapshotType which)
{
    if (blockName.isEmpty() || snapshot == 0)
        return;
    SnapshotBlock blockInfo;
    blockInfo.snapshot = snapshot;
    blockInfo.blockName = blockName;
    m_snapshotBlockList[which].push_back(blockInfo);
}
// Native 2DCDBF is the ZH lookup: empty-token early out, then a walk of
// m_snapshotBlockList[which] comparing each record's name (+4) against the
// by-value token through compare 0x69D6. Callers 2DCE24 and the save-file
// reader 2DEEC3 pass the chunk token read from the file.
GameState::SnapshotBlock *GameState::findBlockInfoByToken(AsciiString token, SnapshotType which)
{
    if (token.isEmpty())
        return 0;
    SnapshotBlock *blockInfo;
    _STL::list<SnapshotBlock>::iterator it;
    for (it = m_snapshotBlockList[which].begin(); it != m_snapshotBlockList[which].end(); ++it)
    {
        blockInfo = &(*it);
        if (blockInfo->blockName == token)
            return blockInfo;
    }
    return 0;
}
