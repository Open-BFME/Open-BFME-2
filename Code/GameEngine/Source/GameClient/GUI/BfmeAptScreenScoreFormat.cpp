// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHs /O1 /arch:SSE /G7 -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// ?Rva0051CC8DFormat@@YA?AVAsciiString@@V1@@Z, RVA 0x0051CC8D, 249 bytes.
// Score-screen thousand-separator formatter: reverses decimal digits inserting
// GlobalLanguage+0x10 separator every 3 digits when all chars are digits.
// Evidence: callers 0x0051CFBA and 0x0051D04D pass score this plus formatted
// strings, callees getCharAt 0x00035720 concat 0x00006987 set 0x000366F0
// copy ctor 0x000365F0 releaseBuffer 0x00036410 operator=(char) 0x000065CA
// all rowed, TheGlobalLanguageData at 0x009FDC84, idiv-3 grouping logic.
#include "ascii_string.h"

class GlobalLanguage
{
public:
	char m_pad00[0x10];
	AsciiString m_sep010;
};

extern GlobalLanguage *TheGlobalLanguageData;

AsciiString __stdcall Rva0051CC8DFormat(AsciiString text)
{
	AsciiString acc;
	AsciiString single;
	bool allDigits = true;
	for (int i = 0; i < text.getLength(); ++i) {
		char c = text.getCharAt(text.getLength() - i - 1);
		if (c < '0' || c > '9')
			allDigits = false;
		single = c;
		if (i % 3 == 0 && i != 0 && allDigits)
			single += TheGlobalLanguageData->m_sep010;
		single += acc;
		acc.setCopyInline(single);
	}
	return acc;
}

// The caller at 0x0051D04D preserves its owner in ECX while invoking the
// grouping routine. This member view keeps that caller ABI; its body must be
// an exact code and relocation twin of the existing free-function row.
class Rva0051D009
{
public:
	AsciiString rva0051CC8DFormat(AsciiString text);
	AsciiString rva0051D009(int value);
};

AsciiString Rva0051D009::rva0051CC8DFormat(AsciiString text)
{
	AsciiString acc;
	AsciiString single;
	bool allDigits = true;
	for (int i = 0; i < text.getLength(); ++i) {
		char c = text.getCharAt(text.getLength() - i - 1);
		if (c < '0' || c > '9')
			allDigits = false;
		single = c;
		if (i % 3 == 0 && i != 0 && allDigits)
			single += TheGlobalLanguageData->m_sep010;
		single += acc;
		acc.setCopyInline(single);
	}
	return acc;
}

AsciiString Rva0051D009::rva0051D009(int value)
{
	AsciiString formatted;
	formatted.format("%d", value);
	return rva0051CC8DFormat(formatted);
}
