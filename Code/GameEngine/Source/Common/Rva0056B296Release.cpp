// cl: /MD
//
// ?rva0056B296@Rva0056B296@@QAEXPAX@Z @0x0056B296 71B.
// Twin-slot conditional release: twin of 0x0056B1F2 on the +4 slot (but
// through +8) plus the same on the +0x8 slot, each via rowed 0x002B7250
// with the branchless container select, nulling on hit. Honest
// address-derived names.
class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *other);
};

class Rva0056B296
{
public:
	void rva0056B296(void *arg);
private:
	char m_pad[4];
	void *m_04;	// +4
	void *m_08;	// +8
};

void Rva0056B296::rva0056B296(void *arg)
{
	if (m_04 == arg) {
		CreateAHeroData *adj = (CreateAHeroData *)((char *)this - 0x14);
		CreateAHeroData *p = adj != 0 ? (CreateAHeroData *)this : 0;
		((Rva002B7250 *)((char *)m_04 + 8))->rva002B7250(p);
		m_04 = 0;
	}
	else if (m_08 == arg) {
		CreateAHeroData *adj = (CreateAHeroData *)((char *)this - 0x14);
		CreateAHeroData *p = adj != 0 ? (CreateAHeroData *)this : 0;
		((Rva002B7250 *)((char *)m_08 + 8))->rva002B7250(p);
		m_08 = 0;
	}
}
