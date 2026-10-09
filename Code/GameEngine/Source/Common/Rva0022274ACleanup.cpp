// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD
// ?rva0022274A@Rva00062908Host@@QAEXXZ @0x0022274A 51B
// Target evidence: this+0xF0 bit 1 conditionally gates the rowed member call
// at 0x00222481. Three address-derived helpers follow, then the pointer global
// at 0x009FE4CC is zeroed and control tail-calls 0x006CDF60. The existing
// g_bfmeAptWindowManager view is provisional; this body proves only the
// nonzero check and reset, not the global's semantic identity.

class AptPlayer { public: bool UnloadLevel(int); };
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

#include "unicode_string.h"
struct RGBColor { float red, green, blue; };
class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};
extern Mouse *TheMouse;

class Rva00062908Host
{
protected:
	struct Slot
	{
		char m_pad[0x24];
		unsigned char m_flags;
		char m_tail[3];
	};

	char m_pad[0xCC];
	Slot m_slots[14];

public:
	void rva0022274A();
};

void Rva00062908Host::rva0022274A()
{
	if (g_bfmeAptWindowManager == 0)
		return;
	if ((m_slots[0].m_flags & 2) != 0)
		reinterpret_cast<AptPlayer *>(this)->UnloadLevel(0);
	Rva006CFAB0(1);
	Rva00411B52();
	reinterpret_cast<unsigned int &>(g_bfmeAptWindowManager) &= 0;
	Rva006CDF60();
}
