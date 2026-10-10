// ??0Rva002CD4A6@@QAE@XZ
// Native 002CD169..002CD4A6, 829 bytes including the complete unwind entry.
// ZH WeaponTemplate constructor supplies semantic defaults; target offsets and
// ownership follow the independently matched destructor, not donor layout.
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHs
// stlport
// ??0Rva002CD4A6@@QAE@XZ @0x002CD169 829B unlock: vtable 0x00802170 ctor with NoNameWeapon plus 999999 plus PI, caller 0x002CD634 new 0x180, neighbours StlportVectorAssignCoord3D and Rva002CD4A6Dtor
#include <vector>
#include <list>
#include "ascii_string.h"
class OpaqueRefCounted {public:void Release_Ref();};
struct Rva002CD169RefSlot { unsigned address; __forceinline Rva002CD169RefSlot(){} __forceinline Rva002CD169RefSlot(const void *p):address((unsigned)p){} __forceinline ~Rva002CD169RefSlot(){if(address)((OpaqueRefCounted*)address)->Release_Ref();} };



struct BfmeE16 { float x, y, z, w; };

class CashHackSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		Upgrades();
		int m_science;
		int m_amount;
	};
};

// The existing Upgrades constructor is a byte-identical two-word initializer
// (-1, null). This containment view transports that existing call; it does
// not assert CashHackSpecialPowerModuleData identity for the Weapon member.
// Ownership of the second word is independently established by the matched
// Weapon destructor at 002CD4A6 (+D4 and +DC).
struct Rva002CD169RefWords {
 CashHackSpecialPowerModuleData::Upgrades words;
 __forceinline ~Rva002CD169RefWords(){if(words.m_amount)((OpaqueRefCounted*)words.m_amount)->Release_Ref();}
};
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
 ~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
private:
	unsigned int m_record;
};

template<int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

extern BitFlags<116> KINDOFMASK_NONE;

class Rva002CD4A6
{
public:
	Rva002CD4A6();
	virtual ~Rva002CD4A6();
private:
	void *m_04;
	AsciiString m_08;
	int m_0C;
	int m_10;
	float m_14;
	float m_18;
	float m_1C;
	float m_20;
	float m_24;
	float m_28;
	float m_2C;
	float m_30;
	float m_34;
	float m_38;
	bool m_3C;
	bool m_3D;
	char m_pad3E[2];
	_STL::vector<BfmeE16> m_40;
	_STL::vector<BfmeE16> m_4C;
	int m_58;
	int m_5C;
	int m_60;
	int m_64;
	float m_68;
	float m_6C;
	float m_70;
	bool m_74;
	bool m_75;
	char m_pad76[2];
	int m_78;
	int m_7C;
	bool m_80;
	bool m_81;
	bool m_82;
	bool m_83;
	float m_84;
	float m_88;
	float m_8C;
	AsciiString m_90;
	const void *m_94[4];
	const void *m_A4[4];
	const void *m_B4;
	const void *m_B8[4];
	Rva002CD169RefSlot m_C8;
	int m_CC;
	Rva002CD169RefWords m_D0;
	Rva002CD169RefWords m_D8;
	const void *m_E0;
	int m_E4;
	int m_E8;
	int m_EC;
	int m_F0;
	int m_F4;
	int m_F8;
	int m_FC;
	int m_100;
	int m_104;
	int m_108;
	int m_10C;
	int m_110;
	bool m_114;
	char m_pad115[3];
	int m_118;
	bool m_11C;
	char m_pad11D[3];
	Rva003623E5Member m_120;
	bool m_124;
	bool m_125;
	bool m_126;
	char m_pad127;
	int m_128;
	int m_12C;
	bool m_130;
	bool m_131;
	bool m_132;
	bool m_133;
	bool m_134;
	bool m_135;
	char m_pad136[2];
	int m_138;
	int m_13C;
	bool m_140;
	bool m_141;
	char m_pad142[2];
	int m_144;
	float m_148;
	float m_14C;
	int m_150;
	bool m_154;
	bool m_155;
	bool m_156;
	bool m_157;
	float m_158;
	float m_15C;
	bool m_160;
	bool m_161;
	char m_pad162[2];
	float m_164;
	bool m_168;
	bool m_169;
	bool m_16A;
	bool m_16B;
	bool m_16C;
	bool m_16D;
	bool m_16E;
	bool m_16F;
	bool m_170;
	bool m_171;
	char m_pad172[2];
	int m_174;
	AsciiString m_178;
	_STL::list<int> m_17C;
};

Rva002CD4A6::Rva002CD4A6()
	: m_04(0)
	, m_40(_STL::allocator<BfmeE16>())
	, m_4C(_STL::allocator<BfmeE16>())
	, m_C8(0)
	, m_17C(_STL::allocator<int>())
{
	m_08 = "NoNameWeapon";
	m_14 = 0.0f;
	m_18 = 0.0f;
	m_1C = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_2C = 0.0f;
	m_30 = 0.0f;
	m_34 = 0.0f;
	m_38 = 0.0f;
	m_0C = 0;
	m_3C = false;
	m_3D = false;
	m_10 = 0;
	m_58 = 0x16;
	m_5C = 0;
	m_60 = 0x1d;
	m_64 = 0;
	m_68 = 999999.0f;
	m_6C = 999999.0f;
	m_70 = 999999.0f;
	m_84 = 0.0f;
	m_74 = false;
	m_75 = false;
	m_78 = -1;
	m_7C = 0;
	m_88 = -3.14159265f;
	m_8C = 3.14159265f;
	m_81 = false;
	m_80 = false;
	m_82 = false;
	m_83 = false;
	for (int i = 0; i < 4; ++i)
	{
		m_94[i] = 0;
		m_A4[i] = 0;
		m_B8[i] = 0;
	}
	m_B4 = 0;
	m_11C = false;
	m_120.initFromStorages((const BfmeFixedStorage0004543D &)KINDOFMASK_NONE, (const BfmeFixedStorage0004543D &)KINDOFMASK_NONE);
	m_174 = -1;
	m_124 = false;
	m_125 = false;
	m_126 = false;
	m_110 = 0xe;
	m_114 = false;
	m_118 = 8;
	m_128 = 0;
	m_12C = 0;
	m_E4 = 0;
	m_F8 = 0x7fffffff;
	m_FC = 0x7fffffff;
	m_100 = 0;
	m_104 = 0;
	m_E8 = 0;
	m_EC = 0;
	m_F0 = 0;
	m_F4 = 0;
	m_CC = 0;
	m_E0 = 0;
	m_108 = 1;
	m_10C = 2;
	m_130 = false;
	m_131 = false;
	m_132 = false;
	m_133 = false;
	m_134 = false;
	m_135 = false;
	m_140 = false;
	m_141 = false;
	m_138 = 0;
	m_13C = 0;
	m_144 = 0;
	m_148 = 0.0f;
	m_14C = 0.0f;
	m_150 = 0;
	m_154 = false;
	m_155 = false;
	m_156 = false;
	m_157 = false;
	m_158 = 1.0f;
	m_15C = 0.0f;
	m_160 = false;
	m_161 = true;
	m_164 = 0.0f;
	m_168 = false;
	m_169 = false;
	m_16A = false;
	m_16B = false;
	m_16C = false;
	m_16D = true;
	m_16E = false;
	m_16F = false;
	m_170 = false;
	m_171 = false;
	((StringBase<char> *)&m_178)->clear();
}
