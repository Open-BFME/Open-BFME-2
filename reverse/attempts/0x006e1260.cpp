// ?call@Rva006E1260@@QAEXPAX@Z
// partial score=1.0 date=2026-10-10
// ?call@Rva006E1260@@QAEXPAX@Z
// partial score=0.99 date=2026-10-09
// cl: /O2 /G6 /MD
// ?call@Rva006E1260@@QAEXPAX@Z, retail 0x006E1260, 722 bytes.
// AptCIH edit-text refresh (AptCIH.cpp): take the text instance (0x006E0F40),
// rebind its variable text from the parent (0x006EBFF0) and, unless already
// valid (+0x6C bit 0), release the previous string handle through
// pfnDeallocateString, assert "pParentAnim" (AptCIH.cpp line 0x2AB) and
// either mark an empty text (+4.0 bounds unless aligned 3) or fill the 0x70
// byte request (glyph source; bounds +0x50..+0x5C; definition +0x2C/+0x30;
// font; text; +0x68 format) and call pfnAllocateString. Right/centre
// alignment (+0x38 == 1/2) moves the x position by the width change through
// inlined factorySetProperty(0 x true); the request's bounds and layout
// outputs are stored back and +0x6C becomes 1.
// Evidence: WorldBuilder twin 0x017950F0 (AptCIH.cpp assert line 683; same
// request fields and order; calls factorySetProperty which retail inlines);
// callees rowed or pinned (0x006E0F40 0x006EBFF0 c_cih IsEmpty 0x00620090
// factoryEnsureProperties); ten retail callers in the Apt text paths.
// Retail float code is x87 (fld/fadd): this unit is built without /arch:SSE.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void (__cdecl *g_00E17774)(void *, int);
extern void *g_aptAllocateStringSlot;
extern char g_00DDC2E0;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC
{
public:
	bool IsEmpty() const;
	const char *rva00620090() const;
	void *data;
};

class AptCIH;
class AptValue
{
public:
	AptCIH *c_cih(bool = false);
};

class BfmeAptValue006DCD20
{
public:
	void *rva006E0F40() const;
};

class AptCIH
{
public:
	char pad[0xc];
	float a, b, c, d, tx, ty;
	float alphaMultiplier, redMultiplier, greenMultiplier, blueMultiplier;
	float alphaOffset, redOffset, greenOffset, blueOffset;
	float *properties;
	char pad2[4];
	void *sprite;
	char pad3[0x5c - 0x50];
	union {
		unsigned int flags;
		struct {
			unsigned int flagsLow : 16;
			unsigned int asChanged : 1;
			unsigned int flagsHigh : 15;
		};
	};
	void factoryEnsureProperties();
	// factorySetProperty(0 value true) as retail inlines it here: only the
	// x-translation case of its property switch survives.
	__forceinline void setPropertyX(float value)
	{
		factoryEnsureProperties();
		properties[0] = value;
		asChanged = 1;
		tx = value;
	}
};

struct AptTextGlyphSource { char pad[8]; const void *glyphs; };
struct AptParentAnimation { char pad[0x10]; AptTextGlyphSource **fonts; };
struct AptParentCharacter { char pad[4]; char *base; };
struct AptParentSprite { char pad[0xc]; AptParentCharacter *character; };
struct AptParentInst { char pad[0x4c]; AptParentSprite *sprite; };

struct AptTextDefinition { char pad[0x18]; int fontIndex; char pad1c[0x2c - 0x1c]; int m_2c; int m_30; };

class AptTextFormat : public EAStringC
{
public:
	char pad04[4];
	int font;
	char pad0c[4];
	int m_10, m_14, m_18, m_1c;
};

struct AptAllocateStringParams
{
	const void *glyphs;
	float x0, y0, x1, y1;
	int m_3c;
	int align;
	int outLines;
	int outHeight;
	int def2c;
	int def30;
	int font;
	int m_30;
	int m_34;
	int bit2;
	int bit1;
	int outWidth;
	int outScroll;
	int m_60;
	int m_2c;
	int unused50;
	const char *text;
	int state;
	void *handle;
	int fmt10, fmt14, fmt18, fmt1c;
};

class Rva006EBFF0 { public: void rva006EBFF0(AptValue *parent); };

class AptCharacterTextInst
{
public:
	char pad[0xc];
	AptTextDefinition *definition;
	char pad10[0x18 - 0x10];
	EAStringC text;
	char pad1c[0x20 - 0x1c];
	void *handle;
	int defaultFont;
	int lines;
	int scroll;
	int m_30, m_34;
	int align;
	int m_3c;
	char pad40[4];
	int width;
	int scrollOut;
	int height;
	float x0, y0, x1, y1;
	int m_60;
	int fontIndex;
	AptTextFormat *format;
	int state;
	char pad70[4];
	unsigned int bit0 : 1;
	unsigned int bit1 : 1;
	unsigned int bit2 : 1;
};

class Rva006E1260
{
public:
	void call(void *parentValue);
};

void Rva006E1260::call(void *parentValue)
{
	AptCharacterTextInst *inst = (AptCharacterTextInst *)((const BfmeAptValue006DCD20 *)this)->rva006E0F40();
	AptTextDefinition *def = inst->definition;
	((Rva006EBFF0 *)inst)->rva006EBFF0((AptValue *)parentValue);
	if (inst->state & 1)
		return;
	if (inst->handle != 0 && inst->handle != (void *)&g_00DDC2E0)
		g_00E17774(inst->handle, inst->state);
	AptParentAnimation *pParentAnim = (AptParentAnimation *)(((AptParentInst *)((AptValue *)parentValue)->c_cih(false))->sprite->character->base + 8);
	if (!pParentAnim) {
		g_bfmeAptAssertAtE17734("pParentAnim", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x2ab);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (inst->text.IsEmpty()) {
		inst->handle = (void *)&g_00DDC2E0;
		if (inst->align != 3) {
			inst->x1 = inst->x0 + 4.0f;
			inst->y1 = inst->y0 + 4.0f;
		}
		inst->width = 0;
		inst->scrollOut = 0;
	} else {
		AptAllocateStringParams params;
		params.def2c = def->m_2c;
		params.def30 = def->m_30;
		params.m_3c = inst->m_3c;
		params.align = inst->align;
		params.m_60 = inst->m_60;
		if (inst->format != 0 && inst->format->font != -1)
			params.font = inst->format->font;
		else
			params.font = inst->defaultFont;
		params.m_2c = inst->scroll;
		if (inst->format != 0 && !inst->format->IsEmpty())
			params.glyphs = inst->format->rva00620090();
		else if (def->fontIndex >= 0)
			params.glyphs = pParentAnim->fonts[inst->fontIndex]->glyphs;
		else
			params.glyphs = 0;
		params.text = inst->text.rva00620090();
		params.x0 = inst->x0;
		params.x1 = inst->x1;
		params.y0 = inst->y0;
		params.y1 = inst->y1;
		params.m_30 = inst->m_30;
		params.m_34 = inst->m_34;
		params.bit2 = inst->bit2;
		params.bit1 = inst->bit1;
		params.state = inst->state;
		params.handle = inst->handle;
		if (inst->format == 0) {
			params.fmt10 = 0;
			params.fmt14 = -1;
			params.fmt18 = -1;
			params.fmt1c = -1;
		} else {
			params.fmt10 = inst->format->m_10;
			params.fmt14 = inst->format->m_14;
			params.fmt18 = inst->format->m_18;
			params.fmt1c = inst->format->m_1c;
		}
		inst->handle = ((void *(__cdecl *)(AptAllocateStringParams *))g_aptAllocateStringSlot)(&params);
		if (inst->align != 3) {
			float oldWidth = inst->x1 - inst->x0;
			float newWidth = params.x1 - params.x0;
			if (inst->align == 2)
				((AptCIH *)this)->setPropertyX(((AptCIH *)this)->tx - (newWidth - oldWidth) / 2.0f);
			else if (inst->align == 1)
				((AptCIH *)this)->setPropertyX(oldWidth + ((AptCIH *)this)->tx - newWidth);
		}
		inst->x0 = params.x0;
		inst->x1 = params.x1;
		inst->y0 = params.y0;
		inst->y1 = params.y1;
		inst->lines = params.outLines;
		if (inst->scroll > inst->lines)
			inst->scroll = inst->lines;
		inst->width = params.outWidth;
		inst->scrollOut = params.outScroll;
		inst->height = params.outHeight;
	}
	inst->state = 1;
}
