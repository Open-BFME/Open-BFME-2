// cl: /EHsc /MD
// ??0Rva00091A80@@QAE@XZ @0x00091A80 44B: dual-vptr ctor over Rva002DAB18 base plus 3 ints and byte zeroed then global W3DGCData00DE2000 cleared.
// Evidence: calls rowed ??0Rva002DAB18@@QAE@XZ 0x002DAB18; vtables 0xBC80A0 0xBC8068 filled by gate; global 0xDE2000 extern W3DGCData00DE2000; caller 0x0004C5E7 new 0x24.
class SnapBase
{
public:
	virtual void keep();
	virtual ~SnapBase();
};
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
private:
	char m_pad04[8];
};
struct IntZero
{
	int m_value;
	IntZero() : m_value(0) {}
};
class Rva002DAB18 : public SnapBase, public SubsystemInterface
{
public:
	Rva002DAB18();
	virtual ~Rva002DAB18();
private:
	IntZero m_10;
};

extern void *W3DGCData00DE2000;

class Rva00091A80 : public Rva002DAB18
{
public:
	Rva00091A80();
private:
	int m_14;
	int m_18;
	int m_1c;
	unsigned char m_20;
};

Rva00091A80::Rva00091A80() : m_14(0), m_18(0), m_1c(0), m_20(0)
{
	W3DGCData00DE2000 = 0;
}
