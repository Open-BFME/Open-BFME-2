// cl: /MD
// ?rva0059534A@Rva0059534A@@QAEXG@Z @0x0059534A 70B evidence: callees UDPDrain dtor 0x00594918 operator delete 0x0002FD60 rowed; 12 callers; prev Disp8Word next Rva0025BFE3Derived

class UDPDrain
{
public:
    ~UDPDrain();
};

class Rva0059534A
{
public:
    void rva0059534A(unsigned short key);
private:
    char m_pad[0x14];
    struct Slot
    {
        UDPDrain *ptr;
        unsigned short key;
        char m_padKey[2];
    };
    Slot m_slots[8];
};

void Rva0059534A::rva0059534A(unsigned short key)
{
    for (int i = 0; i < 8; ++i) {
        if (m_slots[i].key == key) {
            UDPDrain *p = m_slots[i].ptr;
            if (p != 0) {
                delete p;
                m_slots[i].ptr = 0;
            }
            m_slots[i].key = 0;
            break;
        }
    }
}
