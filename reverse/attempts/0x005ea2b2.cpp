// ?rva005EA2B2@Rva005EA33D@@QAEXHH@Z
// partial score=0.9718 date=2026-10-05
// ?rva005EA2B2@Rva005EA33D@@QAEXHH@Z
// partial score=0.99 date=2026-10-03
// cl: /O1 /G7 /DNDEBUG /MD /EHs-c- /arch:SSE
// ?rva005EA2B2@Rva005EA33D@@QAEXHH@Z @ 0x005EA2B2 139B
// Honest address name: __thiscall indexed elem plus two-range search for first a>b, then scaled callback.
// Target evidence: 139B retail, frameless SSE, divisor at edx+0x18,
// two 0xC vectors at edx+0x1C/+0x28 with 0x24 elems (floats +8/+0xC, int +0x14, ptr +0x20),
// callees rowed ?rva005FBB68@Rva005FBB68@@QAEXH@Z and ?rva005FBB70@Rva005FBB68@@QAEXM@Z,
// data kF7C at VA 0xBC292C. Same Data layout as 0x005EA33D in Rva005EA33DMethod.cpp.
extern "C" float kF7C;

class Rva005FBB68
{
public:
	void rva005FBB68(int v);
	void rva005FBB70(float v);
};

struct Rva005EA2B2Elem
{
	char m_pad00[8];
	float m_a;
	float m_b;
	char m_pad10[4];
	int m_val14;
	char m_pad18[8];
	void *m_ptr;
};

struct Rva005EA2B2Vec
{
	Rva005EA2B2Elem *m_begin;
	Rva005EA2B2Elem *m_end;
	Rva005EA2B2Elem *m_allocEnd;
};

struct Rva005EA2B2Data
{
	char m_pad00[0x18];
	float m_divisor;
	Rva005EA2B2Vec m_ranges[2];
};

class Rva005EA33D
{
public:
	void rva005EA2B2(int i1, int i2);
private:
	char m_pad00[4];
	Rva005EA2B2Data *m_data;
};

// ?rva005EA2B2@Rva005EA33D@@QAEXHH@Z present-unmatched
void Rva005EA33D::rva005EA2B2(int i1, int i2)
{
	int j = i2;
	Rva005EA2B2Elem *mbegin = *(Rva005EA2B2Elem **)(i1 * 12 + (unsigned int)&m_data->m_ranges[0]);
	Rva005EA2B2Elem *first = (Rva005EA2B2Elem *)((char *)mbegin + (unsigned int)j * 0x24);
	((Rva005FBB68 *)((char *)first->m_ptr + 8))->rva005FBB68(first->m_val14);
	Rva005EA2B2Data *d = m_data;
	Rva005EA2B2Vec *vec = &d->m_ranges[i1];
next:
	{
		int n = ((char *)vec->m_end - (char *)vec->m_begin) / 0x24;
		++j;
		if (j < (unsigned int)n)
			goto have;
		j = 0;
		if (i1 <= 0)
			return;
		--i1;
		--vec;
	}
have:
	{
		Rva005EA2B2Elem *cur = (Rva005EA2B2Elem *)((char *)vec->m_begin + j * 0x24);
		if (cur->m_a > cur->m_b) {
			float v = (cur->m_a - cur->m_b) / d->m_divisor * kF7C;
			((Rva005FBB68 *)((char *)cur->m_ptr + 8))->rva005FBB70(v);
			return;
		}
		goto next;
	}
}
