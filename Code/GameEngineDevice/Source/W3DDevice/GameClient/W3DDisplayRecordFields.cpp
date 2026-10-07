// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native Ghidra entry 0x0025C09E, 58 bytes, ending at 0x0025C0D8.
// Target facts: ECX addresses the record; RET 0x1C consumes seven stack
// words, the first unused. Two words and four scalar SSE copies populate
// offsets 0/4/8/C/10/14. EAX finishes with the last argument, not this.
// The original class, return type and field meanings remain unidentified.
// This address-qualified method is a callable storage/ABI view, not a claim
// that the target is the constructor named by the earlier bank. Integer
// signedness and float field types are representations of those exact copies.
class Rva0025C09E
{
public:
    Rva0025C09E();
    void clearFields();
    void writeFields(int unused, int word, float a, float b, float c, float d, int tail);
private:
    int m_00;
    float m_04, m_08, m_0C, m_10;
    int m_14;
};

void Rva0025C09E::writeFields(int unused, int word, float a, float b, float c, float d, int tail)
{
    m_00 = word;
    m_04 = a;
    m_08 = b;
    m_0C = c;
    m_10 = d;
    m_14 = tail;
}

Rva0025C09E::Rva0025C09E()
{
    m_00=0; m_14=0;
    m_04=0.0f; m_08=0.0f; m_0C=0.0f; m_10=0.0f;
}

void Rva0025C09E::clearFields()
{
    m_00=0; m_14=0;
    m_04=0.0f; m_08=0.0f; m_0C=0.0f; m_10=0.0f;
}
