// ?rva000B5A72@Rva000B5C41@@QAEXPAUArg000B5A72@@@Z
// partial score=0.8495 date=2026-10-05
// cl: /O1 /MD /arch:SSE /Oi
// ?rva000B5C41@Rva000B5C41@@QAEXXZ 0x000B5C41 318B evidence: chain via 0x002707FA rowed; array at +0x18 base+0x50 end+0x54 stride 0x40 floats +0x34 +0x38 flag +0x3c vs BfmeZeroRange g_Va00BBB8D8; helper +0x110 slot0x14 int; target +0x50 slots 0x194 0x5c; setter +0x8 is Rva002707FA
#include <math.h>
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
	char _pad98[0x98 - 4];
	int m98;
	char _padBC[0xBC - 0x98 - 4];
	unsigned char mBC;
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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class TacticalView
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
	virtual void t08(); virtual void t09(); virtual void t10(); virtual void t11();
	virtual void t12(); virtual void t13(); virtual void t14(); virtual void t15();
	virtual void t16(); virtual void t17(); virtual void t18(); virtual void t19();
	virtual void t20(); virtual void t21(); virtual void t22(); virtual void t23();
	virtual void t24(); virtual void t25(); virtual void t26(); virtual void t27();
	virtual void t28(); virtual void t29(); virtual void t30(); virtual void t31();
	virtual void t32(); virtual void t33(); virtual void t34(); virtual void t35();
	virtual void t36(); virtual void t37(); virtual void t38(); virtual void t39();
	virtual void t40(); virtual void t41(); virtual void t42(); virtual void t43();
	virtual void t44(); virtual void t45(); virtual void t46(); virtual void t47();
	virtual void t48(); virtual void t49(); virtual void t50(); virtual void t51();
	virtual void t52(); virtual void t53(); virtual void t54(); virtual void t55();
	virtual void t56(); virtual void t57(); virtual void t58(); virtual void t59();
	virtual void t60(); virtual void t61(); virtual void t62(); virtual void t63();
	virtual void t64(); virtual void t65(); virtual void t66(); virtual void t67();
	virtual void t68(); virtual void t69(); virtual void t70();
	virtual const Coord3D *t71();
};

class GameLODManager
{
public:
	char _p00[0x1778];
	int m1778;
};

extern TacticalView *TheTacticalView;
extern GameLODManager *TheGameLODManager;

struct Arg000B5A72
{
	char _p00[0x144];
	float m144;
	float m148;
	float m14C;
	char _pad[0x158 - 0x14C - 4];
	int m158;
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
	char _pad118[0x28D - 0x118];
	unsigned char m28D;
public:
	void rva000B5C41();
	void rva000B5A72(Arg000B5A72 *a);
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

// ?rva000B5A72@Rva000B5C41@@QAEXPAUArg000B5A72@@@Z present-unmatched
void Rva000B5C41::rva000B5A72(Arg000B5A72 *a)
{
	m50->mBC = 0;
	if (m28D == 0)
		return;
	if (!(g_Va00BBB8D8 > a->m14C))
		return;
	const Coord3D *p1 = TheTacticalView->t71();
	float x1 = p1->x;
	float y1 = p1->y;
	const Coord3D *p2 = ((BFMERopeDrawable *)m08)->getPosition();
	float dx = x1 - p2->x;
	float dy = y1 - p2->y;
	float dist2 = dy * dy + dx * dx;
	float r144 = a->m144;
	if (dist2 >= r144 * r144) {
		m08->rva002707FA(1);
		m50->s101(0);
		m50->s23(1, 1.0f);
		if (a->m158 < 0)
			return;
		m50->m98 = 0;
		return;
	}
	float r148 = a->m148;
	float r148sq = r148 * r148;
	float res;
	if (r148sq < dist2) {
		float dist = sqrtf(dist2);
		float d1 = r144 - r148;
		float d2 = dist - r148;
		res = ((d1 - d2) * a->m14C + d2) / d1;
	} else {
		res = a->m14C;
	}
	GameLODManager *lm = TheGameLODManager;
	if (lm != 0 && lm->m1778 <= 1) {
		m08->rva002707FA(0);
		m50->s101(1);
		if (a->m158 < 0)
			return;
		m50->m98 = 0;
		return;
	}
	if (res > BfmeZeroRange) {
		m08->rva002707FA(1);
		m50->s101(0);
	} else {
		m08->rva002707FA(0);
		m50->s101(1);
	}
	m50->s23(1, res);
	m50->mBC = 1;
	int v158 = a->m158;
	if (v158 < 0)
		return;
	m50->m98 = v158;
	return;
}
