// cl: -Oy- -GR- -EHsc-
// ?Run@Rva005B7DC3Box@@QAEXXZ @0x005B7DC3 54B: allocate-transform-consume.
// Raw-allocates 0x28 bytes through the pinned cdecl callee (true callee is
// operator new at 0x2FDA0), transforms non-null results through the pinned
// 0-arg method, stamps the block's first word with 4, and runs the +0x0C
// sub-object's pinned consumer on the block pointer. The null path leaves
// a null block (the store is unconditional). Targets from retail REL32.
struct Rva005B7DC3Block
{
	Rva005B7DC3Block *Xform();
};

struct Rva005B7DC3Sub
{
	void Consume(void **pp);
};

struct Rva005B7DC3Box
{
	char pad[0xc];
	Rva005B7DC3Sub m_0C;

	void Run();
};

void *Rva005B7DC3Alloc(int size);

void Rva005B7DC3Box::Run()
{
	Rva005B7DC3Block *p = (Rva005B7DC3Block *)Rva005B7DC3Alloc(0x28);
	p = (p != 0) ? p->Xform() : 0;
	void *out = p;
	*(int *)p = 4;
	m_0C.Consume(&out);
}
