// Target facts: RVAs below refer to BFME2 1.06; table addresses are VAs.
// Script constructors 0x003B417E (122 bytes) and 0x003B7448 (264 bytes) store
// table 0x00C1F424 at +0. Its four entries are 0x007B41F8 (protected deleting
// destructor), 0x004B3FD0 (empty loadPostProcess), 0x007B3662 (const name getter)
// and 0x007B2540 (xfer). The following bytes at 0x00C1F434 are "Script\0".
// Destructor 0x003B35B1 restores 0x00C1F424 before destroying members, then
// stores 0x00BBB554 at 0x003B3651: Snapshot's base table, whose three following
// slots are __purecall (VA 0x0043B810). These are derived/base teardown tables,
// not competing Script tables. There is one vptr and no MemoryPoolObject
// subobject; Zero Hour's additional polymorphic base does not fit these bytes.
// duplicate 0x003B7550 pushes 0x54 at 0x003B755C, allocates at 0x003B7560 and
// calls the copy constructor at 0x003B7575. Both constructors write through
// +0x50, establishing sizeof(Script) == 0x54, rather than a partial view's size.
// Constructors and destructor prove strings +4/+8/+0xC/+0x1C/+0x44; the copy
// constructor calls StringBase<char>'s copy 0x000365F0 for the first three,
// record copy 0x003B3507 on +0x10 and four-byte mask copy 0x002CF0F0 on +0x24.
// Record writes at 0x003B4194..0x003B41A1 prove bytes +0/+1/+8, int +4 and
// string +0xC in its 16 bytes. The loader at 0x003B3536 has the same shape.
// The constructors prove int +0x20, bytes +0x28..+0x2D, condition +0x30,
// two action pointers +0x34/+0x38, int +0x3C, bytes +0x40/+0x41, floats
// +0x48/+0x4C and int +0x50. parse 0x003B79F1 reads the initial active byte
// into +0x28 and +0x40; xfer 0x003B2540 transfers +0x40 and version-2 +0x3C.
// getConditionTeamName 0x002041E1 copies +0x44 out of line. Other rowed methods:
// getUiText 0x003B6AB2, deleteOrCondition 0x003B258F, rva003B25CD 0x003B25CD,
// updateFrom 0x003B3668 and rva003B3836 0x003B3836. Node destructor 0x003B3F5E
// calls Script's protected destructor on its +4 member (BfmeNodeZ friendship).
// executeScript 0x00209E15 reads +0x34/+0x38 at 0x00209EFD/0x00209F4E and
// tests one-shot +0x29 at 0x00209F42 before clearing active +0x40 at 0x00209F48.
// The action union exposes those two pointers and the same eight-byte range
// traversed by the destructor at 0x003B35E9..0x003B3610.
// The donor's condition-time and condition-count members correspond to float
// +0x48 and int +0x50, reset at 0x003B41E1/0x003B41DE and 0x003B7517/0x003B750B.
// Donor names: GeneralsMD GameLogic/Scripts.h supplies the clause, difficulty,
// one-shot, subroutine and runtime accessors. Other field names remain neutral.
#pragma once

#ifndef BFME2_SCRIPTCLASS_H
#define BFME2_SCRIPTCLASS_H

#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class DataChunkInput;
class OrCondition;
class ScriptAction;
class AssetList;
struct AssetLoadMode;

class Rva003B3536
{
public:
    Rva003B3536() : m_field00(false), m_field01(false), m_field04(0), m_field08(true) {}
    Rva003B3536(const Rva003B3536 &);
    void rva003B3536(DataChunkInput &, unsigned short);

    bool m_field00, m_field01;
    int m_field04;
    bool m_field08;
    AsciiString m_field0C;
};

class BfmeFixedStorage002CF0F0
{
public:
    BfmeFixedStorage002CF0F0() {}
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
    unsigned int bits() const { return *(const unsigned int *)m_bytes; }
private:
    char m_bytes[4];
};

class Script : public Snapshot
{
    friend class BfmeNodeZ;
public:
    Script();
    Script(const Script &);
    Script *duplicate() const;
    bool parse(DataChunkInput &, unsigned short);
    AsciiString getConditionTeamName() const;
    AsciiString getUiText();
    void deleteOrCondition(OrCondition *);
    void rva003B25CD(int, ScriptAction *);
    void updateFrom(Script *);
    void rva003B3836(AssetList *, AssetLoadMode *);

    ScriptAction *getAction() const { return m_actions[0]; }
    ScriptAction *getFalseAction() const { return m_actions[1]; }
    OrCondition *getOrCondition() const { return m_condition; }
    void setAction(ScriptAction *action) { m_actions[0] = action; }
    void setFalseAction(ScriptAction *action) { m_actions[1] = action; }
    void setOrCondition(OrCondition *condition) { m_condition = condition; }
    bool isActive() const { return m_isActive; }
    void setActive(bool active) { m_isActive = active; }
    bool isOneShot() const { return m_isOneShot; }
    bool isSubroutine() const { return m_isSubroutine; }
    bool isEasy() const { return m_easy; }
    bool isNormal() const { return m_normal; }
    bool isHard() const { return m_hard; }
    int getDelayEvalSeconds() const { return m_delayEvaluationSeconds; }
    unsigned int getFrameToEvaluate() const { return m_frame; }
    void setFrameToEvaluate(unsigned int frame) { m_frame = frame; }

protected:
    virtual ~Script();
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *);

public:
    AsciiString m_text0, m_text1, m_text2;
    Rva003B3536 m_subrecord;
    int m_delayEvaluationSeconds;
    BfmeFixedStorage002CF0F0 m_mask;
    bool m_active, m_isOneShot, m_isSubroutine, m_easy, m_normal, m_hard;
    OrCondition *m_condition;
    union
    {
        ScriptAction *m_actions[2];
        struct
        {
            ScriptAction *m_action;
            ScriptAction *m_actionFalse;
        };
    };
    unsigned int m_frame;
    bool m_isActive, m_field41;
    AsciiString m_conditionTeamName;
    float m_conditionTime, m_field4C;
    int m_conditionExecutedCount;
};

#endif
