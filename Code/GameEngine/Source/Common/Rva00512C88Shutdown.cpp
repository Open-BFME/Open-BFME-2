// cl: /MD
//
// ?Rva00512C88Shutdown@@YAXXZ, retail 0x00512C88, 69 bytes.
// Global teardown: if 0x00A048CC set call slot3(0) then slot1(0) and delete
// the result, clear the global, then call slot94(0) on 0x009FEDF0.
// Evidence: callers 0x004D23BB 0x004D390F; unblocks 0x004D3906;
// rowed operator delete 0x0002FD60; virtual slots only.

class InGameUI;
extern InGameUI *TheInGameUI;
class Rva00512C88ObjA
{
public:
	virtual void v0(int);
	virtual void *v1(int);
	virtual void v2(int);
	virtual void v3(int);
};

class Rva00512C88ObjB
{
public:
	virtual void _p00(); virtual void _p01(); virtual void _p02(); virtual void _p03();
	virtual void _p04(); virtual void _p05(); virtual void _p06(); virtual void _p07();
	virtual void _p08(); virtual void _p09(); virtual void _p10(); virtual void _p11();
	virtual void _p12(); virtual void _p13(); virtual void _p14(); virtual void _p15();
	virtual void _p16(); virtual void _p17(); virtual void _p18(); virtual void _p19();
	virtual void _p20(); virtual void _p21(); virtual void _p22(); virtual void _p23();
	virtual void _p24(); virtual void _p25(); virtual void _p26(); virtual void _p27();
	virtual void _p28(); virtual void _p29(); virtual void _p30(); virtual void _p31();
	virtual void _p32(); virtual void _p33(); virtual void _p34(); virtual void _p35();
	virtual void _p36(); virtual void _p37(); virtual void _p38(); virtual void _p39();
	virtual void _p40(); virtual void _p41(); virtual void _p42(); virtual void _p43();
	virtual void _p44(); virtual void _p45(); virtual void _p46(); virtual void _p47();
	virtual void _p48(); virtual void _p49(); virtual void _p50(); virtual void _p51();
	virtual void _p52(); virtual void _p53(); virtual void _p54(); virtual void _p55();
	virtual void _p56(); virtual void _p57(); virtual void _p58(); virtual void _p59();
	virtual void _p60(); virtual void _p61(); virtual void _p62(); virtual void _p63();
	virtual void _p64(); virtual void _p65(); virtual void _p66(); virtual void _p67();
	virtual void _p68(); virtual void _p69(); virtual void _p70(); virtual void _p71();
	virtual void _p72(); virtual void _p73(); virtual void _p74(); virtual void _p75();
	virtual void _p76(); virtual void _p77(); virtual void _p78(); virtual void _p79();
	virtual void _p80(); virtual void _p81(); virtual void _p82(); virtual void _p83();
	virtual void _p84(); virtual void _p85(); virtual void _p86(); virtual void _p87();
	virtual void _p88(); virtual void _p89(); virtual void _p90(); virtual void _p91();
	virtual void _p92(); virtual void _p93();
	virtual void v94(int);
};

extern Rva00512C88ObjA *g_Va00A048CC;
// g_Va00A048CC: matched references place it at VA 0xe048cc (zero-filled .bss).
Rva00512C88ObjA * g_Va00A048CC;

void Rva00512C88Shutdown()
{
	if (g_Va00A048CC == 0)
		return;
	g_Va00A048CC->v3(0);
	void *p;
	if (g_Va00A048CC != 0)
		p = g_Va00A048CC->v1(0);
	else
		p = 0;
	operator delete(p);
	g_Va00A048CC = 0;
	(*(Rva00512C88ObjB **)&TheInGameUI)->v94(0);
}

// ?Rva00512CCDShutdown@@YAXXZ @0x00512CCD (18B):
// Guarded slot2(0) on 0x00A048CC; same globals and ObjA as rowed 0x00512C88.
// Evidence: caller 0x004D470E; unblocks 0x004D46FC.
void Rva00512CCDShutdown()
{
	if (g_Va00A048CC != 0)
		g_Va00A048CC->v2(0);
}
