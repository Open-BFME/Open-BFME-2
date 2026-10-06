// cl: /DNDEBUG /MD /EHs-c-
// ?rva005EA33D@Rva005EA33D@@QAEXXZ @ 0x005EA33D 89B
// Honest address name: __thiscall scan of two 0x24-element ranges for first a>b, then scaled callback.
// Target evidence: 89B retail, frameless SSE (movss/comiss/divss/mulss), divisor at edx+0x18,
// two 0xC vectors at edx+0x1C/+0x28 with 0x24 elems (floats +8/+0xC, ptr +0x20),
// callee row ?rva005FBB70@Rva005FBB68@@QAEXM@Z, data kF7C at VA 0xBC292C, callers at 0x005EA7B7/0x005EA79D.
extern "C" float kF7C;

class Rva005FBB68
{
public:
	void rva005FBB68(int v);
	void rva005FBB70(float v);
};

struct Rva005EA33DElem
{
	char m_pad00[8];
	float m_a;
	float m_b;
	char m_pad10[4];
	int m_val14;
	char m_pad18[0x20 - 0x18];
	void *m_ptr;
};

struct Rva005EA33DVec
{
	Rva005EA33DElem *m_begin;
	Rva005EA33DElem *m_end;
	Rva005EA33DElem *m_allocEnd;
};

struct Rva005EA33DData
{
	char m_pad00[0x18];
	float m_divisor;
	Rva005EA33DVec m_ranges[2];
};

class Rva005EA33D
{
public:
	void rva005EA33D();
	void rva005EA2B2(int i1, int i2);
private:
	char m_pad00[4];
	Rva005EA33DData *m_data;
};

void Rva005EA33D::rva005EA33D()
{
	Rva005EA33DData *d = m_data;
	int left = 2;
	Rva005EA33DVec *range = d->m_ranges + 2;
	do {
		--left;
		--range;
		Rva005EA33DElem *cur = range->m_begin;
		Rva005EA33DElem *end = range->m_end;
		for (; cur != end; cur = (Rva005EA33DElem *)((char *)cur + 0x24)) {
			if (cur->m_a > cur->m_b) {
				float v = (cur->m_a - cur->m_b) / d->m_divisor * kF7C;
				((Rva005FBB68 *)((char *)cur->m_ptr + 8))->rva005FBB70(v);
				return;
			}
		}
	} while (left > 0);
}

void Rva005EA33D::rva005EA2B2(int i1, int i2)
{
	Rva005EA33DElem *mbegin = *(Rva005EA33DElem **)(i1 * 12 + (unsigned int)&m_data->m_ranges[0]);
	Rva005EA33DElem *first = (Rva005EA33DElem *)((char *)mbegin + (unsigned int)i2 * 0x24);
	((Rva005FBB68 *)((char *)first->m_ptr + 8))->rva005FBB68(first->m_val14);
	int j = i2;
	Rva005EA33DData *d = m_data;
	Rva005EA33DVec *vec = &d->m_ranges[i1];
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
		Rva005EA33DElem *cur = (Rva005EA33DElem *)((char *)vec->m_begin + j * 0x24);
		if (cur->m_a > cur->m_b) {
			float v = (cur->m_a - cur->m_b) / d->m_divisor * kF7C;
			((Rva005FBB68 *)((char *)cur->m_ptr + 8))->rva005FBB70(v);
			return;
		}
		goto next;
	}
}
