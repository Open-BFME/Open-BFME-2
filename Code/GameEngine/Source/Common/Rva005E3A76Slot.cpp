// cl: /O1 /MD
// ?rva005E3A76@Rva005E3A76@@QAEXXZ retail 0x005E3A76 44 bytes.
// Slot installer plus refcounted release: reads descriptor p from
// (this-0x14), offset q from p+4, stores retail const 0x00C77C50 at
// (base+q) with back-link (q-0x14) at (base+q-4), then releases the
// refcounted slot at (this-8) via dec/jne plus first-virtual tail-jmp.
// Address-derived names; const is retail-opaque (likely a vtable).
class Rva005E3A76Ref
{
public:
	virtual void release();
	int m_refs; // +4
};

class Rva005E3A76
{
public:
	void rva005E3A76();
};

void Rva005E3A76::rva005E3A76()
{
	char *base = (char *)this - 0x14;
	char *p = *(char **)base;
	int off = *(int *)(p + 4);
	char *self = (char *)this;
	*(int *)&((char *)off)[(int)self - 0x14] = 0x00C77C50;
	char *p2 = *(char **)base;
	int off2 = *(int *)(p2 + 4);
	*(int *)(base + off2 - 4) = off2 - 0x14;
	Rva005E3A76Ref *old = *(Rva005E3A76Ref **)((char *)this - 8);
	if (old != 0) {
		if (--old->m_refs == 0)
			old->release();
	}
}
