// cl: /O2 /MD
// Address-derived recovery of 0x006CC880 (186 bytes), the Apt shutdown tail.
// Retail asserts Apt.cpp:0x45E "bInitialized" when the init flag 0x00E17700 is
// clear, then bails unless the Apt object pointer 0x00E176D0 is non-null.
// It walks the pool: clearBIL 0x006E35A0, the unrowed clip-stack step 0x006DFFA0, a
// store-queue flush through the thiscall traversal 0x006F7720 on the pool
// sub-object at +0x30 (hence the separate ecx add the retail body emits),
// ClipStackPop 0x006CBD10, the two AptMath.h clip-stack capacity asserts read
// as unsigned16 at 0x00E18100/0x00E180FC, and finally the empty-stack assert.
// Global 0x00E180C0 is the argument handed to the traversal.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

void rva006dffa0();

void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptMath
{
public:
	struct ClipTransform_t { unsigned char unaccessed[96]; };
	static ClipTransform_t *ClipStackPop();
	static unsigned short m_nStackCapacity; // VA 0x00E180FC
	static unsigned short m_nStackCount;    // VA 0x00E18100
};

// The pool at 0x00E176D0 is AptAnimationPoolData: the matched donor notes that
// this very caller (0x006CC8B9) clears it through clearBIL 0x006E35A0. The
// traversal 0x006F7720 runs on the sub-object at +0x30 and takes the queue
// pointer 0x00E180C0; its body is unnamed, so the member is address-derived.
// The local re-load of the pool is forced because retail reloads it after
// clearBIL and ClipStackShutdown rather than keeping the value in a register.
class AptAnimationPoolData
{
public:
	void clearBIL();
	unsigned char unaccessed[0x30];
	void rva006F7720Sub(void *queue, int zero);
};

extern int g_bfmeAptInitAtE17700;
extern AptAnimationPoolData *g_bfmeAptPtrAtE176D0;
extern void *g_bfmeAptQueueAtE180C0;

void rva006cc880()
{
	if (!g_bfmeAptInitAtE17700) {
		g_bfmeAptAssertAtE17734("bInitialized", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp", 0x45E);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	if (!g_bfmeAptPtrAtE176D0)
		return;

	g_bfmeAptPtrAtE176D0->clearBIL();
	rva006dffa0();
	((AptAnimationPoolData *)((char *)g_bfmeAptPtrAtE176D0 + 0x30))->rva006F7720Sub(g_bfmeAptQueueAtE180C0, 0);
	AptMath::ClipStackPop();

	if (!(AptMath::m_nStackCount < AptMath::m_nStackCapacity)) {
		g_bfmeAptAssertAtE17734("m_nStackCount < m_nStackCapacity", "..\\..\\include\\apt\\AptStd/AptMath.h", 0x65);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	if (AptMath::m_nStackCount != 0) {
		g_bfmeAptAssertAtE17734("AptMath::ClipStackIsEmpty()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp", 0x46F);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
}