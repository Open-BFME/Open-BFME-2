// cl: /O1 /DNDEBUG /MD /EHsc

// Eva::messageToName with BFME2's mod-extended fallback.
//
// Zero Hour's messageToName is a plain static-table lookup. Retail BFME2 keeps
// that table (22 names, "EVA_INVALID" for -1) but, when the id falls outside
// it, walks the dynamic event-name table at Eva+0x34 -- a bucket vector of
// first-non-null head fetch plus lazy node advance -- comparing each node's
// message key and copying its name out, returning "<Unknown>" when nothing
// matches. The table/iterator helpers are the banked ?first@Rva000427195 and
// ?next@Rva000411084 pins; the node shape {next+0 name+4 key+8} is read off
// those pins' archaeology notes and reproduces retail's [eax+8] compare and
// +4 copy exactly.

class AsciiString;

template <typename T>
class StringBase
{
public:
    void concat(const T *text);

private:
    friend class AsciiString;

    StringBase(const T *text);
    StringBase(const StringBase<T> &that);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

// Inline throughout: retail reaches StringBase's private constructors directly
// from the caller rather than through a wrapper, which is what an inlined
// AsciiString constructor looks like.
class AsciiString
{
public:
    AsciiString(const char *text)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(text);
    }

    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            (const StringBase<char> &)that);
    }

    ~AsciiString();

private:
    char *m_text;
};

// Iterator home for the event-name walk. The helpers below are the banked
// Rva000427195/Rva000411084 pins, so the class names spell those pins.
class Rva000411084
{
public:
    void *next();
    void *advance();

    void *m_current;
    void *m_owner;
};

class Rva000427195
{
public:
    void *first(Rva000411084 *iter);
};

// One entry of the dynamic event-name table: the name handed out on a hit at
// +4, the message id compared against the query at +8.
struct EvaMessageNameNode
{
    EvaMessageNameNode *m_next;
    AsciiString m_name;
    int m_message;
};

static const char *TheEvaMessageNames[] =
{
    "DefaultEvaEvent",
    "BeaconDetected",
    "GeneralLevelUp",
    "UnitLevelUp",
    "UpgradeComplete",
    "CastleBreached",
    "AllyDefeated",
    "EnemyDefeated",
    "EnemyCampDestroyed",
    "CampDestroyed",
    "AllyCampDestroyed",
    "BuildQueuePausedDueToCPLimit",
    "CannotBuildDueToCPLimit",
    "BuildQueuePausedDueToFunds",
    "CannotBuildDueToFunds",
    "WallsBeingClimbed",
    "BuildingBeingStolen",
    "BuildingStolen",
    "WorldMustBattle",
    "WorldMustRetreat",
    "WorldMustChooseOwner",
    "WorldRegionLostUncontested",
};

class Eva
{
public:
    AsciiString messageToName(int message);

private:
    // Only the event-name table at +0x34 is known; the preceding members are
    // whatever the rest of Eva lays out and do not participate here.
    char m_unknown[0x34];
    Rva000427195 m_eventNameTable;
};

AsciiString Eva::messageToName(int message)
{
    Rva000411084 iter;

    if (message == -1)
        return AsciiString("EVA_INVALID");

    if (message < 22)
        return AsciiString(TheEvaMessageNames[message]);

    m_eventNameTable.first(&iter);
    while (iter.m_current != 0)
    {
        EvaMessageNameNode *node = (EvaMessageNameNode *)iter.m_current;
        if (node->m_message == message)
            return AsciiString(node->m_name);
        iter.next();
    }

    return AsciiString("<Unknown>");
}


// ?next@Rva000411084@@QAEPAXXZ
void *Rva000411084::next()
{
    EvaMessageNameNode *node = ((EvaMessageNameNode *)m_current)->m_next;
    if (node == 0)
        node = (EvaMessageNameNode *)advance();
    m_current = node;
    return this;
}
