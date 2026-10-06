// cl: /DNDEBUG /MD
// ?rva000B3C61@Rva000B3C61@@QAEXH@Z @0x000B3C61 110B
// Evidence: neighbours 0x000B3A68 (same +0x110 class) and 0x000B3E96;
// array at +0x110 stride 0x1c (elem 28B: ptr/floats/int/bytes);
// release via dec [ecx+4] plus slot-0 virtual then clear; three floats
// zeroed via xorps-movss with middle folded to (index+10)*28.
class RefCounted
{
public:
	virtual void rva000B3C61_virt0();
	int m_ref;
};

struct Rva000B3C61Elem
{
	RefCounted *m_ptr;
	float m_f04;
	float m_f08;
	float m_f0C;
	int m_10;
	int m_14;
	unsigned char m_18;
	unsigned char m_19;
	char m_pad1A[2];
};

class Rva000B3C61
{
public:
	void rva000B3C61(int index);
	void rva000B3BCF(int index, RefCounted *newPtr, unsigned char b19, int i10, float f0C, float f04, float fMid, unsigned char b18, int i14);
	void rva000B3CCF(int dest, int src);
private:
	char m_pad[0x110];
	Rva000B3C61Elem m_items[32];
};

void Rva000B3C61::rva000B3C61(int index)
{
	if (m_items[index].m_ptr)
	{
		RefCounted *p = m_items[index].m_ptr;
		if (--p->m_ref == 0)
			p->rva000B3C61_virt0();
		m_items[index].m_ptr = 0;
	}
	m_items[index].m_10 = 0;
	*(float *)((char *)this + (index + 10) * 28) = 0.0f;
	m_items[index].m_19 = 0;
	m_items[index].m_f0C = 0.0f;
	m_items[index].m_f04 = 0.0f;
	m_items[index].m_18 = 0;
	m_items[index].m_14 = 1;
}

// ?rva000B3BCF@Rva000B3C61@@QAEXHPAURefCounted@@EHM etc @0x000B3BCF 146B. Unlock lane setter
// counterpart of rva000B3C61 clearer: same 0x1c array, release via dec/call/and,
// newPtr store plus inc, then fields from params, middle via (index+10)*28.
// Evidence: callers 0x000B3D27 etc, neighbours Rva000B3A68/Rva000B3C61, SSE floats.
void Rva000B3C61::rva000B3BCF(int index, RefCounted *newPtr, unsigned char b19, int i10, float f0C, float f04, float fMid, unsigned char b18, int i14)
{
	if (m_items[index].m_ptr) {
		RefCounted *p = m_items[index].m_ptr;
		if (--p->m_ref == 0)
			p->rva000B3C61_virt0();
		m_items[index].m_ptr = 0;
	}
	if (!newPtr)
		return;
	m_items[index].m_ptr = newPtr;
	++newPtr->m_ref;
	m_items[index].m_10 = i10;
	m_items[index].m_18 = b18;
	m_items[index].m_f0C = f0C;
	m_items[index].m_14 = i14;
	m_items[index].m_f04 = f04;
	*(float *)((char *)this + (index + 10) * 28) = fMid;
	m_items[index].m_19 = b19;
}

// ?rva000B3CCF@Rva000B3C61@@QAEXHH@Z @0x000B3CCF 106B. Chain lane: move item
// from src slot to dest via setter then clear src. Evidence: calls 0x000B3BCF
// plus 0x000B3C61, same 0x1c array and middle.
void Rva000B3C61::rva000B3CCF(int dest, int src)
{
	rva000B3BCF(dest, m_items[src].m_ptr, m_items[src].m_19, m_items[src].m_10, m_items[src].m_f0C, m_items[src].m_f04, *(float *)((char *)this + (src + 10) * 28), m_items[src].m_18, m_items[src].m_14);
	rva000B3C61(src);
}
