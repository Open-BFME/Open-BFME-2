// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RE: ?parsePrerequisiteUpgrade@@YAXPAVINI@@PAX1PBX@Z @0x0033EB1A (93B).
//
// BFME1 donor: Code/GameEngine/Source/Common/INI/ParsePrerequisiteUpgradeThunk.cpp
// (default-constructed ProductionPrerequisite + addUpgradePrereq of
// bfmeFindUpgradeByName(ini->getNextToken(0)) + push_back into the instance
// vector). BFME2 adaptations (all retail-measured): getNextToken takes a seps
// pointer (NULL here; the matched row is ?getNextToken@INI@@QAEPBDPBD@Z) and
// addUpgradePrereq is outlined as a direct vector<const UpgradeTemplate *>
// push_back call to 0x004DFCB0 (new pin; ICF-folded with the ModuleData-const,
// ObjectCreationNugget and RankInfo pointer-vector rows at the same address).
// /O1 selects the outlined __EH_prolog head (mov eax,scope + call 0x629188),
// same axis as the Science/Unit twins. Shares their replica-vector idiom and
// its ctor/dtor/push_back pins. The finder pin
// (?bfmeFindUpgradeByName@@YAPBVUpgradeTemplate@@PBD@Z @0x33970D) is
// BFME1-donor-backed and shape-proven: global-guard + AsciiString temp +
// lookup call + teardown + null path, sole caller passing a prereq token.

#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class UpgradeTemplate;
class ModuleData;

template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

#include "ascii_string.h"

class ProductionPrerequisite;

namespace _STL
{

// Bind the rowed push_backs to their workers: vector<ScienceType> at
// 0x002E01C6 and vector<ProductionPrerequisite> at 0x0033EA10. The pointer
// vector push_back is the ICF-folded row at 0x004DFCB0. Declarations only:
// the definitions live in the row owners.
template <class T, class A> class vector;
template <> class vector<int, allocator<int> >
{
private:
	int *m_start;
	int *m_finish;
	int *m_endOfStorage;
};
template <> class vector<ScienceType, allocator<ScienceType> >
{
public:
	void push_back(const ScienceType &x);
private:
	ScienceType *m_start;
	ScienceType *m_finish;
	ScienceType *m_endOfStorage;
};
template <> class vector<const UpgradeTemplate *, allocator<const UpgradeTemplate *> >
{
private:
	const UpgradeTemplate **m_start;
	const UpgradeTemplate **m_finish;
	const UpgradeTemplate **m_endOfStorage;
};
template <> class vector<const ModuleData *, allocator<const ModuleData *> >
{
public:
	void push_back(const ModuleData *const &x);
private:
	const ModuleData **m_start;
	const ModuleData **m_finish;
	const ModuleData **m_endOfStorage;
};
template <> class vector<ProductionPrerequisite, allocator<ProductionPrerequisite> >
{
public:
	void push_back(const ProductionPrerequisite &x);
private:
	ProductionPrerequisite *m_start;
	ProductionPrerequisite *m_finish;
	ProductionPrerequisite *m_endOfStorage;
};

}

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class INI
{
public:
	const char *getNextToken(const char *seps);
};

class ProductionPrerequisite
{
public:
	ProductionPrerequisite();
	~ProductionPrerequisite();

	_STL::vector<int> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<const UpgradeTemplate *> m_prereqUpgrades;
};

const UpgradeTemplate *bfmeFindUpgradeByName(const char *name);

// ?bfmeFindUpgradeByName@@YAPBVUpgradeTemplate@@PBD@Z
const UpgradeTemplate *bfmeFindUpgradeByName(const char *name)
{
	if (TheUpgradeCenter != 0)
	{
		AsciiString key(name);
		return TheUpgradeCenter->findUpgrade(key);
	}
	return 0;
}

// ?parsePrerequisiteUpgrade@@YAXPAVINI@@PAX1PBX@Z
void __cdecl parsePrerequisiteUpgrade(INI *ini, void *instance, void *, const void *)
{
	_STL::vector<ProductionPrerequisite> *prerequisites =
		static_cast<_STL::vector<ProductionPrerequisite> *>(instance);

	ProductionPrerequisite prerequisite;
	// 0x004DFCB0 is the ledger-rowed ModuleData* push_back; symbols.csv pins
	// this UpgradeTemplate* call to the same ICF-folded pointer-vector body.
	reinterpret_cast<_STL::vector<const ModuleData *> *>(
		&prerequisite.m_prereqUpgrades)->push_back(
		reinterpret_cast<const ModuleData *>(bfmeFindUpgradeByName(ini->getNextToken(0))));
	prerequisites->push_back(prerequisite);
}
