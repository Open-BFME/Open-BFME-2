// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /G7
// ?rva00219251@Rva00219251@@QAEPAVCreateAHeroData@@HHHABVUnicodeString@@HHH@Z @0x00219251 76B
// Honest-address thiscall factory: new CreateAHeroData with 7 args returns pointer.
// Evidence: retail push 0x140 plus null-checked ctor ??0CreateAHeroData@@QAE@HHHABVUnicodeString@@HHH@Z pin-only and ret 0x1c for 7 stack args and caller 0x005B2768 passes 0 0 0 EmptyString -1 0xff707070 -1 and uses eax.
#include "unicode_string.h"

class CreateAHeroData
{
public:
	CreateAHeroData(int, int, int, const UnicodeString &, int, int, int);
private:
	unsigned char m_pad[0x140];
};

class Rva00219251
{
public:
	CreateAHeroData *rva00219251(int, int, int, const UnicodeString &, int, int, int);
};

CreateAHeroData *Rva00219251::rva00219251(int a1, int a2, int a3, const UnicodeString &a4, int a5, int a6, int a7)
{
	return new CreateAHeroData(a1, a2, a3, a4, a5, a6, a7);
}
