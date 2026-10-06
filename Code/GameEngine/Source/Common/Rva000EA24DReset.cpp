// cl: /EHsc /MD
// ?rva000EA24D@Rva000EA24D@@QAEXXZ 0x000EA24D 115B
// Reset after Rva000E6AC0::rva000E65B1: DX8 lock, zero count at +0x44540,
// set dirty at +0x44544, release 0x40 RefItem array at +0x44558 stride 0x5C
// (dec ref at +4, virtual Release on zero), zero tail at +0x45C58.
// Evidence: calls rowed rva000E65B1; callees rowed; count/dirty offsets match
// Rva000EA21A neighbour; callers at 0x000682A2 0x0006D5C0 0x000EDEBE.

void BFME_DX8_Thread_Lock(void);
bool BFME_DX8_Thread_Assert(void);

class Rva000E6AC0
{
public:
	void rva000E65B1();
};

class RefItem
{
public:
	virtual void Release();
	int m_ref;
};

struct ArrayElem
{
	RefItem *m_ptr;
	char m_pad[0x5C - 4];
};

class Rva000EA24D
{
public:
	void rva000EA24D();
private:
	char _pad0[0x44540];
	int m_count;
	unsigned char m_dirty;
	char _pad1[0x44558 - 0x44540 - 4 - 1];
	ArrayElem m_array[0x40];
	int m_tail;
};

struct DX8Guard
{
	DX8Guard() { BFME_DX8_Thread_Lock(); }
	~DX8Guard() { BFME_DX8_Thread_Assert(); }
};

void Rva000EA24D::rva000EA24D()
{
	DX8Guard _guard;
	((Rva000E6AC0 *)this)->rva000E65B1();
	m_count = 0;
	m_dirty = 1;
	for (int i = 0; i < 0x40; ++i)
	{
		RefItem *&slot = m_array[i].m_ptr;
		RefItem *p = slot;
		if (p != 0)
		{
			if (--p->m_ref == 0)
				p->Release();
			slot = 0;
		}
	}
	m_tail = 0;
}
