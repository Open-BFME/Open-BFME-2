// ?rva00132D0F@Rva00132D0FHolder@@QAE_NXZ
// partial score=0.99 date=2026-10-06
// ?rva00132D0F@Rva00132D0FHolder@@QAE_NXZ
// partial score=0.85 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva00132D0F@Rva00132D0FHolder@@QAEHXZ @0x00132D0F 52B bool.
// Retail (this=esi, no args): m=[esi]; if (m && m->slot17()) return true;
// if (this->rva0013275A()==1 && this->rva00132784()==1) return true;
// return false. Slot 0x44 (index 17) via 18-virtual iface; helpers via pins.
// Names opaque; pins prove nothing.
class Rva00132D0FIface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual bool slot17();
};

class Rva00132D0FHolder
{
public:
	bool rva00132D0F(void);
	int rva0013275A(void);
	int rva00132784(void);
private:
	Rva00132D0FIface *m_00; // +0x00
};

bool Rva00132D0FHolder::rva00132D0F(void)
{
	if (m_00 && m_00->slot17())
		return true;
	return rva0013275A() == 1 && rva00132784() == 1;
}
