// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva00583B54FillN@@YAPAVRva002337F0@@PAV1@IABURva002337F0Blk@@@Z @0x00583B54 27B
// Dispatcher creating Tag at [ebp-1] and tail-calling FillN 0x00583A84.
// Evidence: push ebp mov ebp esp push ecx lea eax [ebp-1] push eax push [ebp+0x10] push [ebp+0xc]
// push [ebp+8] call 0x00583A84 add esp 0x10 leave ret; same shape as Rva0014F90DFillN 27B;
// caller 0x00584493 with 4 pushes.

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

struct Tag
{
	char x;
};

Rva002337F0 *__cdecl Rva00583A84FillN(Rva002337F0 *result, unsigned int count, const Rva002337F0Blk &value, const Tag &tag);

Rva002337F0 *__cdecl Rva00583B54FillN(Rva002337F0 *first, unsigned int count, const Rva002337F0Blk &value)
{
	Tag tag;
	return Rva00583A84FillN(first, count, value, tag);
}
