// cl: /DNDEBUG /MD
//
// ?Rva006CD6F0Get@@YAXPAPAX0@Z, retail 0x006CD6F0, 171B.
// Apt bInitialized-guarded animation-inst data getter with two void** outs.
// Asserts via rowed g_bfmeAptAssert 0xA17734 plus int3 on break flag, aptPtr
// 0xA176D0 null check, value at [[apt+0x30]]+0x54 checked get()==0x12 via
// rowed 0x006DBB30 plus !isUndefined via rowed 0x006DC010, then rowed
// rva006CD650 0x006CD650 +0x4c (+0xC table +0x1C/+0x20 outs); else zero outs.
// Callers 0x000A92B0/0x0040FB9C prove __cdecl two-out shape.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *condition, const char *file, int line);
extern int g_bfmeAptInitAtE17700;
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;

class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
};

class Rva006CD650
{
public:
	void *rva006CD650();
};

struct AptInner54
{
	unsigned char m_pad[0x54];
	Rva006CD650 *m_54;
};

struct AptMid
{
	AptInner54 *m_0;
};

class Rva006E34D0
{
public:
	unsigned char m_pad[0x30];
	AptMid *m_30;
};

struct AnimTable
{
	unsigned char m_pad[0x1c];
	void *m_1c;
	void *m_20;
};

struct AnimData
{
	unsigned char m_pad[0xc];
	AnimTable *m_0c;
};

void __cdecl Rva006CD6F0Get(void **out1, void **out2)
{
	if (!g_bfmeAptInitAtE17700) {
		g_bfmeAptAssertAtE17734("bInitialized", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp", 0x2FC);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}
	Rva006E34D0 *apt = g_bfmeAptPtrAtE176D0;
	if (!apt)
		return;
	Rva006CD650 *val = apt->m_30->m_0->m_54;
	if (val) {
		if (((const Rva006DBB30SarDwordField *)val)->get() == 0x12) {
			if (!((const BfmeAptValue006DCD20 *)val)->isUndefined()) {
				AnimData *anim = (AnimData *)g_bfmeAptPtrAtE176D0->m_30->m_0->m_54->rva006CD650();
				if (out1)
					*out1 = anim->m_0c->m_1c;
				if (out2)
					*out2 = anim->m_0c->m_20;
				return;
			}
		}
	}
	if (out1)
		*out1 = 0;
	if (out2)
		*out2 = 0;
}
