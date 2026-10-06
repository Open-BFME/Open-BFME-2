// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002DAE51@Rva002DAE51@@QAEXVAsciiString@@@Z retail 0x002DAE51 52 bytes.
// AsciiString by-value setter into member at +0x40 via rowed set 0x000366F0,
// by-value copy destroyed via rowed releaseBuffer 0x00036410, EH prolog via
// rowed __EH_prolog 0x00629188. Twin of Rva002DAE1DSet.cpp (52B at +0x4c).
// Evidence: add ecx,0x40 plus lea/push plus set/releaseBuffer shape plus
// caller at 0x002DB758 in 0x002DB64E plus same EH data VA 0x00B77D8E.
class AsciiString;
#include "ascii_string.h"
class Rva002DAE51
{
public:
	void rva002DAE51(AsciiString s);
private:
	char _00[0x40];
	AsciiString m_40;
};
void Rva002DAE51::rva002DAE51(AsciiString s)
{
	AsciiString &slot = m_40;
	slot = s;
}
