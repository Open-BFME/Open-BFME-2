// Target facts (BFME2 RVAs): constructors 0x003B2804 (46 bytes) and 0x003B5413 (54 bytes) store VA 0x00C1F3FC at +0 (sites 0x003B281B/0x003B5420), clear count +8, twelve four-byte Parameter pointers +0x0C..+0x3B, next +0x3C, warning byte +0x40 and dword +0x44, and set byte +0x41 to 1; the default sets type +4 to NO_OP=5. Allocations at 0x003B5458 and 0x003B5EAE request sizeof 0x48, then call the typed/default constructors at 0x003B5473/0x003B5EBC. Table RVA 0x0081F3FC has one slot, scalar deleting destructor 0x003B53F7; it calls virtual ~ScriptAction 0x003B43CC, whose store at 0x003B43D5 restores that same table. The next table at 0x0081F400 belongs to Rva003B3417 (constructor store 0x003B3470). The adjacent Condition table at 0x0081F3F8 instead targets 0x003B4A78 and destructor 0x003B4230; its constructors 0x003B26DF/0x003B5AC7 store VA 0x00C1F3F8. ScriptAction is polymorphic with its destructor in the inherited MemoryPoolObject slot; no additional base storage is observed.
// Target methods: getParameter 0x00203553 bounds-checks +8 and indexes +0x0C with stride 4, matching Zero Hour's inline accessor; getUiStrings 0x003B2843 reads type +4 and its QAVAsciiString ledger argument requires a top-level const pointer; setActionType 0x003B4343 rebuilds the parameter array; duplicate 0x003B5449 copies next +0x3C and byte +0x41; getUiText 0x003B54DC tests +0x40/+0x41 at 0x003B5534/0x003B5546 for warning/disabled prefixes. ScriptEngine::setFade 0x00203777 dispatches action values 0x7C..0x7F (subtract at 0x0020377E and three decrements); Zero Hour supplies their CAMERA_FADE names. ParseAction 0x003B5EA5 and chunk callbacks 0x003B65BF/0x003B65F9 populate the action chain. The ParseAction ledger spelling KAPAV proves protected static access; rva003B3D75 0x003B3D75 retains its ledger argument types void *, void *. Constructors, destructor and nontrivial rowed methods are declared out of line.
// Donor names: Zero Hour GeneralsMD Code/GameEngine/Include/GameLogic/Scripts.h supplies MemoryPoolObject inheritance, ScriptActionType, m_actionType, m_numParms, m_parms, m_nextAction, m_hasWarnings and the common accessors. The registered MemoryPoolObject header supplies its single virtual destructor and four-byte size. BFME2-only storage has neutral offset names; +0x42..+0x43 is alignment padding before the dword at +0x44.
// Target facts: the cheat-key bodies 0x0020CDA2 and 0x0020CE13 call the typed constructor 0x003B5413 with types 3 and 4; Zero Hour names those values VICTORY and DEFEAT, consistent with NO_OP = 5. ParseAction 0x003B5EA5 keeps no unwind state around its default construction, so that constructor is declared throw(); ExecuteScriptAction 0x0033436F and ParseAction bound action types below NUM_ITEMS = 0x257.
#ifndef CANONICAL_SCRIPTACTION_H
#define CANONICAL_SCRIPTACTION_H

#include "../Common/MemoryPoolObject.h"

class AsciiString;
class Parameter;
class DataChunkInput;
struct DataChunkInfo;

class ScriptAction : public MemoryPoolObject
{
public:
    enum ScriptActionType
    {
        VICTORY = 3,
        DEFEAT = 4,
        NO_OP = 5,
        CAMERA_FADE_ADD = 0x7C,
        CAMERA_FADE_SUBTRACT = 0x7D,
        CAMERA_FADE_SATURATE = 0x7E,
        CAMERA_FADE_MULTIPLY = 0x7F,
        NUM_ITEMS = 0x257
    };

    ScriptAction() throw();
    ScriptAction(ScriptActionType type);
    virtual ~ScriptAction();

    void setActionType(ScriptActionType type);
    Parameter *getParameter(int index)
    {
        if (index >= 0 && index < m_numParms)
            return m_parms[index];
        return 0;
    }
    int getUiStrings(AsciiString *const strings);
    AsciiString getUiText();
    ScriptAction *duplicate() const;
    void rva003B3D75(void *, void *);
    static bool ParseActionDataChunk(DataChunkInput &, DataChunkInfo *, void *);
    static bool ParseActionFalseDataChunk(DataChunkInput &, DataChunkInfo *, void *);

    int getActionType() { return m_actionType; }
    int getActionType() const { return m_actionType; }
    int getNumParameters() { return m_numParms; }
    int getNumParameters() const { return m_numParms; }
    ScriptAction *getNext() { return m_nextAction; }
    ScriptAction *getNext() const { return m_nextAction; }
    void setNextAction(ScriptAction *next) { m_nextAction = next; }
    bool hasWarnings() const { return m_hasWarnings; }
    void setWarnings(bool warnings) { m_hasWarnings = warnings; }

    int m_actionType; // +0x04
    int m_numParms; // +0x08
    Parameter *m_parms[12]; // +0x0C
    ScriptAction *m_nextAction; // +0x3C
    bool m_hasWarnings; // +0x40
    unsigned char field41; // +0x41
    char pad42[2]; // +0x42
    int field44; // +0x44

protected:
    static ScriptAction *ParseAction(DataChunkInput &, DataChunkInfo *, void *);
};

#endif
