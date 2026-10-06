// cl: /MD
//
// ?rva004D9596@Rva004D9596@@QAE_NXZ @0x004D9596 28B
// Mode-plus-triple predicate: true when m00 != -1, or m04 != 0 with
// (m18 == 0 or m0C != 0). Frameless __thiscall bool method with shared
// true/false tails (mov al,1 / xor al,al). No donor; honest Rva class with
// only the witnessed offsets modelled. Evidence: 26 callers including
// 0x004D990E and 0x004D9CF3 families; &&-chain shares the single false
// block where separate early returns give setne shape.

class Rva004D9596
{
public:
    bool rva004D9596();
    int rva004D9586();

private:
    int m_00;
    int m_04;
    char m_pad08[4];
    int m_0c;
    char m_pad10[8];
    int m_18;
};

bool Rva004D9596::rva004D9596()
{
    if (m_00 != -1 || (m_04 != 0 && (m_18 == 0 || m_0c != 0)))
        return true;
    return false;
}

int Rva004D9596::rva004D9586()
{
    int result = 0;
    if (m_04 != 0 || m_00 != -1)
        result = 1;
    return result;
}
