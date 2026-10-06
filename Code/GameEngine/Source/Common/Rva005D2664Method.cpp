// cl: /MD
//
// ?rva005D2664@Rva005D2664@@QAEXH@Z @0x005D2664 55B: indexed clear with guarded Hide tail.
// Computes elem = this + (idx+1)*0x1C, clears +0x10/+0x0C via rowed
// 0x002BED91 clear, then if holder +0x04 non-null and its target flag via
// rowed 0x0057C22F get is set calls rowed 0x005C3E79 Hide tail.
// Evidence: retail inc/imul-0x1C/add, lea clear order, mov/test/je plus
// get/test plus second mov/call, chain from 0x005C3E79, callers 0x005D269B 0x005D27BE.
class Rva002BED91
{
public:
	void clear();
private:
	void *m_ptr;
};

class Rva0057C22FByteChaseField
{
public:
	unsigned char get() const;
};

class Rva005C3E79
{
public:
	void rva005C3E79();
};

struct Elem005D2664
{
	char m_pad00[4];
	Rva005C3E79 *m_holder04;
	char m_pad08[4];
	Rva002BED91 m_clear0C;
	Rva002BED91 m_clear10;
	char m_pad14[8];
};

class Rva005D2664
{
public:
	void rva005D2664(int idx);
	void rva005D269B();
private:
	char m_header00[0x1C];
};

void Rva005D2664::rva005D2664(int idx)
{
	Elem005D2664 *e = (Elem005D2664 *)((char *)this + (idx + 1) * 0x1C);
	e->m_clear10.clear();
	e->m_clear0C.clear();
	if (!e->m_holder04)
		return;
	if (!((Rva0057C22FByteChaseField *)e->m_holder04)->get())
		return;
	e->m_holder04->rva005C3E79();
}

// ?rva005D269B@Rva005D2664@@QAEXXZ @0x005D269B 23B: loop 6x over 0x005D2664.
// Calls sibling rowed 0x005D2664 with idx 0..5. Evidence: retail xor/push/call
// inc/cmp-6/jl plus chain from 0x005D2664 in this TU.
void Rva005D2664::rva005D269B()
{
	for (int i = 0; i < 6; ++i)
		rva005D2664(i);
}
