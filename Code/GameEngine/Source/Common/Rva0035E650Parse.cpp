// cl: /MD /EHsc
// ?Rva0035E650Parse@@YAXPAVINI@@PAVRva0035E650Holder@@@Z @ 0x0035E650 81B: factory news 0x28,
// calls ctor ??0Rva0035E60B at 0x0035E60B, parses empty table 0x00C6BB18 via rowed
// INI::initFromINI 0x0002DE78, stores via holder+0x10 setter pinned at 0x005F69CE.
// Gap between ??_GRva0035E378 0x0035E634 and ?init@ButtonFlashTransition 0x0035E97E in
// Code/GameEngine/Source/Common/FamilyTailDtors1DBAC3.cpp (// cl: /O1 /MD).
// Same 81B shape as 0x0035E327/0x0035F4E7; vtable 0x008165F0 via ctor; no callers.
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

class Rva0035E60B : public Rva001DBAA4
{
public:
	virtual ~Rva0035E60B();
	Rva0035E60B();
	char m_pad10[0x10];
	int m_20;
	int m_24;
};

typedef char Rva0035E60BSizeMatchesRetail[(sizeof(Rva0035E60B) == 0x28) ? 1 : -1];

class Rva0035E650Holder
{
public:
	void set(Rva0035E60B *obj);
};

void __cdecl Rva0035E650Parse(INI *ini, Rva0035E650Holder *holder)
{
	Rva0035E60B *obj = new Rva0035E60B;
	ini->initFromINI(obj, reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable));
	holder->set(obj);
}
