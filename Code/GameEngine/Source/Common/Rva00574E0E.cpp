// cl: /MD
// ?rva00574E0E@Rva00574E0E@@QAEXH@Z @0x00574E0E 32B evidence: calls rowed erase
// 0x002B7250 with null-guarded this and clears holder at +0x64; sibling of
// Rva00574E2E (+0x68 guard -0xC) with holder +0x64 guard -8.
class CreateAHeroData;
class Rva002B7250
{
public:
    void rva002B7250(CreateAHeroData *v);
};
struct Holder002B7250
{
    char m_pad[4];
    Rva002B7250 m_list04;
};
class Rva00574E0E
{
public:
    void rva00574E0E(int dummy);
private:
    char m_pad[0x64];
    Holder002B7250 *m_holder64;
};
void Rva00574E0E::rva00574E0E(int /*dummy*/)
{
    Holder002B7250 *h = m_holder64;
    CreateAHeroData *arg = ((char *)this - 8) ? (CreateAHeroData *)this : 0;
    h->m_list04.rva002B7250(arg);
    m_holder64 = 0;
}
