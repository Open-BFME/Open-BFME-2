// cl: /MD
// ?rva005FA91C@Rva005FA91C@@QAEXH@Z, RVA 0x005FA91C, 96 bytes.
// Builds GameMessage type 0x6B4 via MessageStreamSubsystem slot 0x48 and
// appends five ints: [[this+4]+0x14]+0x34, [this+4]+0x18, [this+4]+0x1C,
// entries[idx].key at this+idx*8+0x34, entries[idx+1].key at this+idx*8+0x3C.
// Evidence: same +0x34 stride-8 array as find 0x005FA8F5; callees rowed
// appendIntegerArgument 0x30F936; global MessageStreamSubsystem.
class GameMessage {
public:
    void appendIntegerArgument(int v);
};
class MessageStream {
public:
    virtual void _d00(); virtual void _d01(); virtual void _d02(); virtual void _d03();
    virtual void _d04(); virtual void _d05(); virtual void _d06(); virtual void _d07();
    virtual void _d08(); virtual void _d09(); virtual void _d10(); virtual void _d11();
    virtual void _d12(); virtual void _d13(); virtual void _d14(); virtual void _d15();
    virtual void _d16(); virtual void _d17();
    virtual GameMessage *createMessage(int type);
};
extern class MessageStream *TheMessageStream;
struct Inner005FA91C {
    char m_pad[0x34];
    int m_val34;
};
struct Outer005FA91C {
    char m_pad[0x14];
    Inner005FA91C *m_ptr14;
    int m_val18;
    int m_val1C;
};
struct Rva005FA91CEntry {
    int m_key;
    int m_val;
};
struct Rva005FA91C {
    char m_pad0[4];
    Outer005FA91C *m_ptr4;
    char m_pad8[0x2C];
    Rva005FA91CEntry m_entries[3];
    int m_count;
    void rva005FA91C(int idx);
};
void Rva005FA91C::rva005FA91C(int idx)
{
    GameMessage *msg = TheMessageStream->createMessage(0x6B4);
    msg->appendIntegerArgument(m_ptr4->m_ptr14->m_val34);
    msg->appendIntegerArgument(m_ptr4->m_val18);
    msg->appendIntegerArgument(m_ptr4->m_val1C);
    msg->appendIntegerArgument(m_entries[idx].m_key);
    msg->appendIntegerArgument(m_entries[idx + 1].m_key);
}
