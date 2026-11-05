// Target facts: RVAs use image base 0x00400000. Constructors 0x003B26DF/0x003B5AC7 and destructor 0x003B4230 store VA 0x00C1F3F8 at +0. Its sole slot is the protected scalar deleting destructor 0x003B4A78, which calls 0x003B4230; the next word, VA 0x00C1F3FC, is ScriptAction's table (constructors 0x003B2804/0x003B5413, deleting destructor 0x003B53F7). Condition has no pool getter slot. Allocations at 0x003B5B16 and 0x003B6D9A pass 0x50 to global new, then call the typed/default constructors; the parser 0x003B6D92 keeps no unwind state around its default construction, so that constructor is declared throw().
// Target facts: the constructors write dwords +4/+8/+0x3C/+0x40/+0x44/+0x48 and bytes +0x4C=1/+0x4D=0, and clear twelve pointers at +0x0C. Destructor 0x003B4230 traverses +0x3C and deletes parameters from +0x0C using count +8. Writer 0x003B428C serializes type +4, count +8 and both tail bytes; duplicate 0x003B5B07 copies the tail bytes and recursively duplicates +0x3C. Rowed out-of-line methods are setConditionType 0x003B4A94, rva003B275A 0x003B275A, getUiStrings 0x003B39B2, getUiText 0x003B5BA4, WriteConditionDataChunk 0x003B428C and ParseConditionDataChunk 0x003B6D92. Parser 0x003B6D92 bounds condition types by 0xCA. Retail 0x003B6B29/0x003B6B3C tests the tail bytes to display disabled/NOT text; 0x002097C4 tests +0x4C before evaluation, 0x003EC8DF tests +0x4D to invert its result, and 0x003EA9B6 reads type +4 for the dispatcher.
// Donor facts: Zero Hour GeneralsMD GameLogic/Scripts.h names ConditionType values 0..4 and 0x55, the type/count/parameter/next fields, warning/custom-data/custom-frame fields and their accessors. The two BFME2 tail bytes retain neutral names; no Zero Hour pool inheritance or pool slot is imported.

#ifndef BFME2_SCRIPTCONDITION_H
#define BFME2_SCRIPTCONDITION_H

class AsciiString;
class Parameter;
class DataChunkInput;
class DataChunkOutput;
struct DataChunkInfo;

class Condition
{
protected:
    virtual ~Condition();

public:
    enum ConditionType
    {
        CONDITION_FALSE = 0,
        COUNTER = 1,
        FLAG = 2,
        CONDITION_TRUE = 3,
        TIMER_EXPIRED = 4,
        SKIRMISH_SPECIAL_POWER_READY = 0x55,
        NUM_ITEMS = 0xCA
    };

    Condition() throw();
    Condition(ConditionType type);
    Condition *duplicate() const;
    void setConditionType(ConditionType type);
    int rva003B275A();
    int getUiStrings(AsciiString *const strings);
    AsciiString getUiText();

    static void WriteConditionDataChunk(DataChunkOutput &writer, Condition *condition);
    static bool ParseConditionDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);

    ConditionType getConditionType() const { return (ConditionType)m_conditionType; }
    int getType() const { return m_conditionType; }
    bool isEnabled() const { return m_flag4C; }
    bool isInverted() const { return m_b4D != 0; }
    int getNumParameters() const { return m_numParms; }
    Parameter *getParameter(int index) const
    {
        if (index >= 0 && index < m_numParms)
            return m_parms[index];
        return 0;
    }
    Condition *getNext() const { return m_nextCondition; }
    void setNextCondition(Condition *condition) { m_nextCondition = condition; }
    bool hasWarnings() const { return m_x40 != 0; }
    void setWarnings(bool warnings) { m_x40 = warnings; }
    int getCustomData() const { return m_x44; }
    void setCustomData(int value) { m_x44 = value; }
    unsigned int getCustomFrame() const { return m_x48; }
    void setCustomFrame(unsigned int frame) { m_x48 = frame; }

    int m_conditionType;
    int m_numParms;
    Parameter *m_parms[12];
    Condition *m_nextCondition;
    int m_x40;
    int m_x44;
    int m_x48;
    bool m_flag4C;
    unsigned char m_b4D;
};

#endif
