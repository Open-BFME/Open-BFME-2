// ?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABVUnicodeString@@@Z
// partial score=0.93 date=2026-10-07
// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc
#include "ascii_string.h"
#include "unicode_string.h"
template<> inline void StringBase<unsigned short>::concat(unsigned short character)
{ concat(&character, 1); }
class HotKeyManager
{
public:
	AsciiString searchHotKey( const UnicodeString& );
};

// ?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABVUnicodeString@@@Z
AsciiString HotKeyManager::searchHotKey( const UnicodeString& uStr )
{
	if (uStr.isEmpty())
		return AsciiString::TheEmptyString;

	const unsigned short *marker = uStr.str();
	while (marker && *marker)
	{
		if (*marker == L'&')
		{
			UnicodeString tmp = UnicodeString::TheEmptyString;
			tmp.StringBase<unsigned short>::concat(*(marker + 1));
			AsciiString retStr;
			retStr.translate( tmp );
			return retStr;
		}
		marker++;
	}
	return AsciiString::TheEmptyString;
}
