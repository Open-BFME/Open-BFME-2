// cl: /DNDEBUG /MD /EHsc
// ?rva002CA9CA@Rva002CA9CA@@QAE_NHPBX@Z, retail 0x002CA9CA, 143 bytes.
// Recursive contains: +0x58 id fast path, null arg guard, intrusive list at
// +0x17C (sentinel compare), rowed upgrade-mask test 0x00507558, virtual
// slot 0x1C gate, slot 0x28 id compare at +0x158, slot 0x2C child recurse.
// Evidence: unlock lane, 4 callers including self 0x002CAA39, callees rowed,
// prev Rva002CA88BParse.cpp flags.
class Rva00507823
{
public:
	unsigned char rva00507558(const void *arg);
};

struct ListNode
{
	ListNode *m_next;
	ListNode *m_prev;
	void *m_data;
};

class VirtNode
{
public:
	virtual void v00();
	virtual bool v04(const void *a, int b);
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual bool v1c();
	virtual void v20();
	virtual void v24();
	virtual void *v28();
	virtual void *v2c();
};

struct ChildId
{
	char m_pad[0x158];
	int m_id;
};

struct FilterInner
{
	char m_pad[0x116];
	unsigned char m_flag;
};

struct Filter
{
	char m_pad[4];
	FilterInner *m_04;
};

class VirtNode2
{
public:
	virtual void v00();
	virtual bool v04(int a, const void *b);
	virtual void v08();
	virtual void v0c(int a, const void *b);
	virtual void v10();
	virtual void v14(int a, const void *b);
	virtual void v18();
	virtual bool v1c();
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual void v2c() = 0;
	virtual void v30();
	virtual bool v34();
	virtual void v38();
	virtual void v3c();
};

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
};

class Rva002CAC6ENotify
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24(int a, int b);
};

class Rva002CA9CA
{
public:
	bool rva002CA9CA(int id, const void *arg);
	bool rva002CAA59(int a1, const void *a2);
	void rva002CA942();
	void rva002CA970(int a1, int a2, const void *a3, int a4);
	void rva002CAA9D(int a1, const void *a2, const void *a3, int a4);
	float rva002CACD7(const void *arg);
	bool rva002CAD8B();
	void rva002CAC6E(int a, int b);
private:
	char m_pad00[0x58];
	int m_58;
	char m_pad5c[0xa4 - 0x5c];
	Rva001E11F8 *m_a4;
	Rva001E11F8 *m_a8;
	Rva001E11F8 *m_ac;
	Rva001E11F8 *m_b0;
	char m_padb4[0xb8 - 0xb4];
	Rva001E11F8 *m_b8;
	Rva001E11F8 *m_bc;
	Rva001E11F8 *m_c0;
	Rva001E11F8 *m_c4;
	char m_padc8[0x110 - 0xc8];
	unsigned char m_110;
	char m_pad111[0x130 - 0x111];
	float m_130;
	char m_pad134[0x17c - 0x134];
	ListNode *m_17c;
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const void *key);
};

extern class ThingFactory *TheThingFactory;

struct FloatHolder
{
	char m_pad[0x130];
	float m_130;
};

bool Rva002CA9CA::rva002CA9CA(int id, const void *arg)
{
	if (m_58 == id)
		return true;
	if (arg == 0)
		return false;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode *obj = (VirtNode *)cur->m_data;
		if (((Rva00507823 *)obj)->rva00507558(arg))
		{
			if (obj->v1c())
			{
				void *p = obj->v28();
				if (p != 0)
				{
					if (((ChildId *)p)->m_id == id)
						return true;
				}
			}
			void *child = obj->v2c();
			if (child != 0)
			{
				if (((Rva002CA9CA *)child)->rva002CA9CA(id, arg))
					return true;
			}
		}
		cur = cur->m_next;
	}
	return false;
}

bool Rva002CA9CA::rva002CAA59(int a1, const void *a2)
{
	if (a1 == 0)
		return false;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode *obj = (VirtNode *)cur->m_data;
		if (obj->v04(a2, a1))
			return true;
		cur = cur->m_next;
	}
	return false;
}

void Rva002CA9CA::rva002CA970(int a1, int a2, const void *a3, int a4)
{
	(void)a2;
	(void)a4;
	const Filter *flt = (const Filter *)a3;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode2 *obj = (VirtNode2 *)cur->m_data;
		if (flt != 0 && (flt->m_04->m_flag & 0x20) != 0)
		{
			if (obj->v04(a1, a3))
			{
				obj->v0c(a1, a3);
			}
		}
		cur = cur->m_next;
	}
}

void Rva002CA9CA::rva002CAA9D(int a1, const void *a2, const void *a3, int a4)
{
	(void)a4;
	if (a2 == 0)
		return;
	if (a3 == 0)
		return;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode2 *obj = (VirtNode2 *)cur->m_data;
		if (obj->v1c())
		{
			if (obj->v04(a1, a3))
			{
				obj->v14(a1, a3);
			}
		}
		cur = cur->m_next;
	}
}

float Rva002CA9CA::rva002CACD7(const void *arg)
{
	if (arg == 0)
		return 0.0f;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode *obj = (VirtNode *)cur->m_data;
		if (((Rva00507823 *)obj)->rva00507558(arg))
		{
			Rva002CA9CA *child = (Rva002CA9CA *)obj->v2c();
			if (child != 0 && (child->m_110 & 2) != 0)
			{
				ListNode *inner = child->m_17c->m_next;
				while (inner != child->m_17c)
				{
					VirtNode *iobj = (VirtNode *)inner->m_data;
					if (((Rva00507823 *)iobj)->rva00507558(arg))
					{
						if (iobj->v1c())
						{
							void *p = iobj->v28();
							if (p != 0)
								return ((FloatHolder *)p)->m_130;
						}
					}
					inner = inner->m_next;
				}
			}
		}
		cur = cur->m_next;
	}
	return 0.0f;
}

bool Rva002CA9CA::rva002CAD8B()
{
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode2 *obj = (VirtNode2 *)cur->m_data;
		if (obj != 0 && obj->v34())
			return true;
		cur = cur->m_next;
	}
	return false;
}

void Rva002CA9CA::rva002CA942()
{
	if (TheThingFactory == 0)
		return;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode2 *obj = (VirtNode2 *)cur->m_data;
		obj->v20();
		cur = cur->m_next;
	}
}

void Rva002CA9CA::rva002CAC6E(int a, int b)
{
	char *esi = (char *)this + 0xB8;
	int n = 4;
	do {
		Rva001E11F8 *p1 = *(Rva001E11F8 **)(esi - 0x14);
		if (p1)
			p1->rva001E11F8(a, b);
		Rva001E11F8 *p2 = *(Rva001E11F8 **)(esi);
		if (p2)
			p2->rva001E11F8(a, b);
		esi += 4;
	} while (--n != 0);
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		Rva002CAC6ENotify *obj = (Rva002CAC6ENotify *)cur->m_data;
		if (obj)
			obj->v24(a, b);
		cur = cur->m_next;
	}
}
