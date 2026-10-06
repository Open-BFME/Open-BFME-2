// cl: /DNDEBUG /MD
//
// ??0Made002CCB67@@QAE@XZ retail 0x0050B6B4 29B
// Evidence: pin ??0Made002CCB67; callee base Rva00507823 0x0050775B;
// caller parseStealMoneyNugget 0x002CCB8C; prev Made002CCB67Parse same
// /O1 DNDEBUG MD plus arch:SSE for xorps float zero; vtable 0x00864D80
// plus float at +0x128 zero same shape as Made002CCAA1 0x0050B374.
class Rva00507823
{
public:
	Rva00507823();
	virtual void __pad();
private:
	char m_pad[0x128 - 4];
};

class Made002CCB67 : public Rva00507823
{
public:
	Made002CCB67();
private:
	float m_128;
};

Made002CCB67::Made002CCB67()
{
	m_128 = 0.0f;
}
