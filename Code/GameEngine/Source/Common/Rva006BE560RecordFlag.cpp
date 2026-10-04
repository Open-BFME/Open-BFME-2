// Donor: Open-BFME-1 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngine/Source/Common/UnclaimedSmallLeaves01.cpp, b1 RVA 0x0087ECC0.
// Target: unique 56-byte placement at 0x006BE560, independently verified below.
// Identity remains address-derived. Record and field names describe accesses;
// they do not establish a named retail class or the fields' wider meaning.

struct Rva006BE560Record
{
    char m_lead[0x20];
    char m_flag;
    char m_pad[3];
};

struct Rva006BE560Records
{
    Rva006BE560Record *m_begin;
    Rva006BE560Record *m_end;

    unsigned int size() const { return (unsigned int)(m_end - m_begin); }
    Rva006BE560Record &operator[](unsigned int index) { return *(m_begin + index); }
};

class Rva006BE560Owner
{
public:
    void setFlag(int index, char flag);

    char m_lead[0x2C];
    Rva006BE560Records m_records;
};

void Rva006BE560Owner::setFlag(int index, char flag)
{
    if (index >= 0 && (unsigned int)index < m_records.size())
        m_records[index].m_flag = flag;
}
