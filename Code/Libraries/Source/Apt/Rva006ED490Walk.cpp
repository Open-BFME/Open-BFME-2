// cl: /O2 /DNDEBUG /MD
// Native [0x6ED490,0x6ED56F),231B, cdecl (x, obj, flag): walks a chain of X
// nodes; each node asserts isCharacterInst() (AptCIH.h line 0xA5), scans its
// element table against obj, optionally scans a 16-byte table when flag is set,
// and otherwise moves to the next node at +0x48. Address-derived names: the class
// and callee identities are not proven.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006ED490X;
class Rva006ED490Obj;
// Rowed callees: EAStringC::rva006D3510 (0x006D3510), BfmeAptValue006DCD20::isCharacterInst
// (0x006E0200, int result tested as a byte) and ::rva006DCF60 (0x006DCF60).
class EAStringC
{
public:
	class StringDataC { public: unsigned short m_uRefCount; unsigned short m_uSize; unsigned short m_uMaxSize; unsigned short m_uHash; };
	EAStringC();
	EAStringC(const char *);
	EAStringC(const EAStringC &);
	static void FreeData(StringDataC *);
	EAStringC &clear();
	EAStringC &operator=(const EAStringC&);
	~EAStringC();
	int GetAt(int) const;
	bool IsEmpty() const;
	unsigned int rva006D3750() const;
	bool IsEqualTo(const EAStringC*) const;
	bool rva006D30D0(const EAStringC*) const;
	bool rva006D3510(const char*) const;
	EAStringC &MakeLower();
	EAStringC &Rva006D4F00Append(const EAStringC &other);
	const char *rva00620090() const;
	int rva006D54B0(int,int);
private:
	StringDataC *data; // +0x00
};
class AptCIH;
class AptValue
{
public:
	AptCIH *c_cih(bool bUndefinedOK);
	bool isCIH(bool bUndefinedOK) const;
	bool isUndefined() const;
	bool getIsDefined() const;
	float toFloat() const;
	int toInteger() const;
	void toString(EAStringC &) const;
	virtual void AddRef();
	virtual void Release();
};
class BfmeAptValue006DCD20 : public AptValue
{
public:
	BfmeAptValue006DCD20(int);
	BfmeAptValue006DCD20 *rva006DCF60(bool undefOK);
	BfmeAptValue006DCD20 *checkedString();
	bool isCIH(bool bUndefinedOK) const;
	bool isUndefined() const;
	int isCharacterInst() const;
	int isInteger() const;
	int isString() const;
	int rva006E02B0() const;
	int rva006E03A0() const;
	void *rva006E0F40() const;
	int toInteger() const;
	virtual ~BfmeAptValue006DCD20();
	unsigned int m_flags; // +0x04
};
class Rva006ED490Elem8
{
public:
	int m_a;
	int m_b;
};
class Rva006ED490T
{
public:
	char pad00[0x10];
	int *m_10;
	char pad14[0x0c];
	int m_20;
	char *m_24;
	int m_28;
	Rva006ED490Elem8 *m_2c;
};
class Rva006ED490Z
{
public:
	char pad00[4];
	char *m_04;
};
class Rva006ED490Y
{
public:
	char pad00[0x0c];
	Rva006ED490Z *m_0c;
};
class Rva006ED490X
{
public:
	char pad00[0x48];
	Rva006ED490X *m_48;
	Rva006ED490Y *m_4c;
};
int rva006ED490(Rva006ED490X *characterInst, Rva006ED490Obj *obj, char flag)
{
	Rva006ED490X *cur = characterInst;
	for (;;) {
		if (!(char)((BfmeAptValue006DCD20 *)cur)->isCharacterInst()) {
			g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xa5);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		Rva006ED490T *t = (Rva006ED490T *)(cur->m_4c->m_0c->m_04 + 8);
		int edi;
		for (edi = 0; edi < t->m_28; ++edi) {
			if (((EAStringC *)obj)->rva006D3510((const char *)t->m_2c[edi].m_a))
				return t->m_10[t->m_2c[edi].m_b];
		}
		if (flag != 0) {
			edi = 0;
			if (t->m_20 > 0) {
				int off = 0;
				do {
					if (((EAStringC *)obj)->rva006D3510(*(const char **)(t->m_24 + off + 4)))
						return t->m_10[*(int *)(t->m_24 + edi * 16 + 8)];
					++edi;
					off += 0x10;
				} while (edi < t->m_20);
			}
		}
		Rva006ED490X *next = ((Rva006ED490X *)((BfmeAptValue006DCD20 *)cur)->rva006DCF60(false))->m_48;
		if (next == 0)
			return 0;
		flag = 0;
		cur = next;
	}
}
