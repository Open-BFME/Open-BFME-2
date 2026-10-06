// cl: /MD
//
// ??0Rva001021F7@@QAE@XZ @0x001021F7 30B: unlock ctor for 0x20 holder with two
// ObjectCreationList members at +4 and +0x14 plus nulls at +0 and +0x10.
// Evidence: packet disassembly; caller 0x00102215 new(0x20) singleton; rowed
// ObjectCreationList ctor 0x001F81BF at both slots.

class ObjectCreationList
{
public:
    ObjectCreationList();
private:
    char m_pad[12];
};

class Rva001021F7
{
public:
    Rva001021F7();
    void *m_a;
    ObjectCreationList m_list1;
    void *m_b;
    ObjectCreationList m_list2;
};

Rva001021F7::Rva001021F7() : m_a(0), m_list1(), m_b(0), m_list2()
{
}
