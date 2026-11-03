// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/GameEngine/Source/Common

class BfmeTagZBRefCounted
{
public:
	virtual void Delete_This(unsigned int);
	int m_refs;
};

class BfmeTagZB
{
public:
	BfmeTagZB() : m_bfmeTagZB(0) {}
	BfmeTagZB(const BfmeTagZB &other) throw()
		: m_bfmeTagZB(other.m_bfmeTagZB)
	{
		if (m_bfmeTagZB)
			++((BfmeTagZBRefCounted *)m_bfmeTagZB)->m_refs;
	}
	~BfmeTagZB()
	{
		BfmeTagZBRefCounted *p = (BfmeTagZBRefCounted *)m_bfmeTagZB;
		if (p && --p->m_refs <= 0)
			p->Delete_This(1);
	}
	BfmeTagZBRefCounted *m_bfmeTagZB;
};

// The rowed copy constructor (0x0014A120) only needs an emitting caller; the old one
// forwarded through an unrowed placeholder address (0x0004782A) that kept the unit
// from linking.
// ?bfmeEmitZBCopy@@YAXPAVBfmeTagZB@@ABV1@@Z absent-from-retail
void bfmeEmitZBCopy(BfmeTagZB *p, const BfmeTagZB &source)
{
	p->BfmeTagZB::BfmeTagZB(source);
}
