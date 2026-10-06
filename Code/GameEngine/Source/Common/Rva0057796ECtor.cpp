// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ??0Rva0057796E@@QAE@HHABVAsciiString@@@Z @0x0057796E 42B
// Evidence: all callees rowed (StringBase copy 0x000365F0); caller 0x00577E26 needs this ctor;
// layout +0 int +4 int +8 AsciiString +C int +10 int from retail stores and 0x14 alloc.
#include "ascii_string.h"

class Rva0057796E
{
public:
	Rva0057796E(int a1, int a2, const AsciiString &a3);
private:
	int m_00;
	int m_04;
	AsciiString m_08;
	int m_0C;
	int m_10;
};

Rva0057796E::Rva0057796E(int a1, int a2, const AsciiString &a3)
	: m_00(a1), m_04(a2), m_08(a3), m_0C(0), m_10(0)
{
}
