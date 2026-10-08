// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// ?rva0009C0EB@Rva0009C0EB@@QAEXPAPAURva0009C0EBRef@@PBVAsciiString@@@Z
// @0x0009C0EB 73B: acquire-and-release. Resolves the input string through
// the inlined AsciiString::str (null object yields the empty literal),
// fetches slot 32 of the +0xD4 provider with (text, 0), publishes the
// result through the out-pointer, then runs the pinned 0x0010E4F6 helper
// and drops the +4 refcount, deleting through slot 0 at zero. Honest
// address-derived names; boundary verified (mov at 0x9C0EB, ret 8 at end).
#include "ascii_string.h"

class Rva0009C0EBProvider
{
public:
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void *vslot032(const char *s, int v);
};

struct Rva0009C0EBRef
{
	virtual void vslot000();
	int m_4;
};

class Rva0009C0EB
{
public:
	void rva0009C0EB(Rva0009C0EBRef **out, const AsciiString *in);

private:
	char m_pad00[0xD4];
	Rva0009C0EBProvider *m_D4;
};

void __cdecl rva0010E4F6(void *p, bool v);

// ?rva0009C0EB@Rva0009C0EB@@QAEXPAPAURva0009C0EBRef@@PBVAsciiString@@@Z
void Rva0009C0EB::rva0009C0EB(Rva0009C0EBRef **out, const AsciiString *in)
{
	*out = (Rva0009C0EBRef *)m_D4->vslot032(in->str(), 0);
	if (*out)
	{
		rva0010E4F6(*out, 0);
		Rva0009C0EBRef *t = *out;
		if (--t->m_4 == 0)
			t->vslot000();
	}
}
