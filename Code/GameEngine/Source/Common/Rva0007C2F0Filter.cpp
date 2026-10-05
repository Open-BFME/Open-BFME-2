// cl: /O1 /Oy- /DNDEBUG /MD /arch:SSE
//
// 0x0007C2F0 (38B): Region2D pointer-filter. Forwards (p2, m_04, p1) plus
// the trailing address operand to the rowed 0x0007BF5A through the 4-push
// view (retail pushes 4 and keeps the callee-leftover eax, which the
// definition's own Copy call leaves behind), stores that leftover to
// m_04, and returns p1. Address names.

struct Region2D;

struct Region2D *rva0007BF5A_4(struct Region2D *a, struct Region2D *b, struct Region2D *c, struct Region2D *d);

class Rva0007C2F0Host
{
public:
	Region2D *rva0007C2F0(Region2D *p1, Region2D *p2);
private:
	char m_pad[4];
	Region2D *m_04; // +0x04
};

Region2D *Rva0007C2F0Host::rva0007C2F0(Region2D *p1, Region2D *p2)
{
	m_04 = rva0007BF5A_4(p2, m_04, p1, (Region2D *)((char *)&p1 + 3));
	return p1;
}
