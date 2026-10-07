// ??0Rva005CC37C@@QAE@PAXPAURva005CC3C0In@@@Z
// partial score=0.91 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /O1 /arch:SSE /G7
// ??0Rva005CC37C@@QAE@PAXPAURva005CC3C0In@@@Z @0x005CC3C0 140B
// Ctor sibling of 0x005F5C77 (same button-holder via 0x005E1680, image via
// global 0x00E06620 through rowed 0x005E16B9 and unlock via rowed 0x005E1158);
// two-base MI per dtor 0x005CC37C (Base0 with int at +4, holder at +8) with
// vtables 0x0087A630 then 0x00874E38 at +0 and 0x00874E18 at +8, int at +0x1C
// from input; states and __EH_prolog from AsciiString("button") temporary.
#include "ascii_string.h"

class Image;

class Rva005E1158
{
public:
	void rva005E1158(const Image *image);
	virtual ~Rva005E1158();
private:
	int m_04;
	void *m_ptr08;
};

class Rva005E16B9
{
	char m_pad[8];
	AsciiString m_8;
public:
	const Image *rva005E16B9();
};

struct Rva005F5C77Base0
{
	Rva005F5C77Base0() : m_04(0) {}
	virtual ~Rva005F5C77Base0();
	int m_04;
};

class Rva005CC37CHolder : public Rva005E1158
{
public:
	Rva005CC37CHolder(void *a1, const AsciiString &a2, void *a3);
	virtual ~Rva005CC37CHolder();
private:
	void *m_0C;
	int m_10;
};

struct Rva005CC3C0In
{
	void *m_00;
	int m_04;
};

struct Rva005E16DA;

extern Rva005E16DA g_00E06620;
extern const void *const g_00C7A630[];
extern const void *const g_00C74E38[];
extern const void *const g_00C74E18[];

class Rva005CC37C : public Rva005F5C77Base0, public Rva005CC37CHolder
{
public:
	Rva005CC37C(void *a1, Rva005CC3C0In *a2);
	virtual ~Rva005CC37C();
private:
	int m_1C;
};

Rva005CC37C::Rva005CC37C(void *a1, Rva005CC3C0In *a2)
	: Rva005F5C77Base0()
	, Rva005CC37CHolder(a1, AsciiString("button"), a2->m_00)
{
	m_1C = a2->m_04;
	const Image *img = ((Rva005E16B9 *)&g_00E06620)->rva005E16B9();
	((Rva005E1158 *)this)->rva005E1158(img);
}
