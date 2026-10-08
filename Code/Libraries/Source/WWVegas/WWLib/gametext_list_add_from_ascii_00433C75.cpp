// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Target evidence at 0x00433C75: empty ASCII input becomes TheNullChr; other
// input is fetched as Unicode through GameTextInterface slot 0x38. Both paths
// pass the result and clear flag to the verified 0x00433C18 list helper.
#include "ascii_string.h"
#include "unicode_string.h"

typedef unsigned short WideChar;

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
void Rva00433C18(const UnicodeString &value, bool clearFirst);

void Rva00433C75(const AsciiString &text, bool clearFirst)
{
	if (text.isEmpty())
	{
		UnicodeString converted((const WideChar *)L"");
		Rva00433C18(converted, clearFirst);
	}
	else
	{
		UnicodeString converted = TheGameText->fetch(text, 0);
		Rva00433C18(converted, clearFirst);
	}
}
