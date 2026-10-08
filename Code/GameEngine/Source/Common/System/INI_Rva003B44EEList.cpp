// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// ?rva003B5624@Rva003B44EE@@QAEXVAsciiString@@@Z @0x003B5624 129B list-form bitstring parser driving single-token worker 0x003B44EE per nextToken.
// Evidence: calls rowed nextToken 0x00036D90 and rowed rva003B44EE 0x003B44EE; empty fallback g_Rva0107301CEmptyString; caller 0x003B596A builds by-value AsciiString arg.
#include "ascii_string.h"


class Rva003B44EE
{
public:
	bool rva003B44EE(const char *token, bool *foundNormal, bool *foundAddOrSub);
	void rva003B5624(AsciiString text);
};

void Rva003B44EE::rva003B5624(AsciiString text)
{
	bool foundNormal = false;
	bool foundAddOrSub = false;
	AsciiString token;
	while (text.nextToken(&token, (const char *)0))
	{
		char *raw = *(char **)&token;
		const char *s = raw ? raw + 8 : "";
		if (!rva003B44EE(s, &foundNormal, &foundAddOrSub))
			break;
	}
}
