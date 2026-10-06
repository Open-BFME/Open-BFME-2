// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva002765D4@Drawable@@QAE_NPAVUnicodeString@@@Z, retail 0x002765D4, 109 bytes.
// Drawable wide-label fetch via rowed 0x00274C62 Ascii slot plus TheGameText
// slot 0x38 Ascii fetch plus rowed wide set. Evidence: caller 0x00377378 and
// 0x0048AD15; callee 0x00274C62 row; TheGameText 0x009FF0BC; slots from
// Rva0020E89CFetch GameTextInterface; neighbours 0x0027656F and 0x002768AC.
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

class Drawable
{
public:
	bool rva00274C62(AsciiString *dst);
	bool rva002765D4(UnicodeString *dst);
};

bool Drawable::rva002765D4(UnicodeString *dst)
{
	AsciiString label;
	if (rva00274C62(&label)) {
		dst->set(TheGameText->fetch(label));
		return true;
	}
	return false;
}
