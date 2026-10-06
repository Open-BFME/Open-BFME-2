// cl: /MD
// ?rva00574E2E@Rva00574E2E@@QAEXH@Z @0x00574E2E 32B evidence: calls rowed erase 0x002B7250 with null-guarded this and clears holder at +0x68; no callers
// Holder erase with dummy int arg like Rva005CC2C5 but holder at +0x68 and arg is parent-guarded this.
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
class Rva00574E2E
{
public:
	void rva00574E2E(int dummy);
private:
	char m_pad[0x68];
	Holder002B7250 *m_holder68;
};
void Rva00574E2E::rva00574E2E(int /*dummy*/)
{
	Holder002B7250 *h = m_holder68;
	CreateAHeroData *arg = ((char *)this - 0xC) ? (CreateAHeroData *)this : 0;
	h->m_list04.rva002B7250(arg);
	m_holder68 = 0;
}
