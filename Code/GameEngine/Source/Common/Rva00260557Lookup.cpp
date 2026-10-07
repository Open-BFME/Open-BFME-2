// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00260557Lookup@@YA_NPBDPAVUnicodeString@@@Z retail 0x00260557 120B
// Evidence: ref lane callback constant at 0x0004C5AC in Rva004C585 plus SUBTITLE literal plus TheGameText virtual 0x38 plus rowed StringBase callees; donor reference/open-bfme-1/game Rva00434A90 subtitle lookup.
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

bool Rva00260557Lookup(const char *label, UnicodeString *subtitle)
{
	AsciiString subtitleLabel("SUBTITLE:");
	bool exists;
	subtitleLabel += label;
	*subtitle = TheGameText->fetch(subtitleLabel, &exists);
	return exists;
}
