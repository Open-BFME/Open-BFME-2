// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ??0Rva001E4DB0@@QAE@ABV0@@Z, retail 0x001E4DEB, 961 bytes.
// Copy constructor of the Rva001E4DB0 holder (vtable 0x007DE8B4, rowed dtor
// 0x001E4DB0): base copy constructor (0x007664DD, base Rva001E3624), the AsciiString at
// +0x10 copy-constructed, then the same member-wise int/byte copies up to +0x151 as
// the sibling copy assignment Rva001E3955::operator= (Rva001E3955Assign.cpp).
// Target evidence: retail body and the shared member offsets/widths read byte for byte.
#include "ascii_string.h"
class Rva001E3624
{
public:
	Rva001E3624(const Rva001E3624 &rhs);
	virtual ~Rva001E3624();
	char m_pad[0x0C];
};
class Rva001E4DB0 : public Rva001E3624
{
public:
	Rva001E4DB0(const Rva001E4DB0 &rhs);
	virtual ~Rva001E4DB0();
private:
	AsciiString m_10;
	int m_14;
	int m_18;
	unsigned char m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60;
	int m_64;
	int m_68;
	int m_6C;
	int m_70;
	int m_74;
	int m_78;
	int m_7C;
	int m_80;
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
	int m_94;
	int m_98;
	int m_9C;
	int m_A0;
	int m_A4;
	int m_A8;
	int m_AC;
	int m_B0;
	int m_B4;
	int m_B8;
	int m_BC;
	int m_C0;
	int m_C4;
	unsigned char m_C8;
	int m_CC;
	unsigned char m_D0;
	unsigned char m_D1;
	unsigned char m_D2;
	unsigned char m_D3;
	unsigned char m_D4;
	int m_D8;
	unsigned char m_DC;
	int m_E0;
	int m_E4;
	int m_E8;
	unsigned char m_EC;
	unsigned char m_ED;
	int m_F0;
	int m_F4;
	int m_F8;
	int m_FC;
	unsigned char m_100;
	int m_104;
	unsigned char m_108;
	unsigned char m_109;
	unsigned char m_10A;
	unsigned char m_10B;
	int m_10C;
	int m_110;
	int m_114;
	int m_118;
	int m_11C;
	int m_120;
	int m_124;
	int m_128;
	int m_12C;
	int m_130;
	int m_134;
	int m_138;
	unsigned char m_13C;
	int m_140;
	int m_144;
	int m_148;
	int m_14C;
	unsigned char m_150;
	unsigned char m_151;
};

Rva001E4DB0::Rva001E4DB0(const Rva001E4DB0 &rhs) : Rva001E3624(rhs), m_10(rhs.m_10)
{
	m_14 = rhs.m_14;
	m_18 = rhs.m_18;
	m_1C = rhs.m_1C;
	m_20 = rhs.m_20;
	m_24 = rhs.m_24;
	m_28 = rhs.m_28;
	m_2C = rhs.m_2C;
	m_30 = rhs.m_30;
	m_34 = rhs.m_34;
	m_38 = rhs.m_38;
	m_3C = rhs.m_3C;
	m_40 = rhs.m_40;
	m_44 = rhs.m_44;
	m_48 = rhs.m_48;
	m_4C = rhs.m_4C;
	m_50 = rhs.m_50;
	m_54 = rhs.m_54;
	m_58 = rhs.m_58;
	m_5C = rhs.m_5C;
	m_60 = rhs.m_60;
	m_64 = rhs.m_64;
	m_68 = rhs.m_68;
	m_6C = rhs.m_6C;
	m_70 = rhs.m_70;
	m_74 = rhs.m_74;
	m_78 = rhs.m_78;
	m_7C = rhs.m_7C;
	m_80 = rhs.m_80;
	m_84 = rhs.m_84;
	m_88 = rhs.m_88;
	m_8C = rhs.m_8C;
	m_90 = rhs.m_90;
	m_94 = rhs.m_94;
	m_98 = rhs.m_98;
	m_9C = rhs.m_9C;
	m_A0 = rhs.m_A0;
	m_A4 = rhs.m_A4;
	m_A8 = rhs.m_A8;
	m_AC = rhs.m_AC;
	m_B0 = rhs.m_B0;
	m_B4 = rhs.m_B4;
	m_B8 = rhs.m_B8;
	m_BC = rhs.m_BC;
	m_C0 = rhs.m_C0;
	m_C4 = rhs.m_C4;
	m_C8 = rhs.m_C8;
	m_CC = rhs.m_CC;
	m_D0 = rhs.m_D0;
	m_D1 = rhs.m_D1;
	m_D2 = rhs.m_D2;
	m_D3 = rhs.m_D3;
	m_D4 = rhs.m_D4;
	m_D8 = rhs.m_D8;
	m_DC = rhs.m_DC;
	m_E0 = rhs.m_E0;
	m_E4 = rhs.m_E4;
	m_E8 = rhs.m_E8;
	m_EC = rhs.m_EC;
	m_ED = rhs.m_ED;
	m_F0 = rhs.m_F0;
	m_F4 = rhs.m_F4;
	m_F8 = rhs.m_F8;
	m_FC = rhs.m_FC;
	m_100 = rhs.m_100;
	m_104 = rhs.m_104;
	m_108 = rhs.m_108;
	m_109 = rhs.m_109;
	m_10A = rhs.m_10A;
	m_10B = rhs.m_10B;
	m_10C = rhs.m_10C;
	m_110 = rhs.m_110;
	m_114 = rhs.m_114;
	m_118 = rhs.m_118;
	m_11C = rhs.m_11C;
	m_120 = rhs.m_120;
	m_124 = rhs.m_124;
	m_128 = rhs.m_128;
	m_12C = rhs.m_12C;
	m_130 = rhs.m_130;
	m_134 = rhs.m_134;
	m_138 = rhs.m_138;
	m_13C = rhs.m_13C;
	m_140 = rhs.m_140;
	m_144 = rhs.m_144;
	m_148 = rhs.m_148;
	m_14C = rhs.m_14C;
	m_150 = rhs.m_150;
	m_151 = rhs.m_151;
}
