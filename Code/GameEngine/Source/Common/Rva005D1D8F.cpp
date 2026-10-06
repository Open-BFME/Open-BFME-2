// cl: /MD
//
// ?rva005D1D8F@Rva005D1D8F@@QAEXH@Z, retail 0x005D1D8F, 32 bytes.
// Chain via rowed rva002B7250 0x002B7250: load m_8, interior-this null check
// via (int)this-12 ternary for CreateAHeroData arg, erase via +8, clear m_8.
// Evidence: packet disassembly, rowed callee, Rva005D1F14 neighbour flags,
// ret-4 unused int arg, neg-sbb-and for int-base ternary.
class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class Rva005D1D8F
{
public:
	void rva005D1D8F(int unused);

private:
	char m_pad00[8];
	void *m_8;
};

void Rva005D1D8F::rva005D1D8F(int)
{
	Rva002B7250 *o = (Rva002B7250 *)((char *)m_8 + 8);
	int outer = (int)this - 12;
	CreateAHeroData *v = outer ? (CreateAHeroData *)this : 0;
	o->rva002B7250(v);
	m_8 = 0;
}
