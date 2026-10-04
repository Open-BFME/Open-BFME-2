// cl: /O1 /MD /EHs-c-
// ?Rva00426D14Parse@@YAXPAVINI@@@Z @0x00426D14 194B evidence: calls rowed ctor 0x426C4D plus initFromINI wrapper 0x42666E with new 0x10 plus holder g_00E031E8 at +0x10 plus debug theDebug slots 0x60 0x6c 0x38 0x4c plus literal plus INIException filler 0x2F681 plus throw 0x629094
class INI
{
public:
	char _00[8];
	int m_08;
};

class Rva00426C4D
{
public:
	Rva00426C4D();
	virtual void *v0(int x);
private:
	char _pad[12];
};

class Rva0042666E
{
public:
	void rva0042666E(class INI *ini);
};

struct Holder00426D14
{
	char _00[0x10];
	Rva00426C4D *m_10;
};

// g_00E031E8 is defined as Rva0039B95FHolder* in Rva0039B95FCount.cpp (same
// VA 0x00E031E8, same +0x10 holder slot); declare that exact name here and
// cast at use so the link resolves instead of adding a second global name.
struct Rva0039B95FHolder;
extern Rva0039B95FHolder *g_00E031E8;

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *p);

void __cdecl _bfme_debugRecordCallsite(int kind);

class Debug
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
	virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
	virtual void f24();
	virtual void f25(); virtual void f26();
	virtual void *f27(int a, int b, int c);
};

extern Debug *theDebug;

class LogA
{
public:
	virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3();
	virtual void g4(); virtual void g5(); virtual void g6(); virtual void g7();
	virtual void g8(); virtual void g9(); virtual void g10(); virtual void g11();
	virtual void g12(); virtual void g13();
	virtual void *g14(const char *s);
};

class LogB
{
public:
	virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3();
	virtual void h4(); virtual void h5(); virtual void h6(); virtual void h7();
	virtual void h8(); virtual void h9(); virtual void h10(); virtual void h11();
	virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15();
	virtual void h16(); virtual void h17(); virtual void h18();
	virtual void h19(int x);
};

struct INIExceptionBuf
{
	char *mMsg;
	int mCode;
};

extern "C" void rva002f681_fill(void *e, int argCount, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct ThrowAnchor00426D14 { int a; int b; int c; int d; };
static const ThrowAnchor00426D14 throwAnchor00426D14 = { 0, 0, 0, 0 };

void __cdecl Rva00426D14Parse(INI *ini)
{
	if (ini->m_08 == 2)
	{
		if ((Holder00426D14 *)g_00E031E8 == 0)
			return;
		Rva00426C4D *p = new Rva00426C4D;
		((Rva0042666E *)p)->rva0042666E(ini);
		if (((Holder00426D14 *)g_00E031E8)->m_10 == 0)
		{
			((Holder00426D14 *)g_00E031E8)->m_10 = p;
			return;
		}
		void *q = p ? p->v0(0) : (void *)0;
		::operator delete(q);
		return;
	}
	if (ini->m_08 == 5)
		return;
	_bfme_debugRecordCallsite(1);
	theDebug->f24();
	LogA *a = (LogA *)theDebug->f27(0, 0, 0);
	LogB *b = (LogB *)a->g14("A MissionObjectiveList may only appear in a map.ini file.");
	b->h19(1);
	INIExceptionBuf e;
	rva002f681_fill(&e, 9, (const char *)0);
	_CxxThrowException(&e, (const _s__ThrowInfo *)&throwAnchor00426D14); __assume(0);
}
