// cl: /MD
// ?rva006DCC00@Rva006D6360@@QAEXXZ @0x006DCC00 10B
// Evidence: vtable slot 13 (0x34) of 0x008EA228 (Rva006D6360 ctor 0x006D6360);
// forwarder add ecx,8 to AptNativeHash::rva0070B220 0x0070B220 (ignores arg);
// chain from 0x0070B220 landing; callers at 0x0070DF83 0x006FBC58.
class AptNativeHash {
public:
    void rva0070B220(void *arg);
};

class Rva006D6360 {
    int m_a;
    int m_b;
    AptNativeHash m_hash;
public:
    void rva006DCC00();
};

void Rva006D6360::rva006DCC00()
{
    m_hash.rva0070B220(this);
}
