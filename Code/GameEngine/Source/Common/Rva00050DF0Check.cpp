// cl: /MD
// ?rva00050DF0@Rva00050DF0@@QAE_NXZ @0x00050DF0 21B triple-byte OR predicate at +0x12/+0x13/+0x14; callers 0x00053606 0x00053646; no donor; honest Rva class.
class Rva00050DF0
{
public:
    bool rva00050DF0();
    char m_pad[0x12];
    unsigned char m_a;
    unsigned char m_b;
    unsigned char m_c;
};
bool Rva00050DF0::rva00050DF0()
{
    return m_a != 0 || m_b != 0 || m_c != 0;
}
