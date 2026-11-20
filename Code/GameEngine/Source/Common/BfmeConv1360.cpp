#include "../../Include/GameNetwork/BfmeThingRF.h"
class BfmeMsgVHC
{
public:
	char bfmeGetStrVHC(void *key, char *buf, int size);
};

extern int g_bfmeKeyAVHC;
// g_bfmeKeyAVHC: matched references place it at VA 0xce2d9c (retail .rdata value 1397706833).
int g_bfmeKeyAVHC = 1397706833;
extern int g_bfmeKeyBVHC;
// g_bfmeKeyBVHC: matched references place it at VA 0xce2d94 (retail .rdata value 1313164369).
int g_bfmeKeyBVHC = 1313164369;

class BfmeThingVHC
{
public:
	BfmeThingVHC *bfmeInitVHC(BfmeMsgVHC *msg);
	void bfmeBaseVHC(BfmeMsgVHC *msg);
	int m_bfme00;
	int m_bfme04;
	void *m_bfme08;
	void *m_bfme0c;
};

// ?bfmeInitVHC@BfmeThingVHC@@QAEPAV1@PAVBfmeMsgVHC@@@Z
BfmeThingVHC *BfmeThingVHC::bfmeInitVHC(BfmeMsgVHC *msg)
{
	bfmeBaseVHC(msg);
	m_bfme08 = ((BfmeThingRF *)msg)->bfmeGoRF(&g_bfmeKeyAVHC, 0);
	m_bfme0c = ((BfmeThingRF *)msg)->bfmeGoRF(&g_bfmeKeyBVHC, 0);
	return this;
}

class BfmeThingVHD
{
public:
	BfmeThingVHD *bfmeInitVHD(BfmeMsgVHC *msg);
	void bfmeBaseVHD(BfmeMsgVHC *msg);
	int m_bfme00;
	int m_bfme04;
	void *m_bfme08;
	char m_bfme0c[0x100];
};

// ?bfmeInitVHD@BfmeThingVHD@@QAEPAV1@PAVBfmeMsgVHC@@@Z
BfmeThingVHD *BfmeThingVHD::bfmeInitVHD(BfmeMsgVHC *msg)
{
	bfmeBaseVHD(msg);
	m_bfme08 = ((BfmeThingRF *)msg)->bfmeGoRF((int *)"TYPE", 0);
	msg->bfmeGetStrVHC((int *)"REASON", m_bfme0c, 0x100);
	return this;
}
