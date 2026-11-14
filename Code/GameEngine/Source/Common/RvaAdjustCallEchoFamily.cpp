// flags: region default (reverse/retail_inventory/flag_regions.csv)
// cl: /EHs-c- /ICode/Libraries/Include
// Quad-strip cached bounds and center used by the river virtual-base slots.
// Native 53863E and 538674 return values through hidden output buffers; the
// actual river overrides live with their constructor in Rva0030C1FCOwnerCtor.cpp.
#include <math.h>
#include "Lib/Region2D.h"
struct BfmeE16;
#include "../../Include/Common/Rva0030B72CPoint.h"

class Rva0053863ESub
{
public:
	Region2D run();
	void rva0053856F();
	float rva00538661();

private:
	BfmeE16 *m_begin;
	BfmeE16 *m_finish;
	BfmeE16 *m_end;
	Region2D m_cached;
	float m_cachedScale;
	unsigned char m_refresh;
};

class Rva00538674Sub
{
public:
	Rva0030B72CPoint run();
private:
	char m_pad00[0x0C];
	float m_xMin, m_yMin, m_xMax, m_yMax;
	float m_pad1C;
	unsigned char m_dirty;
};

// Native 538674..5386B7 returns the midpoint of the four floats at C..18.
// Its same-object refresh call uses the existing helper at 53856F; owner and
// original source identities are unknown. The caller supplies return storage.
Rva0030B72CPoint Rva00538674Sub::run()
{
 if (m_dirty)
  reinterpret_cast<Rva0053863ESub *>(this)->rva0053856F();
 Rva0030B72CPoint result;
 result.x = (m_xMax + m_xMin) * 0.5f;
 result.y = (m_yMax + m_yMin) * 0.5f;
 return result;
}


// Target evidence: 0x00538661 is a 19B Ghidra function. It checks the byte at
// this+0x20, calls 0x0053856F with the same this when set, then returns the
// float at this+0x1C (fld, ST0 return). The same-this helper call and the
// +0x1C/+0x20 accesses match Rva0053863ESub's m_cachedScale/m_refresh layout.
// The adjustor thunk at 0x0030BCB2 does add ecx,-0x28 then jmp here, the same
// -0x28 adjustment the bounds slot at 0x0030BEE6 uses to reach this member.
// Contiguous with Rva0053863ESub::run (0x0053863E+35 = here, here+19 = next).
// ?rva00538661@Rva0053863ESub@@QAEMXZ
float Rva0053863ESub::rva00538661()
{
	if (m_refresh)
		rva0053856F();
	return m_cachedScale;
}

// Native 53863E returns the cached 16-byte bounds through its hidden result
// buffer. The canonical Region2D copy constructor is the native 4254E callee.
Region2D Rva0053863ESub::run()
{
 if (m_refresh) rva0053856F();
 return m_cached;
}

struct Rva005381DCPt { float x, y; };
struct Rva005381DCBox { float xMin, yMin, xMax, yMax; };
struct Rva0053856FSeg { Rva005381DCPt p0, p1; };

static __declspec(noinline) void rva005381DC(Rva005381DCBox &box, const Rva005381DCPt &pt)
{
	if (box.xMin > pt.x) box.xMin = pt.x;
	if (box.yMin > pt.y) box.yMin = pt.y;
	if (pt.x > box.xMax) box.xMax = pt.x;
	if (pt.y > box.yMax) box.yMax = pt.y;
}

void Rva0053863ESub::rva0053856F()
{
	const float maxVal = 3.4028234663852886e+38f;
	const float minVal = -3.4028234663852886e+38f;
	Rva0053856FSeg *end = reinterpret_cast<Rva0053856FSeg *>(m_finish);
	Rva005381DCBox *box = reinterpret_cast<Rva005381DCBox *>(&m_cached);
	reinterpret_cast<float *>(&m_cached)[1] = maxVal;
	reinterpret_cast<float *>(&m_cached)[0] = maxVal;
	Rva0053856FSeg *cur = reinterpret_cast<Rva0053856FSeg *>(m_begin);
	reinterpret_cast<float *>(&m_cached)[3] = minVal;
	reinterpret_cast<float *>(&m_cached)[2] = minVal;
	for (; cur != end; ++cur)
	{
		rva005381DC(*box, cur->p0);
		rva005381DC(*box, cur->p1);
	}
	float halfW = (reinterpret_cast<float *>(&m_cached)[2] - reinterpret_cast<float *>(&m_cached)[0]) * 0.5f;
	float halfH = (reinterpret_cast<float *>(&m_cached)[3] - reinterpret_cast<float *>(&m_cached)[1]) * 0.5f;
	m_cachedScale = sqrtf(halfW * halfW + halfH * halfH);
	m_refresh = 0;
}
