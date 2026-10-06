// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002DAEB9@Rva002DAEB9@@QAEXVAsciiString@@@Z retail 0x002DAEB9 52 bytes.
// AsciiString by-value setter into member at +0x50 via rowed set 0x000366F0,
// by-value copy destroyed via rowed releaseBuffer 0x00036410, EH prolog via
// rowed __EH_prolog 0x00629188. Twin of Rva002DAE51Set.cpp (52B at +0x40).
// Evidence: add ecx,0x50 plus lea/push plus set/releaseBuffer shape plus
// caller at 0x002DB782 in 0x002DB64E plus same EH data VA 0x00B77D8E.
class AsciiString;
#include "ascii_string.h"
class Rva002DAEB9
{
public:
	void rva002DAEB9(AsciiString s);
private:
	char _00[0x50];
	AsciiString m_50;
};
void Rva002DAEB9::rva002DAEB9(AsciiString s)
{
	AsciiString &slot = m_50;
	slot = s;
}
