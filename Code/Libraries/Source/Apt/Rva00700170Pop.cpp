// cl: /O2 /DNDEBUG /MD /EHsc
// Native [0x700170,0x7002B9),327B, thiscall with two stack arguments (ret 8): asserts
// the stack is non-empty, takes the top value, converts a string value through
// rva006FFD80, pushes the undefined value, then walks the native hash chain and
// copies each unseen string into a new AptString pushed on this stack.
// Callees match the ledger's exact names; only rva006FFD80 is address-derived.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern class BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AsciiString;
class EAStringC
{
public:
	bool rva006D3560(const EAStringC *other) const;
	EAStringC &operator=(const EAStringC &other);
};
EAStringC *Rva0070B4F0GetString(int which);
class AptString
{
public:
	static AptString *Create(void);
};
class BfmeAptValue006DCD20;
class AptNativeHash
{
public:
	struct Entry
	{
		void *a;
		void *b;
	};
	char pad00[8];
	BfmeAptValue006DCD20 *m_8;
	AsciiString *rva0070AA40(void);
	Entry *rva0070AAA0(Entry *e);
};
class BfmeAptValue006DCD20
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual AptNativeHash *v3(void);
	int isString(void) const;
	BfmeAptValue006DCD20 *checkedString(void);
};
class AptBasePtrStack
{
public:
	void rva00700170(void *a1, void *a2);
	void Push(BfmeAptValue006DCD20 *v);
	void rva006FE7B0(BfmeAptValue006DCD20 *v);
	BfmeAptValue006DCD20 *rva006FFD80(void *a, void *b, void *c, int d, int e, int f);
private:
	int m_0;
	char pad04[4];
	BfmeAptValue006DCD20 **m_8;
};
void AptBasePtrStack::rva00700170(void *a1, void *a2)
{
	if (!(m_0 > 0)) {
		g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x10a);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	BfmeAptValue006DCD20 *v = m_8[m_0 - 1];
	if ((char)v->isString() != 0) {
		BfmeAptValue006DCD20 *s = v->checkedString();
		v = rva006FFD80(a1, a2, (char *)s + 8, 1, 1, 0);
	}
	if (m_0 <= 0) {
		g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0xbf);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	} else {
		m_0 = m_0 - 1;
	}
	rva006FE7B0(g_aptUndefinedAtE18078);
	AptNativeHash *h = v->v3();
	while (h != 0) {
		EAStringC *e = (EAStringC *)h->rva0070AA40();
		while (e != 0) {
			if (!e->rva006D3560(Rva0070B4F0GetString(0)) && !e->rva006D3560(Rva0070B4F0GetString(0x78))) {
				BfmeAptValue006DCD20 *ns = (BfmeAptValue006DCD20 *)AptString::Create();
				*(EAStringC *)((char *)ns + 8) = *e;
				Push(ns);
			}
			e = (EAStringC *)h->rva0070AAA0((AptNativeHash::Entry *)e);
		}
		BfmeAptValue006DCD20 *n8 = h->m_8;
		h = n8 != 0 ? n8->v3() : 0;
	}
	v->v1();
}
