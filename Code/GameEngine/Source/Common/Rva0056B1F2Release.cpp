// cl: /MD
//
// ?rva0056B1F2@Rva0056B1F2@@QAEXPAX@Z @0x0056B1F2 38B.
// Conditional release: when the +4 slot equals the argument, run rowed
// 0x002B7250 on (m_04+4) with the container-adjusted this (branchless
// neg/sbb/and select), then null the slot. Honest address-derived names.
class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *other);
};

class Rva0056B1F2
{
public:
	void rva0056B1F2(void *arg);
private:
	char m_pad[4];
	void *m_04;	// +4
};

void Rva0056B1F2::rva0056B1F2(void *arg)
{
	if (m_04 != arg)
		return;
	CreateAHeroData *adj = (CreateAHeroData *)((char *)this - 0x14);
	CreateAHeroData *p = adj != 0 ? (CreateAHeroData *)this : 0;
	((Rva002B7250 *)((char *)m_04 + 4))->rva002B7250(p);
	m_04 = 0;
}
