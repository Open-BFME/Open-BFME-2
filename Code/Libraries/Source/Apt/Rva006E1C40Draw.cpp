// cl: /O2 /DNDEBUG /MD /EHsc
// Native [0x6E1C40,0x6E1DC7),391B, thiscall with two stack arguments (ret 8): asserts
// this is non-null ("this", AptCIH.h line 0xD8) and a character instance, then
// brackets a drawing call with pushVertexMatrix/popVertexMatrix, choosing among
// the bounding-box, transform and log paths by the value's type. Names match the
// ledger except the unnamed sub-object call at 0x6EBDD0 (address-derived).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
void Rva006CC110Log(int level, const char *message, ...);
class AptRenderingContext
{
public:
	void pushVertexMatrix(void);
	void popVertexMatrix(void);
};
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
class AptDisplayList
{
public:
	void rva006F79B0(void *p, void *q);
};
class Rva006E1C40Sub
{
public:
	void rva006EBDD0(void *p, int a, int b);
};
class Rva006CFCD0
{
public:
	bool isSpriteInstBase(void) const;
};
class Rva006DBB30SarDwordField
{
public:
	int get(void) const;
};
class Rva006E1C40Holder
{
public:
	char pad00[0x0c];
	Rva006E1C40Sub *m_c;
};
class BfmeAptValue006DCD20
{
public:
	char pad00[0x4c];
	Rva006E1C40Holder *m_4c;
	bool isUndefined(void) const;
	int isCharacterInst(void) const;
	int rva006E02B0(void) const;
	void *rva006E0F40(void) const;
	int rva006E0350(void) const;
};
class AptCIH : public BfmeAptValue006DCD20
{
public:
	void rva006E1C40(AptRenderingContext *ctx, int arg2);
	void *rva006E1090(void) const;
};
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
	if (!(char)isCharacterInst()) {
		g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xa5);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	Rva006E1C40Holder *holder = m_4c;
	ctx->pushVertexMatrix();
	((BfmeThingDXH *)ctx)->bfmeGoDXH((char *)this + 0x0c);
	if (((Rva006CFCD0 *)this)->isSpriteInstBase()) {
		if (!((Rva006CFCD0 *)this)->isSpriteInstBase()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((AptDisplayList *)((char *)m_4c + 0x24))->rva006F79B0(ctx, (void *)arg2);
		ctx->popVertexMatrix();
		return;
	}
	if (((Rva006DBB30SarDwordField *)this)->get() == 0x0e && !isUndefined()) {
		char *p = (char *)rva006E1090();
		((AptDisplayList *)(p + 0x1c))->rva006F79B0(ctx, (void *)arg2);
		ctx->popVertexMatrix();
		return;
	}
	if ((char)rva006E02B0()) {
		char *p = (char *)rva006E0F40();
		((BfmeThingXS *)ctx)->bfmeApplyXS((void *)arg2, p + 0x50);
		ctx->popVertexMatrix();
		return;
	}
	if ((char)rva006E0350()) {
		Rva006CC110Log(4, " [APT] Attempting to get the bounding box or shape morphed object\n [APT] bounding box calculation on morphs is not supported...\n");
		ctx->popVertexMatrix();
		return;
	}
	holder->m_c->rva006EBDD0(ctx, arg2, 0);
	ctx->popVertexMatrix();
}
