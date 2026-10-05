// cl: /O1 /DNDEBUG /MD
//
// ??1Rva005EB753@@UAE@XZ @0x005EB753 14B: vptr store then tail clear on member at +4.
// Evidence: vtable 0x00C7823C#0 plus ??_G 0x005EB761 in OpaqueScalarDeletingDtorsB17.cpp
// plus clear row 0x005EB430 plus caller dtor 0x005D06CB. No donor.
class Rva005EB430
{
public:
	void clear();
};

class Rva005EB753
{
public:
	virtual ~Rva005EB753();

private:
	Rva005EB430 m_member04;
};

Rva005EB753::~Rva005EB753()
{
	m_member04.clear();
}
