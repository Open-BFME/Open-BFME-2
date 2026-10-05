// cl: /O1 /DNDEBUG /MD
// ?rva005E5942@Rva005E5942@@QAEXXZ @ 0x005E5942 33B
// Evidence: rowed rva00319B31 0x00319B31 and rva00319B0A 0x00319B0A via Owner at +0x18 and wide validate 0x000B3FD0; chain after 0x00319B0A; neighbours VslotSmallBodiesAI and BitFlags11.
// class-gate: allow StringBase private validate for row ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0
template <typename T> class StringBase
{
	friend class Rva005E5942;
	void validate() const;
};

class Rva00319B0AOwner
{
public:
	void rva00319B0A();
	void rva00319B31();
};

struct Rva005E5942Inner
{
	char m_pad00[0x18];
	Rva00319B0AOwner *m_18;
};

class Rva005E5942
{
public:
	void rva005E5942();
private:
	char m_pad00[8];
	Rva005E5942Inner *m_08;
};

void Rva005E5942::rva005E5942()
{
	m_08->m_18->rva00319B31();
	((StringBase<unsigned short> *)this)->validate();
	m_08->m_18->rva00319B0A();
}
