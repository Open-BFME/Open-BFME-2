// cl: /MD
//
// Target evidence at 0x004FC470 (97 bytes): one byte argument gates the
// +0x20 object's rowed 0x004E0CCB call; the +0x20 owning pointer is then
// cleared through 0x000AD6F4. The method resets +0x30 and +0x34, calls slot
// +0x20 on the +0x24 object with (result, 1), and calls 0x0059DFFB on that
// object when result is false. It finishes by walking the list at +0x08
// through rowed 0x004FC320 with the 0x001FF3A9 listener forwarder and this.
// The enclosing class and the +0x24 object's identity are not established;
// their address-derived names preserve that uncertainty.

class Rva004FC320Listener
{
public:
	virtual void notify(void *);
};

class Rva004FC320List
{
public:
    void forEach(void (Rva004FC320Listener::*notify)(void *), void *arg);
private:
    Rva004FC320Listener **m_begin;
    Rva004FC320Listener **m_end;
    Rva004FC320Listener **m_capacity;
    unsigned int m_index;
};

struct TreeHintRef00217D4C;

class Rva001FF3A9
{
public:
    void rva001FF3A9(const TreeHintRef00217D4C &arg);
    virtual void rva001FF3A9();
};

class Rva004E0B60
{
public:
	void rva004E0CB6();
	void rva004E0CA3();
	bool rva004E0CCB();
};

class Rva000AD6F4
{
public:
    void clear();
    Rva004E0B60 *m_ptr;
};

class Rva0059DFFB
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8(bool result, int value);
};

// 0x0059DFFB is rowed as the virtual Rva0059E242::rva0059DFFB
// (Rva0059DFFBUpdate.cpp); retail calls it directly, so the call is qualified.
class Rva0059E242
{
public:
	virtual ~Rva0059E242();
	virtual void rva0059DF60();
	virtual void rva0059DFFB();
};

class Rva004FC470
{
public:
	void rva004FC470(bool flag);

private:
	char m_pad00[8];
	Rva004FC320List m_list;
	char m_pad18[8];
	Rva000AD6F4 m_member20;
	Rva0059DFFB *m_member24;
	char m_pad28[8];
	int m_30;
	char m_34;
};

void Rva004FC470::rva004FC470(bool flag)
{
	bool result = false;
	if (flag && m_member20.m_ptr)
		result = m_member20.m_ptr->rva004E0CCB();

	m_member20.clear();
	m_30 = 0;
	m_34 = 0;

	if (m_member24)
	{
		m_member24->slot8(result, 1);
		if (!result)
			((Rva0059E242 *)m_member24)->Rva0059E242::rva0059DFFB();
	}

	m_list.forEach((void (Rva004FC320Listener::*)(void *))(void (Rva001FF3A9::*)())&Rva001FF3A9::rva001FF3A9, this);
}
