// Open-BFME5 conversions (trimmed to the placed EMC body; the other seven are
// declared-only here).

struct BfmeSubEMA;
struct BfmeThingEMA;
void bfmeGoEMA(void *a, BfmeThingEMA *b);

struct BfmeThingEMB;
void bfmeGoEMB(BfmeThingEMB *a, void *b);

class BfmeObjEMC
{
public:
	void bfmeCallEMC(void *x, void *b, void *c);
};

extern void *g_bfmeXEMC;

// ?bfmeGoEMC@@YGXPAVBfmeObjEMC@@PAX1@Z
void __stdcall bfmeGoEMC(BfmeObjEMC *o, void *b, void *c)
{
	o->bfmeCallEMC(g_bfmeXEMC, b, c);
}

class BfmeObjEME
{
public:
	bool bfmeAskEME(void *item);
	void *bfmeGetEME(void *item);
};

extern class Q1Receiver0134FAAC *TheQ1Receiver;

// ?bfmeGoEMEa@@YA_NPAX@Z, retail 0x0061F170 (24B).
bool bfmeGoEMEa(void *item)
{
	BfmeObjEME *registry = (*(BfmeObjEME **)&TheQ1Receiver);
	if (!registry)
		return false;
	return registry->bfmeAskEME(item);
}

// ?bfmeGoEMEb@@YAPAXPAX@Z, retail 0x0061F600 (24B).
void *bfmeGoEMEb(void *item)
{
	BfmeObjEME *registry = (*(BfmeObjEME **)&TheQ1Receiver);
	if (!registry)
		return 0;
	return registry->bfmeGetEME(item);
}
void __stdcall bfmeGoEMGa(void *a);
void __stdcall bfmeGoEMGb(void *a);

class BfmeThingEMH
{
public:
	void bfmeGoEMHa(void);
	void bfmeGoEMHb(void);
};
