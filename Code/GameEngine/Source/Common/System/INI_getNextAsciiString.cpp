// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?getNextAsciiString@INI@@QAE?AVAsciiString@@XZ,
// retail 0x0002EA4F, 232 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp,
// INI::getNextAsciiString): quoted-aware token reader with a static line
// buffer. The retail body follows the reference source: a null token leaves
// the result empty, an unquoted token assigns directly, and a quoted token
// accumulates through the quote-separator stream with space joins and a
// trailing-quote strip. The BFME2 deltas are the separator members sitting
// at this+0x418/+0x424 (reference header order m_seps..m_sepsQuote holds),
// the AsciiString return through the protected StringBase copy (0x365F0
// pin), and temp teardown through the folded releaseBuffer (0x36410 pin).

typedef int Int;

#define NULL 0

extern "C" unsigned int strlen(const char *s);
extern "C" char *_mbscpy(char *dst, const char *src);
// Retail calls MSVCR71 _mbscat here (thunk 0x0062988C), not strcat.
extern "C" char *__cdecl _mbscat(char *dest, const char *source);

#include "ascii_string.h"


class INI
{
public:
	AsciiString getNextAsciiString();
	const char *getNextTokenOrNull(const char *seps);
	const char *getSepsQuote() { return m_sepsQuote; }

private:
	char _pad[0x418];
	const char *m_seps; // +0x418
	const char *m_sepsPercent; // +0x41C
	const char *m_sepsColon; // +0x420
	const char *m_sepsQuote; // +0x424
};

// ?getNextAsciiString@INI@@QAE?AVAsciiString@@XZ
AsciiString INI::getNextAsciiString()
{
	AsciiString result;

	const char *token = getNextTokenOrNull(NULL); // if null, just leave an empty string
	if (token != NULL)
	{
		if (token[0] != '\"')
		{
			// if token is simply "
			result.set(token); // Start following the "
		}
		else
		{
			static char buff[1028];
			buff[0] = 0;
			if (strlen(token) > 1)
			{
				_mbscpy(buff, &token[1]);
			}

			token = getNextTokenOrNull(getSepsQuote());
			if (token) {
				if (strlen(token) > 1 && token[1] != '\t')
				{
					_mbscat(buff, " ");
				}
				_mbscat(buff, token);
				result.set(buff);
			} else {
				Int len = strlen(buff);
				if (len && buff[len-1] == '"') { // strip off trailing quote jba. [2/12/2003]
					buff[len-1] = 0;
				}
				result.set(buff);
			}
		}
	}
	return result;
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_strcat=?ji_0062988c@@YAXXZ")
