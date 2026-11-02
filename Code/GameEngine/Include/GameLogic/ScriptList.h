// ScriptList: canonical BFME2 Snapshot interface and bounded data projection.
// Target facts (RVAs): constructors 0x003B7720 and 0x003B88DA install table VA 0x00C1FAAC at +0; copy construction first installs Snapshot VA 0x00BBB554, and destructor 0x003B774B restores it after destroying +0x2C (0x003B7167), +0x0C (0x003B766B), and the +4 head pair (0x003B4071). Table 0x0081FAAC has exactly four code words: deleting destructor 0x003B7D90, loadPostProcess 0x000B3FD0, const GetSnapshotName 0x003B7745 (literal VA 0x00C1FAA0, "ScriptList"), and xfer 0x003B4716; its next word is text. duplicate 0x003B8945 allocates 0x4C and calls the copy constructor. Constructor 0x003B7720 clears dwords +4/+8 and calls 0x003B761E at +0x0C/+0x2C; that constructor builds two 12-byte vectors and sets +0x18/+0x1C to -1. Copy 0x003B88DA calls 0x003B3FCD at +4 and distinct 32-byte set copies 0x003B872A/0x003B8802. xfer 0x003B4716 reads vector pairs +0x0C/+0x10 and +0x2C/+0x30, records +0x18/+0x38 with stride 0x14, and indices +0x28/+0x48. The 0x48-byte payload projects the two sets and the nonvirtual head-pair subobject as storage; their original nominal types are unproved.
// Method names and signatures follow the matched ScriptList ledger rows at the RVAs beside their declarations; rva003B7362 is called by SidesList at 0x0032C88F. Head names follow Zero Hour GeneralsMD GameLogic/Scripts.h; writer 0x003B73C5 passes +8 to WriteScriptDataChunk 0x003B5994 and +4 to WriteGroupDataChunk 0x003B6975. No additional virtual slots or inline lifetime bodies are introduced.
#pragma once
#ifndef BFME2_SCRIPT_LIST_H
#define BFME2_SCRIPT_LIST_H

#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT) || defined(BFME_SNAPSHOT_REFERENCE_XFER) || (defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT))
#error ScriptList requires Snapshot loadPostProcess, const GetSnapshotName, and xfer(Xfer *) slots
#endif
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

template<class T> class StringBase;
class DataChunkOutput;
class Rva003BScriptReference;
class BfmeKeyZK;
struct BfmeHeadXZ;
struct BfmeNodeXZ;
struct BfmeHeadZK;
struct BfmeNodeZK;
struct Rva0034F9D0Head;
struct Rva0034F9D0Node;
struct Rva003B31DF;
struct Rva003B3204;
struct ScriptGroupLink;

class ScriptList : public Snapshot
{
public:
    ScriptList(); // 0x003B7720
    ScriptList(const ScriptList &other); // 0x003B88DA
    virtual ~ScriptList(); // 0x003B774B; deleting wrapper 0x003B7D90
    void clear(); // 0x003B7812
    void swap(ScriptList *other); // 0x003B58DF
    ScriptList *duplicate() const; // 0x003B8945
    void WriteScriptListDataChunk(DataChunkOutput &); // 0x003B73C5
    static void WriteScriptsDataChunk(DataChunkOutput &, ScriptList *[], int); // 0x003B73F6
    void addGroupRef(Rva0034F9D0Head *, Rva0034F9D0Node *, Rva0034F9D0Node *); // 0x003B23DE
    void addScriptRef(BfmeHeadXZ *, BfmeNodeXZ *, BfmeNodeXZ *); // 0x003B23F7
    void deleteGroupRef(void *, Rva003B31DF *); // 0x003B779C
    void deleteScriptRef(void *, Rva003B3204 *); // 0x003B7389
    void *rva003B68E8(const StringBase<char> &); // 0x003B68E8
    void *rva003B6911(const StringBase<char> &); // 0x003B6911
    void rva003B693A(); // 0x003B693A
    void rva003B7362(); // 0x003B7362
    Rva003BScriptReference *rva003B83B1(const StringBase<char> &); // 0x003B83B1
    Rva003BScriptReference *rva003B83FD(const StringBase<char> &, int *); // 0x003B83FD
    void rva003B8383(BfmeNodeZK *, const StringBase<char> &); // 0x003B8383
    void rva003B844D(BfmeNodeZK *, const StringBase<char> &); // 0x003B844D
    void bfmeMoveZK(BfmeKeyZK *, BfmeNodeZK **, BfmeNodeZK **); // 0x003B847B
    void takeScript(BfmeKeyZK *, BfmeHeadZK *, BfmeNodeZK *, BfmeHeadZK *, BfmeNodeZK **); // 0x003B8556
    void takeScripts(ScriptList *, BfmeNodeZK **, BfmeNodeZK **); // 0x003B84C9
    void takeGroups(ScriptList *, ScriptGroupLink **, ScriptGroupLink **); // 0x003B7DAC
    void doTakeGroup(ScriptList *, ScriptGroupLink **, ScriptGroupLink **); // 0x003B89C9
    void takeGroup(ScriptList *, ScriptGroupLink **, ScriptGroupLink *, ScriptGroupLink **, ScriptGroupLink **); // 0x003B8A9B

protected:
    virtual void loadPostProcess(); // slot 1, 0x000B3FD0
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const; // slot 2, 0x003B7745
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *); // slot 3, 0x003B4716

public:
    unsigned char m_data[0x48]; // +0x04, heads and two record sets
};

#endif
