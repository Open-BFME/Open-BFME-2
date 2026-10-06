// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva004EAC8C@Rva004EAC8C@@QAEXM@Z, retail 0x004EAC8C, 39 bytes.
// Sets float at +4 on single ptr +0x4 and on every entry in [begin+0x8, end+0xC).
// Evidence: movss float arg, +4 stores, 4-byte stride loop, caller at 0x004EAF3D.
struct Rva004EAC8CItem
{
	unsigned char pad[4];
	float f;
};

class Rva004EAC8C
{
public:
	void rva004EAC8C(float v);
private:
	void *pad0;
	Rva004EAC8CItem *single;
	Rva004EAC8CItem **begin;
	Rva004EAC8CItem **end;
};

void Rva004EAC8C::rva004EAC8C(float v)
{
	single->f = v;
	Rva004EAC8CItem **e = end;
	Rva004EAC8CItem **p = begin;
	while (p != e)
	{
		(*p)->f = v;
		++p;
	}
}
