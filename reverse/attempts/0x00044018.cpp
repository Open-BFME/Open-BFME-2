// ?rva00044018@Rva00044018@@QAEXI@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /MD /arch:SSE /Oi-
// ?rva00044018@Rva00044018@@QAEXI@Z @0x00044018 479B
// Unlock: fade rect update, two-bar top/bottom via rowed 0x0004263F; callers at 0x0004A913; flag+0xD8 direction, progress+0xD4, start+0xDC, dims+0xC/+0x10.

extern float g_Va00BBB8D8;
extern const float g_00BC26EC;
extern const float g_00BC28F8;
extern const float g_00BC2900;
extern const float g_00BC28FC;
extern float g_Va007C26F0;

class Rva0004263F
{
	virtual void _M_slot_00();
	virtual void _M_slot_01();
	virtual void _M_slot_02();
	virtual void _M_slot_03();
	virtual void _M_slot_04();
	virtual void _M_slot_05();
	virtual void _M_slot_06();
	virtual void _M_slot_07();
	virtual void _M_slot_08();
	virtual void _M_slot_09();
	virtual void _M_slot_10();
	virtual void _M_slot_11();
	virtual void _M_slot_12();
	virtual void _M_slot_13();
	virtual void _M_slot_14();
	virtual void _M_slot_15();
	virtual void _M_slot_16();
	virtual void _M_slot_17();
	virtual void _M_slot_18();
	virtual void _M_slot_19();
	virtual void _M_slot_20();
	virtual void _M_slot_21();
	virtual void _M_slot_22();
	virtual void _M_slot_23();
	virtual void _M_slot_24();
	virtual void _M_slot_25();
	virtual void _M_slot_26();
	virtual void _M_slot_27();
	virtual void _M_slot_28();
	virtual void _M_slot_29();
	virtual void _M_slot_30();
	virtual void _M_slot_31();
	virtual void _M_slot_32();
	virtual void _M_slot_33();
	virtual void _M_slot_34();
	virtual void _M_slot_35();
	virtual void _M_slot_36();
	virtual void _M_slot_37();
	virtual void _M_slot_38();
	virtual void _M_slot_39();
	virtual void _M_slot_40();
	virtual void _M_slot_41();
	virtual void _M_slot_42();
	virtual void _M_slot_43();
	virtual void _M_slot_44();
	virtual void _M_slot_45();
	virtual void _M_slot_46();
	virtual void _M_slot_47();
	virtual void _M_slot_48();
	virtual void _M_slot_49();
	virtual void _M_slot_50();
	virtual void _M_slot_51();
	virtual void _M_slot_52();
	virtual void _M_slot_53();
	virtual void _M_slot_54();
	virtual void _M_slot_55();
	virtual void _M_slot_56();
	virtual void _M_slot_57(float a, float b, float c, float d, int e);
	virtual void _M_slot_58();
	virtual void _M_slot_59();
	virtual void _M_slot_60();
	virtual void _M_slot_61();
	virtual void _M_slot_62();
	virtual void _M_slot_63();
	virtual void _M_slot_64();
public:
	void rva0004263F(float a, float b, float c, float d, int e);
};

class Rva00044018 : public Rva0004263F
{
	char m_pad04[8];
	unsigned int m_w;
	unsigned int m_h;
	char m_pad14[0xC0];
	float m_progress;
	unsigned char m_flag;
	char m_padD9[3];
	unsigned int m_start;
public:
	void rva00044018(unsigned int arg);
};

// ?rva00044018@Rva00044018@@QAEXI@Z present-unmatched
void Rva00044018::rva00044018(unsigned int arg)
{
	if (m_flag != 0)
	{
		if (m_progress != g_Va00BBB8D8)
		{
			arg -= m_start;
			float f = (float)arg * g_00BC28F8;
			m_progress = f;
			if (f > 1.0f)
				m_progress = 1.0f;
		}
		int alpha = (int)(m_progress * g_00BC2900) << 24;
		rva0004263F(0.0f, 0.0f, (float)m_w, ((float)m_h - (float)m_w * g_00BC28FC) * g_Va007C26F0, alpha);
		rva0004263F(0.0f, (float)m_h - ((float)m_h - (float)m_w * g_00BC28FC) * g_Va007C26F0, (float)m_w, (float)m_h, alpha);
	}
	else
	{
		if (m_progress != 0.0f)
		{
			arg -= m_start;
			float f = (float)arg * g_00BC28F8;
			float v = g_Va00BBB8D8 - f;
			m_progress = v;
			if (v < 0.0f)
				m_progress = 0.0f;
			int alpha = (int)(m_progress * g_00BC2900) << 24;
			rva0004263F(0.0f, 0.0f, (float)m_w, ((float)m_h - (float)m_w * g_00BC28FC) * g_Va007C26F0, alpha);
		}
		else
		{
			m_flag = 0;
		}
	}
}
