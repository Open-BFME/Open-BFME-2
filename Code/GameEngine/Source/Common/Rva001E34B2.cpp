// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva001E34B2@Rva001E34B2@@QAE?AURva001E34B2Point@@XZ, retail 0x001E34B2,
// 72 bytes (ret 4: the point comes back by value through the hidden result
// pointer). Position sibling of 0x001E34FA and 0x001E3511 (Rva001E34FA.cpp):
// reads the node at +0x00 of the 16-byte path point that Path 0x00364521
// returns; no node gives (0 0 0); else the node's +0x08 node when set, or the
// node itself, supplies the float triple at +0x0C.
// Caller: Locomotor 0x001E7389 at 0x001E74CD, which hands the returned
// temporary to the horde contain interface slot at +0x1BC.
// Retail writes the zero point with xorps/movss and copies the first float
// with fld/fstp and the other two as dwords: that is the inline
// float-triple constructor and copy constructor below, constructed straight
// into the return slot. The triple's real type is not established.
// Owner identity unproven; honest Rva names.

typedef float Real;

struct Rva001E34B2Point
{
	Real x;
	Real y;
	Real z;
	Rva001E34B2Point(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
	Rva001E34B2Point(const Rva001E34B2Point &o) { x = o.x; y = o.y; z = o.z; }
};

struct Rva001E34B2Node
{
	int m_pad00[2]; // +0x00..+0x07
	Rva001E34B2Node *m_p08; // +0x08
	Rva001E34B2Point m_pos; // +0x0C
};

class Rva001E34B2
{
public:
	Rva001E34B2Point rva001E34B2();
private:
	Rva001E34B2Node *m_p00;
};

Rva001E34B2Point Rva001E34B2::rva001E34B2()
{
	Rva001E34B2Node *p = m_p00;
	if (!p)
		return Rva001E34B2Point(0.0f, 0.0f, 0.0f);
	Rva001E34B2Node *q = p->m_p08;
	if (!q)
		return p->m_pos;
	return q->m_pos;
}
