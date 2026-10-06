// cl: /MD
// ?rva004C0E8B@Rva004C0E8B@@QAEPAXPAX@Z 0x004C0E8B 67B: Ask-gated memcpy-out like BfmeThing Go family.
// Evidence: chain from 0x004C0D4F row; prev BfmeConv565 head 0xF0; memcpy thunk 0x006291A8; slot 0x38.
extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

class Rva004C0D4F
{
public:
	bool rva004C0D4F();
};

class RvaInner004C0E8B
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void *GetPtr(int *tmp);
};

struct RvaSub004C0E8B
{
	char m_pad[0x10];
	RvaInner004C0E8B m_inner;
};

class Rva004C0E8B
{
public:
	void *rva004C0E8B(void *dst);
	char m_pad[0xF0];
	RvaSub004C0E8B *m_sub;
	char m_gap[4];
	int m_fallback;
};

void *Rva004C0E8B::rva004C0E8B(void *dst)
{
	int tmp;
	void *src;
	if (((Rva004C0D4F *)((char *)this - 0x10))->rva004C0D4F())
		src = m_sub->m_inner.GetPtr(&tmp);
	else
		src = (void *)&m_fallback;
	memcpy(dst, src, 4);
	return dst;
}
