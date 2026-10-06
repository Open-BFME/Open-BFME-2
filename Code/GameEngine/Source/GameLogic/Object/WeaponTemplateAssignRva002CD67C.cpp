// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX- /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4WeaponTemplate@@QAEAAV0@ABV0@@Z @0x002CD67C 1170B unlock: WeaponTemplate copy assignment, vectors at +0x40/+0x4C via rowed assigns, list at +0x17C, callers 0x002CE0B0
// Evidence: tu_map proposes Weapon.cpp, +0x17C list<int> nuggets and +0x160 flag match WeaponTemplateRva002CBA59/ParseClearNuggets, +0x40 scatter vector via rowed BfmePod8 assign, caller 0x002CE063 new 0x180 then ctor+assign.
#include <vector>
#include <list>
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct BfmePod8
{
	int a[2];
};

struct OpaqueRefElement4
{
	void *m_ptr;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva002C99FB
{
	int m_first;
	OpaqueRefElement4 m_second;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};

class WeaponTemplate
{
public:
	WeaponTemplate &operator=(const WeaponTemplate &other);
private:
	void *m00;
	int m04;
	AsciiString m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	int m1C;
	int m20;
	int m24;
	int m28;
	int m2C;
	int m30;
	int m34;
	int m38;
	unsigned char m3C;
	unsigned char m3D;
	_STL::vector<BfmePod8> m40;
	_STL::vector<Coord3D> m4C;
	int m58;
	int m5C;
	int m60;
	int m64;
	int m68;
	int m6C;
	int m70;
	unsigned char m74;
	unsigned char m75;
	int m78;
	int m7C;
	unsigned char m80;
	unsigned char m81;
	unsigned char m82;
	unsigned char m83;
	int m84;
	int m88;
	int m8C;
	AsciiString m90;
	int m94[4];
	int mA4[4];
	int mB4;
	int mB8[4];
	OpaqueRefElement4 mC8;
	int mCC;
	Rva002C99FB mD0;
	Rva002C99FB mD8;
	int mE0;
	int mE4;
	int mE8;
	int mEC;
	int mF0;
	int mF4;
	int mF8;
	int mFC;
	int m100;
	int m104;
	int m108;
	int m10C;
	int m110;
	unsigned char m114;
	int m118;
	unsigned char m11C;
	int m120;
	unsigned char m124;
	unsigned char m125;
	unsigned char m126;
	int m128;
	int m12C;
	unsigned char m130;
	unsigned char m131;
	unsigned char m132;
	unsigned char m133;
	unsigned char m134;
	unsigned char m135;
	int m138;
	int m13C;
	unsigned char m140;
	unsigned char m141;
	int m144;
	int m148;
	int m14C;
	int m150;
	unsigned char m154;
	unsigned char m155;
	unsigned char m156;
	unsigned char m157;
	int m158;
	int m15C;
	unsigned char m160;
	unsigned char m161;
	int m164;
	unsigned char m168;
	unsigned char m169;
	unsigned char m16A;
	unsigned char m16B;
	unsigned char m16C;
	unsigned char m16D;
	unsigned char m16E;
	unsigned char m16F;
	unsigned char m170;
	unsigned char m171;
	int m174;
	AsciiString m178;
	_STL::list<int> m17C;
};

WeaponTemplate &WeaponTemplate::operator=(const WeaponTemplate &other)
{
	m04 = other.m04;
	m08.set(other.m08);
	m0C = other.m0C;
	m10 = other.m10;
	m14 = other.m14;
	m18 = other.m18;
	m1C = other.m1C;
	m20 = other.m20;
	m24 = other.m24;
	m28 = other.m28;
	m2C = other.m2C;
	m30 = other.m30;
	m34 = other.m34;
	m38 = other.m38;
	m3C = other.m3C;
	m3D = other.m3D;
	m40 = other.m40;
	m4C = other.m4C;
	m58 = other.m58;
	m5C = other.m5C;
	m60 = other.m60;
	m64 = other.m64;
	m68 = other.m68;
	m6C = other.m6C;
	m70 = other.m70;
	m74 = other.m74;
	m75 = other.m75;
	m78 = other.m78;
	m7C = other.m7C;
	m80 = other.m80;
	m81 = other.m81;
	m82 = other.m82;
	m83 = other.m83;
	m84 = other.m84;
	m88 = other.m88;
	m8C = other.m8C;
	m90.set(other.m90);
	for (int i = 0; i < 4; ++i)
		m94[i] = other.m94[i];
	for (int i = 0; i < 4; ++i)
		mA4[i] = other.mA4[i];
	mB4 = other.mB4;
	for (int i = 0; i < 4; ++i)
		mB8[i] = other.mB8[i];
	mC8 = other.mC8;
	mCC = other.mCC;
	mD0 = other.mD0;
	mD8 = other.mD8;
	mE0 = other.mE0;
	mE4 = other.mE4;
	mE8 = other.mE8;
	mEC = other.mEC;
	mF0 = other.mF0;
	mF4 = other.mF4;
	mF8 = other.mF8;
	mFC = other.mFC;
	m100 = other.m100;
	m104 = other.m104;
	m108 = other.m108;
	m10C = other.m10C;
	m110 = other.m110;
	m114 = other.m114;
	m118 = other.m118;
	m11C = other.m11C;
	m120 = other.m120;
	m124 = other.m124;
	m125 = other.m125;
	m126 = other.m126;
	m128 = other.m128;
	m12C = other.m12C;
	m130 = other.m130;
	m131 = other.m131;
	m132 = other.m132;
	m133 = other.m133;
	m134 = other.m134;
	m135 = other.m135;
	m138 = other.m138;
	m13C = other.m13C;
	m140 = other.m140;
	m141 = other.m141;
	m144 = other.m144;
	m148 = other.m148;
	m14C = other.m14C;
	m150 = other.m150;
	m154 = other.m154;
	m155 = other.m155;
	m156 = other.m156;
	m157 = other.m157;
	m158 = other.m158;
	m15C = other.m15C;
	m160 = other.m160;
	m161 = other.m161;
	m164 = other.m164;
	m168 = other.m168;
	m169 = other.m169;
	m16A = other.m16A;
	m16B = other.m16B;
	m16C = other.m16C;
	m16D = other.m16D;
	m16E = other.m16E;
	m16F = other.m16F;
	m170 = other.m170;
	m171 = other.m171;
	m174 = other.m174;
	m178.set(other.m178);
	m17C = other.m17C;
	return *this;
}
