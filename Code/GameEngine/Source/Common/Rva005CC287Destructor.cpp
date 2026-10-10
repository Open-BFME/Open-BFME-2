// cl: /EHsc /MD
//
// ??1Rva005CC287@@UAE@XZ, retail 0x005CC287..0x005CC2C5 (62 bytes, EH);
// pinned until now as an opaque dtor. A listener over the base Rva0086E330Base
// (vftable 0x00C6E330, as in Rva005CD651Dtor.cpp; own vftable 0x00C74E04): when
// the holder it keeps at +8 is set it erases itself from that holder's list
// at +4 (rowed 0x002B7250). Class name address-derived.
class CreateAHeroData;

class Rva0086E330Base
{
public:
	virtual ~Rva0086E330Base() {}
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct Holder005CC287
{
	int m_0;
	Rva002B7250 m_4;
};

struct Rva005CC287 : public Rva0086E330Base
{
	virtual ~Rva005CC287();
	int m_4;
	Holder005CC287 *m_8;
};

Rva005CC287::~Rva005CC287()
{
	if (m_8 != 0)
		m_8->m_4.rva002B7250((CreateAHeroData *)this);
}
