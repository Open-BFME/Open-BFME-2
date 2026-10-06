// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002DADB5@Rva002DADB5@@QAEXVAsciiString@@@Z retail 0x002DADB5 52 bytes.
// AsciiString by-value setter into member at +0x3c via rowed set 0x000366F0,
// by-value copy destroyed via rowed releaseBuffer 0x00036410, EH prolog via
// rowed __EH_prolog 0x00629188. Twin of Rva002DAD81Set.cpp (52B at +0x34).
// Evidence: add ecx,0x3c plus lea/push plus set/releaseBuffer shape plus
// caller at 0x002DB719 in 0x002DB64E plus prev 0x002DAD81 O1 EHsc flags.
class AsciiString;
#include "ascii_string.h"
class Rva002DADB5
{
public:
	void rva002DADB5(AsciiString s);
private:
	char _00[0x3c];
	AsciiString m_3c;
};
void Rva002DADB5::rva002DADB5(AsciiString s)
{
	AsciiString &slot = m_3c;
	slot = s;
}
