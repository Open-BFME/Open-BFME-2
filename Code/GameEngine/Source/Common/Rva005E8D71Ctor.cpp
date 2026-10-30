// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ob2 /DNDEBUG /EHsc /MD
// ??0Rva005E8D71@@QAE@PAXPAURva005E8DCFIn@@@Z @0x005E8DCF 149B
// Button constructor of the Rva005E8D71 object whose rowed destructor is
// 0x005E8D71 (vtables C77F88/C77F68) and deleting dtor 0x005E8E64.
// Bases: Rva00567960BaseMid at +0 (C7A630 stored before the holder can
// throw, as in Rva005F5C77Ctor.cpp), the "button" image holder at +8 built by
// 0x005E1680, and the 8-byte input struct copied whole into +0x1C/+0x20
// before the final vptrs (a copy-constructed base; storing the two words
// separately schedules ECX after the +0x20 store). The image source is
// primary-vtable slot 2 (0x005E8DB5, called directly in the constructor),
// looked up through 0x005E16B9 and handed to 0x005E1158 on the holder.
#include "ascii_string.h"
#include "../../Include/Common/Rva0007DF07.h"
#include "../../Include/Common/Rva00567960BaseMid.h"

class Image;

class Rva005E1158
{
public:
	void rva005E1158(const Image *image);
	virtual ~Rva005E1158();
private:
	int m_04; // +0x04
	void *m_08; // +0x08
};

class Rva005E12D1 : public Rva005E1158
{
public:
	Rva005E12D1(void *frame, const AsciiString &name, void *owner);
	virtual ~Rva005E12D1();
private:
	void *m_0C;
	int m_10;
};

class Rva005E16B9
{
public:
	const Image *GetImage();
	char m_pad00[0x8];
private:
	AsciiString m_8; // +0x08
};

class Rva005E8DB5
{
public:
	void *rva005E8DB5();
};

struct Rva005E8DCFIn
{
	void *m_00;
	void *m_04;
};

class Rva005E8D71 : public Rva00567960BaseMid, public Rva005E12D1, public Rva005E8DCFIn
{
public:
	Rva005E8D71(void *frame, Rva005E8DCFIn *in);
	virtual ~Rva005E8D71();
};

Rva005E8D71::Rva005E8D71(void *frame, Rva005E8DCFIn *in)
	: Rva00567960BaseMid()
	, Rva005E12D1(frame, AsciiString("button"), in->m_00)
	, Rva005E8DCFIn(*in)
{
	const Image *image = ((Rva005E16B9 *)((Rva005E8DB5 *)this)->rva005E8DB5())->GetImage();
	rva005E1158(image);
}
