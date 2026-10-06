// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002DAD4D@Rva002DAD4D@@QAEXVAsciiString@@@Z retail 0x002DAD4D 52 bytes.
// AsciiString by-value setter into member at +0x38 via rowed set 0x000366F0,
// by-value copy destroyed via rowed releaseBuffer 0x00036410, EH prolog via
// rowed __EH_prolog 0x00629188. Twin of Rva0032A438Set.cpp (52B at +0x04).
// Evidence: add ecx,0x38 plus lea/push plus set/releaseBuffer shape plus
// callers at 0x002DB60D and 0x002DB6E5 plus prev/next O1 EHsc flags.
class AsciiString;
#include "ascii_string.h"
class Rva002DAD4D
{
public:
	void rva002DAD4D(AsciiString s);
private:
	char _00[0x38];
	AsciiString m_38;
};
void Rva002DAD4D::rva002DAD4D(AsciiString s)
{
	AsciiString &slot = m_38;
	slot = s;
}
