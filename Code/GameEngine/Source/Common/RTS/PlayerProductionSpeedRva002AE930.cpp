// cl: /O1 /arch:SSE /G7 /MD /Oy-
// Native Ghidra 002AE930..002AE98B, 91B, RET4. Shares the receiver
// and three maps with rowed Player::rva002AE8CF, whose matched
// ProductionSpeedBonus caller proves Player/string-entry identity.
// Retail: find name in map294; if present, erase from maps2A8 and2BC,
// then erase the captured294 iterator through rowed003A37DC.
// The original method and field names remain unknown. Generic helpers
// keep their existing opaque names and two-word iterator interfaces.
class AsciiString;
class Rva00056F61;
struct Rva0041534BIter
{
    void *m_node;
    Rva00056F61 *m_table;
    Rva0041534BIter(void *node, Rva00056F61 *table)
        : m_node(node), m_table(table) {}
};
class Rva00056F61
{
public:
    Rva0041534BIter rva0041534B(const AsciiString *key);
};
struct VideoPair
{
    struct { void *first, *second; } s;
    VideoPair(void *first, void *second)
    {
        s.first = first;
        s.second = second;
    }
    // Retail constructs the argument table word before the node word.
    VideoPair(const VideoPair &other)
    {
        s.second = other.s.second;
        s.first = other.s.first;
    }
};
class Rva000427195
{
public:
    int rva00223429(const AsciiString *name);
    void rva003A37DC(VideoPair cursor);
};
class Player
{
public:
    void rva002AE930(const AsciiString *name);
};

void Player::rva002AE930(const AsciiString *name)
{
    Rva00056F61 *bonuses = reinterpret_cast<Rva00056F61 *>(
        reinterpret_cast<char *>(this) + 0x294);
    Rva0041534BIter found = bonuses->rva0041534B(name);
    void *node = found.m_node;
    if (node)
    {
        reinterpret_cast<Rva000427195 *>(reinterpret_cast<char *>(this) + 0x2A8)
            ->rva00223429(name);
        reinterpret_cast<Rva000427195 *>(reinterpret_cast<char *>(this) + 0x2BC)
            ->rva00223429(name);
        VideoPair cursor(node, found.m_table);
        reinterpret_cast<Rva000427195 *>(bonuses)->rva003A37DC(cursor);
    }
}
