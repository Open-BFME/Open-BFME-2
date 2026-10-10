// cl: /O2 /G6 /MD /EHsc
// ?call@Rva006E15C0@@QAEXPAX0H@Z retail 0x006E15C0..0x006E1C39 (1657 bytes;
// the ghidra extent of 1636 stops before the shared epilogue) thiscall ret
// 0xC. WB twin 0x01795530 AptCIH::render (Apt/AptCIH.cpp asserts at lines
// 898..1012 = 0x382..0x3F4) supplies the flow and the assert texts; the call
// site 0x006F751D gives the three-argument shape (rendering context, unused,
// pass-through int). Skips a CIH whose property alpha at +0x44/+0x2C is
// below 0.5; a sprite resolves (once) whether its native hash defines the
// string-id 0x12 handler and then either draws the custom control through
// gAptFuncs slot 0x00E177AC (rect object, string-id 0x10 variable, optional
// 0x00E177B0 filter and the instance text) or renders its display list; a
// button records its BIL matrix and renders its list; text instances go to
// the draw-string slot 0x00E17778; static text renders each record glyph by
// glyph (0.05 advance scale); morphs render start and end shapes around the
// ratio callback 0x00E177A4; shapes render their character; anything else is
// NOT_REACHED. Retail uses x87 compares (fcomp/fucompp/fild): it needs this
// unit's own flags without /arch:SSE (the region default emits fcomi/comiss).
// The inline-asm break keeps the pRectObject and NOT_REACHED blocks from
// being tail-merged (as in the matched InputDispatch unit). Owner class and
// method name stay address-derived per the pin; field names are descriptive.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

#define APT_ASSERT(cond, text, file, line)                                     \
    if (!(cond)) {                                                             \
        g_bfmeAptAssertAtE17734(text, file, line);                             \
        if (g_bfmeAptBreakOnAssertAtDDC01C) {                                  \
            __asm int 3                                                        \
        }                                                                      \
    }
#define APT_CIH_H "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"
#define APT_CIH_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp"

class EAStringC
{
    void *mpData;
public:
    EAStringC();
    ~EAStringC();
    EAStringC &operator=(const EAStringC &);
    const char *rva00620090() const; // 0x00620090
};
EAStringC *Rva0070B4F0GetString(int id);

class AptString;
class AptNativeHash;
class AptValue
{
    unsigned int mnValueData;
public:
    virtual void AddRef();
    virtual void Release();
    AptString *c_string() const;  // 0x006DCE50
    EAStringC rva006DDF60();      // 0x006DDF60
};
class AptString : public AptValue
{
public:
    EAStringC str; // +0x08
};
struct AptNativeHash
{
    AptValue *Lookup(const EAStringC *const) const; // 0x0070B380
};

class AptRenderingContext
{
public:
    void pushVertexMatrix();    // 0x0070E4E0
    void popVertexMatrix();     // 0x0070E550
    void pushColourTransform(); // 0x0070E330
    void popColourTransform();  // 0x0070E390
};
class BfmeThingDXH
{
public:
    void bfmeGoDXH(void *matrix); // 0x0070E6C0
};
struct BfmeS1209;
class BfmeA1209
{
public:
    void bfmeOp1209(const BfmeS1209 *cxform); // 0x0070E3E0
};
struct Rva0070E440Box;
class Rva0070E440
{
public:
    void rva0070E440(Rva0070E440Box *out); // 0x0070E440
};
class Rva006EBD30
{
public:
    void render(AptRenderingContext *ctx, void *arg, void *matrix); // 0x006EBD30
};
class AptAnimationPoolData
{
public:
    void rva006F7720Sub(void *ctx, int arg);                    // 0x006F7720
    void appendButtonToBIL(class AptCIH *cih, struct AptMatrix *matrix); // 0x006E35E0
};
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;

struct AptMatrix
{
    float a, b, c, d, tx, ty;
};
extern "C" AptMatrix g_bfmeD1206;
extern "C" void (__cdecl *bfmeNotify1209Callback)(void *ctx);
extern void *g_aptDrawStringSlot;
extern void *g_aptCustomControlRenderSlot;
extern bool (__cdecl *g_00E177B0)(int);
extern char g_00DDC2E0;

class Rva006DBB30SarDwordField
{
public:
    int get() const; // 0x006DBB30
};

struct AptRenderShapeInfo
{
    char pad0[0x18];
    int m_18;
};
struct AptRenderShape
{
    char pad0[0xC];
    AptRenderShapeInfo *m_C;
};
struct AptGlyph
{
    short nIndex;
    short nAdvance;
};
struct AptTextRecord
{
    int nFont;
    char cxform[0x20];
    float x;  // +0x24
    float y;  // +0x28
    float size; // +0x2C
    int nGlyphs; // +0x30
    AptGlyph *aGlyphs; // +0x34
};
struct AptFont
{
    int eType;
    char pad4[8];
    int nGlyphs;                // +0x0C
    Rva006EBD30 **apGlyphs;     // +0x10
};
struct AptTextCharacters
{
    char pad0[0x18];
    AptFont **apCharacters; // +0x18
};
struct AptStaticText
{
    char pad0[4];
    AptTextCharacters *pMovie; // +0x04
    char pad8[0x18 - 8];
    char matrix[0x18];         // +0x18
    int nRecords;              // +0x30
    AptTextRecord *aRecords;   // +0x34
};
struct AptStaticTextInst
{
    char pad0[0xC];
    AptStaticText *pText; // +0x0C
};
struct AptMorph
{
    char pad0[8];
    Rva006EBD30 *pStart; // +0x08
    Rva006EBD30 *pEnd;   // +0x0C
};
struct AptMorphInst
{
    char pad0[0xC];
    AptMorph *pMorph; // +0x0C
    char pad10[8];
    float ratio;      // +0x18
};
struct AptEditText
{
    char pad0[0x20];
    void *pText; // +0x20
};
struct AptButtonChar
{
    char pad0[0x1C];
    AptAnimationPoolData list; // +0x1C
};

class AptCIH;
struct AptRectHolder
{
    char pad0[0x54];
    AptCIH *pRectObject; // +0x54
};
struct AptSprite
{
    char pad0[0x10];
    AptNativeHash *pHash; // +0x10
    char pad14[0x1C - 0x14];
    unsigned int nFlags : 26;
    unsigned int nRectMode : 2;
    unsigned int nFlagsHigh : 4;
    char pad20[4];
    AptRectHolder **ppRect; // +0x24
};
struct AptCIHProperties
{
    char pad0[0x2C];
    float alpha; // +0x2C
};

class AptCIH : public AptValue
{
public:
    bool IsSpriteInstBase() const; // 0x006CFCD0
    void *rva006E1100() const;     // 0x006E1100
    void *rva006E1090() const;     // 0x006E1090
    void *rva006E0FB0() const;     // 0x006E0FB0
    void *rva006E1020() const;     // 0x006E1020
    char pad8[0x44 - 8];
    AptCIHProperties *m_44; // +0x44
    char pad48[4];
    AptSprite *m_4C;        // +0x4C
};
class BfmeAptValue006DCD20
{
public:
    bool isUndefined() const;  // 0x006DC010
    bool rva006E0260() const;  // 0x006E0260 isShapeInst
    bool rva006E02B0() const;  // 0x006E02B0 isTextInst
    int rva006E0300() const;   // 0x006E0300
    int rva006E0350() const;   // 0x006E0350
    void *rva006E0F40() const; // 0x006E0F40
};

class AptActionInterpreter
{
public:
    AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int = 1, int = 1, int = 0);
};
extern AptActionInterpreter g_aptDateInterpreter;

class Rva006E15C0 : public AptCIH
{
public:
    void call(void *ctx, void *arg1, int arg2);
};

void Rva006E15C0::call(void *ctx, void *arg1, int arg2)
{
    if (m_44 && m_44->alpha < 0.5f)
        return;
    const BfmeAptValue006DCD20 *self = (const BfmeAptValue006DCD20 *)this;
    if (IsSpriteInstBase()) {
        APT_ASSERT(IsSpriteInstBase(), "isSpriteInstBase()", APT_CIH_H, 0x7D)
        AptSprite *sprite = m_4C;
        if (!sprite->nRectMode) {
            AptNativeHash *pHash = sprite->pHash;
            AptValue *pHandler = pHash ? pHash->Lookup(Rva0070B4F0GetString(0x12)) : 0;
            if (pHandler)
                sprite->nRectMode = 1;
            else
                sprite->nRectMode = 2;
        }
        if (sprite->nRectMode == 1) {
            AptNativeHash *pHash = sprite->pHash;
            AptValue *pHandler = pHash ? pHash->Lookup(Rva0070B4F0GetString(0x12)) : 0;
            AptCIH *pRectObject = (*sprite->ppRect)->pRectObject;
            APT_ASSERT(pRectObject, "pRectObject", APT_CIH_CPP, 0x382)
            if (!pRectObject)
                return;
            APT_ASSERT(((BfmeAptValue006DCD20 *)pRectObject)->rva006E0260(), "pRectObject->isShapeInst()", APT_CIH_CPP, 0x385)
            AptValue *pValue = g_aptDateInterpreter.getVariable(this, 0, Rva0070B4F0GetString(0x10), 1, 1, 0);
            pValue->AddRef();
            EAStringC text;
            if (!g_00E177B0 || g_00E177B0(((AptRenderShape *)pRectObject->rva006E1100())->m_C->m_18) == true)
                text = rva006DDF60();
            AptString *pValueString = pValue->c_string();
            AptString *pHandlerString = pHandler->c_string();
            ((void (__cdecl *)(const char *, const char *, int, const char *))g_aptCustomControlRenderSlot)(
                pHandlerString->str.rva00620090(), pValueString->str.rva00620090(),
                ((AptRenderShape *)pRectObject->rva006E1100())->m_C->m_18, text.rva00620090());
            pValue->Release();
            return;
        }
        ((AptAnimationPoolData *)&sprite->ppRect)->rva006F7720Sub(ctx, arg2);
        return;
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() == 14 && !self->isUndefined()) {
        AptMatrix matrix;
        ((Rva0070E440 *)ctx)->rva0070E440((Rva0070E440Box *)&matrix);
        ((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->appendButtonToBIL(this, &matrix);
        AptButtonChar *pButton = (AptButtonChar *)rva006E1090();
        pButton->list.rva006F7720Sub(ctx, arg2);
        return;
    }
    if (self->rva006E02B0()) {
        void *pText = ((AptEditText *)self->rva006E0F40())->pText;
        if (pText && pText != &g_00DDC2E0)
            ((void (__cdecl *)(void *, int))g_aptDrawStringSlot)(pText, arg2);
        return;
    }
    if ((char)self->rva006E0300()) {
        AptStaticTextInst *inst = (AptStaticTextInst *)rva006E0FB0();
        AptRenderingContext *context = (AptRenderingContext *)ctx;
        context->pushVertexMatrix();
        ((BfmeThingDXH *)context)->bfmeGoDXH(inst->pText->matrix);
        AptMatrix matrix = g_bfmeD1206;
        float lastX = -99999999.0f;
        float lastY = -99999999.0f;
        float advance = 0.0f;
        for (int i = 0; i < inst->pText->nRecords; ++i) {
            context->pushColourTransform();
            ((BfmeA1209 *)context)->bfmeOp1209((const BfmeS1209 *)inst->pText->aRecords[i].cxform);
            AptFont *pFont = inst->pText->pMovie->apCharacters[inst->pText->aRecords[i].nFont];
            APT_ASSERT(pFont->eType == 3, "pFont->eType == AptCharacterType_Font", APT_CIH_CPP, 0x3BD)
            APT_ASSERT(pFont->apGlyphs, "pFont->font.apGlyphs", APT_CIH_CPP, 0x3BE)
            if (lastX != inst->pText->aRecords[i].x || lastY != inst->pText->aRecords[i].y)
                advance = 0.0f;
            lastX = inst->pText->aRecords[i].x;
            lastY = inst->pText->aRecords[i].y;
            float size = inst->pText->aRecords[i].size;
            for (int j = 0; j < inst->pText->aRecords[i].nGlyphs; ++j) {
                matrix.tx = advance + lastX;
                matrix.ty = lastY;
                matrix.a = size;
                matrix.d = size;
                AptGlyph *pGlyphEntry = &inst->pText->aRecords[i].aGlyphs[j];
                APT_ASSERT(pGlyphEntry->nIndex < pFont->nGlyphs, "pGlyphEntry->nIndex < pFont->font.nGlyphs", APT_CIH_CPP, 0x3D3)
                pFont->apGlyphs[pGlyphEntry->nIndex]->render((AptRenderingContext *)ctx, (void *)arg2, &matrix);
                advance += pGlyphEntry->nAdvance * 0.05f;
            }
            context = (AptRenderingContext *)ctx;
            context->popColourTransform();
        }
        context->popVertexMatrix();
        return;
    }
    if ((char)self->rva006E0350()) {
        AptMorphInst *inst = (AptMorphInst *)rva006E1020();
        AptRenderingContext *context = (AptRenderingContext *)ctx;
        context->pushColourTransform();
        *(float *)context = 1.0f - inst->ratio;
        bfmeNotify1209Callback(context);
        inst->pMorph->pStart->render(context, (void *)arg2, 0);
        *(float *)context = inst->ratio;
        bfmeNotify1209Callback(context);
        inst->pMorph->pEnd->render(context, (void *)arg2, 0);
        context->popColourTransform();
        return;
    }
    if (self->rva006E0260()) {
        AptRenderShape *pShape = (AptRenderShape *)rva006E1100();
        ((Rva006EBD30 *)pShape->m_C)->render((AptRenderingContext *)ctx, (void *)arg2, 0);
        return;
    }
    APT_ASSERT(false, "NOT_REACHED", APT_CIH_CPP, 0x3F4)
}
