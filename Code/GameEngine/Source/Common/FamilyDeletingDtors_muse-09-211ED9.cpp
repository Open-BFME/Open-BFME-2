// cl: /MD
// ?rva00211ED9@Rva00211ED9@@QAEPAXI@Z, RVA 0x00211ED9, 28B. Chain lane:
// scalar-delete shape calling rowed 0x002115C5 then rowed operator delete
// 0x0002FD60 on flag bit0; returns this, ret 4. Rowed dtor keeps rva name
// so honest address name instead of ??_G. No callers.
struct Rva002115C5
{
	void rva002115C5();
};
void __cdecl operator delete(void *p);
struct Rva00211ED9
{
	void *rva00211ED9(unsigned int flags);
};

void *Rva00211ED9::rva00211ED9(unsigned int flags)
{
	((Rva002115C5 *)this)->rva002115C5();
	if (flags & 1)
		operator delete(this);
	return this;
}
