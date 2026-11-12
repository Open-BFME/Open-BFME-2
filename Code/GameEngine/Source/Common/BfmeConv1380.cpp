// Open-BFME5 conversions.

class BfmeMsgVIX
{
public:
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

#include "../../Include/GameNetwork/Rva007E8810Message.h"

extern void *g_bfmeFVIX;
// g_bfmeFVIX: matched references place it at VA 0xe09ec8 (zero-filled .bss).
void * g_bfmeFVIX;
extern void *g_bfmeGVIY;
// g_bfmeGVIY: matched references place it at VA 0xe0a028 (zero-filled .bss).
void * g_bfmeGVIY;

void __stdcall bfmeGoVIX(BfmeMsgVIX *message, void *email, void *parentalEmail, void *countryCode, void *eaMail, void *thirdPartyMail)
{
	void *transactionName = g_bfmeFVIX;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x61636374;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addString("email", (const char *)email);
	((Rva007E8810Message *)message)->addString("parentalEmail", (const char *)parentalEmail);
	((Rva007E8810Message *)message)->addString("countryCode", (const char *)countryCode);
	((Rva007E8810Message *)message)->addBool("eaMailFlag", *(bool *)&eaMail);
	((Rva007E8810Message *)message)->addBool("thirdPartyMailFlag", *(bool *)&thirdPartyMail);
}

class BfmeThingVIY
{
public:
	void bfmeGoVIY(BfmeMsgVIX *message, void *blobIdLowWord, void *blobIdHighWord, void *blobData, void *blobSize, void *version);
	void bfmeSubVIY(BfmeMsgVIX *message, void *blobData, void *blobSize);
};

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate(int size, int flags);
	virtual void release(void *block, int flags);
};

struct Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void v1();
	virtual void __cdecl assertValue(void *value, const char *message);
	virtual void fail(const char *expr, const char *file, int line);
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *one, void *two);
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

extern Rva007EB810Diag *Rva007EB810Get();
class GenAlloc;
GenAlloc *Gen007EFFC0();
void rva007FF100Encode(unsigned int length, const char *source, void *destination);

void BfmeThingVIY::bfmeGoVIY(BfmeMsgVIX *message, void *blobIdLowWord, void *blobIdHighWord, void *blobData, void *blobSize, void *version)
{
	void *transactionName = g_bfmeGVIY;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addInt64("blobId", *(__int64 *)&blobIdLowWord);
	bfmeSubVIY(message, blobData, blobSize);
	((Rva007E8810Message *)message)->addString("version", (const char *)version);
}

void BfmeThingVIY::bfmeSubVIY(BfmeMsgVIX *message, void *blobData, void *blobSize)
{
	Rva007EFFC0Allocator *allocator = (Rva007EFFC0Allocator *)Gen007EFFC0();
	unsigned int length = (unsigned int)blobSize;
	unsigned int size = ((length + 2) / 3) * 4 + 1;
	void *content = allocator->allocate(size, 2);
	if (content == 0)
	{
		Rva007EB810Diag *diag = Rva007EB810Get();
		diag->assertValue(content, "--- out of memory\n");
		Rva007EB810Get()->fail("false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\blobservice.cpp",
			0x17c);
		return;
	}
	rva007FF100Encode(length, (const char *)blobData, content);
	((Rva007E8810Message *)message)->rva007E8EF0("content", (const char *)content);
	((Rva007EFFC0Allocator *)Gen007EFFC0())->release(content, 0);
	((BfmeThingCIB *)message)->bfmeGoCIB((void *)"size", blobSize);
}
