// cl: /O1 /EHsc /MD
// Range-34 dump lane: 104B EH constructor at 0x005E663C (ret 0x1c).
// Base Rva005E67FE (rowed 18B holder ctor 0x005E67FE) takes arg0; the body
// installs vtable 0x00C77E04 over the inherited vptr, then constructs the +8 member
// through the pinned 0x005E62F1 seven-arg ctor, storing null on alloc
// failure. The base dtor is declared for the retail unwind map and left
// undefined. All identities unproven (address-derived).
class Rva005E67FE
{
public:
	// The canonical V3 holder owns the inherited vptr and the held word +4.
	// Its constructor67FE and destructor6810 prove this eight-byte prefix.
	void *m_field04;
	Rva005E67FE(void *held);
	virtual ~Rva005E67FE();
};

class Rva005E62F1
{
public:
	Rva005E62F1(void *parent, int a1, int a2, int a3, int a4, int a5,
		int a6);
private:
	char m_pad[0x44];
};

class Rva005E663C : public Rva005E67FE
{
public:
	Rva005E62F1 *m08;
	virtual ~Rva005E663C();
	Rva005E663C(void *a0, int a1, int a2, int a3, int a4, int a5,
		int a6);
};

Rva005E663C::Rva005E663C(void *a0, int a1, int a2, int a3, int a4, int a5,
	int a6)
	: Rva005E67FE(a0)
{
	m08 = new Rva005E62F1(this, a1, a2, a3, a4, a5, a6);
}
