// BFME1 byte-identical donor: reference/open-bfme-1/Code/GameEngine/Source/Common/BfmeConv1378.cpp
// Trimmed to the bodies that reproduce game.dat bytes. bfmeGoVIT is retail
// 0x656800: the EVIW twin's Run-plus-three-setters shape, but all three
// setters are bfmeSetVIT and the words are TXN/password/newPassword (EVIW at
// 0x6569E0 uses Set/Set4/Set4 with TXN/eaMailFlag/thirdPartyMailFlag).
// bfmeGoVIU's bytes ARE claimed: the five lotrbfme.exe fold-twins
// collapse to one pick by call-arity -- retail 0x65F250 ends `ret 0x10`
// (4 args: msg + 3 void*), which fits only ?bfmeGoVIU@@YGXPAVFeslMessage@@PAX11@Z;
// the bfmeSetupPair twins take (record*, int) and Rva007F2B70 takes 7 args.

class FeslMessage
{
public:
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

#include "../../Include/GameNetwork/Rva007E8810Message.h"

extern void *g_bfmeVIT;
// g_bfmeVIT: matched references place it at VA 0xe09f7c (zero-filled .bss).
void * g_bfmeVIT;
extern void *g_bfmeVIV;
// g_bfmeVIV: matched references place it at VA 0xe09f4c (zero-filled .bss).
void * g_bfmeVIV;
extern void *g_bfmeVIU;
// g_bfmeVIU: matched references place it at VA 0xe0a07c (zero-filled .bss).
void * g_bfmeVIU;

void __stdcall bfmeGoVIT(FeslMessage *message, void *password, void *newPassword)
{
	void *transactionName = g_bfmeVIT;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x61636374;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addString("password", (const char *)password);
	((Rva007E8810Message *)message)->addString("newPassword", (const char *)newPassword);
}

void __stdcall bfmeGoVIU(FeslMessage *message, void *sessionId, void *key, void *value)
{
	void *transactionName = g_bfmeVIU;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x72616e6b;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addString("sessionId", (const char *)sessionId);
	((Rva007E8810Message *)message)->addString("key", (const char *)key);
	((Rva007E8810Message *)message)->addString("value", (const char *)value);
}

void __stdcall bfmeGoVIV(FeslMessage *message, char *code, char *game, char *platform, char *name, char *password, char *email)
{
	void *transactionName = g_bfmeVIV;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x61636374;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addString("code", code);
	((Rva007E8810Message *)message)->addString("game", game);
	((Rva007E8810Message *)message)->addString("platform", platform);
	if (name && *name)
		((Rva007E8810Message *)message)->addString("name", name);
	if (password && *password)
		((Rva007E8810Message *)message)->addString("password", password);
	if (email && *email)
		((Rva007E8810Message *)message)->addString("encryptedInfo", email);
}
