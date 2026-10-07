// ?rva0020EF3E@Rva0020EF3EOuter@@QAEEPAX@Z
// partial score=0.94 date=2026-10-07
// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020EF3E@Rva0020EF3EOuter@@QAEEPAX@Z @0x0020EF3E 98B
// Predicate search over inner vector at *(this+8)+0x2C/+0x30: skips elements
// with +0x13C == -1, runs pinned 0x003F083A(void*) on each, checks result
// +0x20 != 0 then runs pinned stdcall 0x003F1CA2(result,0) and returns 1,
// else 0. Reload-each-iteration count idiom like proven EEF4 sibling.
// Callers: jmp tail from 0x002B25BF (this+0xB0). Unsigned char return gives
// retail xor al,al / mov al,1.
class CreateAHeroData
{
public:
	char m_pad[0x20];
	int m_20;
};
class Rva003F1093
{
public:
	CreateAHeroData *rva003F083A(void *v);
};
void __stdcall rva003F1CA2(CreateAHeroData *a, int b);
struct Rva0020EF3EElem
{
	char m_pad[0x13C];
	int m_13C;
};
struct Rva0020EF3EInner
{
	char m_pad[0x2C];
	Rva0020EF3EElem **m_begin;
	Rva0020EF3EElem **m_end;
};
class Rva0020EF3EOuter
{
public:
	unsigned char rva0020EF3E(void *v);
private:
	char m_pad[8];
	Rva0020EF3EInner *m_inner;
};
unsigned char Rva0020EF3EOuter::rva0020EF3E(void *v)
{
	Rva0020EF3EInner *inner = m_inner;
	if (inner != 0)
	{
		for (unsigned i = 0; i < (unsigned)(((char *)inner->m_end - (char *)inner->m_begin) >> 2); ++i)
		{
			Rva0020EF3EElem *e = inner->m_begin[i];
			if (e->m_13C == -1)
				continue;
			CreateAHeroData *r = ((Rva003F1093 *)e)->rva003F083A(v);
			if (r == 0)
				continue;
			if (r->m_20 != 0)
			{
				rva003F1CA2(r, 0);
				return 1;
			}
		}
	}
	return 0;
}
