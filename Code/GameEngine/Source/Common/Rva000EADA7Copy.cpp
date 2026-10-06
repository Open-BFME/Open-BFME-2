// cl: /MD
// ??0Rva000EADA7@@QAE@ABV0@@Z retail 0x000EADA7 473B unlock lane.
// Evidence: memberwise copy with Region2D copy ctor at +0x48 (row
// ??0Region2D@@QAE@ABU0@@Z); caller at 0x000ED6A9.
struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

struct FourDwords
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
};

struct ThreeDwords
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

class Rva000EADA7
{
public:
	Rva000EADA7(const Rva000EADA7 &that);
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	unsigned char m_44;
	unsigned char m_pad45[3];
	Region2D m_region;
	int m_58;
	int m_5c;
	int m_60;
	int m_64;
	int m_68;
	int m_6c;
	int m_70;
	ThreeDwords m_74;
	int m_80;
	int m_84;
	unsigned char m_88;
	unsigned char m_pad89[3];
	int m_8c;
	int m_90;
	int m_94;
	int m_98;
	int m_9c;
	struct FourDwords
	{
		unsigned int a;
		unsigned int b;
		unsigned int c;
		unsigned int d;
	};
	FourDwords m_a0;
	FourDwords m_b0;
	int m_c0;
	unsigned char m_c4;
	unsigned char m_padc5[3];
	int m_c8;
	int m_cc;
	int m_d0;
	int m_d4;
	int m_d8;
	int m_dc;
	int m_e0;
	int m_e4;
};

Rva000EADA7::Rva000EADA7(const Rva000EADA7 &that)
	: m_00(that.m_00)
	, m_04(that.m_04)
	, m_08(that.m_08)
	, m_0c(that.m_0c)
	, m_10(that.m_10)
	, m_14(that.m_14)
	, m_18(that.m_18)
	, m_1c(that.m_1c)
	, m_20(that.m_20)
	, m_24(that.m_24)
	, m_28(that.m_28)
	, m_2c(that.m_2c)
	, m_30(that.m_30)
	, m_34(that.m_34)
	, m_38(that.m_38)
	, m_3c(that.m_3c)
	, m_40(that.m_40)
	, m_44(that.m_44)
	, m_region(that.m_region)
{
	m_58 = that.m_58;
	m_5c = that.m_5c;
	m_60 = that.m_60;
	m_64 = that.m_64;
	m_68 = that.m_68;
	m_6c = that.m_6c;
	m_70 = that.m_70;
	m_74 = that.m_74;
	m_80 = that.m_80;
	m_84 = that.m_84;
	m_88 = that.m_88;
	m_8c = that.m_8c;
	m_90 = that.m_90;
	m_94 = that.m_94;
	m_98 = that.m_98;
	m_9c = that.m_9c;
	{
		const FourDwords *src = &that.m_a0;
		FourDwords *dst = &m_a0;
		dst->a = src->a;
		dst->b = src->b;
		dst->c = src->c;
		dst->d = src->d;
	}
	{
		const FourDwords *src = &that.m_b0;
		FourDwords *dst = &m_b0;
		dst->a = src->a;
		dst->b = src->b;
		dst->c = src->c;
		dst->d = src->d;
	}
	m_c0 = that.m_c0;
	m_c4 = that.m_c4;
	m_c8 = that.m_c8;
	m_cc = that.m_cc;
	m_d0 = that.m_d0;
	m_d4 = that.m_d4;
	m_d8 = that.m_d8;
	m_dc = that.m_dc;
	m_e0 = that.m_e0;
	m_e4 = that.m_e4;
}
