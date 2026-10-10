// cl: /O1 /Ob1 /Oy- /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
// Native constructor2A8D49..2A8E64 builds the manager's2296B data member.
// The two floats at840/844 form an observed initialization subobject: grouping
// them reproduces the native LEA840 and relative store+4 before allocator setup.
// This does not assert an original source type/name. Values are decoded from
// retail and independently checked as float literals. CombatChainEntry and
// DifficultyTuning names/array sizes are established by adjacent INI parsers.
// ??0Rva002A8D49@@QAE@XZ @ 0x002A8D49 (283B). Inner member at +0x10 of the
// outer ctor at 0x002A9725 (which passes ECX=outer+0x10 and then builds a
// map at +0x908). Owns CombatChainEntry[16] at +0x0 (rowed ctor 0x2A88C7 via
// ??_H size 0x84 count 0x10), floats/bools at +0x840-0x850, vector<BfmeE16>
// at +0x854 (rowed Vector_base 0x211E58), six float defaults at +0x860-0x874
// and Rva002A8823Tuning[4] at +0x878 (pinned ctor 0x2A8823 via ??_H size
// 0x20 count 4, then difficulty=i loop). Evidence: caller 0x002A9725,
// parsers using +0x878 (0x2A89D2) and CombatChainEntry layout (0x2A88C7).
#include <vector>








struct CombatChainEntry
{
	CombatChainEntry();
	int unit;
	int targetTypes[16];
	float targetPriorityModifiers[16];
};

class Rva002A8823Tuning
{
public:
	Rva002A8823Tuning();
	int difficulty;
	int economyUpgradeProbability;
	int field8;
	int specialPowerActivationProbability;
	int field10;
	int offensiveTacticActivationProbability;
	int field18;
	int economyMaxFarms;
};

struct BfmeE16 { float x, y, z, w; };

struct SkirmishScalePair {float zero,weight; __forceinline SkirmishScalePair():zero(0.0f),weight(0.1f){} };
class Rva002A8D49
{
public:
	Rva002A8D49();
	CombatChainEntry m_combat[16];
	SkirmishScalePair m_scale;
	bool m_848;
	bool m_849;
	bool m_84a;
	bool m_84b;
	bool m_84c;
	bool m_84d;
	bool m_84e;
	bool m_84f;
	bool m_850;
	_STL::vector<BfmeE16> m_vec;
	float m_860;
	float m_864;
	float m_868;
	float m_86c;
	float m_870;
	float m_874;
	Rva002A8823Tuning m_tuning[4];
};

Rva002A8D49::Rva002A8D49()
	: m_scale()
	, m_848(false)
	, m_849(false)
	, m_84a(false)
	, m_84b(false)
	, m_84c(false)
	, m_84d(false)
	, m_84e(false)
	, m_84f(false)
	, m_850(false)
	, m_860(50.0f)
	, m_864(3.0f)
	, m_868(200.0f)
	, m_86c(120.0f)
	, m_870(240.0f)
	, m_874(300.0f)
{
	for (int i = 0; i < 4; ++i)
		m_tuning[i].difficulty = i;
}
