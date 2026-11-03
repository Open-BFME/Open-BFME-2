// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?clear@Rva003ECA69Element@@QAEXXZ @0x003ECA69 (24B): zeroes the 0x44-byte
// array element (float at +0 plus 0x40 bytes at +4) via SSE float zero plus
// CRT memset through thunk 0x6291AE. Called by the 20-element array clear
// at 0x003ECB13 (loops 0x14 times calling this) and by 0x00596277. No donor
// name claimed so the name keeps the address token with an honest Rva owner.
#pragma function(memset)

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include <string.h>
#include "../../../../Include/Common/BfmeXfer.h"

class Rva003ECA69Element
{
public:
	void clear();
	void rva003ECAE0(Xfer *xfer);
	class Rva003ECA69Element *rva003ECB52(struct Rva003ECB52Arg *arg);
	class Rva003ECA69Element *rva003ECB94(struct Rva003ECB52Arg *arg);

private:
	float m_0;
	char m_rest[0x40];
};


struct Rva003ECB52Inner
{
	char m_pad[0x51c];
	float m_value;
	int m_index;
};

struct Rva003ECB52Arg
{
	void *m_vtbl;
	Rva003ECB52Inner *m_ptr;
};

void Rva003ECA69Element::clear()
{
	m_0 = 0.0f;
	memset(m_rest, 0, 0x40);
}

// ?rva003ECAE0@Rva003ECA69Element@@QAEXPAVXfer@@@Z, retail 0x003ECAE0 (43B).
// Xfers the 0x44-byte element as 17 floats through Xfer slot 0x70
// (operator==(float&)): the float at +0 then the 16 floats covering +4..+0x43.
// Evidence: caller 0x003ECBF8 loops 20 times with stride 0x44 over this exact
// element type then xfers neighbouring fields via slots 0x6c/0x60/0x70/0x78;
// the push-0x10/add/pop-ebx loop shape matches /O1 size saving. Xfer decl
// copied verbatim from PoisonedBehaviorXfer.cpp so float sits at 0x70.
void Rva003ECA69Element::rva003ECAE0(Xfer *xfer)
{
	*xfer == m_0;
	float *p = reinterpret_cast<float *>(m_rest);
	for (int i = 16; i != 0; --i, ++p)
		*xfer == *p;
}

class Rva003ECA4BElement
{
public:
	Rva003ECA4BElement();

private:
	float m_0;
	char m_rest[0x40];
};

Rva003ECA4BElement::Rva003ECA4BElement()
{
	m_0 = 0.0f;
	memset(m_rest, 0, 0x40);
}

class Rva003ECB13Array
{
public:
	void clear();

private:
	Rva003ECA69Element m_elems[20];
};

void Rva003ECB13Array::clear()
{
	Rva003ECA69Element *element = m_elems;
	for (int i = 20; i != 0; --i, ++element)
		element->clear();
}

// ?rva003ECB52@Rva003ECA69Element@@QAEPAV1@PAURva003ECB52Arg@@@Z @0x003ECB52 (66B):
// accumulates the float at +0x51c of the arg's +4 object into m_0 and into
// m_rest[idx] where idx is the int at +0x520 when the value exceeds
// 0.0f. Evidence: caller 0x003ED07A computes this as array base + idx*0x44
// with idx from player+0x54 and passes Object in edi; caller 0x005962B9 passes
// element at esi+0x54 with Object in ebx; stride 0x44 matches this element type.
Rva003ECA69Element *Rva003ECA69Element::rva003ECB52(Rva003ECB52Arg *arg)
{
	float amount = arg->m_ptr->m_value;
	if (amount > 0.0f) {
		m_0 += amount;
		int idx = arg->m_ptr->m_index;
		reinterpret_cast<float *>(m_rest)[idx] += amount;
	}
	return this;
}

// ?rva003ECB94@Rva003ECA69Element@@QAEPAV1@PAURva003ECB52Arg@@@Z @0x003ECB94 (66B):
// subtracts the float at +0x51c of the arg's +4 object from m_0 and from
// m_rest[idx] where idx is the int at +0x520 when the value exceeds
// 0.0f. Evidence: sibling of 0x003ECB52 in the same TU with identical
// shape but subss; caller 0x005961C5; stride 0x44 element type.
Rva003ECA69Element *Rva003ECA69Element::rva003ECB94(Rva003ECB52Arg *arg)
{
	float amount = arg->m_ptr->m_value;
	if (amount > 0.0f) {
		m_0 -= amount;
		int idx = arg->m_ptr->m_index;
		reinterpret_cast<float *>(m_rest)[idx] -= amount;
	}
	return this;
}
