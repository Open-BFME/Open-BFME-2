// cl: /MD /EHsc
// ?Rva0035F4E7Parse@@YAXPAVINI@@PAVRva0035F4E7Holder@@@Z @ 0x0035F4E7 81B: factory news 0x24,
// calls ctor ??0Rva0035F4A6 at 0x0035F4A6, parses empty table 0x00C6BB18 via rowed
// INI::initFromINI 0x0002DE78, stores via holder+0x10 setter pinned at 0x005F69CE.
// Gap between ??_GRva0035F42E 0x0035F4CB and ??1CountUpTransition 0x0035F694 in
// Code/GameEngine/Source/Common/FamilyTailDtors1DBAC3.cpp (// cl: /O1 /MD).
// Same 81B shape as 0x0035E327/0x0035E650; vtable 0x0081665C via ctor; no callers.
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

class Rva0035F4A6 : public Rva001DBAA4
{
public:
	virtual ~Rva0035F4A6();
	Rva0035F4A6();
	char m_pad10[0x10];
	int m_20;
};

typedef char Rva0035F4A6SizeMatchesRetail[(sizeof(Rva0035F4A6) == 0x24) ? 1 : -1];

class Rva0035F4E7Holder
{
public:
	void set(Rva0035F4A6 *obj);
};

void __cdecl Rva0035F4E7Parse(INI *ini, Rva0035F4E7Holder *holder)
{
	Rva0035F4A6 *obj = new Rva0035F4A6;
	ini->initFromINI(obj, reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable));
	holder->set(obj);
}
