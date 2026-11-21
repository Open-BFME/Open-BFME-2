// cl: /DNDEBUG /MD
// ??0Made002CCBCA@@QAE@XZ, retail 0x0050B8B3, 35 bytes.
// Evidence: pin ??0Made002CCBCA@@QAE@XZ; rowed base Rva00507823 0x0050775B;
// vtable 0x00864DFC plus byte +0x128=0 plus dword +0x12c=5; caller
// parseHordeAttackNugget 0x002CCBEF; Made002CC5E1Ctor precedent for base+members.
// Table 0x00864DFC: the slots the override set below names are defined in
// Made002CCBCA.cpp (1, 5, 6) or fold into shared bodies (2, 7, 8).
#include "../../../Include/GameLogic/Module/Rva00507823.h"

class Made002CCBCA : public Rva00507823
{
public:
	Made002CCBCA();
	virtual unsigned char rva005075D6(const void *a, Object *source);
	virtual unsigned char vslot02(const void *a, int b) { return Rva00507823::rva0050774A(a, b) ? true : false; }
	virtual void vslot05(const void *a, void *value);
	virtual void vslot06(const void *a, void *value);
	virtual bool vslot07() { return false; }
	virtual void rva00507877() { Rva00507823::rva00507877(); }
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
