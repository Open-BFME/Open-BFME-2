// cl: /O1 /DNDEBUG /MD /EHsc
//
// Neighbour smalls around 0x00500xxx sharing one owner layout (+0x00
// field, +0x04 subobject, +0x10 subobject-with-int). 0x005007AA copies +0x00
// and +0x10 from same-layout source and refreshes the +0x04 subobject
// from the source's. All callee identities unproven; honest
// address-derived names. (0x00500839, same family, is claimed by another
// seat and left out.)

class Rva004FCD6D
{
public:
	void rva004FCD6D(int v, void *p);

public:
	int m_val;	// +0x00 (dword copied by 0x005007AA)
};

class Rva004FFFF9
{
public:
	void rva004FFFF9(const void *p);
};

class Rva0050055D
{
public:
	void rva0050055D(const void *p);
};

class Rva00500Owner
{
public:
	Rva00500Owner *rva005007AA(const Rva00500Owner *src);

private:
	void *m_00;		// +0x00
	Rva004FFFF9 m_04;		// +0x04
	char m_pad05[0x0B];	// +0x05..0x0F
	Rva004FCD6D m_10;	// +0x10
};

Rva00500Owner *Rva00500Owner::rva005007AA(const Rva00500Owner *src)
{
	m_00 = src->m_00;
	m_04.rva004FFFF9(&src->m_04);
	m_10.m_val = src->m_10.m_val;
	return this;
}
