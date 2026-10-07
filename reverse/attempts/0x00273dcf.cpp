// ?rva00273DCF@Drawable@@QAEXXZ
// partial score=0.78 date=2026-10-07
// cl: /DNDEBUG /MD /EHsc
// ?rva00273DCF@Drawable@@QAEXXZ @0x00273DCF 421B: update a status animation
// slot and draw its current frame; identity stays address-derived.

enum ObjectStatusTypes;

struct ObjectTemplate
{
	unsigned char m_pad[0x10D];
	unsigned char m_flags10D;
};

struct DrawableTemplate
{
	unsigned char m_pad[0x108];
	unsigned char m_flags108;
};

class ObjectBody254
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual float f4();
	virtual void f5();
	virtual float f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual unsigned int f17();
};

class Object
{
public:
	virtual void f0();
	ObjectTemplate *m_template;
	bool testStatus(ObjectStatusTypes status) const;
private:
	unsigned char m_pad[0x254 - 8];
public:
	ObjectBody254 *m_body254;
};

struct Rva002D752DNode;
class Rva002D752D;

class Anim2D
{
public:
	Anim2D(struct Rva002D752DNode *tmpl, class Rva002D752D *collection);
	unsigned int getCurrentFrameWidth() const;
	unsigned int getCurrentFrameHeight() const;
	void draw(int x, int y, int width, int height);
private:
	unsigned char m_pad[0x34];
};

class Rva00270025
{
public:
	virtual ~Rva00270025();
	Anim2D *m_items[14];
	unsigned int m_vals[14];
	void rva0027006C(int slot);
};

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
private:
	unsigned char m_pad[0x354];
	Rva00270025 *m_354;
};

class GameLogic
{
public:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};

struct Rva002D752DNode;
struct Rva002D752D;

extern GameLogic *TheGameLogic;
extern int g_00DFEBB0;
extern void *g_00DFEB78;
extern Rva002D752D *g_00DFF068;
extern float g_Va007C26F0;
void *__cdecl operator new(unsigned int size) throw();

class Drawable
{
public:
	virtual void f0();
	DrawableTemplate *m_template;
private:
	unsigned char m_pad0[0xFC - 8];
	Object *m_object;
	unsigned char m_pad1[0x354 - 0x100];
	Rva00270025 *m_354;
	unsigned char m_pad2[0x460 - 0x358];
	int m_460;
	int m_464;
	int m_468;
	int m_46C;
public:
	void rva00273DCF();
};

void Drawable::rva00273DCF()
{
	Drawable *self = this;
	Object *object = self->m_object;
	if ((object->m_template->m_flags10D & 4) != 0)
		return;
	if (object->testStatus((ObjectStatusTypes)0x13))
		return;

	ObjectBody254 *body = object->m_body254;
	bool update = false;
	float first = body->f4();
	if (first != body->f6()) {
		unsigned int frame = TheGameLogic->m_frame;
		if (frame > g_00DFEBB0 && frame - body->f17() <= g_00DFEBB0)
			update = true;
	}

	unsigned int slot;
	if ((self->m_template->m_flags108 & 0x80) != 0)
		slot = 1;
	else
		slot = (*((unsigned int *)((char *)self->m_template + 0x108)) >> 8) & 2;

	if (update) {
		Rva00270025 *items = ((Rva00270BA8 *)self)->rva00270BA8();
		if (items->m_items[slot] == 0) {
			Rva002D752DNode **templates = (Rva002D752DNode **)g_00DFEB78;
			Anim2D *anim = new Anim2D(templates[slot], g_00DFF068);
			items = ((Rva00270BA8 *)self)->rva00270BA8();
			items->m_items[slot] = anim;
		}
		items = ((Rva00270BA8 *)self)->rva00270BA8();
		if (items->m_items[slot] != 0) {
			int dw = self->m_468 - self->m_460;
			int width = ((Rva00270BA8 *)self)->rva00270BA8()->m_items[slot]->getCurrentFrameWidth();
			int height = ((Rva00270BA8 *)self)->rva00270BA8()->m_items[slot]->getCurrentFrameHeight();
			int x = (int)((float)dw * 0.75f + (float)self->m_460 - (float)width * g_Va007C26F0);
			int y = self->m_464 - height;
			((Rva00270BA8 *)self)->rva00270BA8()->m_items[slot]->draw(x, y, width, height);
		}
	} else if (self->m_354 != 0) {
		self->m_354->rva0027006C((int)slot);
	}
}
