// cl: /MD /EHsc
// Retail RVA 0x00248CDD, 30 bytes.
// ?rva00248CDD@Rva00248CDD@@QBE_NABV1@@Z
// Honest address name: __thiscall 6-byte key comparison (dword at +0, word at
// +4), 0 when equal, 1 when different. Owner class unproven (7 call sites in
// unclaimed bodies across game/UI/net code), so the class carries the address.
// Unlock lane: landing it makes 1 of 6 waiting functions fully ready.
// Prev GameLogicStartingCamera shares flags.
class Rva00248CDD
{
public:
    bool rva00248CDD(const Rva00248CDD &other) const;
private:
    unsigned int m_key0;
    unsigned short m_key4;
};

bool Rva00248CDD::rva00248CDD(const Rva00248CDD &other) const
{
    return m_key0 != other.m_key0 || m_key4 != other.m_key4;
}
