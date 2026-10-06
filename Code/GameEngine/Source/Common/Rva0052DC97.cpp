// cl: /DNDEBUG /MD
// ?rva0052DC97@Rva0052DC97@@QAEHPBVRva002E6C79@@@Z, retail 0x0052DC97, 170 bytes.
// Path cost with dx/dy zero guard word+10/14 flag+14 second-point dot and 0/4/8/16.
// this+0 holds point, arg is Rva002E6C79 with m_ptr at +0 to point with x+0 y+4
// word+0x12, this byte+0xE flag. Callee Rva002E6C79 returns pointer pair but its
// row types it as int; declared here as pointer (row types wrong). Evidence:
// unlocks 4 callers; ret 4 one stack arg plus ecx thiscall; prev 0x0052DC3F.
struct Rva0052DC97Pt
{
	int x;
	int y;
	char _08[10];
	unsigned short m_12;
};

struct Rva0052DC97Ret
{
	Rva0052DC97Pt *m_0;
};

class Rva002E6C79
{
public:
	int rva002E6C79();
	void *m_ptr;
};

class Rva0052DC97
{
public:
	int rva0052DC97(const Rva002E6C79 *a);
private:
	Rva0052DC97Pt *m_0;
	char _04[10];
	unsigned char m_0E;
};

int Rva0052DC97::rva0052DC97(const Rva002E6C79 *a)
{
	if (a == 0)
		return 0;
	Rva0052DC97Pt *ap = (Rva0052DC97Pt *)a->m_ptr;
	Rva0052DC97Pt *tp = m_0;
	int arg_x = ap->x;
	int arg_y = ap->y;
	int dx1 = arg_x - tp->x;
	int dy1 = arg_y - tp->y;
	int e;
	if (dx1 != 0 && dy1 != 0)
		e = (int)ap->m_12 + 14;
	else
		e = (int)ap->m_12 + 10;
	if ((m_0E & 1) != 0)
		e += 14;
	int eb = 0;
	int rrInt = ((Rva002E6C79 *)a)->rva002E6C79();
	Rva0052DC97Ret *rr = (Rva0052DC97Ret *)rrInt;
	if (rr != 0) {
		int rx = rr->m_0->x;
		int ry = rr->m_0->y;
		int dx2 = rx - arg_x;
		int dy2 = ry - arg_y;
		if (dx2 != dx1 || dy2 != dy1) {
			int dot = dy2 * dy1 + dx2 * dx1;
			if (dot > 0)
				eb = 4;
			else if (dot == 0)
				eb = 8;
			else
				eb = 16;
		}
	}
	return e + eb;
}
