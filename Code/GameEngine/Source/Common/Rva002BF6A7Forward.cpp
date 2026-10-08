// cl: /DNDEBUG /MD /EHsc
// Retail 0x002BF6A7, 16B: pass the argument's +0x44 sub-object to member
// 0x002BF61B on the same object. The existing pin types the argument int.

class Rva002BF6A7
{
public:
	void rva002BF61B(int sub);
	void rva002BF6A7(int owner);
};

void Rva002BF6A7::rva002BF6A7(int owner)
{
	rva002BF61B(owner + 0x44);
}

// Retail 0x005F83A9, 16B: pass the 8-byte element count of the range at
// +0x20/+0x24 to member 0x00578513 on the same object.
struct Rva005F83A9Element
{
	int m_a;
	int m_b;
};

class Rva005F83A9
{
public:
	void rva00578513(int count);
	void rva005F83A9();

private:
	char m_pad00[0x20];
	Rva005F83A9Element *m_begin;
	Rva005F83A9Element *m_end;
};

void Rva005F83A9::rva005F83A9()
{
	rva00578513(m_end - m_begin);
}
