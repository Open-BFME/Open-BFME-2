// ?Rva00210AB8Parse@@YAXPAVINI@@PAVRva0020F77C@@@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /EHs /MD
// ?Rva00210AB8Parse@@YAXPAVINI@@PAVRva0020F77C@@@Z @ 0x00210AB8 (128B)
// Factory via table slot 0x007E41E4 near "ConcurrentRegionBonus": new
// Rva002105A6(++counter 0x00DFE1BC), INI::initFromINI with table 0x00BE4448,
// empty vector at +0x20 deletes, else push to list via 0x0020F77C.
struct FieldParse;
extern const FieldParse g_00BE4448[];
extern int g_00DFE1BC;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class ObjectCreationNugget;

class Rva0020F77C
{
public:
	void rva0020F77C(ObjectCreationNugget *x);
};

class __declspec(novtable) Rva002105A6
{
public:
	Rva002105A6(int id);
	virtual ~Rva002105A6();
private:
	int m_id;
	char m_pad04[0x1C];
	void *m_begin;
	void *m_end;
	char m_pad28[0x58 - 0x28];
};

void Rva00210AB8Parse(INI *ini, Rva0020F77C *list)
{
	Rva002105A6 *obj = new Rva002105A6(++g_00DFE1BC);
	ini->initFromINI(obj, g_00BE4448);
	if (*(void **)((char *)obj + 0x20) != *(void **)((char *)obj + 0x24)) {
		if (list)
			list->rva0020F77C((ObjectCreationNugget *)obj);
	} else if (obj) {
		obj->Rva002105A6::~Rva002105A6();
		::operator delete(obj);
	}
}
