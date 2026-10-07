// Opaque member ABI views use explicit Rva names. Target callee identities now known:
// +4 member cleanup at0x0033B1CD calls protected StringBase<unsigned short>::~StringBase at0x00036E70.
// +0xC member cleanup at0x005CDDF0 calls Coord2D::~Coord2D at0x000B3FD0.
// Holder identity and complete member layouts remain unproven; only access offsets and call ABI are claimed.
// Family-7 tail pairs (20B each): each holder method calls first() on
// itself, then tail-calls second() on a member (three members at positive
// offsets, one reached at this-8). first/second are opaque address-named
// pins; holder, member and callee identities are unproven.
class Rva0004378DMember
{
public:
	void second();
};

class Rva0004378D
{
public:
	void method();
	void first();
private:
	char m_pad[0x280];
	Rva0004378DMember m_280; // +0x280
};

void Rva0004378D::method()
{
	first();
	m_280.second();
}

class Rva0033B1CDMbr
{
public:
	void second();
};

class Rva0033B1CD
{
public:
	void method();
	void first();
private:
	int m_pad;
	Rva0033B1CDMbr m_04; // +4
};


class Rva005CDDF0Mbr
{
public:
	void second();
};

class Rva005CDDF0
{
public:
	void method();
	void first();
private:
	char m_pad[0xC];
	Rva005CDDF0Mbr m_0C; // +0xC
};

void Rva005CDDF0::method()
{
	first();
	m_0C.second();
}

class Rva005E5554Member
{
public:
	void second();
};

class Rva005E5554
{
public:
	void method();
	void first();
};

void Rva005E5554::method()
{
	first();
	((Rva005E5554Member *)((char *)this - 8))->second();
}
