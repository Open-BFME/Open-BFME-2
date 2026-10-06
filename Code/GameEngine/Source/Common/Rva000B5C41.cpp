// cl: /MD
// ?rva000B5C41@Rva000B5C41@@QAEXXZ 0x000B5C41 318B evidence: chain via 0x002707FA rowed; array at +0x18 base+0x50 end+0x54 stride 0x40 floats +0x34 +0x38 flag +0x3c vs BfmeZeroRange g_Va00BBB8D8; helper +0x110 slot0x14 int; target +0x50 slots 0x194 0x5c; setter +0x8 is Rva002707FA
extern const float BfmeZeroRange;
extern float g_Va00BBB8D8;

class Rva002707FA
{
public:
	void rva002707FA(unsigned char value);
};

class Helper000B5C41
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual int s05();
};

class Obj000B5C41
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22();
	virtual void s23(int a, float b);
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
	virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95();
	virtual void s96(); virtual void s97(); virtual void s98(); virtual void s99();
	virtual void s100();
	virtual void s101(int a);
};

struct Entry000B5C41
{
	char _p00[0x34];
	float m34;
	float m38;
	unsigned char m3c;
	char _pad[0x40 - 0x3c - 1];
};

struct Container000B5C41
{
	char _p00[0x50];
	Entry000B5C41 *m50;
	Entry000B5C41 *m54;
};

class Rva000B5C41
{
	char _p00[0x8];
	Rva002707FA *m08;
	char _p0c[0x18 - 0x8 - 4];
	Container000B5C41 *m18;
	char _p1c[0x44 - 0x18 - 4];
	int m44;
	char _p48[0x50 - 0x44 - 4];
	Obj000B5C41 *m50;
	char _p54[0x110 - 0x50 - 4];
	Helper000B5C41 *m110;
	float m114;
public:
	void rva000B5C41();
};

void Rva000B5C41::rva000B5C41()
{
	Container000B5C41 *c = m18;
	if (c == 0)
		return;
	Entry000B5C41 *base = c->m50;
	Entry000B5C41 *end = c->m54;
	if (base == end)
		return;
	int idx = m44;
	if (idx == -1)
		return;
	Entry000B5C41 *e = (Entry000B5C41 *)((char *)base + (idx << 6));
	if (e == 0)
		return;
	if (!(e->m34 > BfmeZeroRange))
		return;
	if (!(e->m38 > e->m34))
		return;
	if (m110 == 0)
		return;
	float f = m114;
	int r1 = m110->s05();
	float f1 = (float)r1;
	float ref;
	if (e->m38 > f1) {
		int r2 = m110->s05();
		ref = (float)r2;
	} else {
		ref = e->m38;
	}
	float baseF = e->m34;
	if (baseF > f) {
		if (e->m3c == 0)
			goto one_assign;
		f = 0.0f;
		goto zero;
	}
	if (f > ref) {
		if (e->m3c == 0) {
			f = 0.0f;
			goto zero;
		}
one_assign:
		f = g_Va00BBB8D8;
		goto one;
	}
	{
		float t = (f - e->m34) / (ref - e->m34);
		float t2;
		if (e->m3c != 0)
			t2 = t;
		else
			t2 = g_Va00BBB8D8 - t;
		f = t2;
		if (t2 > BfmeZeroRange)
			goto one;
		goto zero;
	}
zero:
	m08->rva002707FA(0);
	m50->s101(1);
	m50->s23(1, f);
	return;
one:
	m08->rva002707FA(1);
	m50->s101(0);
	m50->s23(1, f);
	return;
}
