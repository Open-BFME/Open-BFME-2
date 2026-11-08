// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z, retail 0x0026F28B, 325 bytes. Parses
// space-separated upgrade names from the INI stream into a 0x80-byte mask.
#include "ascii_string.h"
#include <string.h>


__forceinline const char *GetStr0026F28B(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/Upgrade.h"


extern UpgradeCenter *TheUpgradeCenter;

void Rva0026F28BParse(INI *ini, void *instance, unsigned int *mask)
{
	(void)instance;
	memset(mask, 0, 0x80);
	bool substituted;
	const char *first = ini->rva0002E03D(0, &substituted);
	if (first == 0)
		return;
	AsciiString expanded(first);
	while (1) {
		AsciiString token;
		unsigned char fetchNext;
		if (substituted) {
			fetchNext = !expanded.nextToken(&token, 0);
		} else {
			((StringBase<char> *)&token)->set(*(const StringBase<char> *)&expanded);
			fetchNext = 1;
		}
		if (!token.isEmpty()) {
			const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(token);
			if (upgrade == 0 && !token.isNone()) {
				throw INIException(3, "An upgrade mask references %s, which is not an Upgrade", GetStr0026F28B(token));
			}
			unsigned int bit = upgrade->field38;
			mask[bit >> 5] |= 1u << (bit & 31);
		}
		if (!fetchNext)
			continue;
		const char *next = ini->rva0002E03D(0, &substituted);
		if (next == 0)
			break;
		expanded = next;
	}
}
