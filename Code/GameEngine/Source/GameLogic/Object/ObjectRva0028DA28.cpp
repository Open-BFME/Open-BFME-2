// cl: /DNDEBUG /MD
// ?rva0028DA28@Object@@QAEXXZ @0x0028DA28 63B: __thiscall void clears +0x284 0x80 via memset then walks null-terminated ptr array at +0x244 calling virtual slot 0x28 and Rva004CE245 on non-zero returns. Evidence: rowed memset thunk ji_006291ae plus rowed Rva004CE245 0x004CE245 plus prev ObjectRva0028D9E5 plus +0x284 bits.
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

void Rva004CE245(void *p);

class ElemProvider
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void *slot10();
};

class Object
{
public:
	void rva0028DA28();
private:
	char m_pad00[0x244];
	void **m_arr244;
	char m_pad248[0x284 - 0x248];
	unsigned char m_clr284[0x80];
};

void Object::rva0028DA28()
{
	ji_006291ae(m_clr284, 0, 0x80);
	void **arr = m_arr244;
	while (*arr != 0)
	{
		void *e = *arr;
		ElemProvider *p = (ElemProvider *)((char *)e + 0xc);
		void *r = p->slot10();
		if (r != 0)
			Rva004CE245(r);
		++arr;
	}
}
