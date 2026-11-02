// cl: /Ireference/shims/bfme2_ascii /EHsc /O1 /MD /arch:SSE /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Split from Rva00380200Getter.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ?rva00380200@Rva00380200@@QAEPAVAsciiString@@XZ @ 0x00380200 (13B): getter returning +4 or AsciiString::TheEmptyString. Callers 0x00380230 0x00380265 push result. Twin of EmptyString fallback pattern.
// ?rva0038020D@Rva00380200@@QAEXXZ @ 0x0038020D (110B): caches at +0x20 the
// value the store (0x00DFE0EC, pinned get 0x002000D7) config for level
// m_14 + 1 reports for this name (0x7FFFFFFF when absent), and at +0x24 the
// one for level m_14 (0 when absent), through the config method 0x00200157
// (pinned from these call sites: thiscall ret 4 taking the name by reference,
// returning a dword field). Retail keeps the config in edx across the
// rva00380200 call, which cl only does when that getter was compiled earlier
// in the same TU; the TU is /O1 so the getter is called rather than inlined.
#include "ascii_string.h"
#include "Lib/BaseType.h"

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
class Thing;
class ModuleData;
class Object;
#include "../../Include/Common/BfmeXfer.h"
class Xfer::Version
{
public:
	unsigned char m_major;
	unsigned char m_minor;
	Version(unsigned char a, unsigned char b) : m_major(a), m_minor(b) {}
};


// The shared empty-string object is defined in Rva00380200Getter.cpp.
// This split unit uses the declaration in ascii_string.h.

extern class RankInfoStore *TheRankInfoStore;

// Native3805BB uses the three-pointer scalar vector at the established +8 member.
// This prefix view does not claim the complete ExperienceScalarTable layout.
class ExperienceScalarTable;
class Rva00380200
{
public:
	// Declared as the Player units (PlayerDestructor.cpp, PlayerCtorBFME2.cpp)
	// declare it, so all three emit one ??_7Rva00380200@@6B@.
	virtual ~Rva00380200() {}
	virtual bool rva0038037C(int level);
	virtual void slot2();
	virtual void resetRank();
	virtual void onRank(void *rank);
	virtual bool isReady();
private:
	AsciiString *m_ptr;
	ExperienceScalarTable *m_scalars;
	float m_0C;
	float m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
public:
	Rva00380200();
 bool rva003805BB(float delta,bool useMultipliers);
	void rva0038028B();
	AsciiString *rva00380200();
	void rva0038020D();
	void rva00380499(Xfer *xfer);
	int rva003802DF();
	int rva00380459(int points);
};




// Complete native RET4 body 0x0058AE53..0x0058AEB6. The same Xfer slots
// as matched 0x00380499 establish Version {1,2}, unsigned int +0x0C,
// floats +0x10/+0x14 and bool +0x18. Retail repeats the +0x0C transfer
// within the version-2 arm. Original receiver/member names are unknown.
// The native BFDC30 table owns setRankLevel at slot1. Keep the established
// neutral class name; WB supplies the method identity independently.

class ExperienceScalarTable;
#include "../../Include/GameLogic/ExperienceLevelStore.h"
// TheExperienceLevelStore is only an alias of the owned global TheExperienceLevelSystem (ledger names column); this unit reads the owner through its own view type.
extern class ExperienceLevelSystem *TheExperienceLevelSystem;
#define TheExperienceLevelStore (*(ExperienceLevelStore * *)&TheExperienceLevelSystem)
Rva00380200::Rva00380200()
 :m_ptr(0),m_scalars(0),m_0C(0),m_10(1),m_14(1),m_18(1),m_1C(0),m_20(0x7FFFFFFF),m_24(0),m_28(0)
{

 if(TheExperienceLevelStore) {
  AsciiString name("PlayerSkillPointsScalarTable");
  m_scalars=TheExperienceLevelStore->FindExperienceScalarTableByName(name);
 }
 rva0038028B();
}

// Native003805BB..003806D4 RET8 and WB F642C0 establish the skill-point
// accumulator. BFME1 Player_addSkillPoints supplied the semantic guide; the
// target rank/scalar fields and virtual setter come from the measured callers.
// const float from floor(total) preserves native POP/FSTP/POP scheduling;
// the explicit double cast made the same body schedule FSTP/POP/POP.
class GameLogic;
extern GameLogic *TheGameLogic;
static __forceinline const float &minimumSciencePoints(const float &cap,const float &candidate)
{
 return cap<candidate ? cap : candidate;
}

