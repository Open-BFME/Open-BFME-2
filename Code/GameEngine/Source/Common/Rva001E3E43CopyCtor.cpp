// cl: /MD /EHsc
//
// ??0Rva001E3E43@@QAE@ABV0@@Z, retail 0x001E4641, 78 bytes.
// Copy ctor: default-constructs 3x0x10 Region3D array at +0x68 via rowed
// vector iterator then stores vtable 0x00BDE888 plus inc global 0x009FDC64
// plus rowed copy assignment 0x001E3CF4.
// Evidence: chain lane calls rowed 0x001E3CF4 plus prev Rva001E3E43Dtor
// plus next Rva001E468FCheck plus EH prolog plus Region3D ctor 0x0047A6A9.
//
extern int g_Va00DFDC64;

class Region3D
{
public:
	Region3D();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

class Rva001E3E43 : public Snapshot
{
public:
	Rva001E3E43(const Rva001E3E43 &rhs);
	Rva001E3E43 &operator=(const Rva001E3E43 &rhs);
private:
	int m_04;
	struct Vec12 { int a, b, c; } m_08, m_14;
	int m_20, m_24, m_28, m_2C;
	int m_30, m_34, m_38, m_3C, m_40, m_44, m_48, m_4C;
	int m_50, m_54, m_58, m_5C, m_60, m_64;
	Region3D m_68[3];
	unsigned char m_98, m_99, m_9A;
	int m_9C, m_A0, m_A4, m_A8, m_AC;
};

Rva001E3E43::Rva001E3E43(const Rva001E3E43 &rhs)
{
	++g_Va00DFDC64;
	*this = rhs;
}
