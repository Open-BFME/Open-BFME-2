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
// Xfer as xferSaveData calls it (slot 2 returns the save/load mode as a bool;
// each named slot is read off retail 0x002DCE24's call offsets).
class Xfer
{
public:
    virtual ~Xfer();
    virtual void v1();
    virtual bool isSaving();	// slot 2 (+0x08)
    virtual void v3(); virtual void v4();
    virtual int beginBlock(const char *name);	// slot 5 (+0x14)
    virtual void endBlock();	// slot 6 (+0x18)
    virtual void skipBlock(const char *name);	// slot 7 (+0x1C)
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void xferSnapshot(Snapshot *snapshot);	// slot 12 (+0x30)
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26();
    virtual void xferAsciiString(AsciiString *asciiStringData);	// slot 27 (+0x6C)
};
// VA 0x00DBD038, ZH's SAVE_FILE_EOF token pointer.
extern const char *SAVE_FILE_EOF;
enum SnapshotType { SNAPSHOT_SAVELOAD=0, SNAPSHOT_DEEPCRC_LOGICONLY=1, SNAPSHOT_NATIVE3=3, SNAPSHOT_NATIVE4=4 };
class GameState
{
    struct SnapshotBlock { Snapshot *snapshot; AsciiString blockName; };
    char m_opaque00[0x10];
    _STL::list<SnapshotBlock> m_snapshotBlockList[5];
    void addSnapshotBlock(AsciiString blockName, Snapshot *snapshot, SnapshotType which);
    SnapshotBlock *findBlockInfoByToken(AsciiString token, SnapshotType which);
public:
    void xferSaveData(Xfer *xfer, SnapshotType which);
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
// Native 2DCE24 is ZH's xferSaveData without the null-xfer check: the save
// branch writes each block's name then the block inside a rethrowing try and
// ends with the SAVE_FILE_EOF token; the load branch reads tokens until EOF,
// skipping unknown blocks. Callers: saveGame 2DD38D, the CRC friend 2DDD0B.
// Both catch (...) trys share the rethrow funclet 2DCF62 (inside the extent).
void GameState::xferSaveData(Xfer *xfer, SnapshotType which)
{
    if (xfer->isSaving())
    {
        SnapshotBlock *blockInfo;
        _STL::list<SnapshotBlock>::iterator it;
        AsciiString blockName;
        for (it = m_snapshotBlockList[which].begin(); it != m_snapshotBlockList[which].end(); ++it)
        {
            blockInfo = &(*it);
            blockName = blockInfo->blockName;
            xfer->xferAsciiString(&blockName);
            try
            {
                xfer->beginBlock("Snapshot");
                xfer->xferSnapshot(blockInfo->snapshot);
                xfer->endBlock();
            }
            catch (...)
            {
                throw;
            }
        }
        AsciiString eofToken = SAVE_FILE_EOF;
        xfer->xferAsciiString(&eofToken);
    }
    else
    {
        AsciiString token;
        bool done = false;
        SnapshotBlock *blockInfo;
        while (done == false)
        {
            xfer->xferAsciiString(&token);
            if (token.compareNoCase(SAVE_FILE_EOF) == 0)
            {
                done = true;
            }
            else
            {
                blockInfo = findBlockInfoByToken(token, which);
                if (blockInfo == 0)
                {
                    xfer->skipBlock("Snapshot");
                    continue;
                }
                try
                {
                    xfer->beginBlock("Snapshot");
                    xfer->xferSnapshot(blockInfo->snapshot);
                    xfer->endBlock();
                }
                catch (...)
                {
                    throw;
                }
            }
        }
    }
}
