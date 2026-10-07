// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003A3717@Team@@QAE_NABVAsciiString@@@Z, retail 0x003A3717 (31B).
// The matched TEAM_HAS_CUSTOM_STATE caller invokes this on Team with its
// state-name parameter. Retail passes Team+0x48 to the rowed
// Rva00056F61::rva0041534B AsciiString-keyed table lookup and returns whether
// the iterator's node is non-null; the owner and table's semantic label remain
// address-qualified.
#include "ascii_string.h"
#include "../GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

struct Rva0041534BIter
{
    void *m_node;
    void *m_table;
};

class Rva00056F61
{
public:
    Rva0041534BIter rva0041534B(const AsciiString *key);
};

class Team
{
public:
    bool rva003A3717(const AsciiString &stateName);
    void rva003A2DBB(float value);
    float rva003A3736(float value);

private:
    union {
        struct {
            char m_beforeStateTable[0x48];
            Rva00056F61 m_stateTable;
        };
        struct {
            char m_pad000[0x120];
            float m_120;
            unsigned int m_124;
        };
    };
};

bool Team::rva003A3717(const AsciiString &stateName)
{
    Rva0041534BIter it = m_stateTable.rva0041534B(&stateName);
    if (it.m_node != 0) {
        return true;
    }
    return false;
}

float Team::rva003A3736(float value)
{
    if (m_124 < TheGameLogic->getFrame())
        rva003A2DBB(value);
    return m_120;
}
