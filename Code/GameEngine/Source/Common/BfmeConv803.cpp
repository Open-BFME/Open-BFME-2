// Two null-guarded field readers off bfmeGetEBN (trimmed from an eight-body
// donor; the other six are declared-only here).

class BfmeObjEBJ
{
public:
	void bfmeCallEBJ(void *b, const char *s);
};

class BfmeObjEBK
{
public:
	void bfmeOneEBK(void *x, int n);
	void bfmeTwoEBK(void *x, void *b);
};

// Provides the storage its two bodies reference; no other TU defines it.
void *g_bfmeXEBK;

class BfmeObjEBL
{
public:
	void bfmeCallEBL(void *a, void *b);
};

char bfmeCmpEBMa(void *a, void *b);
char bfmeCmpEBMb(void *a, void *b);

struct BfmeSubEBN
{
	unsigned char m_bfmeHead[0x20];
	char m_bfmeC;
	unsigned char m_bfmePad[3];
	void *m_bfmeP;
};

class BfmeObjEBN
{
public:
	BfmeSubEBN *bfmeGetEBN();
};

// ?bfmeGoEBNa@@YAPAXPAVBfmeObjEBN@@@Z
void *bfmeGoEBNa(BfmeObjEBN *o)
{
	if (!o)
		return 0;
	BfmeSubEBN *s = o->bfmeGetEBN();
	if (!s)
		return 0;
	return s->m_bfmeP;
}

// ?bfmeGoEBNb@@YADPAVBfmeObjEBN@@@Z
char bfmeGoEBNb(BfmeObjEBN *o)
{
	if (!o)
		return 0;
	BfmeSubEBN *s = o->bfmeGetEBN();
	if (!s)
		return 0;
	return s->m_bfmeC;
}

// ?bfmeGoEBKb@@YGXPAVBfmeObjEBK@@PAX@Z
void __stdcall bfmeGoEBKb(BfmeObjEBK *o, void *b)
{
	o->bfmeTwoEBK(g_bfmeXEBK, b);
}

// ?bfmeGoEBKa@@YGXPAVBfmeObjEBK@@@Z, retail 0x006694E0 (20B).
// Same-donor sister of EBKb above: one-arg stdcall forwarding
// (g_bfmeXEBK, 0) through the pinned bfmeOneEBK at 0x00655990.
void __stdcall bfmeGoEBKa(BfmeObjEBK *o)
{
	o->bfmeOneEBK(g_bfmeXEBK, 0);
}

class GameWindow
{
public:
	void *winGetUserData();
};

// ?Rva00327E0EGet@@YADPAVGameWindow@@@Z, retail 0x00727E0E (20B).
// Target evidence is the GameWindow user-data call and byte read at +0x34;
// the address-based name and argument class are structural inferences.
char Rva00327E0EGet(GameWindow *window)
{
	unsigned char *data = (unsigned char *)window->winGetUserData();
	if (data)
		return data[0x34];
	return 0;
}
