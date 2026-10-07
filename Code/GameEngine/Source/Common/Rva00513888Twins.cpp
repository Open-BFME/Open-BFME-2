// cl: /O1 /DNDEBUG /MD /EHsc
//
// Twins 0x00513888 (48B) and 0x005138B8 (48B): forward three ints to
// different callees (rowed 0x5748AD vs pinned 0x51274F), then if the
// +0x410 subobject holds a non-null pointer and the callee returned zero,
// tail-jump the virtual at slot 5 (0x14) vs slot 6 (0x18) with the same
// three args. Identities unproven.

class Rva005748AD
{
public:
	int rva005748AD(int a, int b, int c);
};

class Rva0051274F
{
public:
	int rva0051274F(int a, int b, int c);
};

class Rva00513888Slot
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05(int a, int b, int c);
};

class Rva005138B8Slot
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06(int a, int b, int c);
};

class Rva00513888Owner
{
public:
	void rva00513888(int a, int b, int c);
	void rva005138B8(int a, int b, int c);

private:
	char m_pad[0x410];		// +0x00..0x40F
	Rva00513888Slot *m_410;		// +0x410 checked pointer
};

void Rva00513888Owner::rva00513888(int a, int b, int c)
{
	int r = ((Rva005748AD *)this)->rva005748AD(a, b, c);
	if (!m_410)
		return;
	if (r)
		return;
	m_410->v05(a, b, c);
}

void Rva00513888Owner::rva005138B8(int a, int b, int c)
{
	int r = ((Rva0051274F *)this)->rva0051274F(a, b, c);
	if (!m_410)
		return;
	if (r)
		return;
	((Rva005138B8Slot *)m_410)->v06(a, b, c);
}
