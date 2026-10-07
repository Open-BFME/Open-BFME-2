// cl: /O1 /Oi /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <algorithm>
// ?rva0042CB81@Rva0042CBB6@@QAEXH@Z @0x0042CB81 53B via conditional counter decrement plus zero-guard clear
// Evidence: layout matches Rva0042CBB6Ctor (+8 +0x30 +0x34 +0x39); callers 5 incl 0x0042CE09 0x0042D0CD; unblocks 0x0042D068
class Mouse
{
public:
	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
	virtual void m16(); virtual void m17(); virtual void m18();
	virtual void m19(int x);
	char m_pad[0x4FA0];
	int m_4FA4;
};
extern Mouse *TheMouse;

class Rva0042CBB6
{
public:
	void rva0042CB81(int x);
	void rva0042CC1B();
	void rva0042CAEB(int y);
	void rva0042CB57(int x);
private:
	const void *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	unsigned char m_38;
	unsigned char m_39;
	char m_3A[4];
	unsigned char m_3E;
	unsigned char m_3F;
	unsigned char m_40;
	unsigned char m_41;
	unsigned char m_42;
};

void Rva0042CBB6::rva0042CAEB(int y)
{
	if (m_04 == y)
		m_04 = 0;
}

void Rva0042CBB6::rva0042CB81(int x)
{
	if (x == 0)
		m_08 = 0;
	else {
		int cur = m_08;
		if ((x & cur) != 0)
			m_08 = cur - x;
	}
	if (m_08 < 0)
		m_08 = 0;
	if (m_08 == 0) {
		m_39 = 0;
		m_30 = 0;
		m_34 = 0;
	}
}

// ?rva0042CB57@Rva0042CBB6@@QAEXH@Z @0x0042CB57 42B via TheMouse+0x4FA4 fill plus bit-gated add
// Evidence: same class layout as neighbours (+8 +0x0C +0x39); TheMouse at 0x009FDCA0 field +0x4FA4 per Rva0042C7B1; callers 0x0042CD88 0x0042CEC4
void Rva0042CBB6::rva0042CB57(int x)
{
	int cur = m_08;
	if (cur == 0)
		m_0C = TheMouse->m_4FA4;
	if ((x & cur) == 0)
		m_08 = cur + x;
	m_39 = 1;
}

// Native Ghidra extent 0x0042CC1B..0x0042CC7B, 96 bytes, thiscall RET0.
// The consumed offsets and reset constants agree with the rowed constructor
// at 0x0042CBB6; original class and field meanings remain unknown.
// STLport 4.5.3's generic fill with a bool value retains the runtime pointer
// span for +0x3A..+0x3D. Its char overload folds that span into a constant
// memset and does not reproduce the retail comparison and REP stores.
void Rva0042CBB6::rva0042CC1B()
{
	m_08 = 0;
	m_0C = 2;
	m_14 = 0;
	m_10 = 0;
	m_1C = 0;
	m_18 = 0;
	m_24 = 0;
	m_20 = 0;
	m_2C = 0;
	m_28 = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 1;
	m_39 = 0;
	m_3E = 0;
	m_3F = 0;
	m_40 = 0;
	m_41 = 0;
	m_42 = 0;
	_STL::fill(m_3A, m_3A + 4, false);
}
