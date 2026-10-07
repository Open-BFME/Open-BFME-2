// cl: /O1 /DNDEBUG /EHsc /MD
// ?rva0022274A@Rva00062908Host@@QAEXXZ @0x0022274A 51B
// Target evidence: this+0xF0 bit 1 conditionally gates the rowed member call
// at 0x00222481. Three address-derived helpers follow, then the pointer global
// at 0x009FE4CC is zeroed and control tail-calls 0x006CDF60. The existing
// g_bfmeAptWindowManager view is provisional; this body proves only the
// nonzero check and reset, not the global's semantic identity.

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00222481Target
{
public:
	void rva00222481(int value);
};

void Rva006CFAB0(int value);
void Rva00411B52();
void Rva006CDF60();

class Rva00062908Host
{
	char m_pad[0xF0];
	unsigned char m_flags;

public:
	void rva0022274A();
};

void Rva00062908Host::rva0022274A()
{
	if (g_bfmeAptWindowManager == 0)
		return;
	if ((m_flags & 2) != 0)
		((Rva00222481Target *)this)->rva00222481(0);
	Rva006CFAB0(1);
	Rva00411B52();
	reinterpret_cast<unsigned int &>(g_bfmeAptWindowManager) &= 0;
	Rva006CDF60();
}
