// cl: /O1 /MD /DNDEBUG
//
// ?testKillerType@CreateCrateDie@@AAE_NPBVCrateTemplate@@PAVObject@@@Z, retail
// 0x00485536 47B: Zero Hour's CreateCrateDie::testKillerType. CreateCrateDie::
// onDie (0x004857B3) calls it with the CreateCrateDie this after the template's
// kind-of mask (+0x1C) tests non-empty; `this` is never read. The killer's
// template (Thing +0x04) keeps its kind-of mask at +0x108, and the test is the
// rowed 7-dword testSetAndClear 0x0030A146 against KINDOFMASK_NONE 0x009FEFA4.
// Kept out of CreateCrateDie.cpp because the ledger names this mask's
// testSetAndClear and KINDOFMASK_NONE BitFlags<116> but its any() (onDie)
// BitFlags<218>.
//
// Zero Hour's ThingTemplate::isKindOfMulti is TEST_KINDOFMASK_MULTI on
// m_kindof, spelled out here. Retail loads the template after pushing both
// masks, the order of a direct field read: an inline getTemplate() makes MSVC
// load it first (Zero Hour defines getTemplate out of line in Thing.cpp).

typedef bool Bool;

#include "../../../../Include/Common/BitFlagsTemplate.h"

typedef BitFlags<116> KindOfMaskType;

extern KindOfMaskType KINDOFMASK_NONE;

#define TEST_KINDOFMASK_MULTI(m, s, c) ((m).testSetAndClear((s), (c)))

#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../Common/Thing/thing.h"

#include "../object.h"

class CrateTemplate
{
public:
	unsigned char m_pad000[0x1C];
	KindOfMaskType m_killedByTypeKindof;	// +0x1C
};

class CreateCrateDie
{
private:
	Bool testKillerType(const CrateTemplate *currentCrateData, Object *killer);
};

// ?testKillerType@CreateCrateDie@@AAE_NPBVCrateTemplate@@PAVObject@@@Z
Bool CreateCrateDie::testKillerType(const CrateTemplate *currentCrateData, Object *killer)
{
	if (killer == 0)
		return false;

	// Must match the whole group of bits set in the KilledBy description (most likely One).
	if (!TEST_KINDOFMASK_MULTI(*(const KindOfMaskType *)killer->m_template->m_kindof, currentCrateData->m_killedByTypeKindof, KINDOFMASK_NONE))
		return false;

	return true;
}
