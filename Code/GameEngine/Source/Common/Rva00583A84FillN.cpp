// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva00583A84FillN@@YAPAVRva002337F0@@PAV1@IABURva002337F0Blk@@ABUTag@@@Z @0x00583A84 37B
// FillN helper looping count times calling rowed Init 0x00583A72 then add 0x1c dec jne returning end.
// Evidence: push esi mov esi [esp+8] push edi mov edi [esp+0x10] test jbe push [esp+0x14] push esi call 0x00583A72;
// same shape as Rva0015344BFillN 37B; callers 0x00583B65 0x0058438B with 4 pushes and add esp 0x10.

struct Rva002337F0Blk
{
	int a;
	int b;
	int c;
	int d;
	char e;
	int f;
	int g;
};

class Rva002337F0
{
	Rva002337F0Blk m;

public:
	Rva002337F0 &set(const Rva002337F0Blk *p);
};

void __cdecl Rva00583A72Set(Rva002337F0 *a, const Rva002337F0Blk *b);

struct Tag
{
	char x;
};

Rva002337F0 *__cdecl Rva00583A84FillN(Rva002337F0 *result, unsigned int count, const Rva002337F0Blk &value, const Tag &tag)
{
	Rva002337F0 *cur = result;
	for (; count > 0; --count)
	{
		Rva00583A72Set(cur, &value);
		++cur;
	}
	return cur;
}
