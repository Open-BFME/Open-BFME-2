// cl: /O2 /DNDEBUG /MD /EHsc
// Native [0x6E1C40,0x6E1DC7),391B, thiscall with two stack arguments (ret 8): asserts
// this is non-null ("this", AptCIH.h line 0xD8) and a character instance, then
// brackets a drawing call with pushVertexMatrix/popVertexMatrix, choosing among
// the bounding-box, transform and log paths by the value's type. Names match the
// ledger, including the sub-object's rowed bounds worker at 0x6EBDD0.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
void Rva006CC110Log(int level, const char *message, ...);
#include "AptRenderingContext.h"
class BfmeThingDXH
{
public:
	void bfmeGoDXH(void *p);
};
class BfmeThingXS
{
public:
	void bfmeApplyXS(void *p, void *q);
};
#include "AptDisplayList.h"
class Rva006EBD30
{
public:
	void bounds(AptRenderingContext *ctx, void *a, void *b);
};
#include "../../../GameEngine/Include/Common/Rva006DBB30SarDwordField.h"
class Rva006E1C40Holder
{
public:
	char pad00[0x0c];
	Rva006EBD30 *m_c;
};
#include "AptCIHClass.h"
#include "BfmeAptValue006DCD20.h"
void AptCIH::rva006E1C40(AptRenderingContext *ctx, int arg2)
{
	if (this == 0) {
		g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xd8);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (((Rva006DBB30SarDwordField *)this)->get() == 0x13) {
		if (!isUndefined())
			return;
	}
	if (!IsCharacterInst()) {
		g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xa5);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	Rva006E1C40Holder *holder = (Rva006E1C40Holder *)field4C;
	ctx->pushVertexMatrix();
	((BfmeThingDXH *)ctx)->bfmeGoDXH((char *)this + 0x0c);
	if (IsSpriteInstBase()) {
		if (!IsSpriteInstBase()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((AptDisplayList *)((char *)field4C + 0x24))->rva006F79B0(ctx, (void *)arg2);
		ctx->popVertexMatrix();
		return;
	}
	if (((Rva006DBB30SarDwordField *)this)->get() == 0x0e && !isUndefined()) {
		char *subObject = (char *)rva006E1090();
		((AptDisplayList *)(subObject + 0x1c))->rva006F79B0(ctx, (void *)arg2);
		ctx->popVertexMatrix();
		return;
	}
	if ((char)((const BfmeAptValue006DCD20 *)this)->rva006E02B0()) {
		char *subObject = (char *)((const BfmeAptValue006DCD20 *)this)->rva006E0F40();
		((BfmeThingXS *)ctx)->bfmeApplyXS((void *)arg2, subObject + 0x50);
		ctx->popVertexMatrix();
		return;
	}
	if ((char)((const BfmeAptValue006DCD20 *)this)->rva006E0350()) {
		Rva006CC110Log(4, " [APT] Attempting to get the bounding box or shape morphed object\n [APT] bounding box calculation on morphs is not supported...\n");
		ctx->popVertexMatrix();
		return;
	}
	holder->m_c->bounds(ctx, (void *)arg2, 0);
	ctx->popVertexMatrix();
}
