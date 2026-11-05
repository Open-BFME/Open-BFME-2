// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// StrategicHUD::StatsDisplayImpl::rva00579D96 @0x00579D96 (class named by
// WorldBuilder's SetRowText 0x00579B17, called on the same this; WB keeps
// these two setters beside it unnamed) 98B slot 5 of 0x0086ED64.
// Float setter with change detection: if arg != m_resourceMultiplier (+0x38), fetch UnicodeString via
// StrategicHUD::FormatResourceMultiplierText 0x00579995, set indexed text via rowed StatsDisplayImpl::SetRowText
// 0x00579B17 with index 4, then store arg to m_resourceMultiplier. Callees rowed, vtable slot
// evidence, neighbours Rva00579AB7Dtor and Rva00579E47Delegate share /O1.
// StrategicHUD::StatsDisplayImpl::rva00579D3D @0x00579D3D 89B slot 3 of same vtable.
// Int array setter at +0x2C with same Get/Set pattern via StrategicHUD::FormatBonusText
// 0x00579900 and index+1.
// StrategicHUD::StatsDisplayImpl::rva00579DF8 @0x00579DF8 79B slot 7: the
// power points at +0x3C, shown on row 5 via rowed Rva00579A2FGet 0x00579A2F.
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

namespace StrategicHUD
{
	UnicodeString FormatResourceMultiplierText(float value);
	UnicodeString FormatBonusText(int value);
}
namespace StrategicHUD { UnicodeString __cdecl FormatPowerPointsText(int value); }
namespace StrategicHUD { UnicodeString __cdecl FormatCommandPointsText(int used, int max); }

// The command-points pair at +0x24; retail compares it through the folded
// two-dword equality 0x0007E394 (pinned _rva0007E394CursorEqual).
struct Rva00579CD4CommandPoints
{
	int used;
	int max;
};
extern "C" bool __cdecl rva0007E394CursorEqual(const Rva00579CD4CommandPoints &a, const Rva00579CD4CommandPoints &b);

// StrategicHUD::StatsDisplayImpl, the stats display: constructor 0x00579E82,
// destructor 0x00579AB7 (deleting 0x0042D507), vtable 0x00C6ED64 whose slots
// 1/3/5/7 are the rowed setters below; the HUD's slot setter is 0x0042D7E0.
// OnStatRollOver keeps the hovered stat at +0x20 and its stat-table entry
// (0x00579770) in the +0x1C holder, pushed to the +0x18 tooltip target.
extern "C" const void *const __identifier("??_7Rva005EEF2FBase0@@6B@")[];

class Rva00579AB7Base
{
public:
	virtual ~Rva00579AB7Base();
};

inline Rva00579AB7Base::~Rva00579AB7Base()
{
	*(const void **)this = __identifier("??_7Rva005EEF2FBase0@@6B@");
}

struct Rva00579AB7Holder1C
{
	Rva00579AB7Holder1C() : m_ptr(0) {}
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva00579AB7Holder1C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

namespace StrategicHUD
{
class StatsDisplayImpl : public Rva00579AB7Base
{
public:
	StatsDisplayImpl(int level, const AsciiString &name); // 0x00579E82
	virtual ~StatsDisplayImpl(); // 0x00579AB7
	void OnStatRollOver(const char *path); // 0x00579B81
	void OnStatRollOut(const char *path); // 0x00579C00
	void SetRowText(int row, const UnicodeString &text); // 0x00579B17
	virtual void rva00579CD4(int used, int max); // slot 1
	virtual void rva00579D3D(int index, int value); // slot 3
	virtual void rva00579D96(float value); // slot 5
	virtual void rva00579DF8(int value); // slot 7

private:
	int m_04;
	AsciiString m_08;
	AptCommandMapAdder m_0C;
	int m_18;
	Rva00579AB7Holder1C m_1C;
	int m_20;
	int m_commandPoints; // +0x24
	int m_commandPointsMax; // +0x28
	int m_bonus[3]; // +0x2C
	float m_resourceMultiplier; // +0x38
	int m_powerPoints; // +0x3C
};
}

void StrategicHUD::StatsDisplayImpl::rva00579D96(float value)
{
	if (value != m_resourceMultiplier)
	{
		SetRowText(4, StrategicHUD::FormatResourceMultiplierText(value));
		m_resourceMultiplier = value;
	}
}

void StrategicHUD::StatsDisplayImpl::rva00579D3D(int index, int value)
{
	int *slot = &m_bonus[index];
	if (value != *slot)
	{
		SetRowText(index + 1, StrategicHUD::FormatBonusText(value));
		*slot = value;
	}
}

void StrategicHUD::StatsDisplayImpl::rva00579DF8(int value)
{
	if (value != m_powerPoints)
	{
		SetRowText(5, StrategicHUD::FormatPowerPointsText(value));
		m_powerPoints = value;
	}
}

// StrategicHUD::StatsDisplayImpl::rva00579CD4 @0x00579CD4 105B slot 1: the
// command-points pair (used, max) at +0x24, shown on row 0 via
// FormatCommandPointsText 0x00579868. The equal-arm read of max keeps retail's
// register home for the second argument.
void StrategicHUD::StatsDisplayImpl::rva00579CD4(int used, int max)
{
	Rva00579CD4CommandPoints *cur = (Rva00579CD4CommandPoints *)&m_commandPoints;
	if (!rva0007E394CursorEqual(*(Rva00579CD4CommandPoints *)&used, *cur))
	{
		int u = used;
		int m = (max ? max : max);
		SetRowText(0, StrategicHUD::FormatCommandPointsText(u, m));
		cur->max = m;
		cur->used = u;
	}
}
