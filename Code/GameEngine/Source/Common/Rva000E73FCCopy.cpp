// cl: /MD
// ??0Rva000E73FC@@QAE@ABU0@@Z 0x000E73FC 301B
// Copy ctor for 0xA0-byte element: 17 dwords then 3 bytes then Region2D at +0x48 via rowed copy ctor then 18 dwords.
// Evidence: straight mov run with Region2D copy call at +0x48 and ret 4; neighbours Rva000E73CE Rva000E76B8 stride 0xA0; callee row ??0Region2D@@QAE@ABU0@@Z.
struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};
struct Rva000E73FC
{
	Rva000E73FC(const Rva000E73FC &that);
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
	unsigned char m_45;
	unsigned char m_46;
	Region2D m_48;
	int m_58;
	int m_5c;
	int m_60;
	int m_64;
	int m_68;
	int m_6c;
	int m_70;
	int m_74;
	int m_78;
	int m_7c;
	int m_80;
	int m_84;
	int m_88;
	int m_8c;
	int m_90;
	int m_94;
	int m_98;
	int m_9c;
};
Rva000E73FC::Rva000E73FC(const Rva000E73FC &that)
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
	, m_45(that.m_45)
	, m_46(that.m_46)
	, m_48(that.m_48)
	, m_58(that.m_58)
	, m_5c(that.m_5c)
	, m_60(that.m_60)
	, m_64(that.m_64)
	, m_68(that.m_68)
	, m_6c(that.m_6c)
	, m_70(that.m_70)
	, m_74(that.m_74)
	, m_78(that.m_78)
	, m_7c(that.m_7c)
	, m_80(that.m_80)
	, m_84(that.m_84)
	, m_88(that.m_88)
	, m_8c(that.m_8c)
	, m_90(that.m_90)
	, m_94(that.m_94)
	, m_98(that.m_98)
	, m_9c(that.m_9c)
{
}
