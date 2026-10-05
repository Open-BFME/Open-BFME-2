// cl: /O2
// Partial transfer from Open-BFME-1 5cae4bdff game/GameEngine/Source/GameNetwork/
// Rva007FCF10DescriptorLookups.cpp: only Rva007FBAB0Codec::findEntry, which the
// BFME1->BFME2 address map places at 0x00667FC0 (bfme1_sweep ambiguous, error 2B);
// its unplaced twin Rva007FCF10Codec::findEntry is left out. Addresses in the
// donor text are BFME1.
// FESL message-codec descriptor lookups at retail 0x007FCF10 (vtable slot
// 0x00D2BFA8) and 0x007FBAB0 (vtable slot 0x00D2BD48). Each codec vtable is
// deleting destructor (Gen007FCF50 / Gen007FBAF0), fetch, this lookup, then
// the per-message encoders. The lookup ignores the codec, reads the message
// id at +0x1c and scans a null-terminated static table of descriptor
// pointers (VA 0x012C3BC8 / 0x012C3B40) for the entry whose +8 id matches.

struct Rva007FCF10Entry
{
    char m_pad00[8];
    int m_id;
};

struct Rva007FCF10Message
{
    char m_pad00[0x1c];
    int m_id;
};

extern Rva007FCF10Entry *g_00DD8298[];

class Rva007FBAB0Codec
{
public:
    virtual ~Rva007FBAB0Codec();
    virtual int fetch();
    virtual Rva007FCF10Entry *findEntry(Rva007FCF10Message *message);
};

Rva007FCF10Entry *Rva007FBAB0Codec::findEntry(Rva007FCF10Message *message)
{
    int id = message->m_id;
    if (id == -1)
        return 0;
    for (Rva007FCF10Entry **entry = g_00DD8298; *entry; ++entry)
        if ((*entry)->m_id == id)
            return *entry;
    return 0;
}
