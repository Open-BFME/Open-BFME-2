// cl: /MD /EHsc
// ?bfmeFinish1279@BfmeNode1279@@QAEXXZ @0x006E2B40 193B. BfmeNode teardown after unlink.
//
// Evidence: LINK BONUS caller names it bfmeFinish1279; callers 0x006F7287 0x006F8133;
// teardown sequence matches AptCIH cluster (bfmeDrop 0x006D2580, singleton 0xE176D0+0x6C
// slot1 Release then clear, AptCIH::rva006E2690 flag 0xE18348, queue 0xE176D0+0xA0
// AptActionQueueC::RemoveActionFor, AptAnimationPoolData::removeFromBIL, refCount>1 assert
// pNext/pPrev AptCIH.cpp:0xB6 via shared assert triple, bfmeUnlinkNestedBE,
// setIsDefined(false) gated on 0xC0000, tail Release slot1).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	unsigned int getRefCount() const;
	void setIsDefined(bool value);
};

class AptCIH
{
public:
	virtual void AddRef();
	virtual void Release();
	void rva006E2690(int arg);
};

class AptActionQueueC
{
public:
	void RemoveActionFor(AptValue *pArg);
};

class AptAnimationPoolData
{
public:
	void removeFromBIL(AptCIH *button);
};

class BfmeObj4310;
class BfmeTracker4310
{
public:
	void bfmeDrop(BfmeObj4310 *obj);
};
extern BfmeTracker4310 *g_00E176F8;
extern unsigned char g_00E18348;

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

class Rva006E34D0
{
public:
	char _pad[0x6C];
	BfmeNode1279 *m_6c;
	char _pad2[0xA0 - 0x6C - 4];
	AptActionQueueC *m_queue;
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;

void BfmeNode1279::bfmeFinish1279()
{
	g_00E176F8->bfmeDrop((BfmeObj4310 *)this);
	if (g_bfmeAptPtrAtE176D0->m_6c == this) {
		g_bfmeAptPtrAtE176D0->m_6c->Release();
		g_bfmeAptPtrAtE176D0->m_6c = 0;
	}
	if (g_00E18348)
		((AptCIH *)this)->rva006E2690(0);
	else
		((AptCIH *)this)->rva006E2690(1);
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
