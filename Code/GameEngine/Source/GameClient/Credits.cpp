// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii
// BFME1 clean donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f:
// game/GameEngine/Source/GameClient/CreditsGetUnicodeString.cpp, over ZH Credits.cpp.
// Retail 0x005B76AC..0x005B776E, 194 bytes, RET8 with hidden UnicodeString result.
// Named CreditsManager::addText (WB 0x01581450) calls this helper just as the
// reference addText does. The <BLANK> test, colon search, localization and
// literal translation establish the same helper purpose independently of bytes.
// BFME2's TheGameText at VA 0x00DFF0BC uses slot 14 and a const AsciiString
// reference here; the donor used slot 9 and a by-value parameter. Canonical
// BFME2 string headers preserve the actual one-pointer ABI and cleanup calls.

#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class CreditsManager
{
	UnicodeString getUnicodeString(AsciiString str);
};

UnicodeString CreditsManager::getUnicodeString(AsciiString str)
{
	UnicodeString uStr;
	if (str.compare("<BLANK>") == 0)
		return UnicodeString::TheEmptyString;

	if (str.find(':'))
		uStr = TheGameText->fetch(str);
	else
		uStr.translate(str);

	return uStr;
}


