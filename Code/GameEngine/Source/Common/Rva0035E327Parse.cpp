// cl: /MD /EHsc
// ?Rva0035E327Parse@@YAXPAVINI@@PAVRva0035E327Holder@@@Z @ 0x0035E327 81B: factory news 0x34,
// calls ctor ??0Rva0035E2E6 at 0x0035E2E6, parses empty table 0x00C6BB18 via rowed
// INI::initFromINI 0x0002DE78, stores via holder+0x10 setter pinned at 0x005F69CE.
// Gap between ??_GRva0035E2CF 0x0035E30B and ??1Rva0035E378 0x0035E378 in
// Code/GameEngine/Source/Common/FamilyTailDtors1DBAC3.cpp (// cl: /O1 /MD).
// Same 81B shape as 0x0035E650/0x0035F4E7; vtable 0x008165D0 via ctor; no callers.
// Opaque address-derived names; base layout from Rva001DBAA4Ctor.cpp.
struct FieldParse;
extern const int g_emptyFieldParseTable[4];

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	int m_C;
};

class Rva0035E2E6 : public Rva001DBAA4
{
public:
	virtual ~Rva0035E2E6();
	Rva0035E2E6();
	char m_pad10[0x10];
	int m_20;
	char m_pad24[0x34 - 0x24];
};

typedef char Rva0035E2E6SizeMatchesRetail[(sizeof(Rva0035E2E6) == 0x34) ? 1 : -1];

class Rva0035E327Holder
{
public:
	void set(Rva0035E2E6 *obj);
};

void __cdecl Rva0035E327Parse(INI *ini, Rva0035E327Holder *holder)
{
	Rva0035E2E6 *obj = new Rva0035E2E6;
	ini->initFromINI(obj, reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable));
	holder->set(obj);
}
