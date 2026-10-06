// cl: /DNDEBUG /MD
//
// ?rva00265143@AIUpdateInterface@@QAEHXZ, retail 0x00265143 (48 bytes).
// AI state-gated element count of the 12-byte state vector at +0x3C of the
// machine at +0x30: getCurrentStateID()==6 or 0x43 selects the count.
// The size() member on the vector subobject is what makes MSVC materialize
// the +0x3C subobject pointer (add ecx,0x3c) instead of folding the
// subtraction to a disp8 addressing mode.

class AIStateVector
{
public:
    int size() const { return (m_finish - m_start) / 12; }
private:
    int m_start;  // +0x3C
    int m_finish; // +0x40
    int m_end;    // +0x44
};

class AIStateMachineInner
{
public:
    char m_pad00[0x3C];
    AIStateVector m_vec; // +0x3C
};

class AIUpdateInterface
{
public:
    int getCurrentStateID() const;
    int rva00265143();

private:
    char m_pad00[0x30];
    AIStateMachineInner *m_machine;
};

int AIUpdateInterface::rva00265143()
{
    if (getCurrentStateID() == 6 || getCurrentStateID() == 0x43)
        return m_machine->m_vec.size();
    return 0;
}
