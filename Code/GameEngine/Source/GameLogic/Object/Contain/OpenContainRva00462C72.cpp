// cl: /DNDEBUG /MD
//
// ?rva00462C72@OpenContain@@UAEXXZ, retail 0x00462C72, 97 bytes.
// Virtual slot 17 (offset 0x44) shared by OpenContain/CaveContain/HealContain
// and 13 other Contain vtables (packet lists 16 vtables, e.g. 0x008435E8,
// 0x00843CB8, 0x00844278). Compares the 0x4C-byte store at +0x84 against the
// Drawable+0x258 payload, forwards to slot 18 (offset 0x48) on difference,
// then copies. Evidence: vtable slot 17, rowed callees Thing::getDrawable
// 0x005508E2, memset import 0x006291AE, Rva00045473Equal 0x00045473 (0x4C
// memcmp predicate). Layout: +8 Thing*, +0x84 0x4C store (OpenContainCtor
// precedent). Honest address name: class plus slot proven, method identity not.

extern "C" void *__cdecl memset(void *dst, int c, unsigned int count);
bool Rva00045473Equal(const void *a, const void *b);

class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
};

struct Store84
{
	unsigned char m_data[0x4C];
};

class Drawable
{
public:
	unsigned char m_pad[0x258];
	Store84 m_store;
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

class OpenContain
{
public:
	SLOT16(s0)
	virtual void s16();
	virtual void rva00462C72();
	virtual void s18();
	const void *m_moduleData;
	Thing *m_thing;
	unsigned char m_padC[0x84 - 0xC];
	Store84 m_store84;
};

void OpenContain::rva00462C72()
{
	Store84 tmp;
	Drawable *d = m_thing->getDrawable();
	memset(&tmp, 0, 0x4C);
	if (!d)
		return;
	tmp = d->m_store;
	if (Rva00045473Equal(&tmp, &m_store84))
		return;
	s18();
	m_store84 = tmp;
}
