// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?RemoveOverButtonHandler@AptPlayer@@QAEXABVAsciiString@@@Z @0x0022453E 70B
// Erase-all wrapper with local AsciiString copy over the rowed Rva00223591 table at +0xa4.
// Evidence: chain packet calls rowed 0x00223736 erase-all plus rowed StringBase copy 0x000365F0 plus rowed releaseBuffer 0x00036410 with EH prolog; copy reuses param slot at [ebp+8] with esi-saved this.
#include "ascii_string.h"

class Rva00223591
{
public:
	int rva00223736(const AsciiString *key);
};

class AptPlayer
{
public:
	void RemoveOverButtonHandler(const AsciiString &key);
private:
	char m_pad[0xa4];
	Rva00223591 m_table;
};

void AptPlayer::RemoveOverButtonHandler(const AsciiString &key)
{
	AsciiString tmp(key);
	m_table.rva00223736(&tmp);
}
