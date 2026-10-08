// ??0Rva0030AFC4Base@@QAE@XZ
// partial score=0.85 date=2026-10-08
// cl: /O2 /MD /EHsc
// ??0Rva0030AFC4Base@@QAE@XZ @0x0030AFC4 55B: derived-class constructor. It calls
// the SubsystemInterface base constructor at 0x001B4E63 first, then installs its
// own vtable (0x00BC8318) and clears the scalar and float fields at +0x0C..+0x44.
// Its only caller in the ledger is the product constructor at 0x00098667, which
// names this as its base constructor. Address-derived name kept honest: the
// product's name is proven by its factory, the base class name is not.
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	int m_04;
	int m_08;
};

class Rva0030AFC4Base : public SubsystemInterface
{
public:
	Rva0030AFC4Base();
	virtual ~Rva0030AFC4Base();

private:
	int m_0C;
	int m_10;
	char m_pad14[0x30 - 0x14];
	int m_30;
	float m_34;
	float m_38;
	int m_3C;
	float m_40;
	float m_44;
};

Rva0030AFC4Base::Rva0030AFC4Base() : SubsystemInterface(), m_0C(0), m_10(0), m_30(0), m_34(0.0f), m_38(0.0f), m_3C(0), m_40(0.0f), m_44(0.0f)
{
}
