// cl: /DNDEBUG /MD
// ?CalcCostSoFar@PathfindCell@@QAEHPBVRva002E6C79@@@Z, retail 0x0052DC97, 170 bytes.
// Path cost with dx/dy zero guard word+10/14 flag+14 second-point dot and 0/4/8/16.
// this+0 holds point, arg is Rva002E6C79 with m_ptr at +0 to point with x+0 y+4
// word+0x12, this byte+0xE flag. Callee Rva002E6C79 returns pointer pair but its
// row types it as int; declared here as pointer (row types wrong). Evidence:
// unlocks 4 callers; ret 4 one stack arg plus ecx thiscall; prev 0x0052DC3F.
// rva002E6C79 returns the parent info's +0x30 dword, the owning PathfindCell
// (MixFileInfoBuffer::field30), whose info supplies the second point.
#include "../../Include/Common/MixFileInfoBuffer.h"
#include "../../Include/GameLogic/PathfindCell.h"

class Rva002E6C79
{
public:
	int rva002E6C79();
	void *m_ptr;
};

int PathfindCell::CalcCostSoFar(const Rva002E6C79 *a)
{
	if (a == 0)
		return 0;
	MixFileInfoBuffer *ap = (MixFileInfoBuffer *)a->m_ptr;
	MixFileInfoBuffer *tp = (MixFileInfoBuffer *)m_info;
	int arg_x = ap->field00;
	int arg_y = ap->field04;
	int dx1 = arg_x - tp->field00;
	int dy1 = arg_y - tp->field04;
	int e;
	if (dx1 != 0 && dy1 != 0)
		e = (int)ap->field12 + 14;
	else
		e = (int)ap->field12 + 10;
	if (getPinched())
		e += 14;
	int eb = 0;
	int rrInt = ((Rva002E6C79 *)a)->rva002E6C79();
	PathfindCell *rr = (PathfindCell *)rrInt;
	if (rr != 0) {
		int rx = ((MixFileInfoBuffer *)rr->m_info)->field00;
		int ry = ((MixFileInfoBuffer *)rr->m_info)->field04;
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
