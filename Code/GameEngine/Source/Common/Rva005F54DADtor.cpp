// cl: /MD /EHsc
//
// ??1Rva005F54DA@@QAE@XZ @0x005F54DA 93B. Dtor calling get-gated unload then three clears.
// Evidence: 2 callers incl clear@Rva005F55FA, callees rowed get@Rva0057C22FByteChaseField
// rva0057C2CC clear@Rva000AD6F4 clear@Rva005F50B9, neighbours OwnedPointerResets /O1 /MD.

class Rva0057C22FByteChaseField
{
public:
	unsigned char get() const;
};

class Rva0057C2CC
{
public:
	void rva0057C2CC();
};

class Rva000AD6F4
{
public:
	void clear();
	~Rva000AD6F4() { clear(); }
private:
	void *m_ptr;
};

class Rva005F501E
{
public:
	~Rva005F501E();
};

class Rva005F50B9
{
public:
	Rva005F501E *m_ptr;
	void clear();
	~Rva005F50B9() { clear(); }
};

class Rva005F54DA
{
public:
	~Rva005F54DA();
private:
	char m_pad00[4];
	Rva0057C2CC *m_p04;
	char m_pad08[4];
	Rva005F50B9 m_a0c;
	Rva005F50B9 m_a10;
	Rva000AD6F4 m_b14;
};

Rva005F54DA::~Rva005F54DA()
{
	if (((const Rva0057C22FByteChaseField *)m_p04)->get())
		m_p04->rva0057C2CC();
}
