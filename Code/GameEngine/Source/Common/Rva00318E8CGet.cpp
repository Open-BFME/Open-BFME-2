// cl: /DNDEBUG /MD
// Complete 00318E8C/18 physical output contract. Native 005667A6 caller
// consumes EAX as the supplied 8-byte buffer, then reads both output words.
// The second word is copied as raw bits. Neither its original source type
// nor explicit-output versus hidden aggregate-return spelling is established.
// Keep address-owned receiver/result names and expose only observed behavior.
struct Rva00318E8COut
{
    float f;
    int i;
};
class Rva00318E8C
{
public:
    Rva00318E8COut *rva00318E8C(Rva00318E8COut *out);
private:
    char m_pad[0x20];
    float m_20;
    int m_24;
};
Rva00318E8COut *Rva00318E8C::rva00318E8C(Rva00318E8COut *out)
{
    out->f = m_20;
    out->i = m_24;
    return out;
}
