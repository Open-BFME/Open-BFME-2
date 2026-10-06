// cl: /MD
//
// ?rva0025ECFC@Rva0025ECFC@@QAEXPAUBigIface0025ECFC@@@Z retail 0x0025ECFC 129
// bytes. Ten virtual out-param gets on iface slots 0x6C 0x60 0x70x6 0x90x2
// into this+4 through +0x2D. Evidence: callers 0x0025F240 and 0x0025F26B,
// no rowed callees only virtual slots, unblocks 0x0025F020.

struct BigIface0025ECFC
{
	virtual void f00(void *);
	virtual void f01(void *);
	virtual void f02(void *);
	virtual void f03(void *);
	virtual void f04(void *);
	virtual void f05(void *);
	virtual void f06(void *);
	virtual void f07(void *);
	virtual void f08(void *);
	virtual void f09(void *);
	virtual void f10(void *);
	virtual void f11(void *);
	virtual void f12(void *);
	virtual void f13(void *);
	virtual void f14(void *);
	virtual void f15(void *);
	virtual void f16(void *);
	virtual void f17(void *);
	virtual void f18(void *);
	virtual void f19(void *);
	virtual void f20(void *);
	virtual void f21(void *);
	virtual void f22(void *);
	virtual void f23(void *);
	virtual void f24(void *);
	virtual void f25(void *);
	virtual void f26(void *);
	virtual void f27(void *);
	virtual void f28(void *);
	virtual void f29(void *);
	virtual void f30(void *);
	virtual void f31(void *);
	virtual void f32(void *);
	virtual void f33(void *);
	virtual void f34(void *);
	virtual void f35(void *);
	virtual void f36(void *);
};

class Rva0025ECFC
{
public:
	void rva0025ECFC(BigIface0025ECFC *iface);
private:
	char m_00[4];
	int m_04;
	int m_08;
	char m_0C[0x14 - 0x0C];
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
};

void Rva0025ECFC::rva0025ECFC(BigIface0025ECFC *iface)
{
	iface->f27(&m_04);
	iface->f24(&m_08);
	iface->f28(&m_14);
	iface->f28(&m_18);
	iface->f28(&m_1C);
	iface->f28(&m_20);
	iface->f28(&m_24);
	iface->f28(&m_28);
	iface->f36(&m_2C);
	iface->f36(&m_2D);
}
