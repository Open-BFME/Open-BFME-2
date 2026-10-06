// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00517048@Rva00517048@@QAEXABVUnicodeString@@@Z @0x00517048 108B
// Chat login APT text plus ChatMessageOpen invoke. AsciiString temp from
// "APT:ChatFriendLogInMessage" via rowed 0x00037BA0; bfmeSetText via pin
// 0x00225301 with false; releaseBuffer via rowed 0x00036410; invoke via pin
// 0x00222A8B with owner at +0x274; global 0x009FE4CC; caller 0x004161F1.
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

#define TheMgr00517048 g_bfmeAptWindowManager
#define TheTgt00517048 (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)

struct Rva00517048
{
	char m_pad[0x274];
	void *m_274Owner;
	void rva00517048(const UnicodeString &text);
};

void Rva00517048::rva00517048(const UnicodeString &text)
{
	{
		AsciiString key("APT:ChatFriendLogInMessage");
		TheMgr00517048->bfmeSetText(key, text, false);
	}
	TheTgt00517048->invoke(m_274Owner, "ChatMessageOpen", 0, 0, 0, 0, 0, 0);
}
