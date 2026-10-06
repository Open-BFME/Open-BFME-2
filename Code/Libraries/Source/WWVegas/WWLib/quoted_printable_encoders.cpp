// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// The two quoted-printable encoders as retail compiled them for BFME 2:
// UnicodeStringToQuotedPrintable (0x0053544C, 250 bytes) and
// AsciiStringToQuotedPrintable (0x00535546, 172 bytes). Bodies adapted from
// the Zero Hour donor (GameEngine/Source/Common/System/QuotedPrintable.cpp);
// unlike the decoders, the encoders kept the donor's i<1021 cap and the
// unrolled two-chars-per-iteration loop. Target facts: static array buffers
// (0xE04A00 / 0xE04E00), str() empty fallbacks, isalnum from msvcr71, and the
// EAX-passing intToHexDigit at 0x00535403. Split from quoted_printable.cpp
// because retail built these bodies with EH (fs:[0] frame) unlike the donor
// TU's flags.

#include <ctype.h>

#define MAGIC_CHAR '_'

#include "ascii_string.h"


// Retail tears the UnicodeString by-value parameter down through a bare
// releaseBuffer call (0x36E70), so the wide string carries an inline-empty
// base destructor here and routes its own destructor to releaseBuffer. The
// narrow instantiation above keeps the undefined destructor so the
// AsciiString parameter still tears down through 0x36410.

#include "unicode_string.h"

// Shared quoted-printable hex helper. Defined static exactly like the
// sibling TUs: MSVC passes the int in EAX and calls out of line, and the
// gate resolves that call to the landed global at 0x00535403.
static char intToHexDigit(int num)
{
	if (num<0 || num >15) return '\0';
	if (num<10)
	{
		return '0' + num;
	}
	return 'A' + (num-10);
}

// Convert unicode strings into ascii quoted-printable strings
AsciiString UnicodeStringToQuotedPrintable(UnicodeString original)
{
	static char dest[1024];
	const char *src = (const char *)original.str();
	int i=0;
	while ( !(src[0]=='\0' && src[1]=='\0') && i<1021 )
	{
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit(((unsigned char)*src)>>4);
			dest[i++] = intToHexDigit((*src)&0xf);
		} else
		{
			dest[i++] = *src;
		}
		src ++;
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit(((unsigned char)*src)>>4);
			dest[i++] = intToHexDigit((*src)&0xf);
		}
		else
		{
			dest[i++] = *src;
		}
		src ++;
	}
	dest[i] = '\0';

	return dest;
}

// Convert ascii strings into ascii quoted-printable strings
AsciiString AsciiStringToQuotedPrintable(AsciiString original)
{
	static char dest[1024];
	const char *src = (const char *)original.str();
	int i=0;
	while ( src[0]!='\0' && i<1021 )
	{
		if (!isalnum(*src))
		{
			dest[i++] = MAGIC_CHAR;
			dest[i++] = intToHexDigit(((unsigned char)*src)>>4);
			dest[i++] = intToHexDigit((*src)&0xf);
		} else
		{
			dest[i++] = *src;
		}
		src ++;
	}
	dest[i] = '\0';

	return dest;
}
