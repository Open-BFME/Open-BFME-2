// cl: /GS
// Open-BFME5 conversions.

#include <stdio.h>

#include "../../Include/GameNetwork/Rva007E8AC0.h"
class BfmeMsgVJF
{
public:
	void bfmeSetVJF(const char *k, void *v);
	void bfmeSet2VJF(const char *k, void *a, void *b);
	void bfmeSet3VJF(const char *k, int v);
	char m_bfmePad[0x1c];
	int m_category;
};

struct FeslUserId
{
	void *m_low;
	void *m_high;
};

extern void *g_bfmeVJF;
// g_bfmeVJF: matched references place it at VA 0xe0a04c (zero-filled .bss).
void * g_bfmeVJF;

void __stdcall bfmeGoVJF(BfmeMsgVJF *m, FeslUserId *arr, int n)
{
	char buf[0x10];
	void *txn = g_bfmeVJF;
	((Rva007E8AC0 *)m)->run();
	m->m_category = 0x6664626b;
	m->bfmeSetVJF("TXN", txn);
	for (int i = 0; i < n; ++i)
	{
		sprintf(buf, "users.%d", i);
		m->bfmeSet2VJF(buf, arr[i].m_low, arr[i].m_high);
	}
	m->bfmeSet3VJF("users.[]", n);
}
