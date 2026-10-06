// cl: /MD /EHsc
// ?Rva0035EEA7Parse@@YAXPAVINI@@PAVRva0035EEA7Holder@@@Z @ 0x0035EEA7 81B: factory news 0x24,
// calls ctor ??0Rva0035EE66 at 0x0035EE66, parses empty table 0x00C6BB18 via rowed
// INI::initFromINI 0x0002DE78, stores via holder+0x10 setter pinned at 0x005F69CE.
// Gap between ??_GRva0035ED92 0x0035EE8B and ??1Rva0035F1D0 0x0035F1D0 in
// Code/GameEngine/Source/Common/FamilyTailDtors1DBAC3.cpp (// cl: /O1 /MD).
// Same 81B shape as 0x0035E327/0x0035E650/0x0035F4E7; vtable 0x0081661C via ctor; no callers.
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

class Rva0035EE66 : public Rva001DBAA4
{
public:
	virtual ~Rva0035EE66();
	Rva0035EE66();
	char m_pad10[0x10];
	int m_20;
};

typedef char Rva0035EE66SizeMatchesRetail[(sizeof(Rva0035EE66) == 0x24) ? 1 : -1];

class Rva0035EEA7Holder
{
public:
	void set(Rva0035EE66 *obj);
};

void __cdecl Rva0035EEA7Parse(INI *ini, Rva0035EEA7Holder *holder)
{
	Rva0035EE66 *obj = new Rva0035EE66;
	ini->initFromINI(obj, reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable));
	holder->set(obj);
}
