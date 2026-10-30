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

class Rva007E8810Message
{
public:
	// Real FESL accessor spellings for the 0x655AA0 addString and 0x655B50
	// reset bodies (also ICF aliases of the BFME1 donor names above).
	void addString(const char *key, const char *value);
	void reset();
};

extern void *g_bfmeVIT;
// g_bfmeVIT: matched references place it at VA 0xe09f7c (zero-filled .bss).
void * g_bfmeVIT;
extern void *g_bfmeVIV;
// g_bfmeVIV: matched references place it at VA 0xe09f4c (zero-filled .bss).
void * g_bfmeVIV;
extern void *g_bfmeVIU;
// g_bfmeVIU: matched references place it at VA 0xe0a07c (zero-filled .bss).
void * g_bfmeVIU;

void __stdcall bfmeGoVIT(FeslMessage *m, void *a, void *b)
{
	void *g = g_bfmeVIT;
	((Rva007E8810Message *)m)->reset();
	m->m_bfme1c = 0x61636374;
	((Rva007E8810Message *)m)->addString("TXN", (const char *)g);
	((Rva007E8810Message *)m)->addString("password", (const char *)a);
	((Rva007E8810Message *)m)->addString("newPassword", (const char *)b);
}

void __stdcall bfmeGoVIU(FeslMessage *m, void *sessionId, void *key, void *value)
{
	void *g = g_bfmeVIU;
	((Rva007E8810Message *)m)->reset();
	m->m_bfme1c = 0x72616e6b;
	((Rva007E8810Message *)m)->addString("TXN", (const char *)g);
	((Rva007E8810Message *)m)->addString("sessionId", (const char *)sessionId);
	((Rva007E8810Message *)m)->addString("key", (const char *)key);
	((Rva007E8810Message *)m)->addString("value", (const char *)value);
}

void __stdcall bfmeGoVIV(FeslMessage *m, char *code, char *game, char *platform, char *name, char *password, char *email)
{
	void *g = g_bfmeVIV;
	((Rva007E8810Message *)m)->reset();
	m->m_bfme1c = 0x61636374;
	((Rva007E8810Message *)m)->addString("TXN", (const char *)g);
	((Rva007E8810Message *)m)->addString("code", code);
	((Rva007E8810Message *)m)->addString("game", game);
	((Rva007E8810Message *)m)->addString("platform", platform);
	if (name && *name)
		((Rva007E8810Message *)m)->addString("name", name);
	if (password && *password)
		((Rva007E8810Message *)m)->addString("password", password);
	if (email && *email)
		((Rva007E8810Message *)m)->addString("encryptedInfo", email);
}
