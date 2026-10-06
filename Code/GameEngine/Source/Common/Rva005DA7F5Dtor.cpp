// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva005DA7F5@@UAE@XZ @0x005DA7F5 60B
// Opaque dtor called by the rowed ??_G 0x005DA7D9 (vtable 0x00C76510#1).
// Target facts: stores its vtable 0x00C76510 { 0x005DA67F, ??_G 0x005DA7D9,
// 0x005DA854 }, frees the malloc'd buffer at +0x08 through the CRT free
// (0x00030830) when non-null, then the inline base dtor resets to the base
// vtable 0x00C70B80 { __purecall, ??_G (Rva005DAA36), slot 2 }. Retail keeps
// EH state 0 (base subobject) around the extern "C" free, which cl only does
// under /EHs (TU-scoped flag). Identity unproven; address-derived names.

extern "C" void __cdecl free(void *);

class Rva005DAA36
{
public:
	virtual void slot0() = 0;
	virtual ~Rva005DAA36() {}
	virtual void slot2();
};

class Rva005DA7F5 : public Rva005DAA36
{
public:
	virtual void slot0();
	virtual ~Rva005DA7F5();
	virtual void slot2();

private:
	int m_04;
	void *m_buffer; // +0x08
};

Rva005DA7F5::~Rva005DA7F5()
{
	if (m_buffer)
		free(m_buffer);
}
