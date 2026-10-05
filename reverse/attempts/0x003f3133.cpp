// ?rva003F3133@Rva003F2352@@QAEXPAV1@@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva003F3133@Rva003F2352@@QAEXPAV1@Z @0x003F3133 38B (dump range 18).
// Same-class sibling of rowed 0x003F2947: builds an 8-byte temporary with
// the 0xE4CD9C42 marker at +0x04, resolves it through rowed
// Rva003F2352::rva003F2947, then copies this+0x04 over the argument+0x04.
class Rva003F2352
{
public:
	Rva003F2352 *rva003F2947(Rva003F2352 *src);
	void rva003F3133(Rva003F2352 *p);
private:
	char m_head[4];
	int m_val; // +0x04
};

void Rva003F2352::rva003F3133(Rva003F2352 *p)
{
	Rva003F2352 tmp;
	tmp.m_val = (int)0xE4CD9C42;
	rva003F2947(&tmp);
	p->m_val = m_val;
}
