// cl: /MD
//
// ?init@Rva006E3CF0@@QAEPAV1@XZ @0x006E3CF0 86B
// Apt-neighbourhood block-init, page of Rva006E3C80.cpp.
//
// Zero-initializes the simple members (+0x00..+0x0C and +0x14), sets the mode
// dword at +0x18 to 6, then allocates a 0x18-byte block from the chain-block
// allocator at VA 0x00E176E8 through the rowed Rva006DB160::allocBlock
// (0x006DB160).  A null block raises the shared Apt assert triple
// (0x00E17734 call target, 0x00DDC01C break flag, int3), exactly the shape
// Rva006E3C80.cpp uses, and stores the allocated block at +0x1C.
//
// The two assert literals pin the class far better than the address does:
// retail pushes 0x00CEBC8C = "m_aElements != NULL" and 0x00CEAE80 =
// "c:\projects\bfme2patch103\bfme2\code\libraries\source\apt\_AptValuePtrStack.h"
// (read at VA-0x400000 in game.dat), so this is an _AptValuePtrStack ctor
// allocating its element array, not a generic block init.  The ledger symbol
// stays address-named because the class identity is not independently proven.
//
// Flags: /O2 with a `__asm int 3` breakpoint, NOT the __debugbreak intrinsic.
// Retail materializes the break-flag load into eax and keeps ONE shared
// epilogue (`cmp eax,edi / je +1 / int3 / pop edi / mov eax,esi / pop esi / ret`),
// which requires the flag value to survive the materialization AND the return
// value to stay out of the pre-branch position.  This VC7 cannot express that
// with the intrinsic: under /O2 the intrinsic splits the epilogue into two
// copies (`mov eax,esi` hoisted above the `je`, 91 bytes) while /O1 keeps one
// epilogue but folds the load into `cmp [flag],edi` (85 bytes, every later
// displacement shifted by one).  `__asm int 3` is an opaque barrier, so under
// /O2 the load stays materialized and the return value is not hoisted, giving
// retail's exact 86 bytes.  Same trade-off, same precedent as
// EAStringCRefCount.cpp (0x006D2F40) and SetSize (0x006D3BC0).
//
// The global addresses are absolute DIR32 operands the gate masks; the class
// and its identity are address-named.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

// 0x00E176E8, the chain-block allocator singleton.
class Rva006DB160
{
public:
	void *allocBlock(int size);
};

Rva006DB160 *g_pChainBlockAllocator;

class Rva006E3CF0
{
public:
	Rva006E3CF0 *init();

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

Rva006E3CF0 *Rva006E3CF0::init()
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
	return this;
}
