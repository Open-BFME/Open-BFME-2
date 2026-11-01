// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Target evidence at 0x00433C75: empty ASCII input becomes TheNullChr; other
// input is fetched as Unicode through GameTextInterface slot 0x38. Both paths
// pass the result and clear flag to the verified 0x00433C18 list helper.
#include "ascii_string.h"
#include "unicode_string.h"

typedef unsigned short WideChar;

#include "../../../../GameEngine/Include/GameClient/GameText.h"

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
