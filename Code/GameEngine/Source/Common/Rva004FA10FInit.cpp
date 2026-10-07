// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FA10F (89B): guarded one-time init. If +0x78 != -1 return; else
// inc +0x7C, call 0x4F922C(0), 0x4F6187, 0x4F9F39, then loop 0x4F971E plus
// 0x4F99CC(&ready) until ready, then 0x4F9D6A, 0x4F9E59, 0x4F61B1.
// All callees pinned/rowed, identities unproven.

class Rva004F922C
{
public:
	void rva004F922C(int v);
};

class Rva004F6187
{
public:
	void rva004F6187();
};

class Rva004F9F39
{
public:
	void rva004F9F39();
};

class Rva004F971E
{
public:
	void rva004F971E();
};

class Rva004F99CC
{
public:
	void rva004F99CC(bool *out);
};

class Rva004F9D6A
{
public:
	void rva004F9D6A();
};

class Rva004F9E59
{
public:
	void rva004F9E59();
};

class Rva004F61B1
{
public:
	void rva004F61B1();
};

class Rva004FA10FOwner
{
public:
	void rva004FA10F();

private:
	char m_pad[0x78];	// +0x00..0x77
	int m_78;		// +0x78 guard (-1 = needs init)
	int m_7C;		// +0x7C counter
};

void Rva004FA10FOwner::rva004FA10F()
{
	if (m_78 != -1)
		return;
	m_7C++;
	((Rva004F922C *)this)->rva004F922C(0);
	((Rva004F6187 *)this)->rva004F6187();
	((Rva004F9F39 *)this)->rva004F9F39();
	bool ready = false;
	do
	{
		((Rva004F971E *)this)->rva004F971E();
		((Rva004F99CC *)this)->rva004F99CC(&ready);
	} while (!ready);
	((Rva004F9D6A *)this)->rva004F9D6A();
	((Rva004F9E59 *)this)->rva004F9E59();
	((Rva004F61B1 *)this)->rva004F61B1();
}
