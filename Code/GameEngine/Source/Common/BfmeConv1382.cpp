// Open-BFME5 conversions.

class BfmeMsgVJC
{
public:
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

#include "../../Include/GameNetwork/Rva007E8810Message.h"

class Rva007F1800Search
{
public:
	void serialize(Rva007E8810Message *message, int count, void *data);
};

extern void *g_bfmeVJC;
// g_bfmeVJC: matched references place it at VA 0xe09ff8 (zero-filled .bss).
void * g_bfmeVJC;

class BfmeThingVJC
{
public:
	void bfmeGoVJC(BfmeMsgVJC *message, int ratingMin, int ratingMax, int downloadMin, int downloadMax, void *searchCount, void *searchData);
};

void BfmeThingVJC::bfmeGoVJC(BfmeMsgVJC *message, int ratingMin, int ratingMax, int downloadMin, int downloadMax, void *searchCount, void *searchData)
{
	void *transactionName = g_bfmeVJC;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)message,
		(int)(unsigned long)searchCount, searchData);
	if (ratingMin > -1)
		((Rva007E8810Message *)message)->addInt("ratingMin", ratingMin);
	if (ratingMax > -1)
		((Rva007E8810Message *)message)->addInt("ratingMax", ratingMax);
	if (downloadMin > -1)
		((Rva007E8810Message *)message)->addInt("downloadMin", downloadMin);
	if (downloadMax > -1)
		((Rva007E8810Message *)message)->addInt("downloadMax", downloadMax);
}

extern void *g_bfmeVJD;
// g_bfmeVJD: matched references place it at VA 0xe0a034 (zero-filled .bss).
void * g_bfmeVJD;

class BfmeThingVJD
{
public:
	void bfmeGoVJD(BfmeMsgVJC *message, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *searchData);
};

void BfmeThingVJD::bfmeGoVJD(BfmeMsgVJC *message, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *searchData)
{
	void *transactionName = g_bfmeVJD;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)message,
		topN, searchData);
	if (ratingMin > -1)
		((Rva007E8810Message *)message)->addInt("ratingMin", ratingMin);
	if (ratingMax > -1)
		((Rva007E8810Message *)message)->addInt("ratingMax", ratingMax);
	if (topN > 0)
		((Rva007E8810Message *)message)->addInt("topN", topN);
	if (periodType > -1)
		((Rva007E8810Message *)message)->addInt("periodType", periodType);
	if (periodsPast > -1)
		((Rva007E8810Message *)message)->addInt("periodsPast", periodsPast);
}
