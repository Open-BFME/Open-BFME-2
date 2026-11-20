// Byte-identical BFME1 donor extract (see reference/open-bfme-1/
// Code/GameEngine/Source/Common/BfmeConv1325.cpp). bfmeDelTWA and
// bfmeDelTWB are served here; the donor's TWC sibling lives in
// BfmeConv1325TWC.cpp, so the whole file cannot land as one TU.

extern "C" void *__identifier("??_7BfmeThingTWA@@6BDemanglerPrimary@@@")[];
extern "C" void *__identifier("??_7BfmeThingTWA@@6BRva00803080@@@")[];
// 0xCE30A8, the vtable already emitted as ??_7Rva00665030@@6B@ (data ledger).
extern "C" void *__identifier("??_7Rva00665030@@6B@")[];

class BfmeStrTWA
{
public:
	void bfmeDtorTWA();
	char m_bfmePad[0x20];
};

void bfmeFreeTWA(void *p, int n);

class BfmeE1036
{
public:
	void bfmeGo1036E();
};
class BfmeThingTWA
{
public:
	void *bfmeDelTWA(unsigned char flags);
	void *m_bfmeVft0;
	void *m_bfmeVft1;
	char m_bfmePad[8];
	BfmeStrTWA m_bfmeStr;
};

void *BfmeThingTWA::bfmeDelTWA(unsigned char flags)
{
	m_bfmeVft0 = __identifier("??_7BfmeThingTWA@@6BDemanglerPrimary@@@");
	m_bfmeVft1 = __identifier("??_7BfmeThingTWA@@6BRva00803080@@@");
	((BfmeE1036 *)this)->bfmeGo1036E();
	m_bfmeStr.bfmeDtorTWA();
	m_bfmeVft0 = __identifier("??_7Rva00665030@@6B@");
	if (flags & 1)
		bfmeFreeTWA(this, 0x30);
	return this;
}

extern "C" void *__identifier("??_7Rva007F6D60Child@@6B@")[];
extern "C" void *__identifier("??_7Rva007F6D60ChildBase@@6B@")[];

class BfmeStrTWB
{
public:
	void bfmeDtorTWB(void);
	char m_bfmePad[0x10];
};

class Rva00800290Buffer
{
public:
	void reset(void);
};
class BfmeListTWB
{
public:
	char m_bfmePad[0x10];
};


class BfmeThingTWB
{
public:
	void *bfmeDelTWB(unsigned char flags);
	void *m_bfmeVft;
	char m_bfmePad[4];
	int m_bfme08;
	char m_bfmePad2[0x10];
	BfmeListTWB m_bfmeList;
	BfmeStrTWB m_bfmeB;
	BfmeStrTWB m_bfmeA;
};

// ?bfmeDelTWB@BfmeThingTWB@@QAEPAXE@Z
void *BfmeThingTWB::bfmeDelTWB(unsigned char flags)
{
	m_bfmeVft = __identifier("??_7Rva007F6D60Child@@6B@");
	m_bfme08 = 0;
	m_bfmeA.bfmeDtorTWB();
	m_bfmeB.bfmeDtorTWB();
	((Rva00800290Buffer *)&m_bfmeList)->reset();
	m_bfmeVft = __identifier("??_7Rva007F6D60ChildBase@@6B@");
	if (flags & 1)
		::operator delete(this);
	return this;
}

