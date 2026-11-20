// Open-BFME5 conversions.

#include "../../Include/Common/Rva00801570.h"
class BfmeSubAVHW
{
public:
	char m_bfmePad[8];
};

#include "../../Include/GameNetwork/Rva008003C0Owner.h"
class BfmeSubBVHW
{
public:
	char m_bfmePad[12];
};

extern "C" int __identifier("??_7Rva00801FB0Elem@@6B@")[];
// 0xCE3B38, the vtable already emitted as ??_7Rva0066D950@@6B@ (data ledger).
extern "C" int __identifier("??_7Rva0066D950@@6B@")[];

class BfmeThingVHW
{
public:
	void bfmeClearVHW();
	void *m_bfmeVfptr;
	int m_bfme04;
	char m_bfmePad08[8];
	BfmeSubBVHW m_bfme10;
	BfmeSubBVHW m_bfme1c;
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	BfmeSubAVHW m_bfme3c;
	int m_bfme44;
	int m_bfme48;
	int m_bfme4c;
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	int m_bfme5c;
	int m_bfme60;
	char m_bfme64;
	char m_bfme65;
	char m_bfmePad66[2];
	int m_bfme68;
	int m_bfme6c;
	int m_bfme70;
	int m_bfme74;
	int m_bfme78;
};

void BfmeThingVHW::bfmeClearVHW()
{
	m_bfmeVfptr = __identifier("??_7Rva00801FB0Elem@@6B@");
	m_bfme04 = 0;
	m_bfme28 = 0;
	m_bfme2c = 0;
	m_bfme30 = 0;
	m_bfme34 = 0;
	m_bfme38 = 0;
	m_bfme44 = 0;
	m_bfme4c = -1;
	m_bfme50 = 0;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5c = 0;
	m_bfme64 = 0;
	m_bfme65 = 0;
	m_bfme68 = 0;
	m_bfme70 = 0;
	m_bfme74 = 0;
	m_bfme6c = 0;
	m_bfme78 = 0;
	((Rva00801570 *)&m_bfme3c)->clear();
	((Rva008003C0Owner *)&m_bfme1c)->clear();
	((Rva008003C0Owner *)&m_bfme10)->clear();
	m_bfmeVfptr = __identifier("??_7Rva0066D950@@6B@");
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00801FB0Elem@@QAE@XZ=?bfmeClearVHW@BfmeThingVHW@@QAEXXZ")

