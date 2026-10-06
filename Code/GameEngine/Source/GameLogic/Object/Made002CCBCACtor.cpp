// cl: /DNDEBUG /MD
// ??0Made002CCBCA@@QAE@XZ, retail 0x0050B8B3, 35 bytes.
// Evidence: pin ??0Made002CCBCA@@QAE@XZ; rowed base Rva00507823 0x0050775B;
// vtable 0x00864DFC plus byte +0x128=0 plus dword +0x12c=5; caller
// parseHordeAttackNugget 0x002CCBEF; Made002CC5E1Ctor precedent for base+members.
class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	char m_pad04[0x128 - 4];
};

class Made002CCBCA : public Rva00507823
{
public:
	Made002CCBCA();
private:
	unsigned char m_128;
	char m_pad129[3];
	int m_12c;
};

Made002CCBCA::Made002CCBCA()
	: m_128(0)
	, m_12c(5)
{
}
