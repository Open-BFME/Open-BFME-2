// GameState: canonical BFME2 declaration; addresses below are retail RVAs unless marked VA.
// Target facts: ctor 0x002DE4E6 calls SubsystemInterface ctor 0x001B4E63 at +0, stores Snapshot VA 0x00BBB554 at +0xC, then VA 0x00C0402C at +0 and VA 0x00C0401C at +0xC. Dtor 0x002DE58D restores the same pair before Snapshot's base table and ~SubsystemInterface 0x001B4E74.
// GameEngine::init pushes 0xE1C at 0x0022FAF4 before new 0x0002FDA0 and the ctor call 0x0022FB0C. SubsystemInterface is 0xC bytes; Snapshot is 4 bytes; own storage starts at +0x10.
// Primary VA 0x00C0402C has fourteen slots: 0 deleting dtor 0x002DF2DA, 1 init 0x002DE641, 2 SubsystemInterface::loadIniFilesFromLegend 0x001B5384, 3/8/12 RET 0x000B3FD0, 4/11 false(int) 0x005CB9FF, 5 false() 0x0047A699, 6 zero() 0x000D43D0, 7/13 RET4 0x0047A69C, 9 reset 0x002DEE9A, 10 update 0x000B3FD0. The next word is string data.
// Snapshot VA 0x00C0401C has four slots: 0 thunk 0x002DE585 (subtract 0xC, jump to 0x002DF2DA), 1 loadPostProcess 0x000B3FD0, 2 GetSnapshotName 0x002DE57F (returns VA 0x00C04064, "GameState"), 3 xfer 0x002DBCCA.
// Ctor 0x002DE4E6 constructs five four-byte lists at +0x10, the 0xDE8-byte member at +0x24 through 0x002DD173, and four-byte lists at +0xE0C/+0xE10 through 0x004EC36C/0x0035C9A6; it clears dword +0xE14 and byte +0xE18. Registration 0x002DE34B indexes the +0x10 lists with stride 4 and copies Snapshot* then AsciiString into its nested SnapshotBlock record.
// friend_xferSaveDataForCRC 0x002DDD0B clears the pristine-map AsciiString at +0x2C, description at +0x44, save type dword +0x48 and mission-map AsciiString at +0x50. Zero Hour GameState.h supplies these member names and m_isInLoadGame; the target constructor/reset and load dispatcher 0x002DD91A prove byte +0xE18. Unmodelled member storage remains opaque.
// The rowed load wrapper 0x002DE3C1 stores 1/0 to VA 0x00DFF090 at 0x002DE3F2/0x002DE409, and doLoadGame tests it at 0x002DD934; s_inLoadGame retains that provider's existing static-member spelling. The data ledger binds TheGameState to VA 0x00DFF08C.
// Nonvirtual row declarations: suffix 0x002DBC97, mode 0x002DBE62, paths 0x002DC340/0x002DC802/0x002DC833/0x002DC9F7/0x002DCB9C, postprocess 0x002DC4B8/0x002DC52B/0x002DCF6C, blocks 0x002DCDBF/0x002DCE24/0x002DE34B, default name 0x002DD282, save 0x002DD38D/0x002DD7E6/0x002DDE43, load 0x002DD91A/0x002DE3C1/0x002DEEC3/0x002DF2F6, CRC friend 0x002DDD0B, iteration 0x002DF1F1, listbox 0x002DF3B0. Their decorated ledger names prove the signatures and access below.

#pragma once
#ifndef CANONICAL_GAMESTATE_H
#define CANONICAL_GAMESTATE_H

#ifndef CANONICAL_SUBSYSTEMINTERFACE_H
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class AsciiString;
class UnicodeString;
class GameWindow;
class Snapshot;
class Xfer;
struct BfmeSubobject0022CE19;
struct TreeHintOpaque0043671B;
struct Rva00229811;
enum SnapshotType;

class GameState : public SubsystemInterface, public Snapshot
{
public:
    GameState();
    virtual ~GameState();
    virtual void init();
    virtual void reset();
    virtual void update();

    int determineCurrentGameSaveFileMode();
    void *rva002DBC97Get(int mode);
    AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
    AsciiString portableMapPathToRealMapPath(const AsciiString &in) const;
    AsciiString getMapLeafName(const AsciiString &in) const;
    AsciiString packPortableMapPath(const AsciiString &in) const;
    AsciiString unpackPortableMapPath(const AsciiString &in) const;
    UnicodeString rva002DD282(int mode);
    int saveGame(UnicodeString filename, const UnicodeString &desc, int which, bool showMessage, int param5);
    int rva002DD7E6AutoSave();
    void rva002DDE43(const UnicodeString &name, const UnicodeString &text, int save, int confirm);
    int rva002DF2F6(const UnicodeString &filename);
    int rva002DE3C1(TreeHintOpaque0043671B gameInfo);
    int doLoadGame(TreeHintOpaque0043671B gameInfo);
    bool getSaveGameInfoFromFile(UnicodeString filename, BfmeSubobject0022CE19 *saveGameInfo);
    void iterateSaveFiles(void (*callback)(UnicodeString, void *), void *userData, int mode);
    void populateSaveGameListbox(GameWindow *listbox, GameWindow *autoSaveListbox, bool newSave, int filter);
    void xferSaveData(Xfer *xfer, SnapshotType which);
    void friend_xferSaveDataForCRC(Xfer *xfer, SnapshotType which);
    void gameStatePostProcessLoad();
    void rva002DC4B8(void *snapshot, unsigned sequence);
    void addPostProcessSnapshot(Snapshot *snapshot, unsigned sequence);
    static bool s_inLoadGame;

    char m_opaque10[0x2C - 0x10];
    AsciiString m_pristineMapName;
    char m_opaque30[0x48 - 0x30];
    int m_saveFileType;
    char m_opaque4C[0xE0C - 0x4C];
    void *field0E0C;
    void *field0E10;
    unsigned field0E14;
    bool m_isInLoadGame;

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif

private:
    struct SnapshotBlock;
    void addSnapshotBlock(AsciiString blockName, Snapshot *snapshot, SnapshotType which);
    SnapshotBlock *findBlockInfoByToken(AsciiString token, SnapshotType which);
};

extern GameState *TheGameState;

#endif
