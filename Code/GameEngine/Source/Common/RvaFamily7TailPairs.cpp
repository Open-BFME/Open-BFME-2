// Family-7 tail pairs (20B each): each holder method calls first() on
// itself, then tail-calls second() on a member (three members at positive
// offsets, one reached at this-8). first/second are opaque address-named
// pins; holder, member and callee identities are unproven.
class Mbr0004378D
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
	Mbr0004378D m_280; // +0x280
};

void Rva0004378D::method()
{
	first();
	m_280.second();
}

class Mbr0033B1CD
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
	Mbr0033B1CD m_04; // +4
};

void Rva0033B1CD::method()
{
	first();
	m_04.second();
}

class Mbr005CDDF0
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
	Mbr005CDDF0 m_0C; // +0xC
};

void Rva005CDDF0::method()
{
	first();
	m_0C.second();
}

class Mbr005E5554
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
	((Mbr005E5554 *)((char *)this - 8))->second();
}
