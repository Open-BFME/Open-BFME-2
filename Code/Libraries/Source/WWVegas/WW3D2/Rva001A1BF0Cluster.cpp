// cl: /DNDEBUG /MD

class VBase
{
public:
	virtual void *slot0(int);
	virtual void *slot1(int);
	virtual void *slot2(int);
	virtual void *slot3(int);
	virtual void slot4(float);
};

void operator delete(void *);

class Rva001A1BF0
{
public:
	void set(VBase *p);

private:
	char m_pad[0xd4];
	VBase *m_ptr;
};

void Rva001A1BF0::set(VBase *p)
{
	if (m_ptr) {
		operator delete(m_ptr->slot0(0));
		m_ptr = 0;
	}
	m_ptr = p;
}

class Rva001A1C40
{
public:
	void set(VBase *p);

private:
	char m_pad[0xe4];
	VBase *m_ptr;
};

void Rva001A1C40::set(VBase *p)
{
	if (m_ptr) {
		operator delete(m_ptr->slot0(0));
		m_ptr = 0;
	}
	m_ptr = p;
	if (p) {
		p->slot4(0.001f);
	}
}
