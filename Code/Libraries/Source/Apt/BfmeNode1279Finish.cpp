// cl: /MD /EHsc
// ?bfmeFinish1279@BfmeNode1279@@QAEXXZ @0x006E2B40 193B. BfmeNode teardown after unlink.
//
// Evidence: LINK BONUS caller names it bfmeFinish1279; callers 0x006F7287 0x006F8133;
// teardown sequence matches AptCIH cluster (bfmeDrop 0x006D2580, singleton 0xE176D0+0x6C
// slot1 Release then clear, AptCIH::ClearCIH flag 0xE18348, queue 0xE176D0+0xA0
// AptActionQueueC::RemoveActionFor, AptAnimationPoolData::removeFromBIL, refCount>1 assert
// pNext/pPrev AptCIH.cpp:0xB6 via shared assert triple, bfmeUnlinkNestedBE,
// setIsDefined(false) gated on 0xC0000, tail Release slot1).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptCIH;
class EAStringC;
class AptValue
{
public:
    unsigned int getRefCount() const;
    void setGCMark(bool mark);
    AptCIH *c_cih(bool = false);
    AptValue *findChild(const EAStringC *, AptValue *);
    void setIsDefined(bool value);
    virtual void AddRef();
    virtual void Release();
};

class EAStringC;
class AptRenderingContext;
struct AptNativeHash;
class AptCIH {
private:
	virtual void unused0();
private:
	virtual void unused1();
private:
	virtual void unused2();
private:
	virtual AptNativeHash *GetNativeHashVirtual();
private:
	virtual void unused4();
private:
	virtual void unused5();
private:
	virtual void unused6();
public:
	virtual AptValue *rva006E0520(AptValue *, const EAStringC *);
public:
	void SetEventHandler(int mask);
	void DestroyGCPointers();
	void rva006dbd80();
public:
	void RemoveEventHandler(int mask);
public:
	virtual bool rva006E0560(AptValue *, const EAStringC *, AptValue *);
public:
	int rva006E1F90(int v);
public:
	int rva006E24D0();
public:
	void ClearCIH(int arg);
	// Existing rectangle workers, also used by the rowed bounds builder.
	void rva006E1DD0(void *pRect);
	void rva006E1C40(AptRenderingContext *context, int arg);
public:
	int rva006E0B80(int nLvl) const;
	int rva006E0B60() const;
	bool rva006E2460(const AptCIH *other) const;
	void *rva006E0FB0() const;
	void *rva006E1020() const;
	void *rva006E1100() const;
	void *rva006E1170() const;
	void *rva006E1090() const;
	void rva006E1F00(int mask);
	const AptCIH *rva006E0CB0() const;
	bool rva006E0C50(const AptCIH *other) const;
	bool rva006E0BF0() const;
	void rva006E11B0();
	bool rva006CFCD0() const;
	bool rva006E24E0() const;
private:
	// Partial operand view shared with the matched level-accessor donor.
	unsigned char _pad[0x40];
	void *m_44;
	AptCIH *m_parent; // +0x48
	void *m_4C;
	unsigned char _pad3[8];
	int m_code; // +0x58
};

class AptActionQueueC
{
public:
	void RemoveActionFor(AptValue *pArg);
};

struct AptMatrix;
class AptAnimationPoolData
{
public:
	void rva006F7720Sub(void *ctx, int arg); // 0x006F7720
	void appendButtonToBIL(class AptCIH *cih, struct AptMatrix *matrix); // 0x006E35E0
	void removeFromBIL(AptCIH *);
	void removeTimerFunctions(AptCIH *);
};

class BfmeObj4310;
class BfmeTracker4310
{
public:
	void bfmeDrop(BfmeObj4310 *obj);
};
extern class AptLinker *g_bfmeAptLinkerAtE176F8;	// retail RVA 0x00A176F8 (.data, 4 bytes), defined here: nothing else owns it
unsigned char g_00E18348;	// retail RVA 0x00A18348 (.data, 4 bytes), defined here: nothing else owns it

class BfmeNestedBE;
BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE *node);

class BfmeNode1279 : public AptValue
{
public:
	void bfmeFinish1279();
private:
	char _pad04[0x50 - 0x4];
	void *m_50;
	void *m_54;
	char _pad58[0x5C - 0x58];
	int m_5C;
};

class BfmeNode1279;
class AptActionQueueC;
class Rva006E0DE0 {public:int rva006E0DE0(AptValue *);char data[8];};
class Rva006E34D0
{
public:
	AptCIH **array; // +0x00
	int count; // +0x04
	Rva006E0DE0 s8; // +0x08
	char m_pad10[0x8];
	Rva006E0DE0 s18; // +0x18
	Rva006E0DE0 s20; // +0x20
	Rva006E0DE0 s28; // +0x28
	char m_pad30[0x30];
	AptValue *v60; // +0x60
	AptValue *v64; // +0x64
	char m_pad68[0x4];
	BfmeNode1279 *m_6c; // +0x6C
	char m_pad70[0x30];
	AptActionQueueC *m_queue; // +0xA0
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;

void BfmeNode1279::bfmeFinish1279()
{
	(*(BfmeTracker4310 **)&g_bfmeAptLinkerAtE176F8)->bfmeDrop((BfmeObj4310 *)this);
	if (g_bfmeAptPtrAtE176D0->m_6c == this) {
		g_bfmeAptPtrAtE176D0->m_6c->Release();
		g_bfmeAptPtrAtE176D0->m_6c = 0;
	}
	if (g_00E18348)
		((AptCIH *)this)->ClearCIH(0);
	else
		((AptCIH *)this)->ClearCIH(1);
	g_bfmeAptPtrAtE176D0->m_queue->RemoveActionFor(this);
	((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->removeFromBIL((AptCIH *)this);
	if (getRefCount() > 1) {
		if (m_54 != 0 || m_50 != 0) {
			g_bfmeAptAssertAtE17734(
				"pNext == NULL && pPrev == NULL && \"This should already be done!\"",
				"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0xB6);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		bfmeUnlinkNestedBE((BfmeNestedBE *)this);
		if ((m_5C & 0xC0000) == 0)
			setIsDefined(false);
	}
	Release();
}
