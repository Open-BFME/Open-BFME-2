// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
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
// Inlined in every row; imported so no non-retail out-of-line copy is emitted.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<ProductionPrerequisite,allocator<ProductionPrerequisite> >::size() const { return (unsigned int)(this->_M_finish - this->_M_start); } }


// ThingTemplate::getBuildable is out of line in BFME 2 (0x0033A632).
#include "../../../Include/Common/ThingTemplate.h"
// KINDOF_STRUCTURE: kindof bit 7.
static inline Bool thingTemplateIsKindOfStructure(const ThingTemplate *tmpl) { return (((const unsigned char *)tmpl->m_kindof)[0] & 0x80) != 0; }
static inline const _STL::vector<ProductionPrerequisite> &thingTemplatePrereqs(const ThingTemplate *tmpl) { return *(const _STL::vector<ProductionPrerequisite> *)tmpl->m_prereqInfo; }
static inline Int thingTemplatePrereqCount(const ThingTemplate *tmpl) { return thingTemplatePrereqs(tmpl).size(); }
static inline const ProductionPrerequisite *thingTemplateNthPrereq(const ThingTemplate *tmpl, Int i) { return &thingTemplatePrereqs(tmpl)[i]; }
static inline short thingTemplateTemplateID(const ThingTemplate *tmpl) { return *(const short *)&tmpl->m5D8; }

typedef _STL::list<short> PlayerTemplateIDList;

class Player
{
public:
	Bool allowedToBuild(const ThingTemplate *tmplate) const;
	Bool canBuild(const ThingTemplate *tmplate) const;
	__declspec(dllimport) __forceinline PlayerType getPlayerType() const { return m_playerType; }
private:
	char m_before_type[0x5c];
	PlayerType m_playerType;				// +0x5C
	char m_before_canBuild[0x338 - 0x60];
	Bool m_canBuildUnits;					// +0x338
	Bool m_canBuildBase;					// +0x339
	char m_before_list[0x700 - 0x33a];
	PlayerTemplateIDList m_templateIdList_700;		// +0x700
};

Bool Player::allowedToBuild(const ThingTemplate *thingTemplate) const
{
	if (!m_canBuildBase && thingTemplateIsKindOfStructure(thingTemplate)) {
		return false;
	}

	if (!m_canBuildUnits && !thingTemplateIsKindOfStructure(thingTemplate)) {
		return false;
	}

	return _STL::find(m_templateIdList_700.begin(), m_templateIdList_700.end(), thingTemplateTemplateID(thingTemplate)) == m_templateIdList_700.end();
}

