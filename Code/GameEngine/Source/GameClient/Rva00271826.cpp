// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??0Rva00271826@@QAE@XZ retail 0x00271826 108B
// FINISH from banked 0.98 by muse-11; vtable 0x007FAF68 at +0 via global;
// 12 floats +0x04-0x30 plus int +0x34 plus bytes +0x38 +0x39 plus floats
// +0x3C +0x40 +0x44 +0x48 +0x4C all zero; prev Rva00271779 same arch.
// Evidence: vtable VA 0x007FAF68, 12 callers including 0x0027543B.

extern const void *const g_007FAF68[];

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva00271826 {
public:
	Rva00271826();
private:
	char m_pad00[0x04];
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
	float m_20;
	float m_24;
	float m_28;
	float m_2C;
	float m_30;
	int m_34;
	unsigned char m_38;
	bool m_39;
	float m_3C;
	float m_40;
	float m_44;
	float m_48;
	float m_4C;
};

Rva00271826::Rva00271826()
{
	*(const void **)this = g_007FAF68;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0C = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	m_1C = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_2C = 0.0f;
	m_30 = 0.0f;
	m_44 = 0.0f;
	m_48 = 0.0f;
	m_4C = 0.0f;
	_ReadWriteBarrier();
	m_38 = 0;
	m_34 = 0;
	m_39 = false;
	m_3C = 0.0f;
	m_40 = 0.0f;
}
