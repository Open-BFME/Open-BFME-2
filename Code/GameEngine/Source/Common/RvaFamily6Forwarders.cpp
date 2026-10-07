// cl: /EHsc /Oy-
// Family-6 value-return forwarders (28B each): each holder method returns
// Helper(m_field); retail forwards the hidden out-slot to the helper under
// /EHsc /Oy- /O1 with no temporary. The return type needs a non-trivial
// destructor for the EH-state init retail shows; the destructor is scaffolding
// (empty, unpinned) and the helpers are opaque address-named pins. Holder,
// member and helper identities are unproven.
struct RvaF6Ret
{
	int m_00;
	int m_04;
	int m_08;
	~RvaF6Ret();
};

// The declared-not-defined destructor is load-bearing: it makes RvaF6Ret a
// non-trivial return type (hidden out-slot plus EH-state init) while no
// visible body lets the compiler elide that protection. Defining it changes
// the codegen (frameless, no EH state). Nothing links this TU in the gates.

RvaF6Ret Helper0030FA44(int v);
RvaF6Ret Helper0056BCE5(int v);
RvaF6Ret Helper0056BABF(int v);
RvaF6Ret Helper0056BB8C(int v);
RvaF6Ret Helper0056BC3D(int v);

class Rva003113DD
{
public:
	RvaF6Ret method();
private:
	int m_pad[4];
	int m_10; // +0x10
};

RvaF6Ret Rva003113DD::method()
{
	return Helper0030FA44(m_10);
}

class Rva005747F9
{
public:
	RvaF6Ret method();
private:
	int m_pad[4];
	int m_10; // +0x10
};

RvaF6Ret Rva005747F9::method()
{
	return Helper0056BCE5(m_10);
}

class Rva005773C0
{
public:
	RvaF6Ret method();
private:
	int m_00; // +0x0
};

RvaF6Ret Rva005773C0::method()
{
	return Helper0056BABF(m_00);
}

class Rva005CE3DE
{
public:
	RvaF6Ret method();
private:
	int m_00; // +0x0
};

RvaF6Ret Rva005CE3DE::method()
{
	return Helper0056BB8C(m_00);
}

class Rva005773A6
{
public:
	RvaF6Ret method();
private:
	char m_pad[8];
	Rva005773C0 m_08; // +0x8
};

RvaF6Ret Rva005773A6::method()
{
	return m_08.method();
}

class Rva005CE3C4
{
public:
	RvaF6Ret rva005CE3C4();
private:
	char m_pad[8];
	Rva005CE3DE m_08; // +0x8
};

RvaF6Ret Rva005CE3C4::rva005CE3C4()
{
	return m_08.method();
}

class Rva005CEC10
{
public:
	RvaF6Ret method();
private:
	int m_00; // +0x0
};

RvaF6Ret Rva005CEC10::method()
{
	return Helper0056BC3D(m_00);
}

class Rva005CEBF6
{
public:
	RvaF6Ret method();
private:
	char m_pad[8];
	Rva005CEC10 m_08; // +0x8
};

RvaF6Ret Rva005CEBF6::method()
{
	return m_08.method();
}

