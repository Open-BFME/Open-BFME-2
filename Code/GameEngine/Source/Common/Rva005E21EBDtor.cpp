// cl: /MD /EHsc
//
// ??1Rva005E21EB@@UAE@XZ retail 0x005E21EB 59B.
// Virtual dtor, not a ctor: the only caller 0x005E25B1 is its scalar deleting
// dtor (dtor call, test flag bit 0, operator delete 0x0002FD60). Retail stores
// vtable 0x00877AB8, clears the owning pointer at +0x0C through the rowed
// Rva000AD6F4::clear 0x000AD6F4 in EH state 0, then calls base dtor
// 0x004E84A4. The unwind map destroys only that base at state 0, so +0x0C has
// no destructor of its own. The base dtor stores vtable 0x007C6F20; it is the
// same class already pinned as Rva00539926Base at 0x004E84A4, identified by
// that vtable. Member modeling follows Rva002D3573Dtor.

class Overridable
{
public:
	void markAsOverride();
};

class Rva005E2439
{
public:
	void rva005E2540();
};

class Rva000AD6F4
{
public:
	void clear();
private:
	char m_pad[8];
};

class Rva00539926Base
{
public:
	virtual ~Rva00539926Base();
};

class Rva005E21EB : public Rva00539926Base
{
public:
	virtual ~Rva005E21EB();
	virtual void rva005E25CD();
private:
	int m_04;
	int m_08;
	Rva000AD6F4 m_0C;
};

Rva005E21EB::~Rva005E21EB()
{
	m_0C.clear();
}
void Rva005E21EB::rva005E25CD()
{
	((Overridable *)this)->markAsOverride();
	((Rva005E2439 *&)m_0C)->rva005E2540();
}
