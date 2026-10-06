// cl: /MD /EHsc
// Family 0: 0x005CD3AA, 0x005CD43D, 0x005CD4D0 (147 bytes each, total 441 bytes)
// Factory helpers constructing refcounted Rva005CD257/Rva005CD2A3/Rva005CD2EF elements
// and adding them to Rva005CD1A9 container.

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct BfmeRefPtr
{
	TargetRef00217D4C *m_ptr;

	BfmeRefPtr(TargetRef00217D4C *p = 0) : m_ptr(p)
	{
		if (m_ptr)
			++m_ptr->references;
	}

	BfmeRefPtr(const BfmeRefPtr &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}

	~BfmeRefPtr()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class Rva005CD1A9
{
public:
	void AddItem(BfmeRefPtr *item);
};

class Rva005CD257 : public TargetRef00217D4C
{
public:
	Rva005CD257(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);
	char m_pad[0x24 - sizeof(TargetRef00217D4C)];
};

class Rva005CD2A3 : public TargetRef00217D4C
{
public:
	Rva005CD2A3(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);
	char m_pad[0x24 - sizeof(TargetRef00217D4C)];
};

class Rva005CD2EF : public TargetRef00217D4C
{
public:
	Rva005CD2EF(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);
	char m_pad[0x24 - sizeof(TargetRef00217D4C)];
};

void rva005CD3AA(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4)
{
	BfmeRefPtr item(new Rva005CD257(container, p1, p2, p3, p4));
	{
		BfmeRefPtr copy(item);
		container->AddItem(&copy);
	}
}

void rva005CD43D(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4)
{
	BfmeRefPtr item(new Rva005CD2A3(container, p1, p2, p3, p4));
	{
		BfmeRefPtr copy(item);
		container->AddItem(&copy);
	}
}

class Rva005CDMorph : public TargetRef00217D4C
{
public:
	Rva005CDMorph(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4);
	char m_pad[0x24 - sizeof(TargetRef00217D4C)];
};

void rva005CD4D0(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4)
{
	BfmeRefPtr item(new Rva005CD2EF(container, p1, p2, p3, p4));
	{
		BfmeRefPtr copy(item);
		container->AddItem(&copy);
	}
}

void rva005CD563(Rva005CD1A9 *container, void *p1, void *p2, void *p3, void *p4)
{
	BfmeRefPtr item(new Rva005CDMorph(container, p1, p2, p3, p4));
	{
		BfmeRefPtr copy(item);
		container->AddItem(&copy);
	}
}
