// cl: /O1 /EHsc /MD
//
// ??1Rva005248D0@@UAE@XZ @0x005248D0 111B: dtor destroying six vector-holder members.
// Stores vtable 0x00802A80 then destroys +0x4C +0x40 +0x34 +0x1C +0x10 +0x04 in reverse
// with EH states 4 3 2 1 0 -1. Callees all rowed QAE dtors; 37 callers incl deleting dtor.
// Evidence: reverse destruction order plus sizes 12 12 24 12 12 from neighbour Rva0052493F
// six clears at same offsets; no base call; vtable 0x00802A80.

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005241B0
{
public:
	~Rva005241B0();
private:
	char m_pad[12];
};

class Rva00524436
{
public:
	~Rva00524436();
private:
	char m_pad[24];
};

class Rva00524265
{
public:
	~Rva00524265();
private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva00524349
{
public:
	~Rva00524349();
private:
	char m_pad[12];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	Rva0052413E m_04;
	Rva005241B0 m_10;
	Rva00524436 m_1C;
	Rva00524265 m_34;
	Rva005242D7 m_40;
	Rva00524349 m_4C;
};

Rva005248D0::~Rva005248D0()
{
}
