// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native5CFAE6..5CFB35: rowed Rva005CF872 base (+0/+4), owning-pointer
// member +8, and a member operation taking the context's pointer at +14.
// C752E4 and the rowed destructor5CFEDF establish the derived owner.
class Rva005CF872
{
public:
	Rva005CF872(void *p) : m_04(p) {}
	virtual ~Rva005CF872() {}
protected:
	void *m_04;
};

class Rva005EBC74
{
public:
	Rva005EBC74();
	~Rva005EBC74();
	bool rva005EC017(void *);
private:
	void *m_ptr;
};

struct Rva005CFAE6Context
{
	char unknown00[0x14];
	void *data;
};

class Rva005CFEDF : public Rva005CF872
{
public:
	Rva005CFEDF(void *);
	virtual void slot1();
private:
	Rva005EBC74 m_08;
};

Rva005CFEDF::Rva005CFEDF(void *p) : Rva005CF872(p)
{
	m_08.rva005EC017(((Rva005CFAE6Context *)m_04)->data);
}
