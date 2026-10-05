// cl: /Od
// Two more run wrappers built on the bfmeMakeOX length helper, siblings of the
// bfmeGoPF pair-of-ends wrappers in Rva00028B90Siblings.cpp. The body passes its
// first argument as the run start and `bfmeMakeOX(first)` as the run length, so
// the same thiscall callee as the range wrapper is reached with a computed end.
// Class names and method names are address-derived; the callees are already
// pinned (bfmeMakeOX at 0x00006F30, bfmeDoPF at 0x00027540, bfmeDoPG at
// 0x00027740).

int bfmeMakeOX(void *text);

class Rva00028B90Thing
{
public:
	int bfmeDoPF(char *at, int pos, int many);
	void rva00028bc0(void *at, void *what);
};

void Rva00028B90Thing::rva00028bc0(void *at, void *what)
{
	bfmeDoPF((char *)at, (int)what, bfmeMakeOX(at));
}

class BfmeThingPG
{
public:
	void bfmeDoPG(char *at, void *what, int many);
	void rva00028cc0(void *at, void *what);
};

void BfmeThingPG::rva00028cc0(void *at, void *what)
{
	bfmeDoPG((char *)at, what, bfmeMakeOX(at));
}
