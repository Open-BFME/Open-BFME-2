// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?rva000D3A17@Rva000D3A17@@QAEXXZ @0x000D3A17 90B
// Evidence: clears ten Rva000D20A9 trees at +0x94 via rowed clear 0x000D2294
// then zeroes +0x08/+0x0C stamps +0x10=0x7530 +0x14=0xea60 releases ten
// refcounted slots at +0x18 and zeroes +0x90. Same header as ctor 0x000D3A8A
// which constructs both arrays with ehvec_ctor then calls this. Callers
// 0x000D3B03 0x0006D5CF 0x00068304.

class Rva000D20A9
{
public:
	void rva000D2294();
private:
	void *m_head; // +0x00
	int m_flag; // +0x04
};

class Rva000D3A17Ref
{
public:
	virtual void release();
	int m_refs; // +0x04 (vtable at +0x00)
};

struct Rva000D3A17RefSlot
{
	Rva000D3A17Ref *m_ptr; // +0x00
	int m_pad0; // +0x04
	int m_pad1; // +0x08
};

struct Rva000D3A17SetSlot
{
	Rva000D20A9 m_tree; // +0x00 (8 bytes: head + flag)
	int m_pad; // +0x08
};

class Rva000D3A17
{
public:
	void rva000D3A17();

private:
	void *m_00; // +0x00
	void *m_04; // +0x04
	int m_08; // +0x08
	int m_0c; // +0x0C
	int m_10; // +0x10
	int m_14; // +0x14
	Rva000D3A17RefSlot m_refs[10]; // +0x18
	int m_90; // +0x90
	Rva000D3A17SetSlot m_sets[10]; // +0x94
};

void Rva000D3A17::rva000D3A17()
{
	{
		Rva000D3A17SetSlot *slot = m_sets;
		int n = 10;
		do {
			slot->m_tree.rva000D2294();
			++slot;
		} while (--n != 0);
	}
	m_0c = 0;
	m_08 = 0;
	m_14 = 0xea60;
	m_10 = 0x7530;
	{
		Rva000D3A17RefSlot *rslot = m_refs;
		int n = 10;
		do {
			Rva000D3A17Ref *p = rslot->m_ptr;
			if (p) {
				if (--p->m_refs == 0)
					p->release();
				rslot->m_ptr = 0;
			}
			++rslot;
		} while (--n != 0);
	}
	m_90 = 0;
}
