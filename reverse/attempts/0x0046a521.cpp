// ?rva0046A521@HordeContain@@QAEHPAURva0046A521Arg@@PAH@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /Oy- /MD
//
// ?rva0046A521@HordeContain@@QAEHPAURva0046A521Arg@@PAH@Z @0x0046A521 144B
// HordeContain method (this is HordeContain: caller 0x00473197 passes its own
// HordeContain this via esi; prev row rva00473125 says that caller passes
// HordeContain this). Searches pointer array at +0x270/+0x274 for entry whose
// key equals arg+4 Object; flag at key+0x115 bit 0x20 returns first entry.
// Evidence: begin==end returns -1; caller compares return to -1 and passes it
// as idx to HordeContain::rva00473125 plus out local to bfmeGo1037F.
//

class Object
{
public:
	unsigned char m_pad[0x115];
	unsigned char m_115;
};

struct Rva0046A521Arg
{
	void *m00;
	Object *m04;
};

struct Rva0046A521Entry
{
	Object *m00;
	int m04;
};

class HordeContain
{
public:
	int rva0046A521(Rva0046A521Arg *a, int *out);

private:
	unsigned char m_pad[0x270];
	Rva0046A521Entry **m_270;
	Rva0046A521Entry **m_274;
};

// ?rva0046A521@HordeContain@@QAEHPAURva0046A521Arg@@PAH@Z present-unmatched
int HordeContain::rva0046A521(Rva0046A521Arg *a, int *out)
{
	Object *key = a->m04;
	Rva0046A521Entry **begin = m_270;
	Rva0046A521Entry **end = m_274;
	if (begin == end)
		return -1;
	if ((key->m_115 & 0x20) != 0) {
		*out = (int)(*begin)->m00;
		return (*m_270)->m04;
	}
	int total = (char *)end - (char *)begin;
	total >>= 2;
	{
		Rva0046A521Entry **p = begin;
		unsigned int i = 0;
		while (i < (unsigned int)total) {
			if ((*p)->m00 == key) {
				int off = (int)(i << 2);
				Rva0046A521Entry *e1 = *(Rva0046A521Entry **)((char *)begin + off);
				*out = (int)e1->m00;
				Rva0046A521Entry *e2 = m_270[i];
				return e2->m04;
			}
			++i;
			++p;
		}
	}
	*out = (int)(*begin)->m00;
	return (*m_270)->m04;
}
