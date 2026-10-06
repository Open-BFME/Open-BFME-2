// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva00583B11Copy@@YAPAVRva002337F0@@PAV1@00ABUTag@@@Z @0x00583B11 38B
// Copy helper looping first to last calling rowed Init 0x00583A72 then add 0x1c returning end.
// Evidence: push esi mov esi [esp+0x10] push edi mov edi [esp+0xc] jmp cmp edi [esp+0x10] jne
// push edi push esi call 0x00583A72; same shape as Rva00153425Copy 38B but stride 0x1c;
// callers 0x0058435E 0x005843A9 0x00584460 0x005844AC with 4 pushes.

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

Rva002337F0 *__cdecl Rva00583B11Copy(Rva002337F0 *first, Rva002337F0 *last, Rva002337F0 *result, const Tag &tag)
{
	Rva002337F0 *cur_result = result;
	Rva002337F0 *cur_first = first;
	while (cur_first != last)
	{
		Rva00583A72Set(cur_result, (const Rva002337F0Blk *)cur_first);
		++cur_first;
		++cur_result;
	}
	return cur_result;
}
