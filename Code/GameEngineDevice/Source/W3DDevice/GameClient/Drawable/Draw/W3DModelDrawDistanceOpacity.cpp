// cl: /ICode/Libraries/Include /O1 /MD /arch:SSE /Oi
// Target B5A72..B5C41 complete463B RET4 and WB944780 independently
// establish draw opacity from view distance, including the two thresholds,
// alpha coefficient and optional final integer. Original method name unknown;
// receiver relationship follows the existing owned sibling Rva000B5C41.
// Native proves drawable8/render50/enable28D; argument fields144/148/14C,
// final value158; renderer byteBC/int98, slots23/101. The TacticalView global
// and slot71 supply a Coord3D pointer; GameLODManager+1778 is compared to1.
// Owned Drawable::getPosition2763E6 replaces the old donor's false
// BFMERopeDrawable spelling; Rva002707FA preserves the owned byte setter ABI.
// WB and ZH math guide vector distance/interpolation semantics; target proves
// layouts separately. Only observed prefixes are asserted. There is no clean
// same-name donor for this BFME2-specific opacity operation.
// The local RangeSample holds the coordinate and rounded distance together:
// it reproduces the native16B frame (pointF0/F4, rounded sqrtFC), instead of
// reusing the freed pointer argument slot. Volatile forces retail's float
// rounding; the compiler barrier preserves the observed reload order after
// FSQRT/FSTP. Near-distance is evaluated before span to preserve SSE roles.
// The matched square root inlines; keep MSVC float overloads local.
#pragma push_macro("inline")
#define inline static inline
#include <math.h>
#pragma pop_macro("inline")

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)



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

#include "Lib/Coord3D.h"
struct RangeSample {Coord3D point;volatile float distance;};
__forceinline void opacityCoordCopy(Coord3D*destination,const Coord3D*source){destination->x=source->x;destination->y=source->y;destination->z=source->z;}
#include "../../../../../../GameEngine/Include/GameClient/Drawable.h"

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

#include "../../../../../../GameEngine/Include/Common/GameLODManager.h"

class View;
extern View *TheTacticalView;
extern GameLODManager *TheGameLODManager;

struct Arg000B5A72
{
	char _p00[0x144];
	float m144;
	float m148;
	float m14C;
	char _pad[0x158 - 0x14C - 4];
	int m_staticSortLevelWhileFading;
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
	void rva000B5A72(Arg000B5A72 *moduleData);
};


void Rva000B5C41::rva000B5A72(Arg000B5A72 *moduleData)
{
	m50->mBC = 0;
	if (m28D == 0)
		return;
	if (!(1.0f > moduleData->m14C))
		return;
	const Coord3D *p1 = ((TacticalView*)TheTacticalView)->t71();
	RangeSample sample;Coord3D &pos=sample.point;opacityCoordCopy(&pos,p1);
	const Coord3D *p2 = ((Drawable *)m08)->getPosition();
	pos.x-=p2->x;pos.y-=p2->y;pos.z-=p2->z;
	float dist2 = pos.y*pos.y+pos.x*pos.x;
	
	if (dist2 >= moduleData->m144 * moduleData->m144) {
		m08->rva002707FA(1);
		m50->s101(0);
		m50->s23(1, 1.0f);
		if (moduleData->m_staticSortLevelWhileFading < 0)
			return;
		m50->m98 = 0;
		return;
	}
	
	float innerSqr = moduleData->m148 * moduleData->m148;
	float res;
 if(dist2<=innerSqr)res=moduleData->m14C;
 else {
  sample.distance=sqrtf(dist2);_ReadWriteBarrier();
  float d2=sample.distance-moduleData->m148;
  float d1=moduleData->m144-moduleData->m148;
  res=((d1-d2)*moduleData->m14C+d2)/d1;
 }
	GameLODManager *lm = TheGameLODManager;
	if (lm != 0 && lm->word1778 <= 1) {
		m08->rva002707FA(0);
		m50->s101(1);
		if (moduleData->m_staticSortLevelWhileFading < 0)
			return;
		m50->m98 = 0;
		return;
	}
	if (res > 0.0f) {
		m08->rva002707FA(1);
		m50->s101(0);
	} else {
		m08->rva002707FA(0);
		m50->s101(1);
	}
	m50->s23(1, res);
	m50->mBC = 1;
	int staticSortLevelWhileFading = moduleData->m_staticSortLevelWhileFading;
	if (staticSortLevelWhileFading < 0)
		return;
	m50->m98 = staticSortLevelWhileFading;
	return;
}
