// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /O1 /arch:SSE /G7
//
// ??0Rva005CC37C@@QAE@PAXPAURva005CC3C0In@@@Z, retail 0x005cc3c0, 140 bytes. Banked partial (score 0.91) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Ctor sibling of 0x005F5C77 (same button-holder via 0x005E1680, image via
// global 0x00E06620 through rowed 0x005E16B9 and unlock via rowed 0x005E1158);
// two-base MI per dtor 0x005CC37C (Base0 with int at +4, holder at +8) with
// vtables 0x0087A630 then 0x00874E38 at +0 and 0x00874E18 at +8, int at +0x1C
// from input; states and __EH_prolog from AsciiString("button") temporary.
#include "ascii_string.h"

class Image;

#include "../../Include/Common/Rva005E1158.h"

#include "../../Include/Common/Rva005E16B9.h"

// First base as in the sibling ctor 0x005F5C77: vptr 0x00C7A630 over the
// zeroed +4 word, unwound through the rowed 0x004E84A4.
#include "../../Include/Common/Rva0007DF07.h"
#include "../../Include/Common/Rva00567960BaseMid.h"

class Rva005E12D1 : public Rva005E1158
{
public:
	Rva005E12D1(void *a1, const AsciiString &a2, void *a3);
	virtual ~Rva005E12D1();
private:
	void *m_0C;
	int m_10;
};

struct Rva005CC3C0In
{
	void *m_00;
	int m_04;
};

extern unsigned int g_Va00E06620[5];
extern const void *const g_00C7A630[];
extern const void *const g_00C74E38[];
extern const void *const g_00C74E18[];

class Rva005CC37C : public Rva00567960BaseMid, public Rva005E12D1
{
public:
	Rva005CC37C(void *a1, Rva005CC3C0In *a2);
	virtual ~Rva005CC37C();
	virtual void rva005CC30B();
private:
	int m_1C;
};

Rva005CC37C::Rva005CC37C(void *a1, Rva005CC3C0In *a2)
	: Rva00567960BaseMid()
	, Rva005E12D1(a1, AsciiString("button"), a2->m_00)
{
	m_1C = a2->m_04;
	const Image *img = ((Rva005E16B9 *)&g_Va00E06620)->GetImage();
	((Rva005E1158 *)this)->rva005E1158(img);
}
