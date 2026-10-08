// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z, retail 0x0026F28B, 325 bytes. Parses
// space-separated upgrade names from the INI stream into a 0x80-byte mask.
#include "ascii_string.h"
#include <string.h>


__forceinline const char *GetStr0026F28B(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class INI
{
public:
	const char *rva0002E03D(const char *seps, bool *substituted);
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

typedef int NameKeyType;

class UpgradeTemplate
{
public:
	NameKeyType getUpgradeNameKey() const { return m_nameKey; }
	int getMaskIndex() const { return m_maskIndex; }
	const UpgradeTemplate *friend_getNext() const { return m_next; }
private:
	unsigned char m_pad00[0x0C];
	NameKeyType m_nameKey;
	unsigned char m_pad10[0x38 - 0x10];
	int m_maskIndex;
	unsigned char m_pad3C[0x64 - 0x3C];
	UpgradeTemplate *m_next;
	UpgradeTemplate *m_prev;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

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
			unsigned int bit = (unsigned int)upgrade->getMaskIndex();
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
