// cl: /MD
// Native6E6060..6E63C1 constructs a32-byte timer array using ctor6E3CF0
// and the existing named AptIntervalTimer destructor6E4F60. The destructor's
// embedded AptValuePtrStack at+14 agrees with count14/capacity18/elements1C.
// These callback and layout facts identify the former opaque init as a ctor;
// the complete86-byte body and ABI remain verified under its constructor name.
// Untouched fields retain opaque names. Inline int3 preserves retail's
// materialized break-flag load and common epilogue under the existing flags.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

// 0x00E176E8, the chain-block allocator singleton.
class Rva006DB160
{
public:
	void *allocBlock(int size);
};

Rva006DB160 *g_pChainBlockAllocator;

class AptIntervalTimer
{
public:
	AptIntervalTimer();

private:
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;	// not touched
	int m14;
	int m18;
	void *m1C;
};

AptIntervalTimer::AptIntervalTimer()
{
	m00 = 0;
	m04 = 0;
	m08 = 0;
	m0C = 0;
	m14 = 0;
	m18 = 6;
	m1C = 0;

	void *block = g_pChainBlockAllocator->allocBlock(0x18);
	m1C = block;

	if (block == 0) {
		g_bfmeAptAssertAtE17734("m_aElements != NULL", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x46);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
}
