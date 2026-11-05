// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Split from PlayerCanBuild.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Player::allowedToBuild @0x002ABE24 (98B) and Player::canBuild @0x002ABEF1
// (175B), with the STLport find over the Player's template-ID list that
// allowedToBuild calls (find 0x002ABB9E, __find 0x002AAD52).
//
// Target evidence: canBuild's only callee before the BSTATUS checks is
// 0x002ABE24 (this, template), then ThingTemplate::getBuildable 0x0033A632
// three times against 2 / 1 / 3 (+ m_playerType +0x5C against 1), then the
// ProductionPrerequisite::isSatisfied(this) 0x004F4CE5 loop over the 0x24-byte
// prerequisite vector at template +0x324 -- the Zero Hour Player::canBuild
// sequence without its canBuildMoreOfType tail (BFME 1's Player_canBuild.cpp
// drops it too). allowedToBuild tests template kindof byte +0x108 bit 0x80
// (KINDOF_STRUCTURE) against bytes +0x339 then +0x338, Zero Hour's
// m_canBuildBase / m_canBuildUnits order, and then refuses any template whose
// 16-bit ID (+0x5D8) is on the STLport list<short> at Player +0x700 -- the list
// rowed list<short>::remove 0x002ABAE4 and push_back 0x002AC00C maintain
// (0x002ABFA0 removes the same +0x5D8 key from it). BFME 1 walks the same
// list (+0x64C there) inline in canBuild; BFME 2 moved the walk into
// allowedToBuild as a std::find. Field names other than the Zero Hour ones
// keep their offsets.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <vector>

typedef bool Bool;
typedef int Int;

enum BuildableStatus
{
	BSTATUS_YES,
	BSTATUS_IGNORE_PREREQUISITES,
	BSTATUS_NO,
	BSTATUS_ONLY_BY_AI
};

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

class Player;

class ProductionPrerequisite
{
public:
	Bool isSatisfied(const Player *player) const;
private:
	char m_unmodelled[0x24];
};

// Preserve inline size arithmetic without a second out-of-line copy.
// ThingFactory.cpp owns the verified vector size at 00626DF0.
namespace _STL {
template<> __declspec(dllimport) __forceinline
vector<ProductionPrerequisite>::size_type vector<ProductionPrerequisite>::size() const
{ return size_type(this->_M_finish - this->_M_start); }
}

// ThingTemplate::getBuildable is out of line in BFME 2 (0x0033A632).
#include "../../../Include/Common/ThingTemplate.h"
// KINDOF_STRUCTURE: kindof bit 7.
static inline Bool thingTemplateIsKindOfStructure(const ThingTemplate *tmpl) { return (((const unsigned char *)tmpl->m_kindof)[0] & 0x80) != 0; }
static inline const _STL::vector<ProductionPrerequisite> &thingTemplatePrereqs(const ThingTemplate *tmpl) { return *(const _STL::vector<ProductionPrerequisite> *)tmpl->m_prereqInfo; }
static inline Int thingTemplatePrereqCount(const ThingTemplate *tmpl) { return thingTemplatePrereqs(tmpl).size(); }
static inline const ProductionPrerequisite *thingTemplateNthPrereq(const ThingTemplate *tmpl, Int i) { return &thingTemplatePrereqs(tmpl)[i]; }
static inline short thingTemplateTemplateID(const ThingTemplate *tmpl) { return *(const short *)&tmpl->m5D8; }

typedef _STL::list<short> PlayerTemplateIDList;

#include "../../../Include/Common/Player.h"


Bool Player::canBuild(const ThingTemplate *thingTemplate) const
{
	if (!thingTemplate)
		return false;

	if (!allowedToBuild(thingTemplate))
		return false;

	if (thingTemplate->getBuildable() == BSTATUS_NO)
		return false;

	if (thingTemplate->getBuildable() == BSTATUS_IGNORE_PREREQUISITES)
		return true;

	if (thingTemplate->getBuildable() == BSTATUS_ONLY_BY_AI && getPlayerType() != PLAYER_COMPUTER)
		return false;

	// we must satisfy all of the prereqs
	Bool prereqsOK = true;
	for (Int i = 0; i < thingTemplatePrereqCount(thingTemplate); i++)
	{
		const ProductionPrerequisite *pre = thingTemplateNthPrereq(thingTemplate, i);
		if (pre->isSatisfied(this) == false)
			prereqsOK = false;
	}

	if (!prereqsOK)
		return false;

	return true;
}
