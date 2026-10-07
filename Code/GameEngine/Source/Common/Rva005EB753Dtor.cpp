// cl: /DNDEBUG /MD
//
// ??1Rva005EB753@@UAE@XZ @0x005EB753 14B: vptr store then tail clear on member at +4.
// Evidence: vtable 0x00C7823C#0 plus ??_G 0x005EB761 in OpaqueScalarDeletingDtorsB17.cpp
// plus clear row 0x005EB430 plus caller dtor 0x005D06CB. No donor.
// The sibling-shaped constructor at 0x005EB706 stores this vtable, allocates
// 0x48 bytes, and calls 0x005EB481 with this plus its three pointer-sized args.
// Its extent is 77B; the vtable xrefs and inner constructor boundary are target
// evidence. The inner type name remains address-derived.
class Rva005EB481Inner
{
public:
	Rva005EB481Inner(void *owner, void *a, void *b, void *c);
	char m_opaque[0x48];
};

class Rva005EB430
{
public:
	void clear();
	void *m_ptr;
};

class Rva005EB753
{
public:
	Rva005EB753(void *a, void *b, void *c);
	virtual ~Rva005EB753();

private:
	Rva005EB430 m_member04;
};

Rva005EB753::Rva005EB753(void *a, void *b, void *c)
{
	m_member04.m_ptr = new Rva005EB481Inner(this, a, b, c);
}

Rva005EB753::~Rva005EB753()
{
	m_member04.clear();
}
