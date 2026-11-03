// Open-BFME5 conversions.

class BfmeMsgVIR
{
public:
	void bfmeRunVIR();
	void bfmeSetVIR(const char *a, void *b);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

struct BfmeOwnerVIR;

extern void *g_bfmeVIR;
// g_bfmeVIR: matched references place it at VA 0xe0a088 (zero-filled .bss).
void * g_bfmeVIR;

class BfmeThingVIR
{
public:
	void bfmeGoVIR(BfmeMsgVIR *message, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c);
	void bfmeSendVIR(BfmeMsgVIR *m, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c);
};

void BfmeThingVIR::bfmeGoVIR(BfmeMsgVIR *message, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c)
{
	void *transactionName = g_bfmeVIR;
	message->bfmeRunVIR();
	message->m_bfme1c = 0x72616e6b;
	message->bfmeSetVIR("TXN", transactionName);
	bfmeSendVIR(message, o, n, a, b, c);
}

extern void *g_bfmeVIS;
// g_bfmeVIS: matched references place it at VA 0xe0a0dc (zero-filled .bss).
void * g_bfmeVIS;

class BfmeThingVIS
{
public:
	void bfmeGoVIS(BfmeMsgVIR *message, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c);
	void bfmeSendVIS(BfmeMsgVIR *m, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c);
};

void BfmeThingVIS::bfmeGoVIS(BfmeMsgVIR *message, const BfmeOwnerVIR *o, const char *const *n, int a, int b, int c)
{
	void *transactionName = g_bfmeVIS;
	message->bfmeRunVIR();
	message->m_bfme1c = 0x72616e6b;
	message->bfmeSetVIR("TXN", transactionName);
	bfmeSendVIS(message, o, n, a, b, c);
}
