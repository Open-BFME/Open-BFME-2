// cl: /MD /EHsc /DNDEBUG
// ?rva000A97C9@@YAXPAVRva000A97C9Holder@@@Z @0x000A97C9 35B: explicit
// destroy-and-clear. Runs the subobject's slot0 probe (or null) through the
// rowed operator delete, then clears the holder slot. Honest
// address-derived names; boundary verified (frameless at 0xA97C9, ret at end).
void operator delete(void *p);
class Rva000A97C9Sub {
public:
	virtual void *vslot0(int v);
};
class Rva000A97C9Holder {
public:
	char m_pad[4];
	Rva000A97C9Sub *m_4;
};
void rva000A97C9(Rva000A97C9Holder *h)
{
	Rva000A97C9Sub *p = h->m_4;
	::operator delete(p ? p->vslot0(0) : 0);
	h->m_4 = 0;
}
