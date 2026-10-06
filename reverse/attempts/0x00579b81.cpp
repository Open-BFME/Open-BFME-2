// ?OnStatRollOver@StatsDisplayImpl@StrategicHUD@@QAEXPBD@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// StrategicHUD::StatsDisplayImpl::~StatsDisplayImpl @0x00579AB7 96B: virtual dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x1C plus rva005796B3 clear.
// Evidence: deleting-dtor callers 0x0042D507 0x0042D7E0 0x0042D803 plus rowed rva005796B3 0x005796B3 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ED64 0x00BFBC9C; sibling Rva005794EDDtor.
//
// The class is StrategicHUD's stats display (its slot setter 0x0042D7E0).
// Its constructor 0x00579E82 binds OnStatRollOver/OnStatRollOut
// (0x00579B81/0x00579C00) as "_level%u." + path + "_OnStatRollOver"/
// "_OnStatRollOut" delegates; OnStatRollOver keeps the hovered stat at +0x20
// and its stat-table entry (0x00579770) in the +0x1C holder, pushed to the
// +0x18 tooltip target.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0xC];
};

class Rva005796B3
{
public:
	void rva005796B3(void *newObj);
};

extern const void *const g_00BFBC9C[];

class Rva00579AB7Base
{
public:
	virtual ~Rva00579AB7Base();
};

// ??1Rva00579AB7Base@@UAE@XZ present-unmatched
inline Rva00579AB7Base::~Rva00579AB7Base()
{
	*(const void **)this = g_00BFBC9C;
}

// The +0x1C handle: the hovered stat's hint, assigned through the rowed
// 0x002174A4 and cleared through the rowed 0x002BED91.
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }

	TargetRef00217D4C *m_ptr;
};

// The stat table (global 0x00E0631C) that builds each stat's hint, and the
// +0x18 help box the hint is shown in.
class Rva00579731
{
public:
	TreeHintRef00217D4C rva00579770(int stat);
};
extern unsigned g_Va00E0631C;
#define TheStatTable ((Rva00579731 *)&g_Va00E0631C)

class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &hint);
};

class Rva002BED91
{
public:
	void clear();
};

bool __cdecl Rva00579676Parse(const char *s, int *out);

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

namespace StrategicHUD {
class StatsDisplayImpl;
}

class StrategicHUD::StatsDisplayImpl : public Rva00579AB7Base
{
public:
	virtual ~StatsDisplayImpl();
	void OnStatRollOver(const char *param);
	void OnStatRollOut(const char *param);
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	void *m_18;
	TreeHintRef00217D4C m_1C;
	int m_20;
};

StrategicHUD::StatsDisplayImpl::~StatsDisplayImpl()
{
	((Rva005796B3 *)this)->rva005796B3(0);
}

// ?OnStatRollOver@StatsDisplayImpl@StrategicHUD@@QAEXPBD@Z @0x00579B81 127B
void StrategicHUD::StatsDisplayImpl::OnStatRollOver(const char *param)
{
	int stat;
	{
		int parsed;
		if (!Rva00579676Parse(param, &parsed))
			return;
		stat = parsed;
	}
	if (stat != m_20)
	{
		m_1C = TheStatTable->rva00579770(stat);
		m_20 = stat;
		if (m_18 != 0 && m_1C.m_ptr != 0)
			((Rva001FF3A9 *)m_18)->rva001FF3A9(m_1C);
	}
}

// ?OnStatRollOut@StatsDisplayImpl@StrategicHUD@@QAEXPBD@Z @0x00579C00 82B:
// un-hovering the stat that is showing clears the tooltip when it still shows
// this entry, then drops the entry and the hovered stat.
void StrategicHUD::StatsDisplayImpl::OnStatRollOut(const char *param)
{
	int stat;
	if (Rva00579676Parse(param, &stat) && stat == m_20)
	{
		if (m_18 != 0)
		{
			TargetRef00217D4C *hint = m_1C.m_ptr;
			if (hint != 0 && ((Rva005CB265 *)m_18)->Rva005CB265::rva005CB265() == (int)hint)
				((Rva005CB260 *)m_18)->rva005CB260();
		}
		((Rva002BED91 *)&m_1C)->clear();
		m_20 = -1;
	}
}
