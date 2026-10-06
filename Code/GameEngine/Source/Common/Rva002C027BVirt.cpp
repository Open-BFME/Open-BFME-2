// cl: /MD
// ?rva002C027B@Rva002C027B@@QAEPAXXZ @0x002C027B 23B: null-checked virtual slot3 forward
// Evidence: gap between GlobalFloatGetters 0x002BFBF0 and DispDwordFieldGetters 0x002C0292; callers 0x002C235A 0x002C248E 0x003149C2; this+0x1A0 ptr plus vtable slot3 jmp; no callees rowed
class Inner
{
public:
	virtual void *s0();
	virtual void *s1();
	virtual void *s2();
	virtual void *s3();
};
class Rva002C027B
{
public:
	void *rva002C027B();
private:
	unsigned char m_pad[0x1A0];
	Inner *m_ptr;
};
void *Rva002C027B::rva002C027B()
{
	if (m_ptr)
		return m_ptr->s3();
	return 0;
}
