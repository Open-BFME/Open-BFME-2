// cl: /DNDEBUG /MD /EHsc
// ?rva006DE400@Rva006DE400Native@@QAE_NPAXPAVEAStringC@@PAVAptValue@@@Z @0x006DE400 (114B).
// Native setter slot (vtable data at 0x008EB1F8 +8): converts the value's
// string form into a scoped EAStringC through the rowed AptValue::toString
// 0x006DD6C0 and hands name and value text to the extern-variable callback
// pointer at 0x00E17764 (the interpreter's SetMember extern branch calls the
// same callback), returning true. The first argument is unused and the
// receiver is not read.

class EAStringC
{
	void *m_pData;

public:
	EAStringC();
	~EAStringC();
	const char *rva00620090() const;
};

class AptValue
{
public:
	void toString(EAStringC &out) const;
};

extern void (__cdecl *g_bfmeAptSetExternAtE17764)(const char *, const char *);

class Rva006DE400Native
{
public:
	bool rva006DE400(void *unused, EAStringC *name, AptValue *value);
};

bool Rva006DE400Native::rva006DE400(void *, EAStringC *name, AptValue *value)
{
	EAStringC text;
	value->toString(text);
	g_bfmeAptSetExternAtE17764(name->rva00620090(), text.rva00620090());
	return true;
}
