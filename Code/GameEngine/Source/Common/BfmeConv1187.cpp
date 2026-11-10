// Open-BFME5 conversions.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// Retail RVA 0x008E3F40 (.rdata, 20 B): the five-word table the base
// constructor stores at +0. Every slot is the address of a matched retail row.
extern "C" {
void __identifier("??_GRva00672460@@UAEPAXI@Z")();
void __identifier("?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")();
void __identifier("?setValue@Rva00806400Owner@@QAEXHPAX@Z")();
void __identifier("?addSlot@FeslStateMachine@@QAEXHH@Z")();
void __identifier("?release@Rva00806400Owner@@QAEXPAX@Z")();
}
extern "C" void *g_bfmeV1187[5] =
{
	(void *)&__identifier("??_GRva00672460@@UAEPAXI@Z"),
	(void *)&__identifier("?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ"),
	(void *)&__identifier("?setValue@Rva00806400Owner@@QAEXHPAX@Z"),
	(void *)&__identifier("?addSlot@FeslStateMachine@@QAEXHH@Z"),
	(void *)&__identifier("?release@Rva00806400Owner@@QAEXPAX@Z"),
};

struct BfmePair1187
{
	BfmePair1187(void)
	{
		m_bfme00 = 0;
		m_bfme04 = 0;
	}
	int m_bfme00;
	int m_bfme04;
};

class BfmeBase1187
{
public:
	BfmeBase1187(void) { m_bfme00 = (char *)g_bfmeV1187; }
	char *volatile m_bfme00;
	volatile int m_bfme04;
};

class BfmeA1187 : public BfmeBase1187
{
public:
	BfmeA1187(void);
	BfmePair1187 m_bfme08[8];
};

BfmeA1187::BfmeA1187(void)
{
	m_bfme04 = 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeCtorECMa@BfmeThingECMa@@QAEPAV1@XZ=??0BfmeA1187@@QAE@XZ")
