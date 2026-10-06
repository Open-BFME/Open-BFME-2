// cl: /EHsc /MD
// ??1Rva0042C833@@UAE@XZ retail 0x0042C833 70B
// Own vptr C3C6EC; under EH state 1 the body unregisters this through the
// rowed ?rva0042CAEB@Rva0042CBB6 0x0042CAEB on the +0xC pointer; the member
// at +0x14 is then torn down (state 0) by its inline dtor calling the rowed
// ?clear@Rva000AD6F4 0x000AD6F4; the inline base dtor restores BDBA74.
// Caller: rowed ??_GRva0042C833 0x0042C977. Supersedes Peppy's 0.94 stash
// reverse/attempts/0x0042c833.cpp (the member dtor was the missing piece).

class Rva0042CBB6
{
public:
	void rva0042CAEB(int who);
};

class Rva000AD6F4
{
public:
	~Rva000AD6F4() { clear(); }
	void clear();

private:
	int m_ptr;
};

class Rva0042C833Base
{
public:
	virtual ~Rva0042C833Base() {}

private:
	int m_04;
	int m_08;
};

class Rva0042C833 : public Rva0042C833Base
{
public:
	virtual ~Rva0042C833();

private:
	Rva0042CBB6 *m_0C;
	int m_10;
	Rva000AD6F4 m_14;
};

Rva0042C833::~Rva0042C833()
{
	m_0C->rva0042CAEB((int)this);
}
