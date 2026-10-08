// cl: /MD
// ?rva00426680@Rva00426713@@QAEXXZ @0x00426680 33B evidence: vslot 9 of vtable 0x0083C408 owned by Rva00426713 plus operator delete 0x0002FD60 plus caller none plus prev next share /O1
extern const void *const g_00C3C408[];

class Inner00426680
{
public:
	virtual void *get(int flag);
};

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) Rva00426713Base
{
public:
	Rva00426713Base() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual void unused();
	char m_flag;
	int m_value;
};

class Rva00426713 : public Rva00426713Base
{
public:
	void rva00426680();
private:
	const void *m_0C;
	Inner00426680 *m_10;
};

void Rva00426713::rva00426680()
{
	void *tmp;
	if (m_10 != 0)
		tmp = m_10->get(0);
	else
		tmp = 0;
	::operator delete(tmp);
	m_10 = 0;
}
