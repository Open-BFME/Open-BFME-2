// cl: /MD /EHsc
// ?ParseRowNum@StrategicHUD@@YA_NPBDPAH@Z @0x00579676 (32B): atoi range check 0<=v<6
// (unlock lane, missing callee of 0x00579B81/0x00579C00 delegate methods).
// Parses int via IAT atoi, rejects <0 or >=6, stores to *out and returns true.
// Evidence: callers at 0x00579B95 and 0x00579C0D (push value then address,
// caller cleans via pop ecx pop ecx, so __cdecl); IAT FF15 atoi needs
// dllimport; pop ecx cleanup and xor-al false indicate /O1. Free-function
// honest Rva name with Parse verb.
#include <stdlib.h>

// WorldBuilder StrategicHUD::ParseRowNum, WB VA 0x014C10A0 (callgraph lead, score 1.0).
namespace StrategicHUD {
bool __cdecl ParseRowNum(const char *s, int *out)
{
    int v = atoi(s);
    if (v < 0 || v >= 6)
        return false;
    *out = v;
    return true;
}
}

// ?OnStatRollOver@StatsDisplayImpl@StrategicHUD@@QAEXPBD@Z, retail 0x00579B81
// (127 bytes): the stat-roll-over callback of the 0x00E0631C StatsDisplay
// instance. Identity (target): the callback registration, the vtable and the
// rowed hint getter 0x00579770. The parsed stat is rejected unless the leaf
// was in range; an existing hint is released through the counted
// TreeHintRef00217D4C temporary and the tooltip's slot1 is notified. The
// helper is defined above so the call is a visible same-TU call (retail's EH
// state/`release` schedule), matching 127/127 bytes.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

class Rva00579731
{
public:
	TreeHintRef00217D4C rva00579770(int);
};

extern unsigned g_Va00E0631C;	// the StatsDisplay instance at 0x00E0631C
// Defined here: nothing else in the tree did. Retail's 56-byte zero-filled
// .bss object (RVA 0x00A0631C), constructed in place by the 0x007AC6DD
// initializer; its referencing units spell it as this scalar.
unsigned g_Va00E0631C;

class Rva003FE20FBase
{
public:
	__declspec(noinline) void slot0(void *) {}
	virtual void slot1(void *);
};

class AsciiString;

namespace StrategicHUD
{
class StatsDisplayImpl
{
public:
	StatsDisplayImpl(int level, const AsciiString &name);
	virtual ~StatsDisplayImpl();
	void OnStatRollOver(const char *);

private:
	char prefix[0x14];
	Rva003FE20FBase *tooltip;
	TreeHintRef00217D4C hint;
	int current;
	unsigned char m_pad[0x40 - 0x24];
};
}

void StrategicHUD::StatsDisplayImpl::OnStatRollOver(const char *param)
{
	int stat;
	{
		int parsed;
		if (!StrategicHUD::ParseRowNum(param, &parsed))
			return;
		stat = parsed;
	}
	if (stat != current)
	{
		hint = ((Rva00579731 *)&g_Va00E0631C)->rva00579770(stat);
		current = stat;
		if (tooltip != 0 && hint.m_ptr != 0)
			tooltip->Rva003FE20FBase::slot1(&hint);
	}
}
