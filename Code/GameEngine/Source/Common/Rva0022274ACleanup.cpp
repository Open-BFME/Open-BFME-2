// cl: /O1 /DNDEBUG /EHsc /MD
// ?rva0022274A@Rva00062908Host@@QAEXXZ @0x0022274A 51B
// ?rva00222481@Rva00062908Host@@QAE_NH@Z @0x00222481 93B
// Target evidence: this+0xF0 bit 1 conditionally gates the rowed member call
// at 0x00222481. Three address-derived helpers follow, then the pointer global
// at 0x009FE4CC is zeroed and control tail-calls 0x006CDF60. The existing
// g_bfmeAptWindowManager view is provisional; this body proves only the
// nonzero check and reset, not the global's semantic identity.

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

void Rva006CFAB0(int value);
void Rva00411B52();
void Rva006CDF60();
void Rva006CC600(const char *first, char *second);
void Rva00411E80(int value);

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
// Retail calls the IAT slot directly rather than the CRT import thunk.
#pragma function(sprintf)

class Rva00062908Host
{
	struct Slot
	{
		char m_pad[0x24];
		unsigned char m_flags;
		char m_tail[3];
	};

	char m_pad[0xCC];
	Slot m_slots[14];

public:
	bool rva00222481(int index);
	void rva0022274A();
};

bool Rva00062908Host::rva00222481(int index)
{
	if ((unsigned int)index >= 14)
		return false;
	Slot &slot = m_slots[index];
	if ((slot.m_flags & 2) == 0)
		return false;
	char key[32];
	sprintf(key, "_level%d", index);
	Rva006CC600("", key);
	slot.m_flags &= 0xF5;
	Rva00411E80(index);
	return true;
}

void Rva00062908Host::rva0022274A()
{
	if (g_bfmeAptWindowManager == 0)
		return;
	if ((m_slots[0].m_flags & 2) != 0)
		rva00222481(0);
	Rva006CFAB0(1);
	Rva00411B52();
	reinterpret_cast<unsigned int &>(g_bfmeAptWindowManager) &= 0;
	Rva006CDF60();
}
