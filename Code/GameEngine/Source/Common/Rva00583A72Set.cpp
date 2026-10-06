// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva00583A72Set@@YAXPAVRva002337F0@@PBURva002337F0Blk@@@Z @0x00583A72 18B
// Null-checked wrapper over Rva002337F0::set at 0x00583A1E (rowed).
// Callers 0x00583A97 0x00583B1F 0x00584373 fill/copy 0x1c-byte elements.
// Prev/next rows in stlport_vector_stringrecord_111acf_allocate_copy.cpp share these flags.

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

void __cdecl Rva00583A72Set(Rva002337F0 *a, const Rva002337F0Blk *b)
{
	if (a)
		a->set(b);
}
