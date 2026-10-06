// cl: /DNDEBUG /MD
//
// ??0Made002CCAA1@@QAE@XZ retail 0x0050B374 29B
// Evidence: pin ??0Made002CCAA1; callee base Rva00507823 0x0050775B;
// caller parseOpenGateNugget 0x002CCAC6; prev Made002CCAA1Parse same
// /O1 DNDEBUG MD plus arch:SSE for xorps float zero; vtable 0x00864C94
// plus float at +0x128 zero.
class Rva00507823
{
public:
	Rva00507823();
	virtual void __pad();
private:
	char m_pad[0x128 - 4];
};

class Made002CCAA1 : public Rva00507823
{
public:
	Made002CCAA1();
private:
	float m_128;
};

Made002CCAA1::Made002CCAA1()
{
	m_128 = 0.0f;
}
