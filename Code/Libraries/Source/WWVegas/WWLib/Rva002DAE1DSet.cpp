// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002DAE1D@Rva002DAE1D@@QAEXVAsciiString@@@Z retail 0x002DAE1D 52 bytes.
// AsciiString by-value setter into member at +0x4c via rowed set 0x000366F0,
// by-value copy destroyed via rowed releaseBuffer 0x00036410, EH prolog via
// rowed __EH_prolog 0x00629188. Twin of Rva002DADB5Set.cpp (52B at +0x3c).
// Evidence: add ecx,0x4c plus lea/push plus set/releaseBuffer shape plus
// caller at 0x002DB743 in 0x002DB64E plus same EH data VA 0x00B77D8E.
class AsciiString;
#include "ascii_string.h"
class Rva002DAE1D
{
public:
	void rva002DAE1D(AsciiString s);
private:
	char _00[0x4c];
	AsciiString m_4c;
};
void Rva002DAE1D::rva002DAE1D(AsciiString s)
{
	AsciiString &slot = m_4c;
	slot = s;
}
