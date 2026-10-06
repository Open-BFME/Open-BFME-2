// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002DAD81@Rva002DAD81@@QAEXVAsciiString@@@Z retail 0x002DAD81 52 bytes.
// AsciiString by-value setter into member at +0x34 via rowed set 0x000366F0,
// by-value copy destroyed via rowed releaseBuffer 0x00036410, EH prolog via
// rowed __EH_prolog 0x00629188. Twin of Rva002DAD4DSet.cpp (52B at +0x38).
// Evidence: add ecx,0x34 plus lea/push plus set/releaseBuffer shape plus
// caller at 0x002DB704 in 0x002DB64E plus prev 0x002DAD4D O1 EHsc flags.
class AsciiString;
#include "ascii_string.h"
class Rva002DAD81
{
public:
	void rva002DAD81(AsciiString s);
private:
	char _00[0x34];
	AsciiString m_34;
};
void Rva002DAD81::rva002DAD81(AsciiString s)
{
	AsciiString &slot = m_34;
	slot = s;
}
