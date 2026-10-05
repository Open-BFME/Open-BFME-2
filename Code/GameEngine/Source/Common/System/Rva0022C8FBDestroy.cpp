// cl: /O1 /DNDEBUG /MD /GX-
// ?Rva0022C8FBDestroy@@YGXPAURva0022C8FBElem@@@Z retail 0x0022C8FB 28B
// Destroys member at +4 via pin 0x0022630F then frees through game free
// 0x00030830 if non-null. Caller 0x0022CC88 in 0x0022CC67. Evidence:
// rowed free plus pin-only member dtor plus ret 4 stdcall shape.
extern "C" void free(void *block);

class Rva00229487
{
public:
	~Rva00229487();
};

struct Rva0022C8FBElem
{
	char _m00[4];
	Rva00229487 m04;
};

void __stdcall Rva0022C8FBDestroy(Rva0022C8FBElem *p)
{
	p->m04.~Rva00229487();
	if (p)
		free(p);
}
