// ?rva00496CA8@Rva00496CA8@@QAEXH@Z
// partial score=0.99 date=2026-10-02
// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// ?rva00496CA8@Rva00496CA8@@QAEXH@Z, retail 0x00496CA8 155B. Unlock: outer vector
// at this+4+0x24/0x28 of SubA* (key at +0 vs arg, inner vector at +4/+8 of SubB*);
// each SubB holds AsciiString at +0 and byte at +4, forwarded as
// drawable->rva002724FD(ascii, byte, 1, 0.0f, 0.0f) via Thing+8 getDrawable.
// Evidence: callees getDrawable 0x005508E2 rva002724FD 0x002724FD, caller 0x00420DC6.
// Row for rva002724FD declares int second param but retail passes byte as unsigned char: mov cl with /G7 no-xor shape.

class AsciiString;

class Drawable
{
public:
	void rva002724FD(const AsciiString &a, unsigned char b, int c, float d, float e);
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

struct Rva00496CA8SubB
{
	char m_ascii00[4];
	unsigned char m_byte04;
};

struct Rva00496CA8SubA
{
	int m_key00;
	Rva00496CA8SubB **m_begin04;
	Rva00496CA8SubB **m_end08;
};

struct Rva00496CA8Holder04
{
	char m_pad00[0x24];
	Rva00496CA8SubA **m_begin24;
	Rva00496CA8SubA **m_end28;
};

class Rva00496CA8
{
public:
	void rva00496CA8(int key);
private:
	char m_pad00[4];
	Rva00496CA8Holder04 *m_p04;
	Thing *m_thing08;
};

void Rva00496CA8::rva00496CA8(int key)
{
	Thing *thing = m_thing08;
	if (thing == 0)
		return;
	Drawable *drawable = thing->getDrawable();
	if (drawable == 0)
		return;
	Rva00496CA8SubA ***outer = &m_p04->m_begin24;
	for (unsigned i = 0; i < (unsigned)(outer[1] - outer[0]); ++i) {
		Rva00496CA8SubA *sub = outer[0][i];
		if (sub->m_key00 != key)
			continue;
		for (unsigned j = 0; j < (unsigned)(sub->m_end08 - sub->m_begin04); ++j) {
			Rva00496CA8SubB *b = sub->m_begin04[j];
			drawable->rva002724FD(*(const AsciiString *)b, b->m_byte04, 1, 0.0f, 0.0f);
		}
	}
}
