// cl: /O1 /MD
// ?rva0030F4AF@Rva0030F47A@@QAEXXZ, retail 0x0030F4AF (59 bytes). Teardown of the rowed Rva0030F47A
// (ctor 0x0030F47A, vtable 0x00C09840 at +0, listener at +0x0C, owned node list head at +0x1C): restore
// the base vtable, free the node chain through the null-tolerant deleteInstance(0) plus operator delete
// path, clear the head, and tell the listener (its slot 0x40) that this object is gone. Whether this is the
// destructor proper is unproven, so it stays a plain member with an address name.
extern const void *const g_00C09840[];

class Rva0030F4AFNode
{
public:
	virtual void *deleteInstance(int flags);
	Rva0030F4AFNode *m_next;	// +0x04
};

class Rva0030F4AFListener
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void gone(void *object);	// slot 0x40
};

class Rva0030F47A
{
public:
	void rva0030F4AF();

private:
	void *m_vft;
	int m_04;
	int m_08;
	Rva0030F4AFListener *m_listener;	// +0x0C
	void *m_10;
	void *m_14;
	bool m_18;
	Rva0030F4AFNode *m_nodes;		// +0x1C
};

void Rva0030F47A::rva0030F4AF()
{
	*(const void **)this = g_00C09840;
	if (m_nodes) {
		Rva0030F4AFNode *node = m_nodes;
		do {
			Rva0030F4AFNode *next = node->m_next;
			::operator delete(node->deleteInstance(0));
			node = next;
		} while (node);
	}
	m_nodes = 0;
	if (m_listener)
		m_listener->gone(this);
}
